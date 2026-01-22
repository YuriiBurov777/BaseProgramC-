#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <string>
#include <atomic>

#pragma comment(lib, "ws2_32.lib")

class TCPServer {

public:
    TCPServer(int port = 12345) : port(port), isRunning(false), serverSocket(INVALID_SOCKET) {}

    ~TCPServer() {
        stop();
    }

    bool start() {
        // Инициализация Winsock
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Fail init Winsock" << std::endl;
            return false;
        }

        // Создание сокета
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Creation error socket: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return false;
        }

        // Настройка параметров сокета
        int opt = 1;
        if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR,
            (char*)&opt, sizeof(opt)) == SOCKET_ERROR) {
            std::cerr << "Socket configuration error: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return false;
        }

        // Привязка сокета к адресу и порту
      
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Socket binding error: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return false;
        }

        // Прослушивание входящих соединений
        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Fail listen: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return false;
        }

        std::cout << "The server is running on the port " << port << std::endl;
        isRunning = true;

        // Основной цикл сервера
        while (isRunning) {
            sockaddr_in clientAddr;
            int clientAddrSize = sizeof(clientAddr);

            std::cout << "Waiting for connections..." << std::endl;

            // Принятие входящего соединения
            SOCKET clientSocket = accept(serverSocket,
                (sockaddr*)&clientAddr,
                &clientAddrSize);

            if (clientSocket == INVALID_SOCKET) {
                if (isRunning) {
                    std::cerr << "Fail accept: " << WSAGetLastError() << std::endl;
                }
                continue;
            }

            // Вывод информации о подключившемся клиенте
            char clientIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);

            std::lock_guard<std::mutex> lock(consoleMutex);
            std::cout << "New connection: " << clientIP << ":"
                << ntohs(clientAddr.sin_port) << std::endl;

            // Создание потока для обработки клиента
            clientThreads.emplace_back([this, clientSocket]() {
                this->handleClient(clientSocket);
                });

            // Очистка завершенных потоков
            for (auto it = clientThreads.begin(); it != clientThreads.end();) {
                if (it->joinable()) {
                    it->join();
                    it = clientThreads.erase(it);
                }
                else {
                    ++it;
                }
            }
        }

        return true;
    }

    void stop() {
        if (isRunning) {
            isRunning = false;

            // Закрытие серверного сокета для прерывания accept
            if (serverSocket != INVALID_SOCKET) {
                closesocket(serverSocket);
                serverSocket = INVALID_SOCKET;
            }

            cleanup();
            std::cout << "Server stoped" << std::endl;
        }
    }

  private:
        SOCKET serverSocket;
        std::atomic<bool> isRunning;
        std::vector<std::thread> clientThreads;
        std::mutex consoleMutex;
        int port;
        sockaddr_in serverAddr;

        void handleClient(SOCKET clientSocket) {
            char buffer[1024];
            int bytesReceived;

            {
                std::lock_guard<std::mutex> lock(consoleMutex);
                std::cout << "The client is connected. Socket: " << clientSocket << std::endl;
            }

            // Получение данных от клиента
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';

                {
                    std::lock_guard<std::mutex> lock(consoleMutex);
                    std::cout << "Received from the client " << clientSocket << ": "
                        << buffer << std::endl;
                }

                // Формирование ответа
                std::string response = "The server received: ";
                response += buffer;
                response += "\nServer response: Hello!";

                // Отправка ответа клиенту
                send(clientSocket, response.c_str(), response.length(), 0);

                {
                    std::lock_guard<std::mutex> lock(consoleMutex);
                    std::cout << "Sent to the client " << clientSocket << ": "
                        << response << std::endl;
                }
            }
            else if (bytesReceived == 0) {
                std::lock_guard<std::mutex> lock(consoleMutex);
                std::cout << "The client has disconnected. Socket: " << clientSocket << std::endl;
            }
            else {
                std::lock_guard<std::mutex> lock(consoleMutex);
                std::cerr << "Error when receiving data. Code: "
                    << WSAGetLastError() << std::endl;
            }

            // Закрытие сокета клиента
            closesocket(clientSocket);
        }

        void cleanup() {
            // Закрытие всех клиентских сокетов
            for (auto& thread : clientThreads) {
                if (thread.joinable()) {
                    thread.join();
                }
            }
            clientThreads.clear();

            // Закрытие серверного сокета
            if (serverSocket != INVALID_SOCKET) {
                closesocket(serverSocket);
                serverSocket = INVALID_SOCKET;
            }

            // Очистка Winsock
            WSACleanup();
        }

};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    TCPServer server(12345);

    std::cout << "Launching a TCP server..." << std::endl;
    std::cout << "Port: 12345" << std::endl;
    std::cout << "To stop the server, press Enter..." << std::endl;

    // Запуск сервера в отдельном потоке
    std::thread serverThread([&server]() {
        if (!server.start()) {
            std::cerr << "Couldn't start the server" << std::endl;
        }
        });

    // Ожидание нажатия Enter для остановки
    std::cin.get();

    server.stop();

    if (serverThread.joinable()) {
        serverThread.join();
    }

    return 0;
}
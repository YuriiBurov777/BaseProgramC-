// TCP_Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class TCPClient {

public:
    TCPClient() : sock(INVALID_SOCKET), connected(false), result(0) {
        result = WSAStartup(MAKEWORD(2, 2), &wsData);
        if (result != 0) { std::cout << "WSAStartup failed" << std::endl; }

    }

    ~TCPClient() {
        closesocket(sock);
        sock = INVALID_SOCKET;
        WSACleanup();
    }

    // Подключиться
    bool connectTo(const char* ip = "127.0.0.1", int port = 8080) {
        
        //Задаем параметры сети в переменную hints
        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        //Задаем параметры сети в переменную hints
        result = getaddrinfo("127.0.0.1", "12345", &hints, &addrResult);
        if (result != 0) {
            std::cout << "getaddrinfo failed" << result << std::endl;
            /*WSACleanup();*/
            return false;
        }

        //Создаем сокет
        sock = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
        if (sock == INVALID_SOCKET) {
            std::cout << "sock failed" << result << std::endl;
           
            //WSACleanup();
            return false;
        }

        //Создаем соединение
        result = connect(sock, addrResult->ai_addr, addrResult->ai_addrlen);
        if (result == SOCKET_ERROR) {
            std::cout << "connect failed" << result <<std::endl;
            return false;
        }

        connected = true;
        return true;
    }

    // Отправить данные
    bool sendClient() {
 
        if (!connected) return false;
        else {
           result = send(sock, sendBuffer, static_cast<int> (strlen(sendBuffer)), 0);
           if (result == SOCKET_ERROR) {
               std::cout << "send failed" << result << std::endl;
               return false;
           }
           else { return true; }
               
        }
    }

    //Ставим сокет на прослушку
    bool ShootD() {
        result = shutdown(sock, SD_SEND);
        if (result == SOCKET_ERROR) {
            std::cout << "shutdown failed" << result << std::endl;
            return false;
        }

    }

    // Получить данные
    std::string receive() {

        if (!connected) {
            return "Empty";
        }
        else {
            do
            {
                ZeroMemory(recvBuffer, 10);
                result = recv(sock, recvBuffer, static_cast<int> (strlen(recvBuffer)), 0);
                if (result > 0) {
                    std::cout << "Result" << result << std::endl;
                    return recvBuffer;
                }
                else if (result == 0) {
                    std::cout << "Connection closed" << result << std::endl;
                    return "";
                }
                else  {
                        std::cout << "recv failed" << result << std::endl;
                        return "";
                };
            } while (result > 0);
        }

    }
private:
    SOCKET sock;
    WSADATA wsData;
    ADDRINFO hints;
    ADDRINFO* addrResult = NULL;
    const char* sendBuffer = "Hallo!";
    char recvBuffer[10]{ "" };
    bool connected;
    int result;
};

int main() {

    TCPClient client;
   
    if (!(client.connectTo())) { client.~TCPClient(); }
    if (!(client.sendClient())) { client.~TCPClient(); }
    if (!(client.ShootD())) { client.~TCPClient(); };
    std::cout << client.receive()<<std::endl;
 

    return 0;
}


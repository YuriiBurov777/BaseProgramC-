FROM ubuntu:latest
RUN apt-get update && apt-get install -y \
    g++ \
    nano 
WORKDIR /app
RUN echo '#include <iostream>\n\
\n\
int main() {\n\
    std::cout << "Hello World from Docker!" << std::endl;\n\
    return 0;\n\
}' > hello.cpp
RUN g++ hello.cpp -o hello
FROM ubuntu:latest
RUN apt-get update && apt-get install -y \
    g++ \
    nano 
COPY docker-cpp/Functor.cpp /src/docker-test2/
WORKDIR /src/docker-test2
RUN g++ Functor.cpp -o Functor
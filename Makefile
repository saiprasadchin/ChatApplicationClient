compiler = g++

all: g++ -pthread --std=c++17 main/main.cpp Utils/Utils.cpp View/View.cpp ClientSocket/ClientSocket.cpp -o client 

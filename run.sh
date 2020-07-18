
g++ -std=c++14 -pthread `pkg-config --cflags opencv` ./Cpp/main.cpp `pkg-config --libs opencv` -o executable.out

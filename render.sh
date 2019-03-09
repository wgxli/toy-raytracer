#! /bin/bash

g++ -std=c++11 -O3 -c main.cpp
g++ main.o src/*.o -O3 -o main.out
strip --strip-all main.out
./main.out

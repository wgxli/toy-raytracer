#! /bin/bash

g++ -std=c++11 -O3 -c animation.cpp
g++ animation.o src/*.o -O3 -o animate.out
strip --strip-all animate.out
./animate.out

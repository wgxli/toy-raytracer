#! /bin/bash

cd src
g++ -std=c++11 -O3 -c *.cpp
cd ..
echo 'Success!'

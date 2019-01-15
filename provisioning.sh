#!/bin/bash
sudo apt-get update -y &&\
sudo apt-get install libgl1-mesa-dev -y &&\
sudo apt install freeglut3-dev -y &&\
sudo apt install cmake -y
gradle wrapper
cd 3rdparty
git clone https://github.com/google/googletest.git googletest-master
cd googletest-master
mkdir build

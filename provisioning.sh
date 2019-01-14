#!/bin/bash
sudo apt-get update -y &&\
sudo apt-get install libgl1-mesa-dev -y &&\
sudo apt install freeglut3-dev -y &&\
sudo apt autoremove -y
gradle wrapper
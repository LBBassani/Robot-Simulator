#!/bin/bash

# Colorizing constants
GREEN='\033[1;32m'
SOFTGREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[1;31m'
NC='\033[0m' # No Color

GOOGLE_TEST_DIR="googletest-master"
DEPENDENCY_LIST="libgl1-mesa-dev freeglut3-dev cmake git"
ALL_DEPENDENCIES_MET=1
echo "${GREEN}[Optimization]${NC} Checking for installed libraries"

for i in $DEPENDENCY_LIST; do
    if [ $(dpkg -s $i 2>/dev/null | grep -c "install ok installed") -eq 0 ]; then
        echo "${YELLOW}[WARNING]${NC} The package $i was not detected."
        echo "${YELLOW}[WARNING]${NC} A package list update was scheduled."
        ALL_DEPENDENCIES_MET=0
        break
    fi
done

if [ $ALL_DEPENDENCIES_MET -eq 0 ]; then
    sudo apt update -y
    ALL_DEPENDENCIES_MET=1
fi

if [ $ALL_DEPENDENCIES_MET -eq 1 ]; then
    for i in $DEPENDENCY_LIST; do
        PKG_OK=$(dpkg -s $i 2>/dev/null | grep -c "install ok installed")
        echo "Checking for $i"
        if [ $PKG_OK -ne 1 ]; then
            echo "${YELLOW}[WARNING]${NC} The package ${SOFTGREEN}$i${NC} is pending. Setting up $i."
            sudo apt-get --force-yes --yes install $i
        else
            echo "${GREEN}[SUCCESS]${NC} Skipping ${SOFTGREEN}$i${NC} package. It's already installed."
        fi
    done
fi

cd 3rdparty
if [ ! -d "$GOOGLE_TEST_DIR" ]; then
    echo "${YELLOW}[WARNING]${NC} Googletest library was not detected, cloning repo."
    git clone https://github.com/google/googletest.git $GOOGLE_TEST_DIR
else
    echo "${GREEN}[SUCCESS]${NC} Googletest library detected, download avoided."
fi

cd googletest-master
rm build -i -rf
mkdir build

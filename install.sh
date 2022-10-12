#!/bin/bash

WORD_DIR_PATH=${PWD}
cd external/
rm -rf json/
git clone https://github.com/nlohmann/json.git

cd /usr/src/gtest
cmake CMakeLists.txt
make

echo "${WORD_DIR_PATH}"
cd ${WORD_DIR_PATH}
rm -rf build
mkdir build
cd build
cmake ..
make

#! /bin/sh

cmake -S . -B build/
cd build && make Convert_test
cd src/Convert && ./Convert_test

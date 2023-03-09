#! /bin/sh

cmake -S . -B build/
cd build && make Utils_test
cd src/Utils && ./Utils_test

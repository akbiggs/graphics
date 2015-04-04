#!/bin/bash
make clean
make all
if [ $? -eq 0 ]; then
    ./main
fi

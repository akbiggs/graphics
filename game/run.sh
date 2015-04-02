#!/bin/bash
make
if [ $? -eq 0 ]; then
    ./main
fi

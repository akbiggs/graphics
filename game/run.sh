#!/bin/bash
make all
if [ $? -eq 0 ]; then
    ./main
fi

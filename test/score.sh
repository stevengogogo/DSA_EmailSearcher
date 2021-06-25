#!/bin/bash
echo "Start Testing"
cp ./build/main.c ./test/testEnv/main.c
cd test/testEnv
sudo make  run 
cd ..
cd ..
echo "$(green)Test Complete$(reset)"
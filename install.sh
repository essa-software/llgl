#!/bin/bash

mkdir build
cd build
cmake .. -GNinja
ninja
sudo ninja install

#!/bin/bash

build_dir="./build"

if [ ! -d "$build_dir" ]; then
    mkdir $build_dir
fi

cd build
cmake ..
make
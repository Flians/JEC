#!/bin/bash

build_dir="./build"

if [ ! -d "$build_dir" ]; then
    mkdir $build_dir
fi

cd build

if [ $# -ge 1 ]
then
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$1 ..
else
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
fi

make
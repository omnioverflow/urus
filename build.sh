#!/bin/bash

if [ ! -d build ]
then
    mkdir build
fi

cd build
cmake -G "Visual Studio 16 2019" ..

# copy shaders
cd ..
cp src/glsl/*.vert build
cp src/glsl/*.frag build

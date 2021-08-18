#!/bin/bash

clear

if [ ! -d build ]
then
	echo "[ ******** -- Creating build directory..."
    mkdir build
	echo "  ******** --> OK ]"
fi

cd build

if [[ $OSTYPE == "darwin"* ]]; then
	# Mac OSX
	echo "[ ******** -- Generating Xcode project from cmake..."
    cmake -G Xcode ..
	echo "  ******** --> OK ]"
elif [[ $OSTYPE == "msys" ]]; then # for Git bash on Windows
    echo "[ ******** -- Generating Visual Studio solution from cmake..."
	# TODO: create some support for Cygwin 
    cmake -G "Visual Studio 16 2019" ..
	echo "  ******** --> OK ]"
else 
    echo "[ ******** /!\ Only Mac OSX and Windows x64 are supported\n"
	echo "  ******** --> KO ]"
	cd ..
	exit 1 
fi 

# go back to the original current dir 
cd ..

# copy shaders (TODO: find a workaround for this)
echo "[ ******** -- Copying shaders"
cp src/glsl/*.vert build
cp src/glsl/*.frag build
echo "  ******** --> OK ]"

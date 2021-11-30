#!/bin/bash

clear

buildWithTests="${1}" 	# flag to configure gtest
gtestRoot="${2}" 		# gtest repo which already cloned on the system

# Check if additional input arguments are set;
if [[ -n $buildWithTests ]]; then
	echo "Set up with unit tests"
fi # buildWithTests
if [[ -n $gtestRoot ]]; then
	echo "GTest root found: " ${gtestRoot}
fi # gtestRoot

if [ ! -d build ]
then
	echo "[ ******** -- Creating build directory..."
    mkdir build
	echo "  ******** --> OK ]"
fi

cd build

successMessage="OK"
failureMessage="KO (failure)"
if [[ $OSTYPE == "darwin"* ]]; then
	# Mac OSX
	echo "[ ******** -- Generating Xcode project from cmake..."

	if [[ $gtestRoot ]]; then
		cmake -G Xcode .. -DGTEST_ROOT=$gtestRoot -DBUILD_TESTS=true
	elif [[ $buildWithTests ]]; then
		cmake -G Xcode .. -DBUILD_TESTS=true
	else
		cmake -G Xcode ..
	fi # run cmake

	cmake -G Xcode ..

	result=$? # result of the most recent command
	resultMessage=$failureMessage
	if [ $result -eq 0 ]; then
		resultMessage=$successMessage
    fi # check result

    echo "  ******** --> " $resultMessage " ]"
elif [ $OSTYPE == "msys" ] || [ $OSTYPE == "cygwin" ]; then
	# Windows cygwin/git bash
	echo "[ ******** -- Generating Visual Studio solution from cmake..."
	# TODO: create some support for Cygwin 

	if [[ $gtestRoot ]]; then
		cmake -G "Visual Studio 16 2019" .. -DGTEST_ROOT=$gtestRoot \
		-DBUILD_TESTS=true
	elif [[ $buildWithTests ]]; then
		cmake -G "Visual Studio 16 2019" .. -DBUILD_TESTS=true
	else
		cmake -G "Visual Studio 16 2019" ..
	fi # run cmake	

	result=$?
	resultMessage=$failureMessage
	if [ $result -eq 0 ]; then
		resultMessage=$successMessage
    fi # check result

    echo "  ******** --> " $resultMessage "]"
else 
	echo "[ ******** /!\ Only Mac OSX and Windows x64 are supported\n"
	echo "Current OSTYPE == " $OSTYPE
	echo "  ******** --> " $failureMessage " ]"
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

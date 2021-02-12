#!/bin/bash

if [[ $OSTYPE == "darwin"* ]]; then
	open build/Urus.xcodeproj
else
	start build/Urus.sln
fi

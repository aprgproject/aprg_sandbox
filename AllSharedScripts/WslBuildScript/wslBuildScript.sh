#!/bin/bash

# Set variable values
projectName=$1
buildOption=$2
scriptPath=$(realpath "$0")

# Display variable values
echo "The project name is [$projectName]"
echo "The build option is [$buildOption]"
echo "The script path is [$scriptPath]"

# Setup folders for compilation
cd ..
mkdir -p WslBuild
cd WslBuild

# Enable the "exit on error" option to automatically stop if there is a failure
set -e

# Perform build actions
if [ "$buildOption" == "GCC" ]; then
	cmake -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ "../$projectName/"
	make -j8
	#"./$projectName"
elif [ "$buildOption" == "Clang" ]; then
	cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ "../$projectName/"
	make -j8
	"./$projectName"
elif [ "$buildOption" == "ClangWithAsan" ]; then
	cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_FLAGS:STRING="${CMAKE_C_FLAGS} -g --coverage -fsanitize=address -fno-omit-frame-pointer" -DCMAKE_CXX_FLAGS:STRING="${CMAKE_C_FLAGS} -g --coverage -fsanitize=address -fno-omit-frame-pointer" "../$projectName/"
	make -j8
	"./$projectName"
else
	echo "$scriptPath:$LINENO:${BASH_LINENO[0]}: error: The build option [$buildOption] is not supported by the WSL shell script."
	exit 1
fi
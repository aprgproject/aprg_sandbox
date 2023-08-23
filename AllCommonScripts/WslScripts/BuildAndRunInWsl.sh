#!/bin/bash

# Set variable values
projectName=$1
scriptOption=$2
scriptPath=$(realpath "$0")
scriptName=$(basename "$0")
WslBuildFolderName="WslBuild"

# Display variable values
echo "[Script: '$scriptName']: The project name is [$projectName] and the build option is [$scriptOption]"
echo "[Script: '$scriptName']: The script path is [$scriptPath]"
echo "[Script: '$scriptName']: The WSL build folder name is [$WslBuildFolderName]"

# Setup folders for compilation
cd ..
mkdir -p $WslBuildFolderName
cd $WslBuildFolderName
echo "[Script: '$scriptName']: The build path is [$(pwd)]"

# Enable the "exit on error" option to automatically stop if there is a failure
set -e

# Perform build actions
if [ "$scriptOption" == "clean" ]; then
	if [ "$WslBuildFolderName" = $(basename "$(pwd)") ]; then
		echo "[Script: '$scriptName']: Deleting everything in $(pwd)."
		rm -rf *
	fi
elif [ "$scriptOption" == "buildWithGcc" ]; then
	cmake -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ "../$projectName/"
	make -j8
elif [ "$scriptOption" == "buildWithClang" ]; then
	cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ "../$projectName/"
	make -j8
elif [ "$scriptOption" == "buildWithClangWithAsan" ]; then
	cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_FLAGS:STRING="${CMAKE_C_FLAGS} -g --coverage -fsanitize=address -fno-omit-frame-pointer" -DCMAKE_CXX_FLAGS:STRING="${CMAKE_C_FLAGS} -g --coverage -fsanitize=address -fno-omit-frame-pointer" "../$projectName/"
	make -j8
elif [ "$scriptOption" == "run" ]; then
	echo "[Script: '$scriptName']: Running executable: [$(pwd)/$projectName]."
	"./$projectName"
else
	echo "$scriptPath:$LINENO:${BASH_LINENO[0]}: error: The build option [$scriptOption] is not supported by the WSL shell script."
	exit 1
fi
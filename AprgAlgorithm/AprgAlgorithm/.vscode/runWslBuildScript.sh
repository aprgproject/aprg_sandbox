#!/bin/bash

# Set the target directory name you want to find
targetDirectoryName="aprg"

# Get the current working directory
projectDirectory=$(pwd)

echo "Target directory name: [targetDirectoryName], Project directory:[projectDirectory]"

# Function to find the target directory
findTargetDirectory() {
    local dir="$projectDirectory"

    # Loop until we reach the root directory ("/")
    while [ "$dir" != "/" ]; do
        # Check if the target directory exists in the current directory
        if [ -d "$dir/$targetDirectoryName" ]; then
			aprgDirectory="$dir/$targetDirectoryName"
            return
        fi

        # Go one directory up
        dir=$(dirname "$dir")
    done

    echo "The directory name [$targetDirectoryName] is not found in any parent directories."
}

#Locating aprg directory
echo "Locating aprg directory..."
aprgDirectory=""
findTargetDirectory
echo "The aprg directory is [$aprgDirectory]"


#Running WSL Build Script

# This build command prints output with highlighting.
#bash "$aprgDirectory/AllSharedScripts/WslBuildScript/wslBuildScript.sh" $1 $2 

# This build command prints correct directory so that you can link warnings and error in Visual Studio directly to the file.
bash "$aprgDirectory/AllSharedScripts/WslBuildScript/wslBuildScript.sh" $1 $2 2>&1 | sed -E "s|$projectDirectory||g"

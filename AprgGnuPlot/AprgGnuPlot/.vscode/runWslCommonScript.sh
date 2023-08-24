#!/bin/bash

# Set variable values
aprgDirectoryName="aprg"
projectDirectory=$(pwd)
scriptName=$(basename "$0")
scriptRunningOption=$1

# Display variable values
echo "[Script: '$scriptName']: The aprg directory name is [$aprgDirectoryName] and the project directory is [$projectDirectory]."

# Function to find the aprg directory
findAprgAsAParentDirectory() {
    local dir="$projectDirectory"

    # Loop until we reach the root directory ("/")
    while [ "$dir" != "/" ]; do
        # Check if the directory exists in the current directory
        if [ -d "$dir/$aprgDirectoryName" ]; then
			aprgDirectory="$dir/$aprgDirectoryName"
            return
        fi

        # Go one directory up
        dir=$(dirname "$dir")
    done

    echo "[Script: '$scriptName']: The directory name [$aprgDirectoryName] is not found in any parent directories."
}

# Locating aprg directory
echo "[Script: '$scriptName']: Locating aprg directory..."
aprgDirectory=""
findAprgAsAParentDirectory
echo "[Script: '$scriptName']: The aprg directory is [$aprgDirectory]"


# Running WSL Build And Run Script

if [ "$scriptRunningOption" == "outputWithHighlighting" ]; then
	# This command prints output with highlighting because stdout and stderr are maintained
	bash "$aprgDirectory/AllCommonScripts/WslScripts/BuildAndRunInWsl.sh" $2 $3 $4
elif [ "$scriptRunningOption" == "outputWithAbsolutePaths" ]; then
    # This command prints output without highlighting but with corrected absolute paths
	bash "$aprgDirectory/AllCommonScripts/WslScripts/BuildAndRunInWsl.sh" $2 $3 $4 2>&1 | sed -E "s|\/mnt\/(\w+)\/|\U\1:/|g"
elif [ "$scriptRunningOption" == "outputWithRelativePaths" ]; then
    # This command prints output without highlighting but with corrected relative paths from the project directory
	bash "$aprgDirectory/AllCommonScripts/WslScripts/BuildAndRunInWsl.sh" $2 $3 $4 2>&1 | sed -E "s|$projectDirectory||g"
else
	echo "[Script: '$scriptName']: The script option [$scriptOption] is not found."
	echo "$scriptPath:$LINENO:${BASH_LINENO[0]}: error: The script option [$scriptOption] is not supported by the WSL shell script."
	exit 1
fi


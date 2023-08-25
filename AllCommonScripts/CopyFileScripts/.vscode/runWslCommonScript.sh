#!/bin/bash

# Set variable values
projectDirectory=$(pwd)
scriptDirectory=$(dirname "$0")
scriptName=$(basename "$0")
scriptRunningOption=$1

# Source needed scripts
source "$scriptDirectory/locateAprgDirectory.sh" 
findAprgDirectory $projectDirectory
echo "aprgDirectory"
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

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
	scriptPrint $scriptName $LINENO "The script option [$scriptOption] is not found."
	echo "$scriptPath:$LINENO:${BASH_LINENO[0]}: error: The script option [$scriptOption] is not supported by the WSL shell script."
	exit 1
fi


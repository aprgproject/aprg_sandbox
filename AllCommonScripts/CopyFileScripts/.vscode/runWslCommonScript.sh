#!/bin/bash

# Set variable values
projectDirectory=$(pwd)
scriptDirectory=$(dirname "$0")
scriptName=$(basename "$0")
scriptRunningOption=$1
exitCode=0

# Source needed scripts
source "$scriptDirectory/locateAprgDirectory.sh" 
findAprgDirectory $projectDirectory
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Running WSL Build And Run Script
if [ "$scriptRunningOption" == "outputWithHighlighting" ]; then
	# This command prints output with highlighting because stdout and stderr are maintained
	"$aprgDirectory/AllCommonScripts/WslScripts/BuildAndRunInWsl.sh" $2 $3 $4
	exitCode=$?
elif [ "$scriptRunningOption" == "outputWithAbsolutePaths" ]; then
    # This command prints output without highlighting but with corrected absolute paths
	"$aprgDirectory/AllCommonScripts/WslScripts/BuildAndRunInWsl.sh" $2 $3 $4 2>&1 | sed -E "s|\/mnt\/(\w+)\/|\U\1:/|g"
	exitCode=$?
elif [ "$scriptRunningOption" == "outputWithRelativePaths" ]; then
    # This command prints output without highlighting but with corrected relative paths from the project directory
	"$aprgDirectory/AllCommonScripts/WslScripts/BuildAndRunInWsl.sh" $2 $3 $4 2>&1 | sed -E "s|$projectDirectory||g"
	exitCode=$?
else
	scriptPrint $scriptName $LINENO "The script option [$scriptOption] is not found."
	echo "$scriptPath:$LINENO:${BASH_LINENO[0]}: error: The script option [$scriptOption] is not supported by the WSL shell script."
	exitCode=$?
fi

scriptPrint $scriptName $LINENO "The exit code is: [$exitCode]"
exit $exitCode
#!/bin/bash

# Set variable values
scriptDirectory=$(dirname "$0")
scriptName=$(basename "$0")
scriptRunningOption=$1
locateScriptPath=$(realpath "$scriptDirectory/locateAprgDirectory.sh")
exitCode=0

# Source needed scripts
if ! [[ -e $locateScriptPath ]]; then
	echo "$scriptName:$LINENO: Error: The script [$locateScriptPath] does not exist."
	exit 1
fi
source "$scriptDirectory/locateAprgDirectory.sh"
findAprgDirectory $scriptDirectory
# Validate path
if ! [[ -e $aprgDirectory ]]; then
	echo "$scriptName:$LINENO: Error: The script [$aprgDirectory] does not exist."
	exit 1
fi
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
	"$aprgDirectory/AllCommonScripts/WslScripts/BuildAndRunInWsl.sh" $2 $3 $4 2>&1 | sed -E "s|$(pwd)||g"
	exitCode=$?
else
	scriptPrint $scriptName $LINENO "The script option [$scriptOption] is not found."
	echo "$scriptPath:$LINENO:${BASH_LINENO[0]}: error: The script option [$scriptOption] is not supported by the WSL shell script."
	exitCode=$?
fi

scriptPrint $scriptName $LINENO "The exit code is: [$exitCode]"
exit $exitCode

#!/bin/bash

# Set variable values
scriptName=$(basename "$0")
scriptDirectory=$(dirname "$0")
aprgDirectory=$(realpath "$scriptDirectory/../../")
shortenedPathLengthForDisplay=50

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Find all files with the same name in the target folder
scriptPrint $scriptName $LINENO "Searching all files in [$aprgDirectory]..."
locationPaths=($(find "$aprgDirectory" -type f -name "*.sh"))

for locationPath in "${locationPaths[@]}"; do
    dos2unix "$locationPaths"
done

scriptPrint $scriptName $LINENO "All shell scripts converted."

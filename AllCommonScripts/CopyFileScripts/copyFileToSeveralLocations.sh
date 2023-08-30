#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
locatorFile=$(basename "$1")
if [ -z "$2" ]; then	# If there are no second argument use the first argument
	fileToCopy=$(realpath "$(pwd)/$1")
else
	fileToCopy=$(realpath "$(pwd)/$2")
fi
skipRegexPattern="\/aprg\/Python\/|\/aprg\/AllCommonScripts\/"
shortenedPathLengthForDisplay=50

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Validate input
if [ -z "$locatorFile" ]; then
    scriptPrint $scriptName $LINENO "Error: The filename cannot be empty."
	exit 1
fi
if ! [[ -e $fileToCopy ]]; then
    scriptPrint $scriptName $LINENO "Error: The file [$fileToCopy] does not exist."
	exit 1
fi

# Find all files with the same name in the target folder
scriptPrint $scriptName $LINENO "Searching all files in [$aprgDirectory] with the filename [$locatorFile]..."
locationPaths=($(find "$aprgDirectory" -type f -name "$locatorFile"))

# Replace each file with the source file
shortenedFileToCopy=$(echo "$fileToCopy" | tail -c $shortenedPathLengthForDisplay)
scriptPrint $scriptName $LINENO "Copying [...$shortenedFileToCopy] ->"
for locationPath in "${locationPaths[@]}"; do
    # Check if it can be skipped
	if  [[ ! "$locationPath" =~ $skipRegexPattern ]]; then
		locationDirectory=$(dirname "$locationPath")
		shortenedLocationPath=$(echo "$locationDirectory" | tail -c $shortenedPathLengthForDisplay)
        scriptPrint $scriptName $LINENO "-> to [...$shortenedLocationPath]."
        cp -f "$fileToCopy" "$locationDirectory"
	fi
done

scriptPrint $scriptName $LINENO "File replacements completed."

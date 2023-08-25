#!/bin/bash

# Source needed scripts
source ../PrintScripts/PrintUtilities.sh

# Set the variables
scriptName=$(basename "$0")
sourceFilePath=$1
targetFolderPath="/mnt/f/Branches/APRG_GIT/aprg/aprg/"
skipRegexPattern="\/aprg\/Python\/|\/aprg\/AllCommonScripts\/"
shortenedPathLengthForDisplay=50

# Get the file name from the source file path
sourceFilename=$(basename "$sourceFilePath")
if [ -z "$sourceFilename" ]; then
    scriptPrint $scriptName $LINENO "Error: The filename cannot be empty."
	exit 1
fi

# Find all files with the same name in the target folder
scriptPrint $scriptName $LINENO "Searching all files in [$targetFolderPath] with the filename [$sourceFilename]"
scriptPrint $scriptName $LINENO "find $targetFolderPath" -type f -name "$sourceFilename"
targetFilePaths=($(find "$targetFolderPath" -type f -name "$sourceFilename"))

# Replace each file with the source file
for targetFilePath in "${targetFilePaths[@]}"; do
    # Check if it can be skipped
	if  [[ ! "$targetFilePath" =~ $skipRegexPattern ]]; then
		shortenedSourcePath=$(echo "$sourceFilePath" | tail -c $shortenedPathLengthForDisplay)
		shortenedTargetPath=$(echo "$targetFilePath" | tail -c $shortenedPathLengthForDisplay)
        scriptPrint $scriptName $LINENO "Replacing [...$shortenedSourcePath] with [...$shortenedTargetPath]"
        #cp -f "$sourceFilePath" "$targetFilePath"
	fi
done

scriptPrint $scriptName $LINENO "File replacements completed."

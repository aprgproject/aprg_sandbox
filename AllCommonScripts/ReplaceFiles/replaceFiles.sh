#!/bin/bash

# Set the variables
# sourceFilePath="/mnt/f/Branches/APRG_GIT/aprg/aprg/111_AprgScripts/ReplaceFiles/CMakePresets.json"
sourceFilePath=$1
targetFolderPath="/mnt/f/Branches/APRG_GIT/aprg/aprg/"
skipRegexPattern="\/aprg\/Python\/"

# Get the file name from the source file path
sourceFilename=$(basename "$sourceFilePath")
# Find all files with the same name in the target folder
echo "Searching all files in $targetFolderPath with the filename $sourceFilename"
echo find "$targetFolderPath" -type f -name "$sourceFilename"targetFilePaths=($(find "$targetFolderPath" -type f -name "$sourceFilename"))

# Replace each file with the source file
for targetFilePath in "${targetFilePaths[@]}"; do
    # Check if it can be skipped
	if ! [[ "$targetFilePath" == $sourceFilePath || "$targetFilePath" =~ $skipRegexPattern ]]; then
		shortenedSourcePath=$(echo "$sourceFilePath" | awk -F'/' '{print ".../"$(NF-2)"/"$(NF-1)"/"$(NF)}')
		shortenedTargetPath=$(echo "$targetFilePath" | awk -F'/' '{print ".../"$(NF-2)"/"$(NF-1)"/"$(NF)}')
        echo "Replacing [$shortenedSourcePath] with [$shortenedTargetPath]"
        cp -f "$sourceFilePath" "$targetFilePath"
	fi
done
echo "File replacements completed."
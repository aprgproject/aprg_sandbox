#!/bin/bash

# Set the source file path and the target folder path
sourceFilePath="/mnt/f/Branches/APRG_GIT/aprg/aprg/111_AprgScripts/ReplaceFiles/CMakePresets.json"
targetFolderPath="/mnt/f/Branches/APRG_GIT/aprg/aprg/"

# Get the file name from the source file path
sourceFilename=$(basename "$sourceFilePath")

# Find all files with the same name in the target folder
echo "Searching all files in $targetFolderPath with the filename $sourceFilename"
echo find "$targetFolderPath" -type f -name "$sourceFilename"
targetFilePaths=($(find "$targetFolderPath" -type f -name "$sourceFilename"))

# Replace each file with the source file
for targetFilePath in "${targetFilePaths[@]}"; do
    # Check if its a different path
	if [ "$sourceFilePath" != "$targetFilePath" ]; then
		shortenedSourcePath=$(echo "$sourceFilePath" | awk -F'/' '{print ".../"$(NF-2)"/"$(NF-1)"/"$(NF)}')
		shortenedTargetPath=$(echo "$targetFilePath" | awk -F'/' '{print ".../"$(NF-2)"/"$(NF-1)"/"$(NF)}')
        echo "Replacing $shortenedSourcePath with $shortenedTargetPath"
        cp -f "$sourceFilePath" "$targetFilePath"
	fi
done

echo "File replacements completed."

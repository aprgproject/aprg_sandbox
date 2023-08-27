#!/bin/bash

# Use this file in the case you have to rename

# Set variables
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
diffsDirectory="$scriptDirectory/diffs"

# Use a for loop to iterate over each file in the directory
for file in "$diffsDirectory"/*; do
    # Check if the current file is a regular file (not a directory)
    if [ -f "$file" ]; then
        # Perform operations on the file here
        directoryWithR=$(echo $file | sed -E "s|(^.*\/diffs\/r)(.*)_(.*$)|\1|")
        revisionCount=$(echo $file | sed -E "s|(^.*\/diffs\/r)(.*)_(.*$)|\2|")
        revisionHashWithUnderscore=$(echo $file | sed -E "s|(^.*\/diffs\/r)(.*)(_.*$)|\3|")
        echo "directoryWithR: $directoryWithR"
        echo "revisionCount: $revisionCount"
        echo "revisionHashWithUnderscore: $revisionHashWithUnderscore"
		reversedCount=$(expr 688 - "$revisionCount")
		newFile="$directoryWithR$reversedCount$revisionHashWithUnderscore"
        echo "reversedCount: $reversedCount"
        echo "newFile: $newFile"
		mv $file $newFile
    fi
done

#!/bin/bash

findAprgDirectory() {
	# Set variable values
	aprgDirectory=""
	local aprgDirectoryName="aprg"
	local inputDirectory=$(realpath "$1")
	local localScriptName="locateAprgDirectory"
	
	# Validate input
	if ! [ -d "$inputDirectory" ]; then
		echo "$localScriptName:$LINENO: Error: The input directory [$inputDirectory] is not a directory."
		return 1
	fi
	
	# Display variable values
	echo "$localScriptName:$LINENO: The aprg directory name is [$aprgDirectoryName]."
	echo "$localScriptName:$LINENO: The input directory is [$inputDirectory] for searching [$aprgDirectoryName] directory."
	
	# Set variables for search
	searchingDirectory="$inputDirectory"
	
	# Loop until we reach the root directory ("/")
	while [ "$searchingDirectory" != "/" ]; do
		# Check if the directory exists in the current directory
		if [ -d "$searchingDirectory/$aprgDirectoryName" ]; then
			aprgDirectory="$searchingDirectory/$aprgDirectoryName"
			break
		else
			# Go one directory up
			searchingDirectory=$(dirname "$searchingDirectory")
		fi
	done
	
	# Validate output
	if [ "$searchingDirectory" == "/" ]; then
		echo "$localScriptName:$LINENO: Error: The directory name [$aprgDirectoryName] is not found in any parent directories of [$inputDirectory]."
		return 1
	fi
	
	echo "$localScriptName:$LINENO: The aprg directory is [$aprgDirectory]."
}

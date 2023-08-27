#!/bin/bash

# Set variables
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
gitNewRepoPath=$(realpath "$scriptDirectory/../gitNewRepoHere/")
svnDiffsPath=$(realpath "$scriptDirectory/../../svn/diffs/")
revision=$1

if [ -z "$revision" ]; then
    echo "No parameter was given. Please provide revision number as a parameter."
    exit 1
fi

set -e
diffFilePath="$svnDiffsPath/r$revision.diff"
echo "diffFilePath: [$diffFilePath]"
cd "$gitNewRepoPath"
echo "Changing directory to $(pwd)"
dos2unix "$diffFilePath"
git apply --check --ignore-space-change --ignore-whitespace --inaccurate-eof "$diffFilePath"
git apply --ignore-space-change --ignore-whitespace --inaccurate-eof "$diffFilePath"
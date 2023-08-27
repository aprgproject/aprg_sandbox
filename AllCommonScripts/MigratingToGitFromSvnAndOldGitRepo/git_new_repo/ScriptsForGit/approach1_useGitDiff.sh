#!/bin/bash

scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
gitNewRepoPath=$(realpath "$scriptDirectory/../gitNewRepoHere/")
gitDiffsPath=$(realpath "$scriptDirectory/../../git_old_repo/diffs/")
lineCount=$1
revisionHash=$2

if [ -z "$lineCount" ]; then
    echo "Please provide lineCount number as a parameter."
    exit 1
fi

if [ -z "$revisionHash" ]; then
    echo "Please provide revisionHash number as a parameter."
    exit 1
fi

set -e
diffFilePath="$gitDiffsPath/r${lineCount}_${revisionHash}.diff"
echo "diffFilePath: [$diffFilePath]"
cd "$gitNewRepoPath"
echo "Changing directory to $(pwd)"
dos2unix "$diffFilePath"
git apply --check --ignore-space-change --ignore-whitespace --inaccurate-eof "$diffFilePath"
git apply --ignore-space-change --ignore-whitespace --inaccurate-eof "$diffFilePath"
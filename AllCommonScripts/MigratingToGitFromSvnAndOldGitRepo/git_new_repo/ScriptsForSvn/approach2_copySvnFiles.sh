#!/bin/bash

# Set variables
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
gitNewRepoPath=$(realpath "$scriptDirectory/../gitNewRepoHere/")
svnRepoPath=$(realpath "$scriptDirectory/../../svn/svnRepoHere/")
revision=$1

if [ -z "$revision" ]; then
    echo "No parameter was given. Please provide revision number as a parameter."
    exit 1
fi

set -e
cd "$svnRepoPath"
echo "Changing directory to $(pwd)"
set +e
svn update -r $revision
svnUpdateStatus=$?
while [ $svnUpdateStatus -ne 0 ]; do
    echo "svnUpdateStatus: [$svnUpdateStatus], sleeping for 1 minute before trying again."
    sleep 60
    svn update -r $revision
    svnUpdateStatus=$?
done
set -e
cd "$gitNewRepoPath"
echo "Changing directory to $(pwd)"
echo "Perform \"rm -rf *\", it should avoid deleting the \".git\" folder."
rm -rf *
echo "List directory (check if .git folder is deleted): $(ls -la)"
rsync  --verbose --archive -recursive --force --exclude='.svn/' $svnRepoPath/* $gitNewRepoPath
find "$gitNewRepoPath" -type f ! -path '/**/.git/**/*' -exec dos2unix {} \;
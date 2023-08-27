#!/bin/bash

scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
gitNewRepoPath=$(realpath "$scriptDirectory/../gitNewRepoHere/")
gitOldRepoPath=$(realpath "$scriptDirectory/../../git_old_repo/gitOldRepoHere/")
revisionHash=$1

if [ -z "$revisionHash" ]; then
    echo "No parameter was given. Please provide revisionHash number as a parameter."
    exit 1
fi

set -e
cd "$gitOldRepoPath"
echo "Changing directory to $(pwd)"
set +e
echo "Performing: git checkout $revisionHash"
git checkout $revisionHash
gitCheckoutStatus=$?
while [ $gitCheckoutStatus -ne 0 ]; do
    echo "gitCheckoutStatus: [$gitCheckoutStatus], sleeping for 1 minute before trying again."
    sleep 60
    git checkout $revisionHash
    gitCheckoutStatus=$?
done
set -e
cd "$gitNewRepoPath"
echo "Changing directory to $(pwd)"
echo "Perform \"rm -rf *\", it should avoid deleting the \".git\" folder."
rm -rf *
echo "List directory (check if .git folder is deleted): $(ls -la)"
rsync  --verbose --archive -recursive --force --exclude='.svn/' $gitOldRepoPath/* $gitNewRepoPath
find "$gitNewRepoPath" -type f ! -path '/**/.git/**/*' -exec dos2unix {} \;
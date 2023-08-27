#!/bin/bash

# Set variables
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")

revisionCount=1
while read -r line; do
    echo "line: [$line]"
    revisionHash=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\1|")
    commitDate=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\2|")
    commitAuthor=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\3|")
    commitMessage=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\4|")
    echo "contents: [$revisionHash] [$commitDate] [$commitAuthor] [$commitMessage]"
    git show "$revisionHash" > "$scriptDirectory/diffs/r${revisionCount}_${revisionHash}.diff"
    ((revisionCount++))
done < "$scriptDirectory/formattedGitHistory.txt"

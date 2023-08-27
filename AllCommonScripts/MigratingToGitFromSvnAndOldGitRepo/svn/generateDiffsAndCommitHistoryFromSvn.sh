#!/bin/bash

# Set variables
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
revisionsRegex="^r[0-9]"
messagesRegex='^[a-zA-Z]'
newEntryRegex='^--------'
savedRevision=""
savedDate=""
savedAuthor=""
savedMessage=""

echo "" > "$scriptDirectory/formattedSvnHistory.txt"
while read -r line; do
    echo "line: [$line]"
    firstItem=$(echo $line | awk '{print $1}')
    
    if [[ "$firstItem" =~ $revisionsRegex ]]; then
        echo "revision: [$firstItem]"
        svn diff -c $firstItem > "$scriptDirectory/diffs/$firstItem.diff"
        savedRevision=$(echo $line | sed -E "s/^(.*) | (.*) | (.*) | .*$/\1/")
        savedAuthor=$(echo $line | sed -E "s/^(.*) | (.*) | (.*) | .*$/\2/")
        unformattedDate=$(echo $line | sed -E "s/^(.*) | (.*) | (.*) | .*$/\3/")
        savedDate=$(echo $unformattedDate | sed -E "s|^.*([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]) ([0-9][0-9]:[0-9][0-9]:[0-9][0-9]).*$|\1T\2|")
    elif [[ "$firstItem" =~ $messagesRegex ]]; then
        echo "commit message: [$line]"
        savedMessage=$firstItem
    elif [[ "$firstItem" =~ $newEntryRegex ]]; then
    	echo "([{$savedRevision}]) ([{$savedDate}]) ([{$savedAuthor}]) ([{$savedMessage}])" >> "$scriptDirectory/formattedSvnHistory.txt"
    fi
done < "$scriptDirectory/svnRevisionsDetails.txt"

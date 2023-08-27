#!/bin/bash

scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
startLineCountPath="$scriptDirectory/startLineCount.log"
endLineCountPath="$scriptDirectory/endLineCount.log"
failedGitCommitsPath="$scriptDirectory/failedGitCommits.log"
approach1="$scriptDirectory/approach1_useGitDiff.sh"
approach2="$scriptDirectory/approach2_copyGitFiles.sh"
gitHistoryPath=$(realpath "$scriptDirectory/../../git_old_repo/formattedGitHistory.txt")

# take note that the range is inclusive
currentLineCount=1
startLineCount=1
endLineCount=1
read startLineCount < "$startLineCountPath"
read endLineCount < "$endLineCountPath"

while read -r line; do
    echo "line: [$line]"
    echo "comparing | startLineCount: [$startLineCount] currentLineCount: [$currentLineCount] endLineCount: [$endLineCount]"
    if [ "$currentLineCount" -gt "$endLineCount" ]; then
        echo "reached end line | currentLineCount: [$currentLineCount] endLineCount: [$endLineCount]"
		exit 0
    elif [ "$currentLineCount" -lt "$startLineCount" ]; then
        echo "skipping | currentLineCount: [$currentLineCount] line: [$line]"
    else
        revisionHash=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\1|")
        date=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\2|")
        author=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\3|")
        message=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\4|")
        echo "revisionHash: [$revisionHash]"
        echo "date: [$date]"
        echo "author: [$author]"
        echo "message: [$message]"
        "$approach1" $currentLineCount $revisionHash
        exitStatus=$?
        echo "exitStatus: [$exitStatus]"
        if [ $exitStatus -ne 0 ]; then
            "$approach2" $revisionHash
            exitStatus=$?
            echo "exitStatus: [$exitStatus]"
            if [ $exitStatus -ne 0 ]; then
                echo "All approaches failed."
                echo "git commit --message \"$message\" --author \"$author\" --date \"$date\"" >> "$failedGitCommitsPath"
                exit 1
            fi
        fi
        set -e
        git add --all
        git commit --message "$message" --author "$author" --date "$date"
        set +e
    fi
    ((currentLineCount++))
    echo "$currentLineCount" > "$startLineCountPath"
    echo "saved currentLineCount: [$currentLineCount]"
done < "$gitHistoryPath"

#!/bin/bash

scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
finishedLineCountPath="$scriptDirectory/finishedLineCount.log"
failedGitCommitsPath="$scriptDirectory/failedGitCommits.log"
approach1="$scriptDirectory/approach1_useSvnDiff.sh"
approach2="$scriptDirectory/approach2_copySvnFiles.sh"
svnHistoryPath=$(realpath "$scriptDirectory/../../svn/formattedSvnHistory.txt")

currentLineCount=0
previousLineCount=0
read previousLineCount < "$finishedLineCountPath"

while read -r line; do
    echo "line: [$line]"
    echo "comparing | currentLineCount: [$currentLineCount] previousLineCount: [$previousLineCount]"
    if [ "$currentLineCount" -lt "$previousLineCount" ]; then
        echo "skipping | currentLineCount: [$currentLineCount] line: [$line]"
    else
        revision=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\1|")
        date=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\2|")
        author=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\3|")
        message=$(echo $line | sed -E "s|^.*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*\(\[\{(.*)\}\]\).*$|\4|")
        echo "revision: [$revision]"
        echo "date: [$date]"
        echo "author: [$author]"
        echo "message: [$message]"
        "$approach1" $revision
        exitStatus=$?
        echo "exitStatus: [$exitStatus]"
        if [ $exitStatus -ne 0 ]; then
            "$approach2" $revision
            exitStatus=$?
            echo "exitStatus: [$exitStatus]"
            if [ $exitStatus -ne 0 ]; then
                echo "All approaches failed."
                echo "git commit --message \"$message\" --author \"$author\" --date \"$date +0800\"" >> "$failedGitCommitsPath"
                exit 1
            fi
        fi
        set -e
        git add --all
        git commit --message "$message" --author "$author" --date "$date +0800"
        set +e
    fi
    ((currentLineCount++))
    echo "$currentLineCount" > "$finishedLineCountPath"
    echo "saved currentLineCount: [$currentLineCount]"
done < "$svnHistoryPath"

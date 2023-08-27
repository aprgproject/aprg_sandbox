#!/bin/bash

# Set variables
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")

git log --oneline --pretty=format:"([{%h}]) ([{%ad}]) ([{%an <%ae>}]) ([{%s}])" --date=iso-strict > "$scriptDirectory/formattedGitHistory.txt"
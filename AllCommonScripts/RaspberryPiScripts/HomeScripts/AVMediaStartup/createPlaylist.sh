#!/bin/bash

# Set variables
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
raspberryPiDirectory="/media/aprg/OVAL/"
itemsDirectory="$raspberryPiDirectory/ItemsToPlay/"
playlistFile="$raspberryPiDirectory/playList.m3u"
# Source needed scripts
source "$scriptDirectory/PrintUtilities.sh"

# Display variable
scriptPrint $scriptName $LINENO "itemsDirectory: [$itemsDirectory]"

# Get list of items
itemsToPlay=($(ls "$itemsDirectory"))

# Write to Playlist
cat /dev/null > "$playlistFile"
for itemToPlay in "${itemsToPlay[@]}"; do
	pathToPlay=$(realpath "$itemsDirectory/$itemToPlay")
	scriptPrint $scriptName $LINENO "[pathToPlay: $pathToPlay]"
	echo "$pathToPlay" >> "$playlistFile"
done

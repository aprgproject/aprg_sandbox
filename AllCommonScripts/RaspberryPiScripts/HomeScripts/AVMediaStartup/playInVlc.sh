#!/bin/bash

# Set variables
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
raspberryPiDirectory="/media/aprg/OVAL/"
playlistFile="$raspberryPiDirectory/playList.m3u"
# Source needed scripts
source "$scriptDirectory/PrintUtilities.sh"

# Display variable
scriptPrint $scriptName $LINENO "playlistFile: [$playlistFile]"

# Play with VLC
scriptPrint $scriptName $LINENO "vlc --fullscreen --quiet $playlistFile"
vlc --fullscreen --quiet $playlistFile

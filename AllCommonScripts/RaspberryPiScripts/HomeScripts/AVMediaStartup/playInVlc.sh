#!/bin/bash

# Set variables
scriptName=$(basename "$0")
scriptDirectory=$(realpath "$(dirname "$0")")
raspberryPiDirectory="/media/aprg/OVAL/"
playlistFile="$raspberryPiDirectory/playList.m3u"

# Source needed scripts
source "$scriptDirectory/PrintUtilities.sh"

# Display variable
scriptPrint $scriptName $LINENO "playlistFile: [$playlistFile]"

# Play with VLC
scriptPrint $scriptName $LINENO "vlc --fullscreen --quiet $playlistFile"
vlc --fullscreen --quiet $playlistFile

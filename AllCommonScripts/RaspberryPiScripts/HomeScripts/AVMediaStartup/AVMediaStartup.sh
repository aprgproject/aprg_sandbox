#!/bin/bash

# Set variables
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")

# Source needed scripts
source "$scriptDirectory/PrintUtilities.sh"
# Display audio visual media at startup
cat /dev/null > "$scriptDirectory/AVMediaStartup.log" 2>&1
scriptPrint $scriptName $LINENO "Starting of Audio Video Media." >> "$scriptDirectory/AVMediaStartup.log" 2>&1
$scriptDirectory/createPlaylist.sh >> "$scriptDirectory/AVMediaStartup.log" 2>&1
$scriptDirectory/playInVlc.sh >> "$scriptDirectory/AVMediaStartup.log" 2>&1




# Used in powerpoint presentation
#soffice --show --norestore --invisible /media/aprg/OVAL/AVMediaStartup.pptx >> AVMediaStartup.log 2>&1



#!/bin/bash

# Set variables
sleepTimeout="30"

# Sleep for some time to prepare computer
scriptPrint $scriptName "Sleeping for $sleepTimeout seconds to ready resources..." 
sleep $sleepTimeout

/home/aprg/AVMediaStartup/AVMediaStartup.sh
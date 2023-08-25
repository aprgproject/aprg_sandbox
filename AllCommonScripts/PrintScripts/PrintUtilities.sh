#!/bin/bash

scriptPrint() {
    local scriptName="$1"
    local lineNumber="$2"
    local message="$3"
	echo "$scriptName:$lineNumber: $message"
}

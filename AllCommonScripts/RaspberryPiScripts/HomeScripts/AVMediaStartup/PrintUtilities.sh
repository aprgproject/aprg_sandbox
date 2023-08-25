#!/bin/bash

scriptPrint() {
    local scriptName="$1"
    local lineNumber="$2"
    local message="$3"
    echo "$scriptName:$lineNumber: $message"
}

printStringWithEscapeCharacters() {
    local scriptName="$1"
    local lineNumber="$2"
    local str="$3"
    result=""
    for character in $str; do
        if [[ $character == "\n" ]]; then
            result+="/n"
        elif [[ $character == "\r" ]]; then
            result+="/r"
        else
            result+=[$character]
        fi
    done
    echo "$scriptName:$lineNumber: String with escape characters [$result]"
}

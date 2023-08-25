#!/bin/bash

# Set variable values
scriptName=$(basename "$0")
scriptDirectory=$(dirname "$0")
copyCommand=$(realpath "$scriptDirectory/copyFileToSeveralLocations.sh")

$copyCommand cmake/LocateAprgDirectory.cmake
$copyCommand .vscode/launch.json
$copyCommand .vscode/tasks.json
$copyCommand .vscode/locateAprgDirectory.sh$copyCommand .vscode/runWslCommonScript.sh
$copyCommand ProjectDirectory/CMakePresets.json

#!/bin/bash

# Set variables
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")

svn log > "$scriptDirectory/svnRevisionDetails.txt"

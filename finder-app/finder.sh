#!/bin/sh
filesdir="$1"
searchstr="$2"

if [ $# -lt 2 ] || [ -z "$filesdir" ] || [ -z  "$searchstr" ]
then
    echo "Error: program expects 2 arguments: path to directory and search string."
    exit 1
fi

if [ ! -d "$filesdir" ]
then
    echo "Error: ${filesdir} should specify path to an existing directory."
    exit 1
fi

numFiles=$(find "$filesdir" -type f | wc -l)
numSearchResult=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are ${numFiles} and the number of matching lines are ${numSearchResult}"
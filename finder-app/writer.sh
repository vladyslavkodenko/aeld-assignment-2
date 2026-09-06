#!/bin/sh

fileName="$1"
fileContent="$2"

if [ $# -lt 2 ] || [ -z "$fileName" ] || [ -z "$fileContent" ]
then
    echo "Error: program expects 2 arguments: path to a file and file content."
    exit 1
fi

dirName=$(dirname "$fileName")

mkdir -p "$dirName"

echo "$fileContent" > "$fileName"

if [ $? -ne 0 ]
then
    echo "Error: couldn't create or write file $fileName"
    exit 1
fi
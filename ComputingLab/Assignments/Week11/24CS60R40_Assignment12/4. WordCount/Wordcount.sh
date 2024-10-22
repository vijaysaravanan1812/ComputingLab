#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <path> <word>"
    exit 1
fi

if [ ! -f "$1" ]; then
    echo "File not found!"
    exit 1
fi

path=$1
word=$2

totalWords=$(wc -w < "$path")
totalLines=$(wc -l < "$path")
totalChars=$(wc -m < "$path")





wordFrequency=$(grep -o -i "\b$word\b" "$path" | wc -l)


echo "Total Lines: $totalLines"
echo "Total Words: $totalWords"
echo "Total Characters: $totalChars"
echo "Frequency of word '$word': $wordFrequency"

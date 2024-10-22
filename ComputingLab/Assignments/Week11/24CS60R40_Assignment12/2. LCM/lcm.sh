#!/bin/bash


greatestCommonDigit() {
    local number1=$1
    local number2=$2

    while [ $number2 -ne 0 ]; do
    
        local temp=$number2
        number2=$((number1 % number2))
        number1=$temp
    done
    
    echo $number1
}


leastCommonMultiple() {
    local a=$1
    local b=$2
   
    echo $((a * b / $(greatestCommonDigit $a $b)))
}


if [ "$#" -ne 1 ]; then
    echo "Usage: $0 filename"
    exit 1
fi


if [ ! -f "$1" ]; then
    echo "File not found!"
    exit 1
fi


numbers=$(cat "$1")


answer=1
for num in $numbers; do
    answer=$(leastCommonMultiple $answer $num)

done


echo "LCM: $answer"

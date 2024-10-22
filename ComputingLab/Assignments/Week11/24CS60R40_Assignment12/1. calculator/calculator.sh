#!/bin/bash 


if [ "$#" -ne 3 ]; then 
    echo "Invalid argument"
    echo "Usage: $0 <operand1> <operator> <operand2>"
    exit 1

fi


number1=$1
number2=$3

operator=$2


answer=""


case $operator in 
    "+" )
        answer=$(echo "$number1 + $number2" | bc -l)
        echo "Output: $answer"
        ;;
    "-" )
        answer=$(echo "$number1 - $number2" | bc -l)
        echo "Output: $answer"
        ;;
    "*" )
        answer=$(echo "$number1 * $number2" | bc -l)
        echo "Output: $answer"
        
        ;;
    "/" )
        if [ "$number2" -eq 0 ]; then
            echo "division by zero problem"
        else
            answer=$(echo "scale=2; $number1 / $number2" | bc -l)
            echo "output: $answer"
        fi
        ;;
    * )
        echo "unknown operation"
        
        ;;
esac 

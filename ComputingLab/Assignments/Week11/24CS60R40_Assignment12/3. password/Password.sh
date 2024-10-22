#!/bin/bash


if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <password length>"
    exit 1
fi


if [ "$1" -lt 4 ]; then
    echo "Password length must be at least 4."
    exit 1
fi


length=$1

lowercase=$(< /dev/urandom tr -dc 'a-z' | head -c 1)
uppercase=$(< /dev/urandom tr -dc 'A-Z' | head -c 1)
special=$(< /dev/urandom tr -dc '!@#$%^&*()' | head -c 1)
digit=$(< /dev/u=random tr -dc '0-9' | head -c 1)



remaining=$(< /dev/urandom tr -dc 'A-Za-z0-9!@#$%^&*()' | head -c $(($length - 4)))


password="$uppercase$lowercase$digit$special$remaining"


password=$(echo "$password" | fold -w1 | shuf | tr -d '\n')


echo "password: $password"

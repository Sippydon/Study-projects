#!/bin/bash
cd $(dirname $0)

if [ -n "$1" ] && (( $#==1 ))
then
    if [[ $1 =~ ^[0-9+\.+\,]+$ ]]
    then
        echo "Enter the string"
    else
        echo $1
    fi
else
    echo "Error"
fi
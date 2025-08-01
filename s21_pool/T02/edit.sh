#!/bin/bash

path=$1
str1=$2
str2=$3

if [[ -f $path ]] && [[ $str1 != '' ]] && [[ $str2 != '' ]] && [[ $(grep  $str1 $path) ]]
    then
        
        sed -i '' 's/'$str1'/'$str2'/g' $path
    
        date=$(date -r $path +"%Y-%m-%d %H:%M")
        filesize=$(stat -f%z $path)
        sha=$((shasum -a 256 $path) | cut -d ' ' -f 1)

        echo $path '-' $filesize '-' $date '-' $sha '-' 'sha256' >> src/files.log

    else 
        echo "not valid data"
fi

#!bin/bash

path=$1

if [[ -f $path ]]
    then
        numberOfLines=$(wc -l < $path)
        uniqString=$(sed '/^$/d' $path | awk '{print $1}'| sort | uniq -u -d | wc -l)
        uniqChanges=$(wc -l < $path)

        echo $numberOfLines $uniqString $uniqChanges
    else
        echo "data not valid"
fi
#!/bin/bash
cd $(dirname $0)

echo "Do you want to write data in file? (Y/n)"
read answer

chmod +x getsysinfo.sh

if [ $answer = y ] || [ $answer = Y ]; then
    file="$(date +"%d_%m_%g_%H_%M_%S").status"
    touch $file
    (./getsysinfo.sh "$0" "tee -a" "$file")
  else
    (./getsysinfo.sh "$0" "head " "-1")
fi
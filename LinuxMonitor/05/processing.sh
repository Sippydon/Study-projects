#!/bin/bash

##/home/sippydon/s21_projects/C5_s21_decimal-4

START=$(date +%s.%N)

TOTAL_FOLDERS=$(sudo ls -l $1 | grep -c ^d)
TOP_FOLDERS_SIZE=$(sudo du -h $1 | sort -h -r | head -n 5 | awk '{print $1}')
TOP_FOLDERS_NAME=$(sudo du -h $1 | sort -h -r | head -n 5 | awk '{print $2}')
TOTAL_FILES=$(sudo ls -laR $1 | grep "^-" | wc | awk '{print $1}')
CONFIG_FILES=$(sudo find $1 -type f -name "*.conf" | wc -l)
TEXT_FILES=$(sudo find $1 -type f -name "*.txt" | wc -l)
EXE_FILES=$(sudo find $1 -type f -executable | wc -l)
LOG_FILES=$(sudo find $1 -type f -name "*.log" | wc -l)
ZIP_FILES=$(sudo find $1 -type f -name "*.zip" -o -name "*.rar" | wc -l)
LINK_FILES=$(sudo find $1 -type l | wc -l)
TOP_FILES_SIZE=$(sudo find $1 -type f -exec du -h {} + | sort -h -r | head -n 10 | awk '{print $1}')
TOP_FILES_NAME=$(sudo find $1 -type f -exec du -h {} + | sort -h -r | head -n 10 | awk '{print $2}')
TOP_FILES_TYPE=$(sudo find $1 -type f -exec du -h {} + | sort -h -r | head -n 10 | awk '{print $2}' | awk 'BEGIN{FS=OFS="."} {print $NF}')
TOP_EXE_FILES_SIZE=$(sudo find $1 -type f -executable -exec du -h {} + | sort -h -r | head -n 10 | awk '{print $1}')
TOP_EXE_FILES_NAME=$(sudo find $1 -type f -executable -exec du -h {} + | sort -h -r | head -n 10 | awk '{print $2}')

folders_name=($TOP_FOLDERS_NAME)
folders_size=($TOP_FOLDERS_SIZE)
count_fo=$(echo -n "$TOP_FOLDERS_NAME" | grep -c '^')

files_name=($TOP_FILES_NAME)
files_size=($TOP_FILES_SIZE)
files_type=($TOP_FILES_TYPE)
count_fi=$(echo -n "$TOP_FILES_NAME" | grep -c '^')

exe_files_name=($TOP_EXE_FILES_NAME)
exe_files_size=($TOP_EXE_FILES_SIZE)
count_ex=$(echo -n "$TOP_EXE_FILES_NAME" | grep -c '^')
for ((i = 0; i < $count_ex; i++)); do
  exe_files_sum[$i]=$(md5sum ${exe_files_name[$i]} | awk '{print $1}')
done

echo "Total numbers of folders (including all nested ones) = $TOTAL_FOLDERS"

echo "TOP 5 folders of maximum size arranged in descending order (path and size):"
for ((i = 1; i <= $count_fo; i++)); do
  echo "$i - ${folders_name[$i - 1]}, ${folders_size[$i - 1]}"
done

echo "Total number of files = $TOTAL_FILES"
echo -e "Number of:\nConfiguration files (with the .conf extension) = $CONFIG_FILES"
echo "Text files = $TEXT_FILES"
echo "Executable files = $EXE_FILES"
echo "Log files (with the extension .log) = $LOG_FILES"
echo "Archive files = $ZIP_FILES"
echo "Symbolic links = $LINK_FILES"

echo "TOP 10 files of maximum size arranged in descending order (path, size and type):"
for ((i = 1; i <= $count_fi; i++)); do
  echo "$i - ${files_name[$i - 1]}, ${files_size[$i - 1]}, ${files_type[$i - 1]}"
done

echo "TOP 10 executable files of maximum size arranged in descending order (path, size and MD5 hash of file):"
for ((i = 1; i <= count_ex; i++)); do
  echo "$i - ${exe_files_name[$i - 1]}, ${exe_files_size[$i - 1]}, ${exe_files_sum[$i - 1]}"
done

FINISH=$(date +%s.%N)
time=$(echo "$FINISH-$START" | bc)

echo "Script execution time (in second) = 0$time"
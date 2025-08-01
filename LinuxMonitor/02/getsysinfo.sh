#!/bin/bash
cd $(dirname $0)

echo "HOSTNAME =" $(hostname) | $2 $3
echo "TIMEZONE =" $(ls -l /etc/localtime | awk -F'/' '{print $7"/"$8}') "UTC"$(date | awk '{print $7}') | $2 $3
echo "USER =" $USER | $2 $3
echo "OS =" $(cat /etc/issue | cut -d " " -f 1-3) | $2  $3
echo "DATE =" $(date -R | cut -d " " -f 2-5) | $2  $3
echo "UPTIME =" $(uptime -p | awk '{print $3, $3, $5}') | $2  $3
echo "UPTIME_SEC =" $(cat /proc/uptime | awk '{print $2,"sec"}') | $2  $3
echo "IP =" $(netstat -rn | head -4 | tail -1 | awk '{print $2}') | $2  $3
echo "MASK =" $(netstat -rn | head -4 | tail -1 | awk '{print $3}') | $2  $3
echo "GATEWAY =" $(netstat -rn | head -3 | tail -1 | awk '{print $3}') | $2  $3
echo "RAM_TOTAL ="  $(free  |  head -2 | tail -1 | awk '{printf("%.3f", $3/(1024*1024))}') "Gb" | $2  $3
echo "RAM_USED =" $(free  |  head -2 | tail -1 | awk '{printf("%.3f", $3/(1024*1024))}')  "Gb" | $2  $3
echo "RAM_FREE =" $(free  |  head -2 | tail -1 | awk '{printf("%.3f", $4/(1024*1024))}') "Gb" | $2  $3
echo "SPACE_ROOT =" $(df / |  head -2 | tail -1 | awk '{printf("%.2f", $3/1024)}') "Mb" | $2  $3
echo "SPACE_ROOT_USED =" $(df / |  head -2 | tail -1 | awk '{printf("%.2f", $3/1024)}') "Mb" | $2  $3
echo "SPACE_ROOT_FREE =" $(df / |  head -2 | tail -1 | awk '{printf("%.2f", $4/1024)}') "Mb" | $2  $3
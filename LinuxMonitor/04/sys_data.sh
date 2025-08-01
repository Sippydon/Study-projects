#!/bin/bash
SCR_COL=./color.sh
chmod +x color.sh
echo $($SCR_COL $1 $2) "HOSTNAME =" $($SCR_COL $3 $4) $(hostname)  $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "TIMEZONE =" $($SCR_COL $3 $4) $(ls -l /etc/localtime | awk -F'/' '{print $7"/"$8}') $(date | awk '{print $7}') $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "USER =" $($SCR_COL $3 $4) $USER $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "OS =" $($SCR_COL $3 $4) $(cat /etc/issue | cut -d " " -f 1-3) $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "DATE =" $($SCR_COL $3 $4) $(date -R | cut -d " " -f 2-5)  $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "UPTIME =" $($SCR_COL $3 $4) $(uptime -p | awk '{print $2, $3, $5}') $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "UPTIME_SEC =" $($SCR_COL $3 $4) $(cat /proc/uptime | awk '{print $1,"sec"}') $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "IP =" $($SCR_COL $3 $4) $(netstat -rn | head -4 | tail -1 | awk '{print $1}')  $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "MASK =" $($SCR_COL $3 $4) $(netstat -rn | head -4 | tail -1 | awk '{print $3}') $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "GATEWAY =" $($SCR_COL $3 $4) $(netstat -rn | head -3 | tail -1 | awk '{print $2}') $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "RAM_TOTAL ="  $($SCR_COL $3 $4) $(free  |  head -2 | tail -1 | awk '{printf("%.3f", $2/(1024*1024))}') "Gb" $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "RAM_USED =" $($SCR_COL $3 $4) $(free  |  head -2 | tail -1 | awk '{printf("%.3f", $3/(1024*1024))}')  "Gb" $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "RAM_FREE =" $($SCR_COL $3 $4) $(free  |  head -2 | tail -1 | awk '{printf("%.3f", $4/(1024*1024))}') "Gb" $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "SPACE_ROOT =" $($SCR_COL $3 $4) $(df / |  head -2 | tail -1 | awk '{printf("%.2f", $2/1024)}') "Mb" $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "SPACE_ROOT_USED =" $($SCR_COL $3 $4) $(df / |  head -2 | tail -1 | awk '{printf("%.2f", $3/1024)}') "Mb" $($SCR_COL 0 0)
echo $($SCR_COL $1 $2) "SPACE_ROOT_FREE =" $($SCR_COL $3 $4) $(df / |  head -2 | tail -1 | awk '{printf("%.2f", $4/1024)}') "Mb" $($SCR_COL 0 0)

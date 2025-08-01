#!/bin/bash
cd $(dirname $0)
source conf.conf

#Присваивание цветов из конфиг-файла переменным
color[0]=$column1_background
color[1]=$column1_font_color
color[2]=$column2_background
color[3]=$column2_font_color

#Создание массива дефолтных цветов
default[0]=6
default[1]=1
default[2]=2
default[3]=4

#Проверка данных из  конфиг-файла
for (( i = 0; i < 4; i++ ))
do
     if [[ ${color[$i]} =~ ^[1-6$]+$ ]]
        then
            :
        else
            color[$i]=${default[$i]}
        fi
done

#Запуск рабочего скрипта с указанными цветами
chmod +x sys_data.sh
./sys_data.sh ${color[0]} ${color[1]} ${color[2]} ${color[3]}

#Вывод таблицы цветов в конце
arr=(zero white red green blue purple black)
for (( i=0; i<2; i++ ))
do
    echo -n "Column $(( i+1 ))" "background = "
    if [ ${color[($i*2)]} -eq ${default[($i*2)]} ]  
    then
        echo  "default" "(${arr[${color[($i*2)]}]})"
    else
        echo  "${color[($i*2)]}" "(${arr[${color[($i*2)]}]})"
    fi

    echo -n "Column $(( i+1 ))" "font color = "
    if [ ${color[($i*2)+1]} -eq ${default[($i*2)+1]} ]  
    then
        echo  "default" "(${arr[${color[($i*2)+1]}]})"
    else
        echo  "${color[($i*2)+1]}" "(${arr[${color[($i*2)+1]}]})"
    fi
done
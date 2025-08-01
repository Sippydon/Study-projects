## Part 1. Готовый докер
##### Взять официальный докер образ с **nginx** и выкачать его при помощи `docker pull`
![pull_nginx.png](screenshots%2Fpull_nginx.png)  

##### Проверить наличие докер образа через `docker images`
![nginx_image.png](screenshots%2Fnginx_image.png)  
##### Запустить докер образ через `docker run -d [image_id|repository]`
![nginx_run.png](screenshots%2Fnginx_run.png)
```
Для запуска контейнера в отсоединенном режиме используется опция -d=true или просто -d. По замыслу, контейнеры, запущенные в отсоединенном режиме, завершаются при выходе корневого процесса, используемого для запуска контейнера
```
##### Проверить, что образ запустился через `docker ps`
![docker_ps.png](screenshots%2Fdocker_ps.png)
##### Посмотреть информацию о контейнере через `docker inspect [container_id|container_name]`
![docker_inspect.png](screenshots%2Fdocker_inspect.png)
##### По выводу команды определить и поместить в отчёт размер контейнера, список замапленных портов и ip контейнера
* Размер контейнера  
![nginx_container)size.png](screenshots%2Fnginx_container%29size.png)
* Список замапленных портов  
![mapped_ports.png](screenshots%2Fmapped_ports.png)
* IP контейнера  
![container_ip_address.png](screenshots%2Fcontainer_ip_address.png)

##### Остановить докер образ через `docker stop [container_id|container_name]`
##### Проверить, что образ остановился через `docker ps`
![docker_stop_ps.png](screenshots%2Fdocker_stop_ps.png)
##### Запустить докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду *run*
![docker_run_with_mapped_ports.png](screenshots%2Fdocker_run_with_mapped_ports.png)
##### Проверить, что в браузере по адресу *localhost:80* доступна стартовая страница **nginx**
![localhost_80.png](screenshots%2Flocalhost_80.png)
##### Перезапустить докер контейнер через `docker restart [container_id|container_name]`
![docker_restart_nginx.png](screenshots%2Fdocker_restart_nginx.png)
##### Проверить любым способом, что контейнер запустился
![docker_ps_after_restart.png](screenshots%2Fdocker_ps_after_restart.png)

## Part 2. Операции с контейнером
##### Прочитать конфигурационный файл *nginx.conf* внутри докер контейнера через команду *exec*
![nginx_conf.png](screenshots%2Fnginx_conf.png)
##### Создать на локальной машине файл *nginx.conf*
##### Настроить в нем по пути */status* отдачу страницы статуса сервера **nginx**
![create_nginx_conf.png](screenshots%2Fcreate_nginx_conf.png)
##### Скопировать созданный файл *nginx.conf* внутрь докер образа через команду `docker cp`
![cp_nginx_conf.png](screenshots%2Fcp_nginx_conf.png)
##### Перезапустить **nginx** внутри докер образа через команду *exec*
![nginx_reload.png](screenshots%2Fnginx_reload.png)
##### Проверить, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**
![localcgost_status.png](screenshots%2Flocalcgost_status.png)
##### Экспортировать контейнер в файл *container.tar* через команду *export*
##### Остановить контейнер
![docker_export_stop.png](screenshots%2Fdocker_export_stop.png)
##### Удалить образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры
![docker_rmi_f.png](screenshots%2Fdocker_rmi_f.png)
##### Удалить остановленный контейнер
![docker_rm_container.png](screenshots%2Fdocker_rm_container.png)
##### Импортировать контейнер обратно через команду *import*
![docker_import.png](screenshots%2Fdocker_import.png)
##### Запустить импортированный контейнер
![docker_run_import_container.png](screenshots%2Fdocker_run_import_container.png)
##### Проверить, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**
![local_status_import_container.png](screenshots%2Flocal_status_import_container.png)


## Part 3. Мини веб-сервер
##### Написать мини сервер на **C** и **FastCgi**, который будет возвращать простейшую страничку с надписью `Hello World!`
![server_c.png](screenshots%2Fserver_c.png)  
![nginx_conf_part3.png](screenshots%2Fnginx_conf_part3.png)
##### Запустить написанный мини сервер через *spawn-fcgi* на порту 8080
* Запускаем контейнер на выбранном порту(у меня это 81) -> перекидываем конфиг и сервер -> перезагружаем nginx в контейнере
![cp_and_reload.png](screenshots%2Fcp_and_reload.png)
* подключаемся к bash в контейнере
![bash_container.png](screenshots%2Fbash_container.png)
* обновляем систему и устанавливаем необходимые для запуска FastCGI утилиты `gcc`, `spawn-fcgi`, `libfcgi-dev`
![apt_install.png](screenshots%2Fapt_install.png)
* компилируем и запускаем сервер на порту 8080  
![compile_and_run.png](screenshots%2Fcompile_and_run.png)
* проверяем, что все работает  
![localhost_81.png](screenshots%2Flocalhost_81.png)

## Part 4. Свой докер
#### Написать свой докер образ, который:
##### 1) собирает исходники мини сервера на FastCgi из [Части 3](#part-3-мини-веб-сервер)
##### 2) запускает его на 8080 порту
##### 3) копирует внутрь образа написанный *./nginx/nginx.conf*
##### 4) запускает **nginx**.
* пишем Dockerfile, который будет запускать наш контейнер  
![script_part4.png](screenshots%2Fscript_part4.png)
* пишем небольшой скрипт, который запускает сервер после развертывания контейнера
![dockerfile_part4.png](screenshots%2Fdockerfile_part4.png)
* собираем написанный образ Docker
![build_image.png](screenshots%2Fbuild_image.png)


##### Запустить собранный докер образ с маппингом 81 порта на 80 на локальной машине и маппингом папки *./nginx* внутрь контейнера по адресу, где лежат конфигурационные файлы **nginx**'а (см. [Часть 2](#part-2-операции-с-контейнером))
##### Проверить, что по localhost:80 доступна страничка написанного мини сервера
![docker_run_part4.png](screenshots%2Fdocker_run_part4.png)
##### Дописать в *./nginx/nginx.conf* проксирование странички */status*, по которой надо отдавать статус сервера **nginx**
![part4_status_conf.png](screenshots%2Fpart4_status_conf.png)
##### Перезапустить докер образ
*Если всё сделано верно, то, после сохранения файла и перезапуска контейнера, конфигурационный файл внутри докер образа должен обновиться самостоятельно без лишних действий*
##### Проверить, что теперь по *localhost:80/status* отдается страничка со статусом **nginx**
![part4_restar_docker_container.png](screenshots%2Fpart4_restar_docker_container.png)


## Part 5. **Dockle**

##### Просканировать образ из предыдущего задания через `dockle [image_id|repository]`
![part5_dockle_notdone.png](screenshots%2Fpart5_dockle_notdone.png)
##### Исправить образ так, чтобы при проверке через **dockle** не было ошибок и предупреждений
![part5_dockly_done.png](screenshots%2Fpart5_dockly_done.png)

## Part 6. Базовый **Docker Compose**

##### Написать файл *docker-compose.yml*, с помощью которого:
##### 1) Поднять докер контейнер из [Части 5](#part-5-инструмент-dockle) _(он должен работать в локальной сети, т.е. не нужно использовать инструкцию **EXPOSE** и мапить порты на локальную машину)_
![part6_compose_1.png](screenshots%2Fpart6_compose_1.png)
##### 2) Поднять докер контейнер с **nginx**, который будет проксировать все запросы с 8080 порта на 81 порт первого контейнера
![part6_compose_2.png](screenshots%2Fpart6_compose_2.png)
##### Замапить 8080 порт второго контейнера на 80 порт локальной машины
![part6_compose_3.png](screenshots%2Fpart6_compose_3.png)

##### Остановить все запущенные контейнеры
![part6_compose_4.png](screenshots%2Fpart6_compose_4.png)
##### Собрать и запустить проект с помощью команд `docker-compose build` и `docker-compose up`
![part6_copmose_5.png](screenshots%2Fpart6_copmose_5.png)  
![part6_compose_6.png](screenshots%2Fpart6_compose_6.png)
##### Проверить, что в браузере по *localhost:80* отдается написанная вами страничка, как и ранее
![part6_compose_7.png](screenshots%2Fpart6_compose_7.png)
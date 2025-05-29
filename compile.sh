#!/bin/bash
CONTAINER_NAME=TPE-ARQUI-1C2025

docker start $CONTAINER_NAME
docker exec -it $CONTAINER_NAME make clean -C /root/Toolchain
docker exec -it $CONTAINER_NAME make clean -C /root
docker exec -it $CONTAINER_NAME make -C /root/Toolchain
docker exec -it $CONTAINER_NAME make -C /root
#docker stop tpe2


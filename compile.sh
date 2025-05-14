#!/bin/bash

CONTAINER_NAME=TP5

docker start $CONTAINER_NAME

docker exec -it $CONTAINER_NAME make clean -C /root/Toolchain
docker exec -it $CONTAINER_NAME make clean -C /root

docker exec -it $CONTAINER_NAME make -C /root/Toolchain

docker exec -it $CONTAINER_NAME make -C /root

docker stop $CONTAINER_NAME
#!/bin/bash

docker start tpe2
docker exec -u $USER -it tpe2 make clean -C/root/Toolchain
docker exec -u $USER -it tpe2 make clean -C/root/
docker exec -u $USER -it tpe2 make -C/root/Toolchain
docker exec -u $USER -it tpe2 make -C/root/
#docker stop tpe2


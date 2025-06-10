#!/bin/bash

if [ "$1" = "-d" ]; then
sudo qemu-system-x86_64 -s -S -hda Image/x64BareBonesImage.qcow2 -m 512
else
sudo qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512

#sudo -E qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev sdl,id=snd0 -machine pcspk-audiodev=snd0
fi

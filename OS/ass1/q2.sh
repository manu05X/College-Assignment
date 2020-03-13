#!/bin/bash

FILE=/home/usr/student/ug/yr17/be1757/os/ass1
echo $PATH
export PATH="${PATH:+${PATH}:}$PWD"
echo ${PATH}

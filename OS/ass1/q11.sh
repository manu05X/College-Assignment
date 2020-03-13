#!/bin/bash

PATHS=$(find $HOME -name '*.c')

for filepath in $PATHS
do
	ln -s $filepath $HOME/os/ass1/backup
done

#!/bin/bash
COMMAND = $1
stty -F /dev/tty0 9600 cs8 -cstopb -parenb
echo COMMAND > /dev/tty0
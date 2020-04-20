#!/bin/sh
echo -e "======================================================="
echo -e "First script\n"
echo -e "Print working directory"
pwd
echo -e "\nCurrent date and time"
date '+%d/%m/%Y_%H:%M:%S'
echo -e "\nThe contents of the PATH environment variable"
echo $PATH
echo -e "======================================================="
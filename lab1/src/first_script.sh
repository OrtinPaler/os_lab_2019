#!/bin/sh
echo
echo -e "First script\n"
echo -e "Print working directory\n"
pwd
echo -e "\nCurrent date and time\n"
date '+%d/%m/%Y_%H:%M:%S'
echo -e "\nThe contents of the PATH environment variable\n"
echo $PATH
echo
#!/bin/sh
if [ -n "$1" ]
then
echo There were $# parameters passed.
for var in $@
do
sum=$[$sum+$var]
done
echo Average: $[$sum/$#]
else
echo "No parameters found."
fi

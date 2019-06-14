#! /bin/bash

for i in $(seq 1 9)
do
	touch in0$i.txt
	touch out0$i.txt
done
touch in10.txt
touch out10.txt

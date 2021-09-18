#!/bin/bash 
# 清理

make clean -C ../src

rm -f *.s *.kpatch *.stripped

for f in $(ls) 
do
	if [ `file $f | awk '{print $2}'` = "ELF" ]; then 
		echo delete ELF file $f;
		rm -f $f
	fi
done

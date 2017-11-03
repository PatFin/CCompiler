#!/bin/bash
for i in *.c
do
    name=`basename $i .c`
    echo "CCompiler.exe -c $name.s <$i"
    ./../bin/CCompiler.exe -c $name.s <$i
    echo "gcc -static -o $name.exe $name.s"
    gcc -static -o $name.exe $name.s
    echo "-----------------------------"
done

#!/bin/bash

make std
./test_ft_containers > ./std_compare/std.out
make
./test_ft_containers > ./std_compare/ft.out

DIFF="$(diff ./std_compare/std.out ./std_compare/ft.out | wc -l)"
zero=0

if [[ $DIFF -ne $zero ]]
then
	diff ./std_compare/std.out ./std_compare/ft.out > ./std_compare/diff.out
	cat ./std_compare/diff.out
fi
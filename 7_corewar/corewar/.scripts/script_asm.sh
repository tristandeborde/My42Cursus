#!/bin/sh

for file in ./../resources/champs/*.s; do
	echo "-------CHAMP="${file##*/}"--------"
	echo "asm of Zaz"
	./../resources/asm $file
	hexdump "${file%.*}".cor > log1.txt
	echo "our asm"
	./asm $file
	hexdump "${file%.*}".cor > log2.txt
	res=$(diff log1.txt log2.txt)
	rm log2.txt log1.txt
	if [[ -z "$res" ]]
	then echo "Output are the same, congrats\n"
	else
		echo "$res"
	fi
done

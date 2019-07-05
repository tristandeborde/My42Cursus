if [ -z "$1" ]; 
then 
	echo "./test.sh <player> [<nb of cycle>]"; 
	echo "Player must be just 'Car' and not 'Car.cor'"
	echo "If you dont specify [<nb of cycle>], last possible is chosen"
else
	if [ -z "$2" ]
	then
		A2=$(( $(./../resources/corewar -v 30 $1 | grep "It is" | tail -n 1 | cut -d ' ' -f 5)-1 ))
	else
		A2=$2
	fi
	./../resources/corewar -d $A2 -v 30 $1 | tail -n 64 > .b
	if ! [[ $(cat .b | grep cycles | wc -l) -eq 0 ]]
	then
		A2=$(( $(./../resources/corewar -v 30 $1 | grep "It is" | tail -n 1 | cut -d ' ' -f 5)-1 ))
		./../resources/corewar -d $A2 -v 30 $1 | tail -n 64 > .b
	fi
	echo "cycle: $A2"
	./corewar -dump $A2 -n '-1' $1 | grep -A 63 '0x0000' > .a
	res=$(diff .a .b)
	if [[ -z "$res" ]]
	then
		echo "Output are the same, congrats"
		if [ -z "$2" ]
		then
			./../resources/corewar -v 30 $1 | tail -n 1
			./corewar -n '-1' $1 | tail -n 2
		fi
	else
		echo "$res"
	fi
	rm .a .b
fi

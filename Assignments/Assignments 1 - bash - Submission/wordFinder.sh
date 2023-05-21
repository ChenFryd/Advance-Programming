#!/bin/bash

if [[ $# < 3 ]]; then
	echo "Number of parameters received : $#" >&2
	echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>"
elif [[ $# > 2 ]]; then
	#we got 3 arguments
	array=($@)
	argLast=(${array[-1]})
	argOneBeforeLast=$(echo ${array[-2]} | tr [:upper:] [:lower:]) 
	argAmountFiles=$(( $#-2 ))
	if [[ "$argOneBeforeLast" =~ [a-zA-Z0-9] && ${#argOneBeforeLast} == 1 ]]; then
	#the second argument 
		if [[ "$argLast" =~ [0-9] && "$argLast" -gt 0 ]]; then
			#file syste
			touch outputfile.txt			
			for (( c=0; c<$argAmountFiles; c++ ))
			do
				if [[ -e ${array[$c]} ]]; then
					argLocFile=${array[$c]}
					cat $argLocFile | tr -c -s '[:alnum:]' ' ' >> outputfile.txt
				elif [[ -e "`pwd`/${array[$c]}" ]]; then
					argLocFile=${`pwd`/${array[$c]}}
					cat $argLocFile | tr -c -s '[:alnum:]' ' ' >> outputfile.txt
				else
					echo "File does not exist : ${array[$c]}" >&2
					echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>"
					rm outputfile.txt
					break
				fi
			done
			if [[ -e outputfile.txt ]]; then
				argLastMinusOne=$(( $argLast-1 ))
				cat outputfile.txt | tr [:upper:] [:lower:] | tr -s ' ' '\n' | grep -E "^$argOneBeforeLast.{$argLastMinusOne,}$"  | sort -f | uniq -c | sed 's/^ *//' | sort -n 
				rm outputfile.txt
			fi
		else
			echo "Not a positive number : $argLast" >&2
			echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>"
		fi
	else
	 #we got a number
		echo "Only one char needed : $argOneBeforeLast" >&2
		if ! [[ $argLast =~ [0-9] && $argLast -gt 0 ]]; then
			echo "Not a positive number : $argLast" >&2
		fi
		echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>"
        fi
fi

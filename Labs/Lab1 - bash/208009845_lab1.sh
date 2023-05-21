#!/bin/bash
# Comments start with "#" sign 

# Directory name variable
WORKING_DIR=".pb"

# File name variable
DATA="$WORKING_DIR/phonebook" 

# Create the directory here:
mkdir "$WORKING_DIR"
echo "1"
# Creates the file here: (this file will contain the phonebook registries)
if [ ! -e $DATA ]; then
	touch "$DATA"
fi
echo "2"
# The main-menu function - 
# an endless loop that prints the menu, gets input from user and 
# call the appropiate functions. 
addRecord()
{
	echo "got addr"
	read -p	"Name: " name;
	read -p "Number: " num;
	REC=("$name $num")
	echo "$REC">>"$DATA"
	echo "entered the data"
	sleep 2
}
searchRecord()
{
	read -p "search: " search
	if [ -z $search ]; then
		echo "INVALID SEARCH"

	else
		found=`grep "$search" "$DATA"`;
		if [ -z "$search" ];then
			echo "there is no $search in the pb"
		else
			echo "$found"
		fi
	fi
	sleep 2
}
viewRecords()
{
	echo "phone book:"
	cat $DATA
	sleep 2
}

eraseRecords()
{
	read -p "Are you sure you want to delete all the phone book? Enter Y/y " usrInput;
	if [[ $usrInput == "Y" || $usrInput == "y" ]];then
		rm $DATA
		echo "Phonebook deleted"
	else
		echo "Phonebook not deleted"
	fi
	sleep 2
	
}
mainMenu(){
	while true; do 
		clear;
		echo "**************"
		echo "Phonebook App"
		echo "**************"
		echo "Please select an option"
		echo "a) add a record "
		echo "s) search a record "
		echo "v) view all records "
		echo "d) delete a record "
		echo "e) erase all records "
		echo "q) quit "
		read -p 'Option:' -n 1 option
		# drops one line
		echo ""

		# That's how a 'switch'	looks like in bash
		case $option in
			a) addRecord ;;
			s) searchRecord ;;
			v) viewRecords ;;
			d) deleteRecord ;;
			e) eraseRecords ;;
			q) exit ;;
			*) echo "Please type a valid option" ; sleep 1 ;; 
		esac
	done
}
mainMenu


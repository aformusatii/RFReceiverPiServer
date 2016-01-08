case $1 in
	24) mpc volume +1 > /dev/null 2>&1;;
	25) mpc volume -1 > /dev/null 2>&1;;
	20) mpc stop > /dev/null 2>&1;;
	21) mpc play > /dev/null 2>&1;;
	23) mpc pause > /dev/null 2>&1;;
	27) mpc next > /dev/null 2>&1;;
	28) mpc prev > /dev/null 2>&1;;
	8) echo "eight" ;;
	9) echo "nine" ;;
	10) echo "ten" ;;
	*) echo "INVALID NUMBER!" ;;
esac


case $1 in
	24) mpc volume +1;;
	25) mpc volume -1;;
	20) mpc stop;;
	21) mpc play;;
	23) mpc pause;;
	27) mpc next;;
	28) mpc prev;;
	8) echo "eight" ;;
	9) echo "nine" ;;
	10) echo "ten" ;;
	*) echo "INVALID NUMBER!" ;;
esac


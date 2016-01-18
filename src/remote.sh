case $1 in
	24) mpc volume +1 > /dev/null 2>&1;;
	25) mpc volume -1 > /dev/null 2>&1;;
	20) mpc stop > /dev/null 2>&1;;
	21) mpc play > /dev/null 2>&1;;
	23) mpc pause > /dev/null 2>&1;;
	27) mpc next > /dev/null 2>&1;;
	28) mpc prev > /dev/null 2>&1;;
	18) mpc seek -1% > /dev/null 2>&1;;
	19) mpc seek +1% > /dev/null 2>&1;;
	10) echo "ten" ;;
         6) /home/pi/repository/PiSocketClient/src/socketClient 192.168.1.120 1 1 1;;
         5) /home/pi/repository/PiSocketClient/src/socketClient 192.168.1.120 255 255 255;;
         4) /home/pi/repository/PiSocketClient/src/socketClient 192.168.1.120 50 5 0;;
         3) /home/pi/repository/PiSocketClient/src/socketClient 192.168.1.120 0 0 0;;
	*) echo "INVALID NUMBER!" ;;
esac


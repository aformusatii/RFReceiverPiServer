
case $1 in
	24) /home/pi/repository/PiSocketClient/src/socketClient 192.168.1.120 116 100 0;;
	25) /home/pi/repository/PiSocketClient/src/socketClient 192.168.1.120 116 101 0;;
	20) mpc stop > /dev/null 2>&1;;
	21) mpc play $(cat key_buf.txt);echo -n '' > key_buf.txt;;
	23) mpc pause > /dev/null 2>&1;;
	27) mpc next > /dev/null 2>&1;;
	28) mpc prev > /dev/null 2>&1;;
	18) mpc seek -1% > /dev/null 2>&1;;
	19) mpc seek +1% > /dev/null 2>&1;;
        30) /home/pi/repository/PiSocketClient/src/socketClient 192.168.1.120 115 1 1 1;;
        31) /home/pi/repository/PiSocketClient/src/socketClient 192.168.1.120 115 255 255 255;;
        32) /home/pi/repository/PiSocketClient/src/socketClient 192.168.1.120 115 50 5 0;;
         3) /home/pi/repository/PiSocketClient/src/socketClient 192.168.1.120 115 0 0 0;;
        14) echo -n '0' >> key_buf.txt;;
         4) echo -n '1' >> key_buf.txt;;
         5) echo -n '2' >> key_buf.txt;;
         6) echo -n '3' >> key_buf.txt;;
         7) echo -n '4' >> key_buf.txt;;
         8) echo -n '5' >> key_buf.txt;;
         9) echo -n '6' >> key_buf.txt;;
        10) echo -n '7' >> key_buf.txt;;
        11) echo -n '8' >> key_buf.txt;;
        12) echo -n '9' >> key_buf.txt;;
        13) echo -n '' > key_buf.txt;;
	*) echo "INVALID NUMBER!" ;;
esac


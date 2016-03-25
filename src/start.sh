#!/bin/bash
cd "$(dirname "$0")"

sudo ./receiver > receiver.log 2>&1 &
ps aux | grep receiver
echo Started NRF24L01 receiver.

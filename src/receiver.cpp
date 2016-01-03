/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include "../nrf24l01/RF24.h"

volatile int listen_enabled = 0;
RF24 radio;
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
void loop();

int main(int argc, char** argv)
{

  printf("Start NRF24L01P test...\n");

  radio.begin();
  radio.setRetries(15,15);
  radio.setPayloadSize(8);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(110);

  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);

  radio.startListening();

  radio.printDetails();

  listen_enabled = 1;

  fflush(stdout);

  while (1) {
	  //loop();
     sleep(5);
  }

  return 0;
}

void loop() {
    while (!radio.available()) {
    }

	uint8_t data[] = {0, 0};
    radio.read(data, 2);

    // Spew it
    //printf("Data: %i, %i\n\r", data[0], data[1]);
    int16_t temp_int_rec = (int16_t) (((data[0] & 0x00FF) << 8) | (data[1] & 0x00FF));
    printf("\n temp_int_rec=%d", temp_int_rec);
}

void dataReceivedIRQ() {
    if (!listen_enabled) {
    	return;
    }

    bool tx_ok, tx_fail, rx_ok;
    radio.whatHappened(tx_ok,tx_fail,rx_ok);

    printf("\nIRQ!");

    //while (!radio.available()) {
    //}

    if (rx_ok) {
		uint8_t data[] = {0, 0, 0, 0};
		radio.read(data, 4);

		if (data[0] == 100) {
                    // Spew it
                    int16_t temp_int_rec = (int16_t) (((data[2] & 0x00FF) << 8) | (data[3] & 0x00FF));
                    printf("\n temp_int_rec=%d", temp_int_rec);

                    char buffer[255];
                    sprintf(buffer, "./save.sh %d %d", data[1], temp_int_rec);
                    system(buffer);
		}
    }

    fflush(stdout);
}

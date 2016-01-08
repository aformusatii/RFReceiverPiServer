/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include "../nrf24l01/RF24.h"

volatile int irq_enabled = 0;
RF24 radio;
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

int main(int argc, char** argv) {

    printf("Start NRF24L01P test...\n");

    radio.begin();
    radio.setRetries(15, 15);
    radio.setPayloadSize(8);
    radio.setPALevel(RF24_PA_MAX);
    radio.setChannel(110);

    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1, pipes[1]);

    radio.startListening();

    radio.printDetails();

    irq_enabled = 1;

    fflush(stdout);

    while (1) {
        sleep(5);
    }

    return 0;
}

void dataReceivedIRQ() {
    if (!irq_enabled) {
        return;
    }

    bool tx_ok, tx_fail, rx_ok;
    radio.whatHappened(tx_ok, tx_fail, rx_ok);

    printf("\nIRQ!");

    if (rx_ok) {
        uint8_t data[] = { 0 };
        radio.read(data, 1);

        if (data[0] == 100) {
            uint8_t temp_data[] = { 0, 0, 0 };
            radio.read(temp_data, 3);

            // Spew it
            int16_t temp_int_rec = (int16_t) (((temp_data[1] & 0x00FF) << 8)
                    | (temp_data[2] & 0x00FF));
            printf("\nT=%d", temp_int_rec);

            char cmd[255];
            sprintf(cmd, "./save.sh %d %d", temp_data[0], temp_int_rec);
            system(cmd);

        } else {
            printf("\nIR -> [%d]", data[0]);
        }

        while (radio.available()) {
            uint8_t buff[] = { 0 };
            radio.read(buff, 1);
            printf("\n[%d]", buff[0]);
        }
    }

    fflush(stdout);
}

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

        uint8_t data[50];
        uint8_t len = radio.getDynamicPayloadSize();
        radio.read(data, len);

        if (data[0] == 100) {
            int16_t value_int_rec = (int16_t) (((data[3] & 0x00FF) << 8) | (data[4] & 0x00FF));
            printf("\nSensor=%d, Type=%d, Value=%d", data[1], data[2], value_int_rec);

            char cmd[255];
            sprintf(cmd, "./save.sh %d %d %d &", data[1], data[2], value_int_rec);
            system(cmd);

        } else {
            printf("\n[%d]", data[0]);
            char cmd[255];
            sprintf(cmd, "./remote.sh %d &", data[0]);
            system(cmd);
        }

        radio.flush_rx();
    }

    fflush(stdout);
}

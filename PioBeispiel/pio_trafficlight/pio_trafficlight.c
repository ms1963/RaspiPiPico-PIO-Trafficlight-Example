/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_trafficlight.pio.h"


const uint freq = 2029;
const uint pin = 17;
const uint pincount = 4;
// Pattern = 0x8C1 GYRW
const uint32_t pattern =  0x48634863; 
//WRYG or GYRW
const uint32_t delay = 200;

int main() {
    stdio_init_all();
    setup_default_uart();

    // Wir verwenden pio0
    PIO pio = pio0;
    // Programm zum Programmspeicher hinzufügen => offset
    uint offset = pio_add_program(pio, &trafficlight_program);
    printf("Programm geladen an Adresse %d\n", offset);
    // Frei verfügbare Zustandsmaschine akquirieren
    int sm = pio_claim_unused_sm(pio, true);
    // Initialisieren der Zustandsmaschine
    trafficlight_program_init(pio, sm, offset, pin, pincount, freq);
    // starten
  
    pio_sm_put(pio, sm, delay);
    sleep_ms(500); 
    pio_sm_put(pio, sm, pattern);
    sleep_ms(1000000); // Schlafen für 4 Minuten
    pio_sm_set_pins(pio, sm, 0); // Alle Pins auf Low
    pio_sm_set_enabled(pio, sm, false); // SM stoppen
}


#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_trafficlight.pio.h"


const uint freq =     2029;  // Gewünschte Frequenz der Zustandsmaschine
const uint pin      =   17;  // Start-Pin 
const uint pincount =    4;  // Zahl der Ausgabe-Pins
                                       //     ==> RIGHT SHIFT ==>
                                       // 2 x GYRW GYRW GYRW GYRW ... LEDs          
const uint32_t pattern =  0x48634863;  // 2 x 0100 1000 0110 0011 ... LEDs

const uint32_t delay = 200; // initiales Zeit für Gelb-Phasen

int main() {
    setup_default_uart();

    // Wir verwenden pio0
    PIO pio = pio0;
    // Programm zum Programmspeicher hinzufügen => offset
    uint offset = pio_add_program(pio, &trafficlight_program);
    printf("Programm geladen an Adresse %d\n", offset);
    // Frei verfügbare Zustandsmaschine akquirieren
    int sm = pio_claim_unused_sm(pio, true);
    // Initialisieren und Konfigurieren der Zustandsmaschine
    trafficlight_program_init(pio, sm, offset, pin, pincount, freq);
 
    // Delay an TX-FIFO der Zustandsmaschine übergeben
    pio_sm_put(pio, sm, delay);
    // Bisschen warten
    sleep_ms(500); 
    // Bitmuster zum LED-Schalten an Zustandsmaschine übergeben
    pio_sm_put(pio, sm, pattern);
    sleep_ms(1000000); // Lange laufen lassen
    pio_sm_set_pins(pio, sm, 0); // Alle Pins auf Low
    pio_sm_set_enabled(pio, sm, false); // Zustandsmaschine stoppen
}


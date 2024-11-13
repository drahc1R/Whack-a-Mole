// GPIO app
//
// Uses MMIO to control GPIO pins

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"
#include "gpio.h"

int main(void) {
  printf("Board started!\n");

  // Turn on all LEDs on the back of the Microbit
  // Add code here

  // The Microphone LED is Port 0, Pin 20 and is active high
  // You will need to write to the DIR and OUT registers (in that order)

  // Write to the DIR register: set Pin 20 as output by
  *(uint32_t*)(0x50000514) |= (1 << 20);

  // Write to the OUT register: set Pin 20 high to turn on the LED
  *(uint32_t*)(0x50000504) |= (1 << 20);

  // Control LED with raw MMIO
  // Microphone LED is P0.20 and active high
  // Add code here

  void conf() {
    // ROW1	- P0.21
    // ROW2 - P0.22
    // ROW3 - P0.15
    // ROW4 - P0.24
    // ROW5 - P0.19
    // COL1	- P0.28
    // COL2	- P0.11
    // COL3	- P0.31
    // COL4	- P1.05 (i.e., pin number 37)
    // COL5	- P0.30

    // ====== part 13 ======
    // config the LEDs
    gpio_config(LED_MIC, 1);
    gpio_clear(LED_MIC);
    gpio_config(21, 1);
    gpio_config(22, 1);
    gpio_config(15, 1);
    gpio_config(24, 1);
    gpio_config(19, 1);
    gpio_config(28, 1);
    gpio_config(11, 1);
    gpio_config(31, 1);
    gpio_config(37, 1);
    gpio_config(30, 1);

    // config the buttons
    gpio_config(BTN_A, 0); // A
    gpio_config(BTN_B, 0); // B
    NRF_GPIO->PIN_CNF[14] &= (0 << 1);
    NRF_GPIO->PIN_CNF[23] &= (0 << 1);
  }
  
  conf();

  // loop forever
  while (1) {
    printf("Looping\n");
    // Control LED with buttons
    // Button A is P0.14 and active low
    // Button B is P0.23 and active low
    // Add code here
    nrf_delay_ms(100);

    bool btn_a_state = gpio_read(BTN_A);
    bool btn_b_state = gpio_read(BTN_B);
    printf("LED_MIC: %d\n", gpio_read(LED_MIC));
    printf("BTN_A: %d\n", gpio_read(BTN_A));
    printf("BTN_B: %d\n", gpio_read(BTN_B));

    // part 13
    if (!btn_a_state) { // button pressed when state is 0 bc active low
        gpio_set(LED_MIC);
    } else if (!btn_b_state) {
        gpio_clear(LED_MIC);
    }

    //  ====== part 12 ======

    // gpio_set(21); // uncomment this for part 12
    // gpio_set(22);
    // gpio_set(15);
    // gpio_set(24);
    // gpio_set(19);

    // gpio_clear(28);
    // gpio_clear(11);
    // gpio_clear(31);
    // gpio_clear(37);
    // gpio_clear(30);

    // nrf_delay_us(100); 

    // ====== interrupt checkpoint ======
    // gpio_print(); // uncomment this for the interrupt

  }
}
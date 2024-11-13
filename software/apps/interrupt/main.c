// Interrupt app
//
// Trigger GPIO and Software interrupts

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"

// Initialize software interrupts
void software_interrupt_init(void) {
  NRF_EGU1->INTENSET = 0x1;
  NVIC_EnableIRQ(SWI1_EGU1_IRQn);
}

// Trigger a software interrupt
void software_interrupt_trigger(void) {
  NRF_EGU1->TASKS_TRIGGER[0] = 1;

  printf("Trigger software interrupt\n");
  nrf_delay_ms(5000);
  printf("After sleep inside the interrupt.\n");


}

void SWI1_EGU1_IRQHandler(void) {
  // Clear interrupt event
  NRF_EGU1->EVENTS_TRIGGERED[0] = 0;

  // Implement me
}

void GPIOTE_IRQHandler(void) {
  // Clear interrupt event
  NRF_GPIOTE->EVENTS_IN[0] = 0;
  printf("Interrupted!!!\n");
  

  // Implement me
}

int main(void) {
  printf("Board started!\n");

  // First task. Trigger a GPIOTE interrupt
  // You can access the GPIOTE register map as NRF_GPIOTE->
  //    where the register name in all caps goes after the arrow.
  //    For example, NRF_GPIOTE->CONFIG[0]
  // Add code here

  //  0000 0000 0000 0010 000 01101 000000 01;
  //  e               d    c    b            a
  // uint32_t bitMask = 0b 0000 0000 0000 0010 000 01110 000000 01;
  uint32_t bitMask = 0x20E01;

  NRF_GPIOTE->CONFIG[0] = bitMask | NRF_GPIOTE->CONFIG[0];

  // Stuff above should ideally do the stuff below
  // NRF_GPIOTE->CONFIG[0].MODE = 1  ;

  // NRF_GPIOTE->CONFIG[0].PSEL = 13;
  // NRF_GPIOTE->CONFIG[0].PORT = 0;
  // // Set the event
  // NRF_GPIOTE->CONFIG[0].POLARITY = 2;

  // LEAVE OUTINIT in default state
  // NRF_GPIOTE->CONFIG[0].OUTINIT = 2;

  // enables interrupts for register 0 (CONFIG[0])
  NRF_GPIOTE->INTENSET = NRF_GPIOTE->INTENSET | 0x1;

  NVIC_SetPriority(GPIOTE_IRQn, 0);
  NVIC_EnableIRQ(GPIOTE_IRQn);

  // Task (output), Event (input), Disabled
  // Polarity
    // Low to high
    // High to low
    // Toggle



  // Second task. Trigger a software interrupt
  // Use the software_interupt_* functions defined above
  // Add code here




  // loop forever
  while (1) {
    printf("Looping\n");
    nrf_delay_ms(1000);

      for (int i = 0; i < 5; i++) {
        software_interrupt_init();
        software_interrupt_trigger();
        nrf_delay_ms(5000);
      }

  }
}


#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "Systick.h"
#include "ADC.h"


void Systick_init(){

        //initializing Systick timer interrupts every 1/30 secs //

    NVIC_ST_RELOAD_R = 2666667 ;       //reload with period that's equivalent to 1/30 secs
    NVIC_ST_CURRENT_R = 0 ;       //clearing any value in the current register
    NVIC_PRI3_R = 0x00000000;     //setting the interrupt priority to 0 (highest priority) in PRI3 register.
    NVIC_ST_CTRL_R = 0x07 ;       //enabling systick timer,interrupts and picking the system clock

    }

void Systick_Handler(){


     ADC_value = ADC_Value_Calculator(); // capture an ADC sample



}

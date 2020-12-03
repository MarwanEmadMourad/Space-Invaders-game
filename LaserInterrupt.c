#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "ADC.h"
#include "GameEngine.h"
#include "LaserInterrupt.h"

FireFlag = 0 ;
Restart = 0 ;

void PORTB_init(){


       SYSCTL_RCGCGPIO_R |= 0x00000002 ;                  // initializing clock to port B
       GPIO_PORTB_LOCK_R = 0x4C4F434B;                    // unlock GPIO Port B
       GPIO_PORTB_CR_R  |= 0xFF;                          // allow changes to PB7-0
       GPIO_PORTB_DEN_R |= 0x000000A0 ;                   // setting digital enable on PB5,PB7
       GPIO_PORTB_DIR_R &= ~0x000000A0;                   // setting PB5,PB7 as i/p

       GPIO_PORTB_PCTL_R  &= 0x00 ;                       // disable alternative functions on PORTB
       GPIO_PORTB_AFSEL_R &= 0x00000000;                  // also disabling alternative functions
       GPIO_PORTB_AMSEL_R &= 0x00 ;                       // disabling any analog input or output
}

void PORTB_interrupt_enable(){

            /* activating interrupts on PB5,PB7 (2 switches) */

      GPIO_PORTB_IS_R  &= ~ 0X000000A0 ;                   //adjusting interrupt sense register to be edge sensitive
      GPIO_PORTB_IBE_R &= ~0xA0 ;                          //PB5,PB7 are not triggered on both edges
      GPIO_PORTB_IEV_R &= ~ 0X000000A0 ;                   //adjusting interrupt event to be active on the falling edge
      GPIO_PORTB_ICR_R |= 0xA0 ;                           //setting bits 6,7 in ICR to clear the trigger flag
      GPIO_PORTB_IM_R  |= 0x000000A0   ;                   //allow PC6 & PC7 to interrupt the controller
      NVIC_EN0_R |= 0x00000002   ;                         //setting bit 1 in NVIC-EN0 to enable interrupts on port B
      NVIC_PRI0_R = 0x00000000 ;                           //setting priority to 1st priority

}

void GPIOPortB_Handler(){

    if ( GPIO_PORTB_DATA_R & 0x80 )              //Restart Button is pressed
        {
            GPIO_PORTB_ICR_R |= 0xA0;            //setting bits 5,7 in ICR to clear the trigger flag.
            Restart = 1 ;
        }

    else if ( GPIO_PORTB_DATA_R & 0x20 )         //Fire button is pressed
        {
            GPIO_PORTB_ICR_R |= 0xA0;            // setting bits 5,7 in ICR to clear the trigger flag.
            FireFlag = 1 ;
            Laser.x = ADC_value/62 ;             // update the x-coordinate of the laser
        }
}


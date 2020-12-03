#include "inc/tm4c123gh6pm.h"
#include <stdint.h>

ADC_value = 0 ;

void ADC_init(void){

                /*Activating ADC0 on PE2~~AIN1*/

       SYSCTL_RCGC2_R     |= 0x00000010 ; // initializing clock to port E
       GPIO_PORTE_DIR_R   &= ~0x04;       // setting PE2 as i/p
       GPIO_PORTE_AFSEL_R |= 0x04 ;       // enabling alternative function on PE2
       GPIO_PORTE_DEN_R   &= ~0x04;       // disabling any digital signal on PE2
       GPIO_PORTE_AMSEL_R |= 0x04 ;       // enabling analog input on PE2

       SYSCTL_RCGC0_R |= 0x00010000 ;    // enable clock on ADC0
       SYSCTL_RCGC0_R &= ~0x00000300;    // setting sample rate to be 125K sample/sec
       ADC0_SSPRI_R = 0x0123 ;           // setting priority of sample sequencer 3 with highest priority (0x00)
       ADC0_ACTSS_R &= ~0x0008  ;        // disable sample sequencer 3
       ADC0_EMUX_R &= ~0x0000F000;       // Selecting the processor to be the trigger for the sample sequencer
       ADC0_SSMUX3_R = 0x00000001 ;      // attach AIN1(PE2) to sample sequencer 3
       ADC0_SSCTL3_R = 0x0006 ;          // fire interrupt at the end of the sample sequence and setting the proper bit as we are using single sapmle sequence
       ADC0_ACTSS_R |=  0x0008 ;         // enable sample sequencer 3

 }

    uint32_t ADC_Value_Calculator(void){

            /*capturing a sample */

    uint32_t result ;
    ADC0_PSSI_R  = 0x8 ;        // initiate sampling on sequencer 3 that's attached to PE2

        while (! (ADC0_RIS_R & 0x8) )
                    {};
    result = ADC0_SSFIFO3_R ;
    ADC0_ISC_R = 0x8 ;         // clearing the done sampling flag
    return result ;     // return the converted ADC value

    }

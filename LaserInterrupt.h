#ifndef LASERINTERRUPT_H
#define LASERINTERRUPT_H

void PORTB_init();
void PORTB_interrupt_enable();


extern int FireFlag ;
extern int Restart  ;

#endif

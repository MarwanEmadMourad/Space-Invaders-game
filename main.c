#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "PLL.h"
#include "ADC.h"
#include "Systick.h"
#include "GameEngine.h"
#include "LaserInterrupt.h"

/*
 * This is lab-15 from shape the world course that aims to develop Space Invaders Game using Nokia5110 LCD
 * The game is simply enemies throwing missiles at you trying to kill you and you are shooting laser back
 * At them trying to do the same.
 *
 * You can move your player ship with rotary/sliding potentiometer (ADC) that's attached to PE2.
 *
 * You have two switches that are attached to PB5 (Fire button) , and PB(7) (Restart button).
 *
 * You can find the Nokia5110 LCD connections at the beginning of the NOKIA5110 library (Nokia5110.c).
 *
 * */
void delay(float N){

    // N is the time value in seconds

    uint32_t time = 8000000 ;        //number of bus cycles that is equivalent to 1sec obtained from Systick timer
    uint32_t x = N*time ;            //value of the total delay time multiplied by the bus cycles number
    while (x)                        //delay loop
    {x-- ;}
}

void Game_init(){

        // this function initializes the whole game in order to restart it

        PlayerShip_init();
        Bunker_init();
        Enemies_init();
        Missile_init();
        Laser_init();
}

int main(void)
{

    PLL_Init() ;
    Nokia5110_Init() ;
    ADC_init();
    Systick_init();
    PORTB_init();
    PORTB_interrupt_enable();

    Game_init();

    while(1)
     {
        int score = 0;               // clearing the score after each game
        float Missile_Delay = 0.05;  // setting the delay to it's initial value

        while(1)                     // this is the playing loop
        {
            score ++ ;               // increment the score

            if (Restart == 1)        // if restart button is pressed then restart the game
            {
                Restart = 0 ;
                Game_init();
                PlayerShip.life = 1 ;
            }

        Draw_PlayerShip();

        if (PlayerShip.life == 0)    // if player ship is dead draw explosion at the same place
            {
            Draw_Explosion() ;
            delay(3);
            break ;
            }

        Draw_Bunker();
        Draw_Enemies();

        if ( FireFlag == 1 )        // if fire button is pressed then fire laser
            {
            Draw_Laser();
            Move_Laser();
            }

        Draw_Missile();
        Move_Missile();

        if (Missile_Delay >= 0.01000002)   // decremenet the delay value in order to speed up the missiles and level up the game
            { Missile_Delay -= 0.00002 ; }

        delay(Missile_Delay);

        }

        // after losing print out the score you have got

        Nokia5110_Clear() ;
        Nokia5110_SetCursor(1,1);
        Nokia5110_OutString("Your Score") ;
        Nokia5110_SetCursor(2,3);
        Nokia5110_OutUDec(score);
        delay(3);
        Nokia5110_Clear() ;

        // printing "press sw2 to restart" until the restart button is pressed making the game to start all over again

        while(Restart == 0)
            {
                Nokia5110_SetCursor(2,1);
                Nokia5110_OutString("Game Over") ;
                Nokia5110_SetCursor(1,3);
                Nokia5110_OutString("Press SW2") ;
                Nokia5110_SetCursor(1,4);
                Nokia5110_OutString("to Restart") ;
            }
      }
}



#ifndef GAMEENGINE_H
#define GAMEENGINE_H

extern const unsigned char Bunker1[] ;
extern const unsigned char BigExplosion0[];
extern const unsigned char Laser1[];
extern const unsigned char Missile1[];
extern const unsigned char PlayerShip0[];
extern const unsigned char SmallEnemynew[];

struct State {
   uint32_t x;      // x coordinate
   uint32_t y;      // y coordinate
   const unsigned char *image ; // Pointer->image
   long life ;            // 0=dead, 1=alive
 };
 typedef struct State object;


object Explosion ;
object PlayerShip ;
object Bunker ;
object Enemies[5] ;
object Missile[5] ;
object Laser ;


void Draw_Explosion();
void PlayerShip_init () ;
void Draw_PlayerShip () ;
void Bunker_init();
void Draw_Bunker();
void Enemies_init();
void Draw_Enemies();
void Missile_init();
void Draw_Missile();
void Move_Missile();
void Laser_init();
void Draw_Laser();
void Move_Laser();









#endif

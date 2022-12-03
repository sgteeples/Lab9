#include "projectiles.h"
#include "settings.h"
#include "display.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

//Declarations
#define DEAD_COORDINATE_X 0
#define DEAD_COORDINATE_Y 0
#define SQUARED 2
void init_helper(projectile_t *projectile);
// Enum for our state machine
enum projectileState_t {INIT, MOVING, DEAD};
static enum projectileState_t currentState;

// Initialize eggs and projectiles as a dead .  This is useful at the start of the
// game to ensure that player and plamissile_t of the screen
void projectile_init_gun(projectile_t *projectile, uint16_t x_dest, uint16_t y_dest){

}

// Initialize the projectile as a egg projectile.  This function takes an (x, y)
// location of the plane which will be used as the origin.  The destination will be the gun
void projectile_init_egg(projectile_t *projectile, int16_t plane_x, int16_t plane_y){

}

////////// State Machine TICK Function //////////
void projectile_tick(projectile_t *projectile){

}

// Return whether the given projectile is dead.
bool projectile_is_dead(projectile_t *projectile){
  // Need to check what state in the state machine we're in
  if (projectile->currentState == DEAD) {
    return true;
  }
  // not true
  else {
    return false;
  }
}

// Return whether the given projectile is flying.
bool projectile_is_flying(projectile_t *projectile){
   // Need to check what state in the state machine we're in
  if (projectile->currentState == MOVING) {
    return true;
  }
  // not true
  else {
    return false;
  }   
}


// This function takes in a missle and it sets the values that were not set
void init_helper(projectile_t *projectile) {
projectile->x_current = projectile->x_origin;
projectile->y_current = projectile->y_origin;
projectile->radius = 15;
projectile->length = 0.0;
projectile->die_me = false;
projectile->egged = false;
projectile->total_length = sqrt(pow((projectile->y_dest - projectile->y_origin), SQUARED) +
pow((projectile->x_dest - projectile->x_origin), SQUARED));

}

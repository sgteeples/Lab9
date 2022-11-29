#include "projectiles.h"

// Initialize eggs and projectiles as a dead .  This is useful at the start of the
// game to ensure that player and plane projectiles aren't moving before they
// should.
void projectile_init_dead(projectile_t *projectile){

}

// Initialize the projectile as a player projectile.  This function takes an (x, y)
// destination of the projectile (where the user touched on the touchscreen).  The
// Firing location from middle center of the screen
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

}

// Return whether the given projectile is flying.
bool projectile_is_flying(projectile_t *projectile){
    
}
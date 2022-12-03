#ifndef PROJECTILES
#define PROJECTILES

#include <stdbool.h>
#include <stdint.h>

/* The same projectile structure will be used for all projectiles in the game,
so this enum is used to identify the type of projectile */
typedef enum {
  PROJECTILE_TYPE_EGG,
  PROJECTILE_TYPE_GUN
} projectile_type_t;

/* This struct contains all information about a projectile */
typedef struct {

  // Missle type (player, egg)
  projectile_type_t type;

  // Current state (the 'enum' will be defined in your projectile.c file, so it's
  // just declared as an integer type here)
  int32_t currentState;

  // Starting x,y of projectile
  uint16_t x_origin;
  uint16_t y_origin;

  // Ending x,y of projectile, and the total length from origin to destination.
  uint16_t x_dest;
  uint16_t y_dest;
  double total_length;

  // Used to track the current x,y of projectile
  int16_t x_current;
  int16_t y_current;

  // While flying, this tracks the current length of the flight path
  double length;

  // While flying, this flag is used to indicate the projectile should be detonated
  bool die_me;

  // Used for game statistics, this tracks whether the projectile impacted the
  // ground.
  bool egged;

  // used to track radius of the missile
  double radius;

} projectile_t;

////////// State Machine INIT Functions //////////

// Initialize eggs and projectiles as a dead .  This is useful at the start of the
// game to ensure that player and plane projectiles aren't moving before they
// should.
void projectile_init_dead(projectile_t *projectile);

// Initialize the projectile as a player projectile.  This function takes an (x, y)
// destination of the projectile (where the user touched on the touchscreen).  The
// Firing location from middle center of the screen
void projectile_init_gun(projectile_t *projectile, uint16_t x_dest, uint16_t y_dest);

// Initialize the projectile as a egg projectile.  This function takes an (x, y)
// location of the plane which will be used as the origin.  The destination will be the gun
void projectile_init_egg(projectile_t *projectile, int16_t plane_x, int16_t plane_y);

////////// State Machine TICK Function //////////
void projectile_tick(projectile_t *projectile);

// Return whether the given projectile is dead.
bool projectile_is_dead(projectile_t *projectile);

// Return whether the given projectile is flying.
bool projectile_is_flying(projectile_t *projectile);

#endif /* PROJECTILES */
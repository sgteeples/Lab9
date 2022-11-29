#ifndef DUCK
#define DUCK

#include "display.h"
#include "missile.h"

/* This struct contains all information about a duck */
typedef struct {

  // currentState
  int32_t currentState;

  // Starting x,y of duck
  uint16_t x_origin;
  uint16_t y_origin;

  // Ending x,y of missile, and the total length from origin to destination.
  uint16_t x_dest;
  uint16_t y_dest;

  // Used to track the current x,y of missile
  int16_t x_current;
  int16_t y_current;

  // plane explode
  bool duck_die;

  // plane missile
  missile_t egg;

} duck_t;

void duck_init(projectile_t *);

// State machine tick function
void duck_tick();

// Trigger the duck to la muerte
void duck_die();

// Get the XY location of the duck
display_point_t duck_getXY();

#endif /* DUCK */
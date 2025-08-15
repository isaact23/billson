#include "player.h"

static int x;
static int y;

void player_init() {
    x = 0;
    y = 0;
}

void player_update() {
    u16 pressed = keysHeld();

    if ((pressed & KEY_LEFT) && !(pressed & KEY_RIGHT)) {
        x -= 1;
    }
    else if ((pressed & KEY_RIGHT) && !(pressed & KEY_LEFT)) {
        x += 1;
    }

    if ((pressed & KEY_DOWN) && !(pressed & KEY_UP)) {
        y += 1;
    }
    else if ((pressed & KEY_UP) && !(pressed & KEY_DOWN)) {
        y -= 1;
    }

    OAM[0].attr0 = OBJ_Y(y) | OBJ_SHAPE(TALL) | OBJ_256_COLOR;
    OAM[0].attr1 = OBJ_X(x) | OBJ_SIZE(2);
    OAM[0].attr2 = OBJ_CHAR(0);
}
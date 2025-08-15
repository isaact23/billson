#include "main.h"

int main() {
    player_init();

    // Initialize vblank interrupt
    irqInit();
    irqEnable(IRQ_VBLANK);

    // Set up display control
    REG_DISPCNT = MODE_0 | BG0_ON | OBJ_ON;

    // Set up background 0
    REG_BG0CNT = BG_256_COLOR | SCREEN_BASE(16) | BG_WRAP | BG_SIZE_0;

    // Load sprite palette
    for (int i = 0; i < BILLSON_SPRITE_PALETTE1_SIZE; i++) {
        SPRITE_PALETTE[i] = BILLSON_SPRITE_PALETTE1[i];
    }

    // Load sprite tilemap
    for (int i = 0; i < BILLSON_SPRITE_TILEMAP1_WIDTH * BILLSON_SPRITE_TILEMAP1_HEIGHT * 32; i++) {
        SPRITE_GFX[i] = ((u16*)BILLSON_SPRITE_TILEMAP1)[i];
    }

    // Load background palette
    for (int i = 0; i < BILLSON_TILEMAP_PALETTE_SIZE; i++) {
        BG_PALETTE[i] = BILLSON_TILE_PALETTE[i];
    }

    // Load background tilemap
    u16* dest = CHAR_BASE_BLOCK(0);
    for (int i = 0; i < BILLSON_TILEMAP_WIDTH * BILLSON_TILEMAP_HEIGHT * 32; i++) {
        dest[i] = ((u16*)BILLSON_TILE_BITMAP)[i];
    }

    // Disable sprites
    for (int i = 0; i < 128; i++) {
        OAM[i].attr0 = OBJ_DISABLE;
    }

    while (1) {
        VBlankIntrWait();
        scanKeys();
        player_update();
    }
}

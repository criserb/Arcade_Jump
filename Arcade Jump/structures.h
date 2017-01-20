#pragma once

//structures
typedef struct avatar {
	int w, h;
	int x = 40; // position of avatar in X
	int y; // position of avatar in Y
	float vely = 0;
	const float gravity = 1.05;
	ALLEGRO_BITMAP *image;
	mask_t *mask;
}avatar;

typedef struct c_object {
	ALLEGRO_BITMAP *image;
	mask_t *mask;
}c_object;

typedef struct parallax_image {
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;
	int width;
	int height;
	ALLEGRO_BITMAP *image;
}parallax_image;

typedef struct game_backgrounds {
	ALLEGRO_BITMAP *game_background_up;
	ALLEGRO_BITMAP *game_background_down;
}game_backgrounds;

typedef struct explosion {
	int count = 0, fx = 0, fy = 0;
	int frame_width;
	int frame_height;
	ALLEGRO_BITMAP *image;
}explosion;
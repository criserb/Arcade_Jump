#include "all_headers.h"

ALLEGRO_DISPLAY *display;
int width = 640;
int height = 480;

int main(void)
{
	//allegro variables
	if (!al_init())		// test allegro
		al_show_native_message_box(display, "Arcade Jump", "ERROR", "ERROR WITH ALLEGRO", "Error with allegro", ALLEGRO_MESSAGEBOX_WARN);

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(width, height);
	al_set_window_title(display, "Arcade Jump");
	al_hide_mouse_cursor(display);

	if (!display)		//test display
		al_show_native_message_box(display, "Arcade Jump", "ERROR", "ERROR WITH DISPLAY", "Error with display", ALLEGRO_MESSAGEBOX_WARN);

	ALLEGRO_TIMER *fps_timer = al_create_timer(1.0 / fps);
	al_start_timer(fps_timer);

	//addon init
	al_install_audio();
	al_init_acodec_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_video_addon();

	intro();
	menu();

	// destroying globall variables
	al_destroy_display(display);
	al_destroy_timer(fps_timer);
	return EXIT_SUCCESS;
}
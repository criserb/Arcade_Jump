#include "All_headers.h"

struct avatar {
	ALLEGRO_BITMAP *image;
	int x = 0;
	int y = height - 60;
	int velocity = 2;
};

void game(void)
{
	avatar avatar;
	bool done = false, main_menu_on = false;

	ALLEGRO_BITMAP *pause_background = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	pause_background = al_load_bitmap("Pause_background.png");
	avatar.image = al_load_bitmap("Avatar.png");
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(fps_timer));

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:

				break;
			case ALLEGRO_KEY_ESCAPE:
				al_draw_bitmap(avatar.image, avatar.x, avatar.y, 0);
				al_draw_bitmap(pause_background, 0, 0, 0);
				al_pause_event_queue(event_queue, 1);
				if (pause() == 'm')
				{
					done = true;
					main_menu_on = true;
				}
				else
					al_pause_event_queue(event_queue, 0);
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			al_draw_bitmap(avatar.image, avatar.x, avatar.y, 0);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
		avatar.x = (avatar.x + avatar.velocity) % width;
	}
	// destroying objects
	al_destroy_bitmap(pause_background);
	al_destroy_bitmap(avatar.image);
	al_destroy_event_queue(event_queue);
	if (main_menu_on == true) menu();
}
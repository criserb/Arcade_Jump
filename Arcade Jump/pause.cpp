#include "all_headers.h"

char pause(void)
{
	bool done = false;
	bool main_menu_on = false;

	ALLEGRO_EVENT_QUEUE *pause_event_queue = al_create_event_queue();
	ALLEGRO_FONT *pause_title = al_load_ttf_font("Arcade_Classic.ttf", 42, 0);
	ALLEGRO_FONT *pause_item = pause_item = al_load_ttf_font("Arcade_Classic.ttf", 18, 0);

	al_register_event_source(pause_event_queue, al_get_keyboard_event_source());
	al_register_event_source(pause_event_queue, al_get_timer_event_source(fps_timer));

	while (!done)
	{
		ALLEGRO_EVENT pause_ev;
		al_wait_for_event(pause_event_queue, &pause_ev);
		if (pause_ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (pause_ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ENTER:
				done = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				main_menu_on = true;
				break;
			}
		}
		else if (pause_ev.type == ALLEGRO_EVENT_TIMER)
		{
			al_draw_text(pause_title, al_map_rgb(color[0], color[1], color[2]), width / 2, (height / 2) - 160, ALLEGRO_ALIGN_CENTRE, "PAUSE");
			al_draw_text(pause_item, al_map_rgb(color[0], color[1], color[2]), width / 2, (height / 2), ALLEGRO_ALIGN_CENTRE, "PRESS ENTER TO CONTINUE");
			al_draw_text(pause_item, al_map_rgb(color[0], color[1], color[2]), width / 2, (height / 2) + 30, ALLEGRO_ALIGN_CENTRE, "PRESS ESC TO BACK MAIN MENU");
			al_flip_display();
		}
	}
	// destroying objects
	al_destroy_font(pause_item);
	al_destroy_font(pause_title);
	al_destroy_event_queue(pause_event_queue);
	switch (main_menu_on)
	{
	case true: return 'm'; break;
	case false: return 'g'; break;
	}
}
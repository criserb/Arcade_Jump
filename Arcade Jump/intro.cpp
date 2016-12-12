#include "All_headers.h"
#include <string>

void intro(void)
{
	ALLEGRO_SAMPLE *intro_music = al_load_sample("Intro/Intro_music.ogg");
	ALLEGRO_BITMAP *image = NULL;
	std::string count = "000000";
	std::string name = "Intro/Intro_";
	std::string png = ".png";
	std::string all_name;
	std::string s;
	std::string buffer;
	bool done = false;
	int c = 0, i = 0;

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(fps_timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_reserve_samples(1);
	al_play_sample(intro_music, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
				done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			all_name = name + count + png;
			image = al_load_bitmap(all_name.c_str());
			al_draw_bitmap(image, 0, 0, 0);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_destroy_bitmap(image);
			c++;
			count.clear();
			count = std::to_string(c);
			while (buffer.length() + count.length() < 6)
				buffer += '0';
			count = buffer + count;
			while (count.length() > 6)
				count.erase(count.begin());
			++i;
		}
		if (i == 390)
			done = true;
	}
	al_destroy_sample(intro_music);
}
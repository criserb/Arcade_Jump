#include "all_headers.h"
#include <string>

void end_of_map(ALLEGRO_BITMAP *game_end)
{
	ALLEGRO_SAMPLE *click = al_load_sample("Sounds/Keyboard_tap.ogg");
	ALLEGRO_BITMAP *pause_background = al_load_bitmap("Graphics/Pause_background.png");
	ALLEGRO_FONT *text = al_load_ttf_font("Arcade_Classic.ttf", 32, 0);

	std::string letters = "GRATULATIONS!";
	std::string letter;
	std::string final_letters;

	for (unsigned int i = 0; i < letters.size(); ++i)
	{
		letter = letters.at(i);
		final_letters += letter;
		al_draw_bitmap(game_end, 0, 0, 0);
		al_stop_samples();
		al_play_sample(click, 1, 0, 2, ALLEGRO_PLAYMODE_ONCE, 0);
		al_draw_text(text, al_map_rgb(color[0], color[1], color[2]), width / 2, (height / 2) - 120, ALLEGRO_ALIGN_CENTRE, final_letters.c_str());
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_rest(0.1);
	}

	letters = "MAP COMPLETED!";
	final_letters.clear();

	for (unsigned int i = 0; i < letters.size()-1; ++i)
	{
		letter = letters.at(i);
		final_letters += letter;
		al_draw_bitmap(game_end, 0, 0, 0);
		al_stop_samples();
		al_play_sample(click, 1, 0, 2, ALLEGRO_PLAYMODE_ONCE, 0);
		al_draw_text(text, al_map_rgb(color[0], color[1], color[2]), width / 2, (height / 2) - 120, ALLEGRO_ALIGN_CENTRE, final_letters.c_str());
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_rest(0.1);
	}
	letter = letters.at(letters.size() - 1);
	final_letters += letter;
	al_draw_bitmap(game_end, 0, 0, 0);
	al_stop_samples();
	al_play_sample(click, 1, 0, 2, ALLEGRO_PLAYMODE_ONCE, 0);
	al_draw_text(text, al_map_rgb(color[0], color[1], color[2]), width / 2, (height / 2) - 120, ALLEGRO_ALIGN_CENTRE, final_letters.c_str());
	al_flip_display();
	al_rest(0.1);
	for (int i = 255; i != 210; --i)
	{
		al_draw_tinted_bitmap(game_end, al_map_rgba(0, 0, 0, 255-i), 0, 0, 0);
		al_flip_display();
		al_rest(0.05);
	}
	al_rest(1);
	al_destroy_sample(click);
	al_destroy_font(text);
	al_destroy_bitmap(pause_background);
}
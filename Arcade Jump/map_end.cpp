#include "all_headers.h"
#include <string>

void end_of_map(ALLEGRO_BITMAP *game_end)
{
	ALLEGRO_BITMAP *pause_background = al_load_bitmap("Graphics/Pause_background.png");
	ALLEGRO_FONT *text = al_load_ttf_font("Arcade_Classic.ttf", 32, 0);
	std::string letters = "GRATULATIONS!";
	std::string letter;
	std::string final_letters;

	for (int i = 0; i < letters.size(); ++i)
	{
		letter = letters.at(i);
		final_letters += letter;
		al_draw_bitmap(game_end, 0, 0, 0);
		al_draw_text(text, al_map_rgb(color[0], color[1], color[2]), width / 2, (height / 2) - 120, ALLEGRO_ALIGN_CENTRE, final_letters.c_str());
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_rest(0.1);
	}

	letters = "MAP COMPLETED!";
	final_letters.clear();

	for (int i = 0; i < letters.size(); ++i)
	{
		letter = letters.at(i);
		final_letters += letter;
		al_draw_bitmap(game_end, 0, 0, 0);
		al_draw_text(text, al_map_rgb(color[0], color[1], color[2]), width / 2, (height / 2) - 120, ALLEGRO_ALIGN_CENTRE, final_letters.c_str());
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_rest(0.1);
	}
	al_destroy_font(text);
	al_destroy_bitmap(pause_background);
}
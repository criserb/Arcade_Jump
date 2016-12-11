#include "All_headers.h"

void splash_screen(void)
{
	ALLEGRO_VIDEO *splash_vid = al_open_video("Intro.ogv");
	ALLEGRO_MIXER *mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	ALLEGRO_BITMAP *bitmap;

	std::cout << al_is_video_playing(splash_vid) << std::endl;

	ALLEGRO_EVENT_QUEUE *vid_event_queue = al_create_event_queue();

	al_register_event_source(vid_event_queue, al_get_video_event_source(splash_vid));
	al_register_event_source(vid_event_queue, al_get_keyboard_event_source());

	std::cout << al_is_event_source_registered(vid_event_queue,al_get_video_event_source(splash_vid)) << std::endl;

	al_start_video(splash_vid, mixer);

	bool done = false;
	while (!done)
	{
		ALLEGRO_EVENT vid_ev;
		//std::cout << al_is_event_queue_empty(vid_event_queue) << std::endl;
		al_wait_for_event(vid_event_queue, &vid_ev);
		if (vid_ev.type == ALLEGRO_EVENT_VIDEO_FRAME_SHOW)
		{
			bitmap = al_get_video_frame(splash_vid);
			al_draw_bitmap(bitmap, 0, 0, 0);
			al_flip_display();
			std::cout << __LINE__ << ' ' << __FILE__ << std::endl;
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
		else if (vid_ev.type == ALLEGRO_EVENT_VIDEO_FINISHED)
			done = true;
		if (vid_ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (vid_ev.keyboard.keycode == ALLEGRO_KEY_SPACE || vid_ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;
		}
	}

	al_destroy_event_queue(vid_event_queue);
	al_close_video(splash_vid);
	al_destroy_mixer(mixer);
}
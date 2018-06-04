#include <stdio.h>
#include <allegro5\allegro.h>

int main(int argc, char **argv) {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *queue;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(640, 480);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	al_install_keyboard();
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	bool gameIsRunning = true;

	do {
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		al_init_timeout(&timeout, 0.06);
		//al_wait_for_event(queue, &event);
		bool get_event = al_wait_for_event_until(queue, &event, &timeout);
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					gameIsRunning = false;
				break;
				/*case ALLEGRO_KEY_UP:
					
				break;
				case ALLEGRO_KEY_DOWN:
					
				break;
				case ALLEGRO_KEY_RIGHT:
					
				break;
				case ALLEGRO_KEY_LEFT:
					
				break;*/
			}
		}
	} while (gameIsRunning);

	al_destroy_display(display);

	return 0;
}
#include <stdio.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <iostream>

#define ETAM 4

float displayW = 640;
float displayH = 480;

float playerW = 50;
float playerH = 50;
float playerS = 20;

float enemyW = 50;
float enemyH = 50;
float enemyS = 20;

using namespace std;

int main(int argc, char **argv) {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_BITMAP *player = NULL;
	ALLEGRO_BITMAP *enemy [ETAM];
	for (int i = 0; i < ETAM; i++){
		enemy[i] = NULL;
	}

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(displayW, displayH);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	al_install_keyboard();

	al_init_image_addon();

	player = al_load_bitmap("test.jpg");
	for (size_t i = 0; i < ETAM; i++)
	{
		enemy[i] = al_load_bitmap("test2.jpg");
	}
	
	if (!player) {
		fprintf(stderr, "failed to create bitmap!\n");
		return -1;
	}
	

	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	

	//Player positions
	float px = 0;
	float py = 0;

	float plx = 0;
	float prx = 0;
	float puy = 0;
	float pdy = 0;

	//Enemies positions
	float ex [ETAM];
	float ey [ETAM];

	float elx [ETAM];
	float erx [ETAM];
	float euy [ETAM];
	float edy [ETAM];
	for (size_t i = 0; i < ETAM; i++)
	{
		elx[i] = 0;
		erx[i] = 0;
		euy[i] = 0;
		edy[i] = 0;
	}


	bool gameIsRunning = true;

	do {
		al_clear_to_color(al_map_rgba_f(0, 0, 0, 1));
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		al_init_timeout(&timeout, 0.06);
		//al_wait_for_event(queue, &event);
		bool get_event = al_wait_for_event_until(queue, &event, &timeout);

		al_draw_scaled_bitmap(player, 0, 0, al_get_bitmap_width(player), al_get_bitmap_height(player), px, py, playerW, playerH, 0);
		
		ex[0] = 100, ey[0] = 100;

		ex[1] = 200, ey[1] = 200;

		ex[2] = 300, ey[2] = 300;

		ex[3] = 400, ey[3] = 400;

		al_draw_scaled_bitmap(enemy[0], 0, 0, al_get_bitmap_width(enemy[0]), al_get_bitmap_height(enemy[0]), ex[0], ey[0], enemyW, enemyH, 0);
		al_draw_scaled_bitmap(enemy[1], 0, 0, al_get_bitmap_width(enemy[1]), al_get_bitmap_height(enemy[1]), ex[1], ey[1], enemyW, enemyH, 0);
		al_draw_scaled_bitmap(enemy[2], 0, 0, al_get_bitmap_width(enemy[2]), al_get_bitmap_height(enemy[2]), ex[2], ey[2], enemyW, enemyH, 0);
		al_draw_scaled_bitmap(enemy[3], 0, 0, al_get_bitmap_width(enemy[3]), al_get_bitmap_height(enemy[3]), ex[3], ey[3], enemyW, enemyH, 0);

		plx = px, prx = px + playerW, pdy = py + playerH, puy = py;

		for (size_t i = 0; i < ETAM; i++){
			elx[i] = ex[i], erx[i] = ex[i] + enemyW, euy[i] = ey[i], edy[i] = ey[i] + enemyH;
		}

		for (size_t i = 0; i < ETAM; i++){
			if ((elx[i] < prx && euy[i] < pdy) || (erx[i] > plx && euy[i] < pdy) || (elx[i] < prx && edy[i] < puy) || (erx[i] > plx && edy[i] < puy))
			{
				gameIsRunning = false;
			}
		}

		al_flip_display();
		
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && gameIsRunning == true) {
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					gameIsRunning = false;
				break;
				case ALLEGRO_KEY_UP:
					py -= playerS;
				break;
				case ALLEGRO_KEY_DOWN:
					py += playerS;
				break;
				case ALLEGRO_KEY_RIGHT:
					px += playerS;
				break;
				case ALLEGRO_KEY_LEFT:
					px -= playerS;
				break;
			}
		}
	} while (gameIsRunning);

	al_destroy_display(display);
	al_uninstall_keyboard();
	al_destroy_bitmap(player);
	for (size_t i = 0; i < ETAM; i++){
		al_destroy_bitmap(enemy[i]);
	}

	return 0;
}
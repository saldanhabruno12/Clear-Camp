#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>

#define KEY_SEEN 1
#define KEY_DOWN 2


int main() {
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon();

	ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_FONT* fonte = al_create_builtin_font();

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool running = true;
	bool redraw = true;
	ALLEGRO_EVENT event;

	al_start_timer(timer);

	int x = 1280 / 2;

	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));

	while (running) {
		al_wait_for_event(queue, &event);

		switch (event.type) {
		case ALLEGRO_EVENT_TIMER:

			if (key[ALLEGRO_KEY_D]) {
				x += 2;
			}
			if (key[ALLEGRO_KEY_A]) {
				x -= 2;
			}

			for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
				key[i] &= ~KEY_SEEN;

			redraw = true;
			break;


		case ALLEGRO_EVENT_KEY_DOWN:
			key[event.keyboard.keycode] = KEY_SEEN | KEY_DOWN;
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) running = false;
			break;

		case ALLEGRO_EVENT_KEY_UP:
			key[event.keyboard.keycode] &= ~KEY_DOWN;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			running = false;
			break;
		}
		if (running == false) {
			break;
		}
		if (redraw) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_filled_circle(x, 700, 20, al_map_rgb(255, 0, 255));
			al_flip_display();
		}
	}
	al_destroy_font(fonte);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
}
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <iostream>

#define M_PI 3.1415926535879323846

int main()
{
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_EVENT Event;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* ogre = NULL;
    ALLEGRO_BITMAP* image = NULL;
    const float FPS = 60;
    const int width = 900;
    const int height = 700;
    const int ogreSize = 32;
    float ogreX = width / 2 - ogreSize / 2;
    float ogreY = height / 2 - ogreSize / 2;
    float ogreDX = -4.0, ogreDY = 4.0;
    float angle = 0;
    bool redraw = true;
    bool exit = false;

    al_init();
    al_init_image_addon();
    timer = al_create_timer(1.0 / FPS);

    display = al_create_display(width, height);

    al_init_image_addon();
    image = al_load_bitmap("shrekSwamp.jpg");
    ogre = al_load_bitmap("shrekLayingDown.png");
    al_convert_mask_to_alpha(ogre, al_map_rgb(255, 0, 255));
    event_queue = al_create_event_queue();

    if (!event_queue) {
        al_destroy_bitmap(ogre);
        al_destroy_display(display);
        al_destroy_timer(timer);
    }
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);

    while (!exit) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                angle -= 0.1;
                al_draw_rotated_bitmap(ogre, width, height, ogreX, ogreY, angle, 0);
            }
        }
        if (ev.type == ALLEGRO_EVENT_TIMER) {
             if (ogreX < 0 || ogreX > width - ogreSize) {
                ogreDX = -ogreDX;
            }
            if (ogreY < 0 || ogreY > height - ogreSize) {
                ogreDY = -ogreDY;
            }
            ogreX += ogreDX;
            ogreY += ogreDY;

            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        if (redraw && al_is_event_queue_empty(event_queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(ogre, ogreX, ogreY, 0);
            al_flip_display();
        }
    }
    al_destroy_bitmap(ogre);
    al_destroy_timer(timer);
}

 
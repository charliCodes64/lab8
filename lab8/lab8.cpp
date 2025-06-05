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
    const int height = 800;
    const int ogreSize = 210;
    float ogreX = width / 2 - ogreSize / 2;
    float ogreY = height / 2 - ogreSize / 2;
    float ogreDX = 0, ogreDY = 0;
    float angle = 0;
    bool redraw = true;
    bool stop = false;

    al_init();
    al_install_keyboard();
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
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);

    while (1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            break;
        }
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                ogreDX = -7; //setting speed by direction
                ogreDY = 0;
                angle = 0;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                ogreDX = 7;
                ogreDY = 0;
                angle = M_PI; //used to flip
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
                ogreDY = -7; 
                ogreDX = 0;   
                angle = M_PI / 2; 
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                ogreDY = 7;
                ogreDX = 0;
                angle = -M_PI / 2;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                stop = !stop;
            }
        }
        //same format from lab 8 video 
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if(!stop) {
                if (ogreX < 0 || ogreX > width - ogreSize) {//handleing left and right
                    ogreDX = -ogreDX;
                    angle = M_PI;
                    if (ogreDX < 0) {
                        angle = 0;
                    }
                }

                if (ogreY < 0 || ogreY > height - ogreSize) {//handleing up and down
                    ogreDY = -ogreDY;
                    angle = -M_PI / 2;
                     if (ogreDY < 0) {
                        angle = M_PI / 2;
                    }
                }
                ogreX += ogreDX;
                ogreY += ogreDY;
            }
            redraw = true;
        }
        //reused from lab 8
        if (redraw && al_is_event_queue_empty(event_queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 0, 0, width, height,1);
            //al_draw_bitmap(image, width, height, 0);
            al_draw_rotated_bitmap(ogre, ogreSize / 2, ogreSize / 2, ogreX + ogreSize / 2, ogreY + ogreSize / 2, angle, 0);
            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_bitmap(ogre);
    al_destroy_timer(timer);
}

 
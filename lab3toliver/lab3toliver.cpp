#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

// Function prototypes
void draw_screen(int objectX, int objectY, int mouseX, int mouseY, int quadrant, ALLEGRO_FONT* font);
void draw_player(int x, int y);

int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_FONT* font = NULL;

    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    int width = 800;
    int height = 600;

    int objectX = width / 2;
    int objectY = height / 2;

    int mouseX = objectX;
    int mouseY = objectY;

    // 0 = default, 1 = upper-left, 2 = upper-right, 3 = lower-left, 4 = lower-right
    int quadrant = 0;

    bool done = false;

    display = al_create_display(width, height);

    if (!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_init_primitives_addon();
    al_init_font_addon();

    font = al_create_builtin_font();

    if (!font)
    {
        fprintf(stderr, "failed to create font!\n");
        return -1;
    }

    if (!al_install_mouse())
    {
        fprintf(stderr, "failed to install mouse!\n");
        return -1;
    }

    event_queue = al_create_event_queue();

    if (!event_queue)
    {
        fprintf(stderr, "failed to create event queue!\n");
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Draw starting screen
    draw_screen(objectX, objectY, mouseX, mouseY, quadrant, font);
    al_flip_display();

    while (!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            // Save mouse click location
            mouseX = ev.mouse.x;
            mouseY = ev.mouse.y;

            // Move object to mouse click location
            objectX = mouseX;
            objectY = mouseY;

            // Determine which quadrant was clicked
            if (mouseX < width / 2 && mouseY < height / 2)
            {
                quadrant = 1; // upper-left
            }
            else if (mouseX >= width / 2 && mouseY < height / 2)
            {
                quadrant = 2; // upper-right
            }
            else if (mouseX < width / 2 && mouseY >= height / 2)
            {
                quadrant = 3; // lower-left
            }
            else
            {
                quadrant = 4; // lower-right
            }

            // Redraw everything after click
            draw_screen(objectX, objectY, mouseX, mouseY, quadrant, font);
            al_flip_display();
        }
    }

    al_destroy_font(font);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}

void draw_screen(int objectX, int objectY, int mouseX, int mouseY, int quadrant, ALLEGRO_FONT* font)
{
    ALLEGRO_COLOR backgroundColor;
    ALLEGRO_COLOR textColor;

    // Set background and text colors based on clicked quadrant
    if (quadrant == 1)
    {
        // Upper-left: white background, black text
        backgroundColor = al_map_rgb(255, 255, 255);
        textColor = al_map_rgb(0, 0, 0);
    }
    else if (quadrant == 2)
    {
        // Upper-right: black background, white text
        backgroundColor = al_map_rgb(0, 0, 0);
        textColor = al_map_rgb(255, 255, 255);
    }
    else if (quadrant == 3)
    {
        // Lower-left: blue background, yellow text
        backgroundColor = al_map_rgb(0, 0, 255);
        textColor = al_map_rgb(255, 255, 0);
    }
    else if (quadrant == 4)
    {
        // Lower-right: yellow background, blue text
        backgroundColor = al_map_rgb(255, 255, 0);
        textColor = al_map_rgb(0, 0, 255);
    }
    else
    {
        // Starting background before any click
        backgroundColor = al_map_rgb(30, 30, 30);
        textColor = al_map_rgb(255, 255, 255);
    }

    // Clear screen to selected background color
    al_clear_to_color(backgroundColor);

    // Draw center lines to show quadrants
    al_draw_line(400, 0, 400, 600, textColor, 2);
    al_draw_line(0, 300, 800, 300, textColor, 2);

    // Draw object at current location
    draw_player(objectX, objectY);

    // Print mouse location on screen
    al_draw_textf(font, textColor, 20, 20, 0, "Mouse Location: x = %d, y = %d", mouseX, mouseY);
}

void draw_player(int x, int y)
{
    // Simple object made from primitives
    al_draw_filled_circle(x, y, 25, al_map_rgb(0, 180, 255));
    al_draw_circle(x, y, 25, al_map_rgb(255, 255, 255), 2);
    al_draw_filled_triangle(x, y - 45, x - 15, y - 15, x + 15, y - 15, al_map_rgb(255, 60, 60));
    al_draw_filled_circle(x, y, 8, al_map_rgb(255, 255, 255));
}
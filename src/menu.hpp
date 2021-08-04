//amirh_z

#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace std;
using namespace sf;

#define MENU_ITEMS 6

class Menu
{
private:
    int selected_item_index;
    string high_score;
    
    Font menu_font;
    Text menu_items[MENU_ITEMS];
    
public:
    Menu(float width, float height);
    ~Menu();

    bool is_saved;

    FloatRect menu_item_box_collider(Text& menu_item);

    SoundBuffer menu_sound_buffer;
    Sound menu_sound;

    void init_menu_item(Text& menu_item, string menu_item_text, int menu_item_size);
    void read_high_score();
    void read_save_file();
    void draw_menu(RenderWindow& window);

};


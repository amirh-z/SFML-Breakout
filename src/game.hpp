//amirh_z

#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"wall.hpp"
#include"paddle.hpp"
#include"brick.hpp"
#include"ball.hpp"

using namespace std;
using namespace sf;

#define GAME_ITEMS 11 
#define BRICKS 156

class Game
{
    private:
        int score;
        int level;
        int lives;
        string high_score;

        Text game_items[GAME_ITEMS];
        Font game_font;
    
    public:
        Game(RenderWindow& window);
        ~Game();

        enum game_state{lost, won, ongoing, paused, menu};
        game_state gs;

        bool is_saved;

        SoundBuffer game_clicking_sound_buffer;
        SoundBuffer game_ball_bounce_sound_buffer;
        SoundBuffer game_brick_break_sound_buffer;
        SoundBuffer game_lose_live_sound_buffer;
        SoundBuffer game_won_sound_buffer;
        SoundBuffer game_lost_sound_buffer;
        Sound game_clicking_sound;
        Sound game_ball_bounce_sound;
        Sound game_brick_break_sound;
        Sound game_lose_live_sound;
        Sound game_won_sound;
        Sound game_lost_sound;

        Ball ball;
        Paddle paddle;
        Brick brick;
        Brick bricks[BRICKS];
        Wall wall;
        vector<Wall> walls;

        void init_game_item(Text& game_item, string game_item_text, int game_item_size, Color game_item_color, float x, float y);
        void open_save_game();
        void set_saved_bricks();
        void set_bricks();
        void set_walls();
        void set_audio();
        void save_high_score();
        void save_game();
        void game_update(RenderWindow& window);
        void draw_game(RenderWindow& window);
};
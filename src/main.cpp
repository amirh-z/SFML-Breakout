//amirh_z

#include<iostream>
#include"menu.hpp"
#include"game.hpp"
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1080, 792), "Breakout");

    Menu menu(window.getSize().x, window.getSize().y);
    Game game(window);

    Clock game_pause_clock;
    Clock game_brick_collision_clock;
    Time game_pause_elapsed_time;
    Time game_brick_collision_time;

    game.gs = game.menu;
    
    while (window.isOpen())
    {
        Event ev;
        while (window.pollEvent(ev))
        {
            if(ev.type == Event::Closed)
            {
                window.close();
            }
            
        }

        window.clear(Color(50, 50, 50, 255));
        
        if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        else if(Keyboard::isKeyPressed(Keyboard::P) && game.gs == game.menu)
        {
            menu.menu_sound.play();
            game.gs = game.paused;
            game.set_bricks();
        }
        else if(Keyboard::isKeyPressed(Keyboard::Enter) && game.gs == game.menu && menu.is_saved)
        {
            menu.menu_sound.play();
            game.gs = game.paused;
            game.open_save_game();
            game.set_saved_bricks();
        }

        if(game.gs == game.menu)
        {
            menu.draw_menu(window);
        }
        else if(game.gs != game.menu)
        {
            if(Keyboard::isKeyPressed(Keyboard::Space))
            {
                game.ball.is_moving_with_paddle = false;
                
                game_pause_elapsed_time = game_pause_clock.restart();
                if(game_pause_elapsed_time.asMilliseconds() > 100)
                {
                    if(game.gs == game.paused)
                    {
                        game.gs = game.ongoing;
                        game.game_clicking_sound.play();
                    }
                    else if(game.gs == game.ongoing)
                    {
                        game.gs = game.paused;
                        game.game_clicking_sound.play();
                    }
                }
            }
            window.clear(Color(50, 50, 50, 255));
            game.game_update(window);
            game.draw_game(window);
        }
        
        window.display();
    }
    
    return 0;
}
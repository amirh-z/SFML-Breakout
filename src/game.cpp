//amirh_z

#include"game.hpp"

Game::Game(RenderWindow& window)
{
    window.setFramerateLimit(60);

    this->ball.is_moving_with_paddle = true;
    this->score = 0;
    this->level = 0;
    this->lives = 3;
    this->gs = paused;

    if (!(this->game_font.loadFromFile("Fonts/AtariClassic.ttf")))
    {
        cout << "Font not found" << '\n';
    }

    this->init_game_item(this->game_items[0], "Score:", 24, Color::Green, 50, 20);
    this->init_game_item(this->game_items[1], to_string(this->score), 24, Color::Green, 200, 20);
    this->init_game_item(this->game_items[2], "X", 24, Color::Cyan, 325, 20);
    this->init_game_item(this->game_items[3], to_string(this->level), 24, Color::Cyan, 355, 20);
    this->init_game_item(this->game_items[4], "Lives:", 24, Color::Green, 853, 20);
    this->init_game_item(this->game_items[5], to_string(this->lives), 24, Color::Green, 1000, 20);
    this->init_game_item(this->game_items[6], "Paused", 24, Color::Yellow, 469.5, 20);
    this->init_game_item(this->game_items[7], "Level Completed :)", 50, Color::Green, 102.5, 500);
    this->init_game_item(this->game_items[8], "Press <right> to continue", 24, Color::Yellow,241.5, 600);
    this->init_game_item(this->game_items[9], "You Lost :(", 60, Color::Red, 221, 500);
    this->init_game_item(this->game_items[10], "Press <r> to restart", 24, Color::Yellow, 301.5, 600);

    this->set_audio();
    this->set_walls();
}

Game::~Game(){}

void Game::init_game_item(Text& game_item, string game_item_text, int game_item_size, Color game_item_color, float x, float y)
{
    game_item.setFont(this->game_font);
    game_item.setColor(game_item_color);
    game_item.setCharacterSize(game_item_size);
    game_item.setString(game_item_text);
    game_item.setPosition(Vector2f(x, y));
}

void Game::set_audio()
{
    if(!(this->game_clicking_sound_buffer.loadFromFile("Sounds/Click.wav")))
    {
        cout << "Something went wrong!" << '\n';
    }
    this->game_clicking_sound.setBuffer(this->game_clicking_sound_buffer);

    if(!(this->game_ball_bounce_sound_buffer.loadFromFile("Sounds/Bounce.wav")))
    {
        cout << "Something went wrong!" << '\n';
    }
    this->game_ball_bounce_sound.setBuffer(this->game_ball_bounce_sound_buffer);

    if(!(this->game_brick_break_sound_buffer.loadFromFile("Sounds/Brick_Break.wav")))
    {
        cout << "Something went wrong!" << '\n';
    }
    this->game_brick_break_sound.setBuffer(this->game_brick_break_sound_buffer);

    if(!(this->game_lose_live_sound_buffer.loadFromFile("Sounds/Lose_Life.wav")))
    {
        cout << "Something went wrong!" << '\n';
    }
    this->game_lose_live_sound.setBuffer(this->game_lose_live_sound_buffer);

    if(!(this->game_won_sound_buffer.loadFromFile("Sounds/Win.wav")))
    {
        cout << "Something went wrong!" << '\n';
    }
    this->game_won_sound.setBuffer(this->game_won_sound_buffer);

    if(!(this->game_lost_sound_buffer.loadFromFile("Sounds/Lose.wav")))
    {
        cout << "Something went wrong!" << '\n';
    }
    this->game_lost_sound.setBuffer(this->game_lost_sound_buffer);

}

void Game::open_save_game()
{
    ifstream save_file;
    save_file.open("save.txt");

    string status;
    for(int i = 0; i < 167; i++)
    {
        getline(save_file, status);
        if(i == 0)
        {
            if(status == "0")
            {
                this->is_saved = false;
                break;
            }
            else
            {
                this->is_saved = true;
            }
        }
        else if((i > 0) && (i < 157))
        {
            this->bricks[i - 1].is_broken = stoi(status);
        }
        else if(i == 157)
        {
            this->score = stoi(status);
        }
        else if(i == 158)
        {
            this->lives = stoi(status);
        }
        else if(i == 159)
        {
            this->level = stoi(status);
        }
        else if(i == 160)
        {
            this->ball.ball_pos.x = stof(status);
        }
        else if(i == 161)
        {
            this->ball.ball_pos.y = stof(status);
        }
        else if(i == 162)
        {
            this->ball.ball_vel.x = stof(status);
        }
        else if(i == 163)
        {
            this->ball.ball_vel.y = stof(status);
        }
        else if(i == 164)
        {
            this->paddle.paddle_pos.x = stof(status);
        }
        else if(i == 165)
        {
            this->paddle.paddle_pos.y = stof(status);
        }
        else if(i == 166)
        {
            this->ball.is_moving_with_paddle = stoi(status);
        }
    }

    //setting ball and paddle pos when the game is first loaded
    this->paddle.update_paddle_pos();
    this->ball.update_ball_pos();

    //setting lives strings
    if(this->lives == 2)
    {
        this->game_items[4].setFillColor(Color::Yellow);
        this->game_items[5].setString(to_string(this->lives));
        this->game_items[5].setFillColor(Color::Yellow);
    }
    else if(this->lives == 1)
    {
        this->game_items[4].setFillColor(Color::Red);
        this->game_items[5].setString(to_string(this->lives));
        this->game_items[5].setFillColor(Color::Red);
    }
    else if(this->lives == 0)
    {
        this->game_items[4].setFillColor(Color::Red);
        this->game_items[5].setString(to_string(this->lives));
        this->game_items[5].setFillColor(Color::Red);
    }

    //setting score
    this->game_items[1].setString(to_string(this->score));

    //setting level string
    this->game_items[3].setString(to_string(this->level));
}

void Game::set_walls()
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 2; j < 22; j++)
        {
            this->wall.set_wall_pos(i * 36, j * 36);
            this->walls.push_back(this->wall);
        } 
    }

    for(int i = 28; i < 30; i++)
    {
        for(int j = 2; j < 22; j++)
        {
            this->wall.set_wall_pos(i * 36, j * 36);
            this->walls.push_back(this->wall);
        } 
    }

    for(int i = 2; i < 28; i++)
    {
        for(int j = 2; j < 4; j++)
        {
            this->wall.set_wall_pos(i * 36, j * 36);
            this->walls.push_back(this->wall);
        } 
    }
}

void Game::set_saved_bricks()
{
    //red bricks
    for(int i = 0; i < 26; i++)
    {
        if(!this->bricks[i].is_broken)
        {
            this->bricks[i].set_brick_color(187, 81, 77);
        }
        else
        {
            this->bricks[i].set_brick_color(50, 50, 50);
        }
    }
    //orange bricks
    for(int i = 26; i < 52; i++)
    {
        if(!this->bricks[i].is_broken)
        {
            this->bricks[i].set_brick_color(187, 112, 69);
        }
        else
        {
            this->bricks[i].set_brick_color(50, 50, 50);
        }
    }
    //light orange bricks
    for(int i = 52; i < 78; i++)
    {
        if(!this->bricks[i].is_broken)
        {
            this->bricks[i].set_brick_color(173, 123, 62);
        }
        else
        {
            this->bricks[i].set_brick_color(50, 50, 50);
        }
    }
    //yellow bricks
    for(int i = 78; i < 104; i++)
    {
        if(!this->bricks[i].is_broken)
        {
            this->bricks[i].set_brick_color(163, 160, 65);
        }
        else
        {
            this->bricks[i].set_brick_color(50, 50, 50);
        }
    }
    //green bricks
    for(int i = 104; i < 130; i++)
    {
        if(!this->bricks[i].is_broken)
        {
            this->bricks[i].set_brick_color(96, 157, 83);
        }
        else
        {
            this->bricks[i].set_brick_color(50, 50, 50);
        }
    }
    //blue bricks
    for(int i = 130; i < 156; i++)
    {
        if(!this->bricks[i].is_broken)
        {
            this->bricks[i].set_brick_color(61, 78, 193);
        }
        else
        {
            this->bricks[i].set_brick_color(50, 50, 50);
        }
    }

    int n = 0;
    for(int i = 6; i < 12; i++)
    {
        for(int j = 2; j < 28; j++)
        {
            bricks[n].set_brick_pos(j * 36, i * 36); 
            n += 1;
        }
    }
}

void Game::set_bricks()
{
    int n = 0;
    for(int j = 6; j < 12; j++)
    {
        for(int i = 2; i < 28; i++)
        {
            this->brick.set_brick_pos(i * 36, j * 36);
            switch(j)
            {
                case 6:
                    brick.set_brick_color(187, 81, 77);
                    brick.is_broken = false;
                    break;
            
                case 7:
                    brick.set_brick_color(187, 112, 69);
                    brick.is_broken = false;
                    break;

                case 8:
                    brick.set_brick_color(173, 123, 62);
                    brick.is_broken = false;
                    break;

                case 9: 
                    brick.set_brick_color(163, 160, 65);
                    brick.is_broken = false;
                    break;

                case 10: 
                    brick.set_brick_color(96, 157, 83);
                    brick.is_broken = false;
                    break;

                case 11: 
                    brick.set_brick_color(61, 78, 193);
                    brick.is_broken = false;
                    break;        
            }
            this->bricks[n] = this->brick;  
            n += 1; 
        }
    }
}

void Game::save_high_score()
{
    ifstream read_hs_file;
    read_hs_file.open("hs.txt");
    if(!read_hs_file)
    {
        cout << "Something went wrong!" << '\n';
    }
    else
    {
        read_hs_file >> this->high_score;
        read_hs_file.close();
    }

    ofstream write_hs_file;
    write_hs_file.open("hs.txt");
    if(!write_hs_file)
    {
        cout << "Something went wrong!\n";
    }
    else
    {
        if(((156 * this->level) + this->score) > stoi(this->high_score))
        {
            write_hs_file << to_string((156 * this->level) + this->score);
        }
        else
        {
            write_hs_file << this->high_score;
        }
        write_hs_file.close();
    }
}

void Game::save_game()
{
    ofstream write_save_file;
    write_save_file.open("save.txt");
    if(!write_save_file)
    {
        cout << "Something went wrong!" << '\n';
    }
    else
    {
        write_save_file << "1" << '\n';
        for(int i = 0; i < 156; i++)
        {
            write_save_file << to_string(bricks[i].brick_status()) << '\n';
        }
        write_save_file << to_string(this->score) << '\n';
        write_save_file << to_string(this->lives) << '\n';
        write_save_file << to_string(this->level) << '\n';
        write_save_file << to_string(this->ball.ball_pos.x) << '\n';
        write_save_file << to_string(this->ball.ball_pos.y) << '\n';
        write_save_file << to_string(this->ball.ball_vel.x) << '\n';
        write_save_file << to_string(this->ball.ball_vel.y) << '\n';
        write_save_file << to_string(this->paddle.paddle_pos.x) << '\n';
        write_save_file << to_string(this->paddle.paddle_pos.y) << '\n';
        write_save_file << to_string(this->ball.is_moving_with_paddle);
    }
}

void Game::game_update(RenderWindow& window)
{

    if(this->score == 156)
    {
        this->gs = won;
    }
    else if(this->lives <= 0)
    {
        this->gs = lost;
    }

    //exit
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
        this->save_high_score();
        this->save_game();
        window.close();
    }

    //moving ball with paddle
    if((this->gs == paused) && (this->ball.is_moving_with_paddle == true))
    {
        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            if(this->paddle.paddle_pos.x <= 862)
            {
                this->paddle.move_right();
                this->ball.move_right_with_paddle(this->paddle);
                this->ball.update_ball_pos();
                this->paddle.update_paddle_pos();
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::A))
        {
            if(this->paddle.paddle_pos.x >= 74)
            {
                this->paddle.move_left();
                this->ball.move_left_with_paddle(this->paddle);
                this->ball.update_ball_pos();
                this->paddle.update_paddle_pos();
            }
        }
    }
        
    //restart
    if(this->gs == lost)
    {
        if(Keyboard::isKeyPressed(Keyboard::R))
        {
            this->lives = 3;
            this->score = 0;
            this->level = 0;
            this->set_bricks();
            this->gs = paused;
            this->ball.is_moving_with_paddle = true;
            this->game_clicking_sound.play();

            //setting score and lives and level
            this->game_items[1].setString(to_string(score));
            this->game_items[3].setString(to_string(this->level));
            this->game_items[5].setString(to_string(lives));
            this->game_items[4].setFillColor(Color::Green); 
            this->game_items[5].setFillColor(Color::Green);
        }
    }

    //continue
    if(this->gs == won)
    {
        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            this->score = 0;
            this->level += 1;
            this->set_bricks();
            this->gs = paused;
            this->ball.is_moving_with_paddle = true;
            this->game_clicking_sound.play();

            //setting score and level
            this->game_items[1].setString(to_string(score));
            this->game_items[3].setString(to_string(this->level));
        }
    }

    //play
    if(this->gs == ongoing)
    {
        //paddle movement
        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            if(this->paddle.paddle_pos.x <= 862)
            {
                this->paddle.move_right();
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::A))
        {
            if(this->paddle.paddle_pos.x >= 74)
            {
                this->paddle.move_left();
            }
        }
        
        //ball movement
        if(((this->ball.ball_pos.x <= 74) || (this->ball.ball_pos.x >= 990)) && (this->ball.ball_pos.y <= 148))
        {
            this->ball.rebound_x_axis();
            this->ball.rebound_y_axis();
            this->game_ball_bounce_sound.play();
        }
        else if((this->ball.ball_pos.x <= 74) || (this->ball.ball_pos.x >= 990))
        {
            this->ball.rebound_x_axis();
            this->game_ball_bounce_sound.play();
        }
        else if(this->ball.ball_pos.y <= 148)
        {
            this->ball.rebound_y_axis();
            this->game_ball_bounce_sound.play();
        }
        else if(this->ball.ball_box_collider().intersects(this->paddle.paddle_box_collider()))
        {
            this->ball.rebound_paddle(this->paddle);
            this->game_ball_bounce_sound.play();
        }
        else if(this->ball.ball_pos.y >= 792)
        {
            this->ball.ball_restart();
            this->paddle.paddle_restart();
            this->game_lose_live_sound.play();
            this->gs = paused;
            this->ball.is_moving_with_paddle = true;
            this->lives -= 1;
            this->game_items[5].setString(to_string(lives));
            if(this->lives == 3)
            {
                this->game_items[4].setFillColor(Color::Green);
                this->game_items[5].setFillColor(Color::Green);
            }
            else if(this->lives == 2)
            {
                this->game_items[4].setFillColor(Color::Yellow);
                this->game_items[5].setFillColor(Color::Yellow);
            }
            else if(this->lives == 1)
            {
                this->game_items[4].setFillColor(Color::Red);
                this->game_items[5].setFillColor(Color::Red);
            }
            else if(this->lives < 1)
            {
                this->gs = lost;
                this->game_lost_sound.play();
                this->save_high_score();
            }
        }

        //bricks collision
        for (int i = 0; i < 156; i++)
        {
            if(this->ball.ball_box_collider().intersects(this->bricks[i].brick_box_collider()))
            {
                if(!this->bricks[i].brick_status())
                {
                    this->ball.rebound_brick(this->bricks[i]);
                    this->game_brick_break_sound.play();
                    this->score += 1;
                    this->game_items[1].setString(to_string(score));
                    if(this->score == 156)
                    {
                        this->game_won_sound.play();
                        this->gs = won;
                        this->ball.ball_restart();
                        this->paddle.paddle_restart();
                        this->save_high_score();
                    }
                }
            }
        }

        //update
        this->paddle.update_paddle_pos();
        this->ball.update_ball_pos();
    }
}

void Game::draw_game(RenderWindow& window)
{
    for(int i = 0; i < 6; i++)
    {
        window.draw(this->game_items[i]);
    }

    
    for(int i = 0; i < this->walls.size(); i++)
    {
        window.draw(this->walls[i].wall);
    }

    for(int i = 0; i < 156; i++)
    {
        window.draw(this->bricks[i].brick);
    } 

    window.draw(this->paddle.paddle);
    
    window.draw(this->ball.ball);

    if(this->gs == paused)
    {
        window.draw(this->game_items[6]);
    }
    if(this->gs == lost)
    {
        window.draw(this->game_items[9]);
        window.draw(this->game_items[10]);
    }
    if(this->gs == won)
    {
        window.draw(this->game_items[7]);
        window.draw(this->game_items[8]);
    }
}
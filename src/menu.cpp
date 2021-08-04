//amirh_z

#include"menu.hpp"

Menu::Menu(float width, float height)
{
    if (!(this->menu_font.loadFromFile("Fonts/AtariClassic.ttf")))
    {
        cout << "Something went wrong!" << '\n';
    }

    if(!(this->menu_sound_buffer.loadFromFile("Sounds/Click.wav")))
    {
        cout << "Something went wrong!" << '\n';
    }
    this->menu_sound.setBuffer(this->menu_sound_buffer);

    this->read_high_score();
    this->read_save_file();

    this->init_menu_item(this->menu_items[0], "BREAKOUT", 90);
    this->init_menu_item(this->menu_items[1], "High Score", 40);
    this->menu_items[1].setFillColor(Color::Green);
    this->init_menu_item(this->menu_items[2], this->high_score, 40);
    this->menu_items[2].setFillColor(Color::Green);
    this->init_menu_item(this->menu_items[3], "Press <p> to play new game", 24);
    this->init_menu_item(this->menu_items[4], "Press <enter> to continue", 24);
    if(!this->is_saved)
    {
        this->menu_items[4].setFillColor(Color(168, 170,167, 255));
    }
    this->init_menu_item(this->menu_items[5], "Press <esc> to exit", 24);

    for(int i = 0; i < 6; i++)
    {
        this->menu_items[i].setOrigin(this->menu_item_box_collider(this->menu_items[i]).width / 2.f, this->menu_item_box_collider(this->menu_items[i]).height / 2.f);
    }

    this->menu_items[0].setPosition(Vector2f(width / 2.f, height - 650));
    this->menu_items[1].setPosition(Vector2f(width / 2.f, height - 450));
    this->menu_items[2].setPosition(Vector2f(width / 2.f, height - 380));
    this->menu_items[3].setPosition(Vector2f(width / 2.f, height - 220));
    this->menu_items[4].setPosition(Vector2f(width / 2.f, height - 150));
    this->menu_items[5].setPosition(Vector2f(width / 2.f, height - 80));
}

Menu::~Menu(){}

FloatRect Menu::menu_item_box_collider(Text& menu_item)
{
    return menu_item.getGlobalBounds();
}

void Menu::draw_menu(RenderWindow& window)
{
    for (int i = 0; i < 6; i++)
    {
        window.draw(menu_items[i]);
    }
}

void Menu::read_high_score()
{
    ifstream high_score_file;
    high_score_file.open("hs.txt");
    if(!high_score_file)
    {
        cout << "Something went wrong!" << '\n';
    }
    else
    {
        high_score_file >> this->high_score;
        high_score_file.close();
    }
}


void Menu::read_save_file()
{
    ifstream save_file;
    save_file.open("save.txt");
    string check;
    if(!save_file)
    {
        cout << "Something went wrong!" << '\n';
    }
    else
    {
        getline(save_file, check);
        if(check == "1")
        {
            this->is_saved = true;
        }
    }
}


void Menu::init_menu_item(Text& menu_item, string menu_item_text, int menu_item_size)
{
    menu_item.setFont(this->menu_font);
    menu_item.setColor(Color::Yellow);
    menu_item.setCharacterSize(menu_item_size);
    menu_item.setString(menu_item_text);
}

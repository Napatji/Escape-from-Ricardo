#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp> 
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include "Escape from Ricardo.h"
#include "Menu.h"

static const float VIEW_HEIGHT = 1024.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
    //state object
    bool restart = false;
    bool win = false;
    bool menustate = false;
    bool stage_1 = false;
    bool stage_2 = false;
    bool stage_3 = false;
    bool close_window = false;
    bool howtoplay = false;
    int score = 0;

    sf::Music music;
    music.openFromFile("Menu.wav");
    music.setVolume(10);
    music.play();

    sf::Vector2f posplayer, posmonster;
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Escape from Ricardo", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    sf::RectangleShape Avatar(sf::Vector2f(50.0f, 100.0f));
    sf::RectangleShape ricardo1(sf::Vector2f(50.0f, 100.0f));
    sf::RectangleShape End(sf::Vector2f(150.0f, 10.0f));

    sf::Texture MenuBackground;
    MenuBackground.loadFromFile("Ricardo Sprites/Ricardo bg.jpg");
    sf::Sprite Menu_Background;
    Menu_Background.setTexture(MenuBackground);
    Menu_Background.setPosition(-125, 0);

    //Include Item
    sf::Texture item;
    item.loadFromFile("item.png");
    float random_x[9] = { 3798, 4560, 6675, 6675, 4970, 5165, 4000, 1845, 3990 };
    float random_y[9] = { -568, -330, -440, 520, 460, 1635, 1635, 1235, 225 };
    sf::Sprite Item;
    Item.setTexture(item);
    Item.setScale(0.05, 0.05);
    Item.setPosition(random_x[0], random_y[0]);
    sf::Texture item2;
    item2.loadFromFile("item.png");
    sf::Sprite Item2;
    Item2.setTexture(item2);
    Item2.setScale(0.05, 0.05);
    Item2.setPosition(random_x[1], random_y[1]);
    sf::Texture item3;
    item3.loadFromFile("item.png");
    sf::Sprite Item3;
    Item3.setTexture(item3);
    Item3.setScale(0.05, 0.05);
    Item3.setPosition(random_x[2], random_y[2]);
    sf::Texture item4;
    item4.loadFromFile("item.png");
    sf::Sprite Item4;
    Item4.setTexture(item4);
    Item4.setScale(0.05, 0.05);
    Item3.setPosition(random_x[3], random_y[3]);
    sf::Texture item5;
    item5.loadFromFile("item.png");
    sf::Sprite Item5;
    Item5.setTexture(item5);
    Item5.setScale(0.05, 0.05);
    Item5.setPosition(random_x[4], random_y[4]);
    sf::Texture item6;
    item6.loadFromFile("item.png");
    sf::Sprite Item6;
    Item6.setTexture(item6);
    Item6.setScale(0.05, 0.05);
    Item6.setPosition(random_x[5], random_y[5]);
    sf::Texture item7;
    item7.loadFromFile("item.png");
    sf::Sprite Item7;
    Item7.setTexture(item7);
    Item7.setScale(0.05, 0.05);
    Item7.setPosition(random_x[6], random_y[6]);
    sf::Texture item8;
    item8.loadFromFile("item.png");
    sf::Sprite Item8;
    Item8.setTexture(item8);
    Item8.setScale(0.05, 0.05);
    Item8.setPosition(random_x[7], random_y[7]);
    sf::Texture item9;
    item9.loadFromFile("item.png");
    sf::Sprite Item9;
    Item9.setTexture(item9);
    Item9.setScale(0.05, 0.05);
    Item9.setPosition(random_x[8], random_y[8]);

    //Include Stage1
    sf::Texture stage1;
    stage1.loadFromFile("Map1.png");
    sf::Sprite Map1;
    Map1.setTexture(stage1);
    Map1.setPosition(0, 0);
    Map1.setScale(3.5, 3.5);

    //Include Stage2
    sf::Texture stage2;
    stage2.loadFromFile("Map2.png");
    sf::Sprite Map2;
    Map2.setTexture(stage2);
    Map2.setPosition(0, 0);
    Map2.setScale(3.5, 3.5);

    //Include Stage3
    sf::Texture stage3;
    stage3.loadFromFile("Map3.png");
    sf::Sprite Map3;
    Map3.setTexture(stage3);
    Map3.setPosition(3235, -895);
    Map3.setScale(3.5, 3.5);
    
    //Include Main Character
    sf::Texture playerTexture;
    playerTexture.loadFromFile("main sprite.png");
    sf::Sprite Boy;
    Boy.setTexture(playerTexture);
    playerTexture.setSmooth(true);

    //Include Enemy
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Ricardo.png");
    sf::Sprite Ricardo;
    Ricardo.setTexture(enemyTexture);
    enemyTexture.setSmooth(true);
    sf::Vector2f posEnemy;

    sf::Texture gameover;
    gameover.loadFromFile("gameover.jpg");
    sf::RectangleShape over(sf::Vector2f(1024.0f, 768.0f));
    over.setTexture(&gameover);

    //Include Player animation
    Player player(&playerTexture, sf::Vector2u(4, 4), 0.3f, 100.0f);

    //Include Enemy animation
    Enemy ricardo(&enemyTexture, sf::Vector2u(4, 1), 0.3f, 1.0f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    // Restart State   
    // Manu State 
    Menu menu(window.getSize().x, window.getSize().y);
    bool checkGameOpen = false;
    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::KeyReleased:
                switch (evnt.key.code) {
                case sf::Keyboard::W:
                    menu.MoveUp();
                    break;
                case sf::Keyboard::S:
                    menu.MoveDown();
                    break;
                case sf::Keyboard::Return:
                    howtoplay = false;
                    switch (menu.GetPressedItem()) {
                    case 0:
                        std::cout << "Play is Pressed\n";
                        stage_1 = true;
                        break;
                    case 1:
                        std::cout << "Exit is Pressed\n";
                        window.close();
                        break;
                    case 2:
                        window.close();
                        break;
                    }
                }
                break;

            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                std::cout << "\Resized\n";
                ResizeView(window, view);
                break;
            }

        }
        window.clear();
        window.draw(Menu_Background);
        menu.draw(window);
        window.display();
        if (stage_1 == true)
        break;
    }

    sf::Font font;
    if (!font.loadFromFile("Font/KingsButcher-Regular.ttf"))
    {
        //handle error
    }
    sf::Text Text;
    Text.setCharacterSize(150);
    Text.setFont(font);
    Text.setFillColor(sf::Color::Red);
    Text.setString("You win!!!");
    while (true)
    {
        if (menustate == true)
        {
            while (window.isOpen())
            {
                std::cout << "Enter" << std::endl;
                sf::Event evnt;
                while (window.pollEvent(evnt))
                {
                    switch (evnt.type)
                    {
                    case sf::Event::KeyReleased:
                        switch (evnt.key.code) {
                        case sf::Keyboard::W:
                            menu.MoveUp();
                            break;
                        case sf::Keyboard::S:
                            menu.MoveDown();
                            break;
                        case sf::Keyboard::Return:
                            howtoplay = false;
                            switch (menu.GetPressedItem()) {
                            case 0:
                                std::cout << "Play is Pressed\n";
                                stage_1 = true;
                                break;
                            case 1:
                                std::cout << "Exit is Pressed\n";
                                window.close();
                                break;
                            case 2:
                                window.close();
                                break;
                            }
                        }
                        break;

                    case sf::Event::Closed:
                        window.close();
                        break;

                    case sf::Event::Resized:
                        std::cout << "\Resized\n";
                        ResizeView(window, view);
                        break;
                    }

                }
                window.clear();
                window.draw(Menu_Background);
                menu.draw(window);
                window.display();
                if (stage_1 == true)
                    break;
            }
        }
        if (stage_1 == true)
        {
            //FOR STAGE1
            Platform room1(nullptr, sf::Vector2f(500.0f, 10.0f), sf::Vector2f(534.0f, 615.0f));
            Platform roomside1(nullptr, sf::Vector2f(10.0f, 590.0f), sf::Vector2f(270.0f, 730.0f));
            Platform roomside2(nullptr, sf::Vector2f(10.0f, 400.0f), sf::Vector2f(790.0f, 643.0f));
            Platform roomside3(nullptr, sf::Vector2f(10.0f, 50.0f), sf::Vector2f(790.0f, 985.0f));
            Platform roomside4(nullptr, sf::Vector2f(230.0f, 10.0f), sf::Vector2f(680.0f, 1015.0f));
            Platform roomside5(nullptr, sf::Vector2f(230.0f, 10.0f), sf::Vector2f(380.0f, 1015.0f));
            Platform wall1(nullptr, sf::Vector2f(300.0f, 10.0f), sf::Vector2f(955.0f, 838.0f));
            Platform wall2(nullptr, sf::Vector2f(1550.0f, 10.0f), sf::Vector2f(1590.0f, 964.0f));
            Platform wall3(nullptr, sf::Vector2f(490.0f, 10.0f), sf::Vector2f(1425.0f, 838.0f));
            Platform wall4(nullptr, sf::Vector2f(440.0f, 10.0f), sf::Vector2f(1960.0f, 838.0f));
            Platform wall5(nullptr, sf::Vector2f(120.0f, 10.0f), sf::Vector2f(2305.0f, 838.0f));
            Platform wall6(nullptr, sf::Vector2f(10.0f, 150.0f), sf::Vector2f(2360.0f, 893.0f));
            Platform room2(nullptr, sf::Vector2f(500.0f, 10.0f), sf::Vector2f(1150.0f, 350.0f));
            Platform roomside6(nullptr, sf::Vector2f(10.0f, 400.0f), sf::Vector2f(885.0f, 470.0f));
            Platform roomside7(nullptr, sf::Vector2f(10.0f, 400.0f), sf::Vector2f(1408.0f, 470.0f));
            Platform roomside8(nullptr, sf::Vector2f(230.0f, 10.0f), sf::Vector2f(995.0f, 675.0f));
            Platform roomside9(nullptr, sf::Vector2f(230.0f, 10.0f), sf::Vector2f(1300.0f, 675.0f));
            Platform roomside10(nullptr, sf::Vector2f(10.0f, 150.0f), sf::Vector2f(1109.0f, 765.0f));
            Platform roomside11(nullptr, sf::Vector2f(10.0f, 150.0f), sf::Vector2f(1185.0f, 765.0f));
            Platform room3(nullptr, sf::Vector2f(500.0f, 10.0f), sf::Vector2f(1706.0f, 350.0f));
            Platform roomside12(nullptr, sf::Vector2f(10.0f, 150.0f), sf::Vector2f(1672.0f, 765.0f));
            Platform roomside13(nullptr, sf::Vector2f(10.0f, 150.0f), sf::Vector2f(1745.0f, 765.0f));
            Platform roomside14(nullptr, sf::Vector2f(10.0f, 400.0f), sf::Vector2f(1448.0f, 470.0f));
            Platform roomside15(nullptr, sf::Vector2f(10.0f, 400.0f), sf::Vector2f(1970.0f, 470.0f));
            Platform roomside16(nullptr, sf::Vector2f(230.0f, 10.0f), sf::Vector2f(1563.0f, 675.0f));
            Platform roomside17(nullptr, sf::Vector2f(230.0f, 10.0f), sf::Vector2f(1853.0f, 675.0f));
            Platform room4(nullptr, sf::Vector2f(300.0f, 10.0f), sf::Vector2f(2208.0f, 455.0f));
            Platform roomside18(nullptr, sf::Vector2f(10.0f, 300.0f), sf::Vector2f(2063.0f, 510.0f));
            Platform roomside19(nullptr, sf::Vector2f(10.0f, 300.0f), sf::Vector2f(2360.0f, 510.0f));
            Platform roomside20(nullptr, sf::Vector2f(120.0f, 10.0f), sf::Vector2f(2125.0f, 675.0f));
            Platform roomside21(nullptr, sf::Vector2f(120.0f, 10.0f), sf::Vector2f(2305.0f, 675.0f));
            Platform roomside22(nullptr, sf::Vector2f(10.0f, 150.0f), sf::Vector2f(2178.0f, 765.0f));
            Platform roomside23(nullptr, sf::Vector2f(10.0f, 150.0f), sf::Vector2f(2249.0f, 765.0f));
            Platform door1(nullptr, sf::Vector2f(75.0f, 10.0f), sf::Vector2f(530.0f, 1075.0f));
            Platform desk1(nullptr, sf::Vector2f(150.0f, 5.0f), sf::Vector2f(533.0f, 738.0f));
            Platform bed1(nullptr, sf::Vector2f(75.0f, 75.0f), sf::Vector2f(1060.0f, 412.0f));
            Platform bed2(nullptr, sf::Vector2f(75.0f, 75.0f), sf::Vector2f(1230.0f, 412.0f));
            Platform bed3(nullptr, sf::Vector2f(75.0f, 75.0f), sf::Vector2f(1565.0f, 412.0f));
            Platform bath1(nullptr, sf::Vector2f(150.0f, 50.0f), sf::Vector2f(2265.0f, 480.0f));

            while (window.isOpen())
            {
                deltaTime = clock.restart().asSeconds();

                sf::Event evnt;
                //Window Event
                while (window.pollEvent(evnt))
                {
                    if (evnt.type == sf::Event::Closed)
                        window.close();

                    if (evnt.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                        close_window = true;
                        //window.close();
                }

                //Update Player Animation
                player.Update(deltaTime);

                //Declare playerCollision
                Collider playerCollision = player.GetCollider();

                //Declare enemyCollision
                Collider enemyCollision = ricardo.GetCollider();

                //Set collision
                ricardo.GetCollider().CheckCollision(playerCollision, 1.0f);


                //Collider Stage 1
                room1.Getcollider().CheckCollision(playerCollision, 1.0f);
                room1.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside1.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside1.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside2.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside2.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside3.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside3.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside4.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside4.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside5.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside5.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside6.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside6.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside7.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside7.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside8.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside8.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside9.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside9.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside10.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside10.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside11.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside11.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside12.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside12.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside13.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside13.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside14.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside14.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside15.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside15.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside16.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside16.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside17.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside17.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside18.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside18.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside19.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside19.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside20.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside20.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside21.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside21.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside22.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside22.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside23.Getcollider().CheckCollision(playerCollision, 1.0f);
                wall1.Getcollider().CheckCollision(playerCollision, 1.0f);
                wall1.Getcollider().CheckCollision(enemyCollision, 1.0f);
                wall2.Getcollider().CheckCollision(playerCollision, 1.0f);
                wall2.Getcollider().CheckCollision(enemyCollision, 1.0f);
                wall3.Getcollider().CheckCollision(playerCollision, 1.0f);
                wall3.Getcollider().CheckCollision(enemyCollision, 1.0f);
                wall4.Getcollider().CheckCollision(playerCollision, 1.0f);
                wall4.Getcollider().CheckCollision(enemyCollision, 1.0f);
                wall5.Getcollider().CheckCollision(playerCollision, 1.0f);
                wall5.Getcollider().CheckCollision(enemyCollision, 1.0f);
                wall6.Getcollider().CheckCollision(playerCollision, 1.0f);
                wall6.Getcollider().CheckCollision(enemyCollision, 1.0f);
                room2.Getcollider().CheckCollision(playerCollision, 1.0f);
                room2.Getcollider().CheckCollision(enemyCollision, 1.0f);
                room3.Getcollider().CheckCollision(playerCollision, 1.0f);
                room3.Getcollider().CheckCollision(enemyCollision, 1.0f);
                room4.Getcollider().CheckCollision(playerCollision, 1.0f);
                room4.Getcollider().CheckCollision(enemyCollision, 1.0f);
                door1.Getcollider().CheckCollision(playerCollision, 0.0f);
                door1.Getcollider().CheckCollision(enemyCollision, 1.0f);
                desk1.Getcollider().CheckCollision(playerCollision, 1.0f);
                desk1.Getcollider().CheckCollision(enemyCollision, 1.0f);
                bed1.Getcollider().CheckCollision(playerCollision, 1.0f);
                bed1.Getcollider().CheckCollision(enemyCollision, 1.0f);
                bed2.Getcollider().CheckCollision(playerCollision, 1.0f);
                bed2.Getcollider().CheckCollision(enemyCollision, 1.0f);
                bed3.Getcollider().CheckCollision(playerCollision, 1.0f);
                bed3.Getcollider().CheckCollision(enemyCollision, 1.0f);
                bath1.Getcollider().CheckCollision(playerCollision, 1.0f);
                bath1.Getcollider().CheckCollision(enemyCollision, 1.0f);

                //Set center as PLayer & print position
                view.setCenter(player.GetPosition());
                std::cout << "player x = " << player.GetPosition().x << " player y = " << player.GetPosition().y << std::endl;

                //print Enemy position
                std::cout << "enemy x = " << ricardo.GetPosition().x << " enemy y = " << ricardo.GetPosition().y << std::endl;

                //Set View
                window.setView(view);

                window.clear();


                //Stage Update
                if (player.GetPosition().y > 1020)
                {
                    stage_2 = true;;
                    stage_1 = false;
                }

                else
                {
                    //window.draw(Map1);
                    window.draw(Map1);
                    player.Draw(window);
                }
                if (stage_2 == true)
                    break;
                window.display();

            }
        }
        else if (stage_2 == true)
        {
            //FOR STAGE2
            Platform roomup(nullptr, sf::Vector2f(2495.0f, 10.0f), sf::Vector2f(1865.0f, 1180.0f));
            Platform roomup2(nullptr, sf::Vector2f(5000.0f, 10.0f), sf::Vector2f(5030.0f, -660.0f));
            Platform roomup3(nullptr, sf::Vector2f(400.0f, 10.0f), sf::Vector2f(3595.0f, -275.0f));
            Platform roomup4(nullptr, sf::Vector2f(400.0f, 10.0f), sf::Vector2f(3565.0f, -100.0f));
            Platform roomup5(nullptr, sf::Vector2f(385.0f, 10.0f), sf::Vector2f(3822.5f, 10.0f));
            Platform roomup6(nullptr, sf::Vector2f(385.0f, 10.0f), sf::Vector2f(3822.5f, 170.0f));
            Platform roomup7(nullptr, sf::Vector2f(445.0f, 10.0f), sf::Vector2f(4073.0f, -100.0f));
            Platform roomup7_2(nullptr, sf::Vector2f(445.0f, 10.0f), sf::Vector2f(4073.0f, -275.0f));
            Platform roomup8(nullptr, sf::Vector2f(500.0f, 10.0f), sf::Vector2f(4665.0f, -275.0f));
            Platform roomup9(nullptr, sf::Vector2f(500.0f, 10.0f), sf::Vector2f(4665.0f, -100.0f));
            Platform roomup10(nullptr, sf::Vector2f(330.0f, 10.0f), sf::Vector2f(4075.0f, -440.0f));
            Platform roomup11(nullptr, sf::Vector2f(330.0f, 10.0f), sf::Vector2f(4075.0f, -565.0f));
            Platform roomup12(nullptr, sf::Vector2f(655.0f, 10.0f), sf::Vector2f(5365.0f, -275.0f));
            Platform roomup13(nullptr, sf::Vector2f(655.0f, 10.0f), sf::Vector2f(5365.0f, -100.0f));
            Platform roomup14(nullptr, sf::Vector2f(655.0f, 10.0f), sf::Vector2f(4555.0f, 170.0f));//
            Platform roomup15(nullptr, sf::Vector2f(775.0f, 10.0f), sf::Vector2f(4525.0f, 10.0f));
            Platform roomup16(nullptr, sf::Vector2f(655.0f, 10.0f), sf::Vector2f(5365.0f, 170.0f));
            Platform roomup17(nullptr, sf::Vector2f(700.0f, 10.0f), sf::Vector2f(5385.0f, 10.0f));
            Platform roomup18(nullptr, sf::Vector2f(650.0f, 10.0f), sf::Vector2f(4535.0f, 795.0f));
            Platform roomup19(nullptr, sf::Vector2f(650.0f, 10.0f), sf::Vector2f(4535.0f, 965.0f));
            Platform roomup20(nullptr, sf::Vector2f(655.0f, 10.0f), sf::Vector2f(5365.0f, 795.0f));
            Platform roomup21(nullptr, sf::Vector2f(750.0f, 10.0f), sf::Vector2f(5455.0f, 965.0f));
            Platform roomup22(nullptr, sf::Vector2f(200.0f, 10.0f), sf::Vector2f(3455.5f, 10.0f));
            Platform roomup23(nullptr, sf::Vector2f(200.0f, 10.0f), sf::Vector2f(3455.5f, 170.0f));
            Platform roomup24(nullptr, sf::Vector2f(200.0f, 10.0f), sf::Vector2f(3455.5f, 570.0f));
            Platform roomup25(nullptr, sf::Vector2f(200.0f, 10.0f), sf::Vector2f(3455.5f, 765.0f));
            Platform roomup26(nullptr, sf::Vector2f(200.0f, 10.0f), sf::Vector2f(3750.5f, 570.0f));
            Platform roomup27(nullptr, sf::Vector2f(300.0f, 10.0f), sf::Vector2f(3795.5f, 765.0f));
            Platform roomup28(nullptr, sf::Vector2f(250.0f, 10.0f), sf::Vector2f(3480.5f, 960.0f));
            Platform roomup29(nullptr, sf::Vector2f(375.0f, 10.0f), sf::Vector2f(3880.5f, 960.0f));
            Platform roomup30(nullptr, sf::Vector2f(700.0f, 10.0f), sf::Vector2f(6185.0f, -275.0f));
            Platform roomup31(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(6650.0f, -275.0f));
            Platform roomup32(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(6650.0f, -15.0f));
            Platform roomup33(nullptr, sf::Vector2f(655.0f, 10.0f), sf::Vector2f(6195.0f, -15.0f));
            Platform roomup34(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(5780.0f, 115.0f));
            Platform roomup35(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(5780.0f, 280.0f));
            Platform roomup36(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(5780.0f, 570.0f));
            Platform roomup37(nullptr, sf::Vector2f(500.0f, 10.0f), sf::Vector2f(5590.0f, 1075.0f));
            Platform roomup38(nullptr, sf::Vector2f(500.0f, 10.0f), sf::Vector2f(5590.0f, 1295.0f));
            Platform roomup39(nullptr, sf::Vector2f(1000.0f, 10.0f), sf::Vector2f(4650.0f, 1295.0f));

            Platform roomdown(nullptr, sf::Vector2f(1200.0f, 10.0f), sf::Vector2f(1060.0f, 1672.0f));
            Platform roomdown2(nullptr, sf::Vector2f(1200.0f, 10.0f), sf::Vector2f(2500.0f, 1672.0f));
            Platform roomdown3(nullptr, sf::Vector2f(200.0f, 10.0f), sf::Vector2f(3230.0f, 1275.0f));
            Platform roomdown4(nullptr, sf::Vector2f(200.0f, 10.0f), sf::Vector2f(3230.0f, 1465.0f));
            Platform roomdown5(nullptr, sf::Vector2f(5000.0f, 10.0f), sf::Vector2f(5030.0f, 1690.0f));
            Platform roomdown6(nullptr, sf::Vector2f(250.0f, 10.0f), sf::Vector2f(3500.0f, 1180.0f));
            Platform roomdown7(nullptr, sf::Vector2f(330.0f, 10.0f), sf::Vector2f(3850.0f, 1180.0f));
            Platform roomdown8(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(4075.0f, 1455.0f));
            Platform roomdown9(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(4075.0f, 1330.0f));
            Platform roomdown10(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(4690.0f, 1520.0f));
            Platform roomdown11(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(4690.0f, 1390.0f));
            Platform roomdown12(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(5810.0f, 1520.0f));
            Platform roomdown13(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(5810.0f, 1390.0f));
            Platform roomdown14(nullptr, sf::Vector2f(1100.0f, 10.0f), sf::Vector2f(4625.0f, 1080.0f));


            Platform roomside(nullptr, sf::Vector2f(10.0f, 600.0f), sf::Vector2f(454.0f, 1331.0f));
            Platform roomside2(nullptr, sf::Vector2f(10.0f, 180.0f), sf::Vector2f(620.0f, 1095.0f));
            Platform roomside3(nullptr, sf::Vector2f(10.0f, 180.0f), sf::Vector2f(498.0f, 1095.0f));
            Platform roomside4(nullptr, sf::Vector2f(10.0f, 220.0f), sf::Vector2f(3125.0f, 1170.0f));
            Platform roomside5(nullptr, sf::Vector2f(10.0f, 220.0f), sf::Vector2f(3125.0f, 1570.0f));
            Platform roomside6(nullptr, sf::Vector2f(10.0f, 75.0f), sf::Vector2f(1685.0f, 1705.0f));
            Platform roomside7(nullptr, sf::Vector2f(10.0f, 75.0f), sf::Vector2f(1895.0f, 1705.0f));
            Platform roomside8(nullptr, sf::Vector2f(10.0f, 220.0f), sf::Vector2f(3340.0f, 1570.0f));
            Platform roomside9(nullptr, sf::Vector2f(10.0f, 220.0f), sf::Vector2f(4030.0f, 1570.0f));
            Platform roomside10(nullptr, sf::Vector2f(10.0f, 220.0f), sf::Vector2f(4122.0f, 1570.0f));
            Platform roomside11(nullptr, sf::Vector2f(10.0f, 1500.0f), sf::Vector2f(3340.0f, 290.0f));
            Platform roomside12(nullptr, sf::Vector2f(10.0f, 5000.0f), sf::Vector2f(6715.0f, 50.0f));
            Platform roomside13(nullptr, sf::Vector2f(10.0f, 220.0f), sf::Vector2f(3620.0f, 1065.0f));
            Platform roomside14(nullptr, sf::Vector2f(10.0f, 220.0f), sf::Vector2f(3690.0f, 1065.0f));
            Platform roomside15(nullptr, sf::Vector2f(10.0f, 180.0f), sf::Vector2f(3565.0f, 670.0f));
            Platform roomside16(nullptr, sf::Vector2f(10.0f, 180.0f), sf::Vector2f(3635.0f, 670.0f));
            Platform roomside17(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(3565.0f, 95.0f));
            Platform roomside18(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(3635.0f, 95.0f));
            Platform roomside19(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(3790.0f, -175.0f));
            Platform roomside20(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(3855.0f, -175.0f));
            Platform roomside21(nullptr, sf::Vector2f(10.0f, 450.0f), sf::Vector2f(3390.0f, -530.0f));//ห้องบน left
            Platform roomside22(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(3915.0f, -355.0f));
            Platform roomside23(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4235.0f, -355.0f));
            Platform roomside24(nullptr, sf::Vector2f(10.0f, 450.0f), sf::Vector2f(3860.0f, 300.0f));//ห้องบน left2
            Platform roomside25(nullptr, sf::Vector2f(10.0f, 750.0f), sf::Vector2f(3955.0f, 390.0f));//ห้องกลาง 
            Platform roomside26(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4295.0f, -175.0f));
            Platform roomside27(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4415.0f, -175.0f));
            Platform roomside28(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4910.0f, -175.0f));
            Platform roomside29(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5035.0f, -175.0f));
            Platform roomside30(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5690.0f, -175.0f));
            Platform roomside31(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5815.0f, -175.0f));
            Platform roomside32(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4910.0f, 95.0f));
            Platform roomside33(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5035.0f, 95.0f));
            Platform roomside34(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4010.0f, 95.0f));
            Platform roomside35(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4140.0f, 95.0f));
            Platform roomside36(nullptr, sf::Vector2f(10.0f, 220.0f), sf::Vector2f(4030.0f, 1190.0f));
            Platform roomside37(nullptr, sf::Vector2f(10.0f, 220.0f), sf::Vector2f(4122.0f, 1190.0f));
            Platform roomside38(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4640.0f, 4615.0f));
            Platform roomside39(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4740.0f, 4615.0f));
            Platform roomside40(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4640.0f, 1300.0f));
            Platform roomside41(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4740.0f, 1300.0f));
            Platform roomside42(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4640.0f, 1600.0f));
            Platform roomside43(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4740.0f, 1600.0f));
            Platform roomside44(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5760.0f, 1600.0f));
            Platform roomside45(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5855.0f, 1600.0f));
            Platform roomside46(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5760.0f, 1300.0f));
            Platform roomside47(nullptr, sf::Vector2f(10.0f, 300.0f), sf::Vector2f(5855.0f, 1230.0f));//
            Platform roomside48(nullptr, sf::Vector2f(10.0f, 220.0f), sf::Vector2f(5185.0f, 1190.0f));
            Platform roomside49(nullptr, sf::Vector2f(10.0f, 220.0f), sf::Vector2f(5315.0f, 1190.0f));
            Platform roomside50(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4195.0f, 225.0f));
            Platform roomside51(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4235.0f, 225.0f));
            Platform roomside52(nullptr, sf::Vector2f(10.0f, 400.0f), sf::Vector2f(4195.0f, 770.0f));
            Platform roomside53(nullptr, sf::Vector2f(10.0f, 400.0f), sf::Vector2f(4235.0f, 770.0f));
            Platform roomside54(nullptr, sf::Vector2f(10.0f, 120.0f), sf::Vector2f(4065.0f, 1020.0f));
            Platform roomside55(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4905.0f, 880.0f));
            Platform roomside56(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5030.0f, 880.0f));
            Platform roomside57(nullptr, sf::Vector2f(10.0f, 400.0f), sf::Vector2f(5705.0f, 770.0f));
            Platform roomside58(nullptr, sf::Vector2f(10.0f, 400.0f), sf::Vector2f(5860.0f, 770.0f));
            Platform roomside59(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(3915.0f, -640.0f));
            Platform roomside60(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(4235.0f, -640.0f));
            Platform roomside61(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5875.0f, -640.0f));
            Platform roomside62(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5910.0f, -640.0f));
            Platform roomside63(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5875.0f, -355.0f));
            Platform roomside64(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5910.0f, -355.0f));
            Platform roomside65(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5705.0f, 202.0f));
            Platform roomside66(nullptr, sf::Vector2f(10.0f, 160.0f), sf::Vector2f(5855.0f, 205.0f));
            Platform roomside67(nullptr, sf::Vector2f(10.0f, 260.0f), sf::Vector2f(6530.0f, -140.0f));
            Platform roomside68(nullptr, sf::Vector2f(10.0f, 260.0f), sf::Vector2f(6600.0f, -140.0f));
            Platform roomside69(nullptr, sf::Vector2f(10.0f, 450.0f), sf::Vector2f(4755.0f, -530.0f));//ห้องบน right
            Platform roomside70(nullptr, sf::Vector2f(10.0f, 450.0f), sf::Vector2f(4845.0f, -530.0f));//ห้องบน right2
            Platform DoorEndGame(nullptr, sf::Vector2f(150.0f, 10.0f), sf::Vector2f(1790.0f, 1785.0f));

            while (window.isOpen())
            {
                float speedx = 10.0f;
                float speedy = 10.0f;
                int randomtime, r;
                srand(time(NULL));
                r = rand() % 4;

                deltaTime = clock.restart().asSeconds();
                Avatar.setPosition(player.GetPosition().x - 25, player.GetPosition().y - 50);
                ricardo1.setPosition(ricardo.GetPosition().x - 25, ricardo.GetPosition().y - 50);

                End.setPosition(1750.0f, 1750.0f);

                sf::Event evnt;

                //Window Event
                while (window.pollEvent(evnt))
                {
                    if (evnt.type == sf::Event::Closed)
                        window.close();

                    if (evnt.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                        close_window = true;
                        //window.close();
                }



                //Update Player Animation
                player.Update(deltaTime);

                //Update Enemy Animation
                ricardo.Update(deltaTime,player.GetPosition());

                //Declare playerCollision
                Collider playerCollision = player.GetCollider();

                //Declare enemyCollision
                Collider enemyCollision = ricardo.GetCollider();

                //Set collision
                ricardo.GetCollider().CheckCollision(playerCollision, 1.0f);
                player.GetCollider().CheckCollision(enemyCollision, 1.0f);

                //Collider Stage 2
                roomup.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup2.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup2.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup3.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup3.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup4.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup4.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup5.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup5.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup6.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup6.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup7.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup7.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup7_2.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup7_2.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup8.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup8.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup9.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup9.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup10.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup10.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup11.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup11.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup12.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup12.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup13.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup13.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup14.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup14.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup15.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup15.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup16.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup16.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup17.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup17.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup18.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup18.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup19.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup19.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup20.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup20.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup21.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup21.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup22.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup22.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup23.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup23.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup24.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup24.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup25.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup25.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup26.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup26.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup27.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup27.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup28.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup28.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup29.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup29.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup30.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup30.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup31.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup31.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup32.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup32.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup33.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup33.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup34.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup34.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup35.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup35.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup36.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup36.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup37.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup37.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup38.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup38.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomup39.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomup39.Getcollider().CheckCollision(enemyCollision, 1.0f);

                roomdown.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown2.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown2.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown3.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown3.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown4.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown4.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown5.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown5.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown6.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown6.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown7.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown7.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown8.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown8.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown9.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown9.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown10.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown10.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown11.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown11.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown12.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown12.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown13.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown13.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomdown14.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomdown14.Getcollider().CheckCollision(enemyCollision, 1.0f);

                roomside.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside2.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside2.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside3.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside3.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside4.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside4.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside5.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside5.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside6.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside6.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside7.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside7.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside8.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside8.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside9.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside9.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside10.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside10.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside11.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside11.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside12.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside12.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside13.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside13.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside14.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside14.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside15.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside15.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside16.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside16.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside17.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside17.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside18.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside18.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside19.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside19.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside20.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside20.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside21.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside21.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside22.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside22.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside23.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside23.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside24.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside24.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside25.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside25.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside26.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside26.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside27.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside27.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside28.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside28.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside29.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside29.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside30.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside30.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside31.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside31.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside32.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside32.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside33.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside33.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside34.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside34.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside35.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside35.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside36.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside36.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside37.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside37.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside38.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside38.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside39.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside39.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside40.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside40.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside41.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside41.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside42.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside42.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside43.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside43.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside44.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside44.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside45.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside45.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside46.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside46.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside47.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside47.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside48.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside48.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside49.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside49.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside50.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside50.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside51.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside51.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside52.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside52.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside53.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside53.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside54.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside54.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside55.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside55.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside56.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside56.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside57.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside57.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside58.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside58.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside59.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside59.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside60.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside60.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside61.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside61.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside62.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside62.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside63.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside63.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside64.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside64.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside65.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside65.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside66.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside66.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside67.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside67.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside68.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside68.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside69.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside69.Getcollider().CheckCollision(enemyCollision, 1.0f);
                roomside70.Getcollider().CheckCollision(playerCollision, 1.0f);
                roomside70.Getcollider().CheckCollision(enemyCollision, 1.0f);
                DoorEndGame.Getcollider().CheckCollision(playerCollision, 1.0f);
                DoorEndGame.Getcollider().CheckCollision(enemyCollision, 1.0f);

                //Set center as PLayer & print position
                view.setCenter(player.GetPosition());
                std::cout << "player x = " << player.GetPosition().x << " player y = " << player.GetPosition().y << std::endl;

                //print Enemy position
                std::cout << "-enemy x = " << ricardo.GetPosition().x << " -enemy y = " << ricardo.GetPosition().y << std::endl;

                //Score
                std::cout << "Score = " << score << std::endl;


                //Set View
                window.setView(view);

                window.clear();

                //Stage Update
               
                //Die
                if (ricardo1.getGlobalBounds().intersects(Avatar.getGlobalBounds()))
                {
                    while (window.isOpen())
                    {
                        Menu menu(window.getSize().x, window.getSize().y);
                        over.setPosition(Avatar.getPosition().x - 512, Avatar.getPosition().y - 384);
                        //Close Window//
                        sf::Event evnt;
                        while (window.pollEvent(evnt))
                        {
                            switch (evnt.type)
                            {
                            case sf::Event::Closed:
                                window.close();
                                break;
                            case sf::Event::Resized:
                                std::cout << "\Resized\n";
                                ResizeView(window, view);
                                break;
                            case sf::Event::KeyReleased:
                                if (evnt.key.code == sf::Keyboard::Return)
                                    std::cout << "\Menu\n" << std::endl;
                                    menustate = true;
                                break;
                            }
                        }
                        window.clear();
                        window.draw(over);
                        window.setView(view);
                        window.display();
                    }
                    if (menustate == true)
                        break;
                }

                if (End.getGlobalBounds().intersects(Avatar.getGlobalBounds()))
                {
                    if (score == 8)
                    {
                        while (window.isOpen())
                        {
                            Text.setPosition(player.GetPosition().x - 250, player.GetPosition().y - 384);
                            sf::Event evnt;
                            while (window.pollEvent(evnt))
                            {
                                switch (evnt.type)
                                {
                                case sf::Event::Closed:
                                    window.close();
                                    break;

                                case sf::Event::Resized:
                                    std::cout << "\Resized\n";
                                    ResizeView(window, view);
                                    break;
                                }

                            }
                            window.clear();
                            window.draw(Text);
                            window.display();

                        }
                    }
                    break;
                }
                if (Item.getGlobalBounds().intersects(Avatar.getGlobalBounds()))
                { 
                    std::cout << "Milk" << std::endl;
                    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        Item.setPosition(0, 0);
                        score++;
                    }
                }
                if (Item2.getGlobalBounds().intersects(Avatar.getGlobalBounds()))
                {
                    std::cout << "Milk" << std::endl;
                    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        Item2.setPosition(0, 0);
                        score++;
                    }
                }
                if (Item3.getGlobalBounds().intersects(Avatar.getGlobalBounds()))
                {
                    std::cout << "Milk" << std::endl;
                    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        Item3.setPosition(0, 0);
                        score++;
                    }
                }
                if (Item4.getGlobalBounds().intersects(Avatar.getGlobalBounds()))
                {
                    std::cout << "Milk" << std::endl;
                    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        Item4.setPosition(0, 0);
                        score++;
                    }
                }
                if (Item5.getGlobalBounds().intersects(Avatar.getGlobalBounds()))
                {
                    std::cout << "Milk" << std::endl;
                    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        Item5.setPosition(0, 0);
                        score++;
                    }
                }
                if (Item6.getGlobalBounds().intersects(Avatar.getGlobalBounds()))
                {
                    std::cout << "Milk" << std::endl;
                    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        Item6.setPosition(0, 0);
                        score++;
                    }
                }
                if (Item7.getGlobalBounds().intersects(Avatar.getGlobalBounds()))
                {
                    std::cout << "Milk" << std::endl;
                    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        Item7.setPosition(0, 0);
                        score++;
                    }
                }
                if (Item8.getGlobalBounds().intersects(Avatar.getGlobalBounds()))
                {
                    std::cout << "Milk" << std::endl;
                    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        Item8.setPosition(0, 0);
                        score++;
                    }
                }
                if (Item9.getGlobalBounds().intersects(Avatar.getGlobalBounds()))
                {
                    std::cout << "Milk" << std::endl;
                    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        Item9.setPosition(0, 0);
                        score++;
                    }
                }

                if (player.GetPosition().y < 1020 && player.GetPosition().x < 970)
                {
                    stage_2 = false;;
                    stage_1 = true;
                }
                if (restart)
                {
                    std::cout << "\nRestart in State 1\n";
                    break;
                }
                else
                {
                    window.draw(Map3);
                    window.draw(Map2);
                    window.draw(Item);
                    window.draw(Item2);
                    window.draw(Item3);
                    window.draw(Item4);
                    window.draw(Item5);
                    window.draw(Item6);
                    window.draw(Item7);
                    window.draw(Item8);
                    window.draw(Item9);
                    player.Draw(window);
                    ricardo.Draw(window);
                }
                if (stage_1 == true)
                    break;
                if (restart == true)
                {
                    std::cout << "XXXX\n\n";
                    break;
                }
                window.display();

            }
        }
            if(win == true)
            {
            while (window.isOpen())
            {
                deltaTime = clock.restart().asSeconds();

                sf::Event evnt;
                //Window Event
                while (window.pollEvent(evnt))
                {
                    if (evnt.type == sf::Event::Closed)
                        window.close();

                    if (evnt.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                        close_window = true;
                        window.close();
                }

                window.clear();
                window.draw(Text);
                window.display();

            }
        }

    }
    return 0;
}

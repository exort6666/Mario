#include "Character.hpp"
#include "Block.hpp"
#include "Heart.hpp"
#include "Mobs.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>


struct AppMode {
    enum Type { Debug, Release };
};

class Logger {
    std::ofstream file;
public:
    Logger(const std::string& filename) {
        file.open(filename, std::ios::out | std::ios::app);
    }

    ~Logger() {
        file.close();
    }

            SpriteEnemy.setTexture(Enemy);
    void log(AppMode::Type A, const std::string& message) {
        if (A == AppMode::Debug)
        {
            std::time_t now = std::time(nullptr);
            std::string timestamp = std::ctime(&now);
            timestamp = timestamp.substr(0, timestamp.length() - 1);
            file << "[" << timestamp << "] " << message << std::endl;
        }
    }
};

int main(){ 

#ifdef NDEBUG
    AppMode::Type mode = AppMode::Release;
#else
    AppMode::Type mode = AppMode::Debug;
#endif
    Logger logger("log.txt");

   //Шрифт
    sf::Font font;
    font.loadFromFile("Font/font.TTF");
    sf::Text text("", font, 100);
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    // Позиция блоков
    coords Block_pos;
    // Выбирается цвет блоков
    sf::Color color_blocks = sf::Color::Black;

    // Всё для бэкграунда
    sf::Texture background;
    background.loadFromFile("Background/background.png");
    sf::Sprite backgrounds(background);

    std::unique_ptr<MA::Character> Hero(new MA::Character({ 100,400 }));
    std::unique_ptr<MA::Mob> Skeleton(new MA::Mob({ 800,400 }));

    logger.log(mode, "Созданы классы персонажа и противника");

    // Создаются размеры окна
    coords Field{ 1200, 600 };
    sf::RenderWindow window(sf::VideoMode(Field.x, Field.y), "SFML works!");
    // Создается сердце
    coords heart_pos = { 0,0 };
    MA::Heart heart(heart_pos);
    sf::Clock clock;
    // Количество ударов,получаемое героем
    int hit = 0;
    //Булл переменная,для постоянного выйгрыша после победы
    bool victory = false;

    while (window.isOpen()) {
        float deltaTime = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        deltaTime = deltaTime / 5000;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Hero->Health > 0)
            Hero->move({ 2,0 }, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)&& Hero->Health > 0)
            Hero->move({ -2,0 }, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (Hero->OnGround) && (!Hero->fall))
            Hero->OnGround = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && (!Hero->strike) && (!Hero->fall) && (Hero->OnGround)) {
            Hero->attack();
            if (Skeleton->HitDetected(Skeleton->position().x - Hero->position().x)) {
                Skeleton->TakeDamage = true;
            }
        }
        if (Skeleton->Hitting_Hero) {
            Hero->getHit = true;
            hit++;
            Hero->Health--;
            if( Hero->Health == 0)
                logger.log(mode, "Главный герой убит");
        }
        Hero->update(deltaTime);
        Skeleton->update((Skeleton->position().x - Hero->position().x), deltaTime);
        //Урон по герою//
        window.clear();
        //Бэкграунд
        window.draw(backgrounds);
        //Выбираются позиции блоков и рисуются
        Block_pos = { 0, 460 };
        while (Block_pos.y < Field.y) {
            while (Block_pos.x < Field.x) {
                MA::Block Block(Block_pos, color_blocks);
                Block.draw(window);
                Block_pos.x += 50;
            }
            Block_pos.x = 0;
            Block_pos.y += 50;
        }
        coords heart_pos = { 0,0 };
        for (int i = 0; i < 3 - hit; i++) {
            heart.draw(window);
            heart_pos.x += 20;
            heart.setCoords(heart_pos);
        }
        Hero->draw(window);
        Skeleton->draw(window);
        if ((Hero->position().x >= Field.x) || (victory)) {
            if (victory != true) {
                victory = true;
            }
            text.setString("YOU WIN");
            text.setPosition(400, 200);
            window.clear();
            window.draw(backgrounds);
            window.draw(text);
            logger.log(mode, "Игра пройдена");
        }
        window.display();
        }
    return 0;
}
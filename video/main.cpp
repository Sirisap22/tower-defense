#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Draw with the click!");

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);

    sf::RectangleShape rectangle(sf::Vector2f(100.f, 100.f));
    rectangle.setFillColor(sf::Color::Red);

    // Mouse Position
    sf::Vector2f mousePosition = sf::Vector2f(0.f, 0.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // update ���˹觢ͧ Mouse
        // mapPixelToCoords ����ŧ��Ҩҡ range ��駨� monitor ��˹�ҵ�ҧ window
        mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        // ��� Mouse ���¶١��ԡ draw circle
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            
            circle.setPosition(mousePosition.x - circle.getRadius(), mousePosition.y - circle.getRadius());

            window.draw(circle);
        }

        // ��� Mouse ��Ҷ١��ԡ draw rectangle
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

            rectangle.setPosition(mousePosition.x - rectangle.getSize().x / 2, mousePosition.y - rectangle.getSize().y / 2);

            window.draw(rectangle);
        }

        // �� c ����������˹�Ҩ�
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            window.clear();

        // �ʴ����Ҿ
        window.display();
        
    }

    return 0;
}
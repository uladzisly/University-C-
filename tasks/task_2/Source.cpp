#include <SFML/Graphics.hpp>
#include <functional>
#include <cmath>
#include <sstream>
#include <iomanip>

// Функция для отрисовки графика
void drawGraph(sf::RenderWindow& window, std::function<float(float)> func,
    float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x);                      // вычисление значения функции

        float screenX = 400 + x * scaleX;       // преобразование координат в экранные
        float screenY = 300 - y * scaleY;

        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"Приложение для вывода графиков");

    sf::CircleShape userPoint(5);               // пользовательская точка, радиус 5 пикселей
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false;

    // 1 _ Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("arial.ttf") and
        !font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        return -1;
    }

    // 2 _ Текст для отображения координат
    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setPosition(10, 10);
    coordinatesText.setFillColor(sf::Color::Green);

    // Оси X и Y
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300);  xAxis[0].color = sf::Color::White;
    xAxis[1].position = sf::Vector2f(750, 300); xAxis[1].color = sf::Color::White;
    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 50);  yAxis[0].color = sf::Color::White;
    yAxis[1].position = sf::Vector2f(400, 550); yAxis[1].color = sf::Color::White;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Преобразование экранных координат в «математические»
                    float mathX = (mousePos.x - 400) / 30.0f;
                    float mathY = -(mousePos.y - 300) / 10.0f;

                    userPoint.setPosition(mousePos.x - userPoint.getRadius(),
                        mousePos.y - userPoint.getRadius());
                    userPointExists = true;

                    // 3 _ Определение зоны
                    const float eps = 0.1f;
                    float y1 = -3 * mathX + 1;
                    float y2 = 2 * mathX - 1; 
                    std::string zone;

                    if (std::abs(mathY - y1) < eps or std::abs(mathY - y2) < eps)
                        zone = "on line";
                    else if (mathY > y1 and mathY < y2) zone = "1";
                    else if (mathY < y1 and mathY < y2) zone = "2";
                    else if (mathY > y1 and mathY > y2) zone = "3";
                    else                               zone = "4";

                    std::ostringstream ss;
                    ss << std::fixed << std::setprecision(2)
                        << "Coordinates: (" << mathX << ", " << mathY << ")  Zone: " << zone;
                    coordinatesText.setString(ss.str());
                }
            }
        }

        // 4 _ Очистка экрана
        window.clear(sf::Color::Black);

        window.draw(xAxis);
        window.draw(yAxis);

        // 5 _ Мой график
        drawGraph(window, [](float x) { return -3 * x + 1; }, -10, 10, 30, 10, sf::Color::Red);
        drawGraph(window, [](float x) { return  2 * x - 1; }, -10, 10, 30, 10, sf::Color::Blue);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }

        window.display();
    }

    return 0;
}
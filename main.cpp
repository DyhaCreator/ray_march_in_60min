#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

sf::Event ev;
sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Ray");

std::vector<float> render(float x, float y) {
    int cx = 0, cy = 0;
    float ox = x, oy = y, obr = 0.5;
    std::vector<float>a = std::vector<float>(100);
    for (int i = 0; i < a.size(); i++) {
        float rayx = cx, rayy = cy;
        float rayr = (float)(i - int(a.size()) / 2) / int(a.size());
        float s = 0.0;
        //std::cout << rayr << std::endl;
        for (int j = 0; j < 100; j++) {
            float l = sqrt((float)(rayx - ox) * (float)(rayx - ox) + (float)(rayy - oy) * (float)(rayy - oy)) - obr;
            s += l;
            rayx = rayx + (sin(rayr) * l);
            rayy = rayy + (cos(rayr) * l);
            //std::cout << rayx << " " << rayy << " " << l << std::endl;
        }
        //std::cout << "----" << std::endl;
        a[i] = s;
    }
    return a;
}

int main() {
    window.setFramerateLimit(100);
    float r = 0;
    while(window.isOpen()){
        while(window.pollEvent(ev)){
            switch(ev.type){
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        window.clear(sf::Color(150, 150, 150));
        float x = cos(r) * 2.0;
        float y = 3.0 + sin(r) * 2.0;
        std::cout << x << " " << y << std::endl;
        std::vector<float>a = render(x, y);
        r += 0.01;
        /*for (auto x : a)
            std::cout << x << " ";
        std::cout << std::endl;*/

        for (int i = 0; i < a.size(); i++) {
            sf::CircleShape shape(10);
            shape.setFillColor(sf::Color(100, 250, 50));
            //shape.setPosition(i * (800 / a.size()), a[i] * 100);
            //window.draw(shape);
            shape.setPosition(i * (800 / a.size()), 300 - 100.0 / a[i]);
            window.draw(shape);
            shape.setPosition(i * (800 / a.size()), 300 + 100.0 / a[i]);
            window.draw(shape);
        }
        window.display();
    }
    
    return 0;
}
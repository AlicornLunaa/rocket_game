#include <SFML/Graphics.hpp>
using namespace sf;

int main(void){
    RenderWindow window(VideoMode(640, 480), "Hello World!");
    Event e;

    while(window.isOpen()){
        while(window.pollEvent(e)){
            switch(e.type){
                case Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}
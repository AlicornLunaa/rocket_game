#include <SFML/Graphics.hpp>
#include <reactphysics3d/reactphysics3d.h>
using namespace sf;
using namespace reactphysics3d;

int main(void){
    PhysicsCommon physCommon;
    PhysicsWorld* world = physCommon.createPhysicsWorld();

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
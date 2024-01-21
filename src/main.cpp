#include <iostream>
#include <SFML/Graphics.hpp>
#include <reactphysics3d/reactphysics3d.h>
#include <imgui.h>
#include <imgui-SFML.h>
using namespace std;
using namespace sf;
using namespace reactphysics3d;

int main(void){
    PhysicsCommon physCommon;
    PhysicsWorld* world = physCommon.createPhysicsWorld();

    RenderWindow window(VideoMode(640, 480), "Hello World!");
    Clock deltaClock;
    Time deltaTime;
    
    if(!ImGui::SFML::Init(window)){
        cout << "Failure to initialize ImGUI\n";
        return 1;
    }

    while(window.isOpen()){
        Event e;

        while(window.pollEvent(e)){
            ImGui::SFML::ProcessEvent(window, e);

            switch(e.type){
                case Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        deltaTime = deltaClock.restart();
        ImGui::SFML::Update(window, deltaTime);

        ImGui::Begin("Hello, world!");
        if(ImGui::Button("Look at this pretty button"))
            cout << "Button test\n";
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
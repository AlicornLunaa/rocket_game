#include "statistics.hpp"
#include <imgui.h>

using namespace sf;

void Widgets::drawRenderStats(const Time& deltaTime){
    ImGui::Begin("Stats");
    ImGui::SetWindowPos(ImVec2(15, 15));
    ImGui::SetWindowSize(ImVec2(175, 50));
    ImGui::Text("Frame time: %f", deltaTime.asSeconds());
    ImGui::End();
}
#include "UserInterface.h"

void UserInterface::OnGui(ImGuiContext *context) {
    ImGui::SetCurrentContext(context);
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("New Scene");
            ImGui::MenuItem("Open Scene");
            ImGui::MenuItem("Open Recent");
            ImGui::Separator();
            ImGui::MenuItem("Save");
            ImGui::MenuItem("Save As...");
            ImGui::MenuItem("Save As Scene Template...");
            ImGui::Separator();
            ImGui::MenuItem("New Project...");
            ImGui::MenuItem("Open Project...");
            ImGui::MenuItem("Save Project");
            ImGui::Separator();
            ImGui::MenuItem("Build Settings");
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")){
                engine->Exit();
            }


            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Assets")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("GameObject")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Component")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            ImGui::EndMenu();
        }
        ImGui::Separator();
        ImGui::Text("%.1fms %.0fFPS | AVG: %.2fms %.1fFPS",
                    ImGui::GetIO().DeltaTime*1000,
                    1.0f/ImGui::GetIO().DeltaTime,
                    1000.0f/ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::EndMenuBar();
    }
}

UserInterface::UserInterface(Engine *pEngine) : GameObject(pEngine) {}

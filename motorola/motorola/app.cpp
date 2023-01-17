#include "app.h"
#include "imgui/imgui.h"
#include <iostream>

using namespace ImGui;

ImVec4 decToVec4(int color[4]) {    // konwerter wartoœci z RGBA na akcepltowalne przez ImVec4
    return ImVec4((float)color[0] / 255, (float) color[1] / 255, (float)color[2] / 255, (float)color[3] / 255);
}

namespace App{

    int screen = 0;

    void RenderSequenceInputScreen() {
        Text("WprowadŸ Sekwencjê\n");
        TextColored(ImVec4(0, 0, 0, 1), "RNA/DNA");

        if(Button("WprowadŸ")){
            // kod wykonany po klikniêciu
            screen = 1;
        };
    }

    void RenderProteinScreen() {
        Text("Ekran 2");


    }

    void RenderProteinPropertiesScreen() {



    }


    void RenderGUI() {

        // Style okna
        // ImVec4 przechowuje 4 parametry, ka¿dy ma wartoœæ od 0-1, gdzie 1 to 255
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Text] = decToVec4(new int[4]{ 58, 72, 57, 255 });
        style.Colors[ImGuiCol_TextDisabled] = decToVec4(new int[4]{ 58, 72, 57, 255 });
        style.Colors[ImGuiCol_WindowBg] = decToVec4(new int[4]{ 218, 218, 218, 255 });
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0,0,0,0);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0,0,0,0);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0,0,0,0);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0,0,0,0);
        style.Colors[ImGuiCol_Button] = decToVec4(new int[4]{ 58, 72, 57, 255 });
        style.Colors[ImGuiCol_ButtonHovered] = decToVec4(new int[4]{39, 39, 39, 255 });
        style.Colors[ImGuiCol_ButtonActive] = decToVec4(new int[4]{ 39, 39, 39, 255 });
        // drawList zobaczyæ

        // Ustawienia okna
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoScrollbar;
        window_flags |= ImGuiWindowFlags_MenuBar;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        window_flags |= ImGuiWindowFlags_NoNav;
        //window_flags |= ImGuiWindowFlags_NoBackground;
        //window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        //window_flags |= ImGuiWindowFlags_UnsavedDocument;

        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();      
        ImGui::SetNextWindowPos(ImVec2(0,0));       // Startowa pozycja
        //ImGui::SetNextWindowSize(ImVec2(main_viewport->Size.x, main_viewport->Size.y));     // Rozmiar wewnêtrznego okna dopasowany do zewnêtrznego
        ImGui::SetNextWindowSize(ImVec2(500,300));



        Begin("Bioinformatyka", NULL, window_flags);    //tytu³ okna, czy siê zamyka, cechy
            
        switch (screen){
        case 0:
            RenderSequenceInputScreen();

            break;
        case 1:
            RenderProteinScreen();
        
            break;
        case 2:
            RenderProteinPropertiesScreen();
            
            break;
        default:
            RenderSequenceInputScreen();
        }

        ImGui::DebugTextEncoding("a¹Ÿ ó ó");

        End();
        ShowDemoWindow();       // okienko, które moze pomóc
    }


}

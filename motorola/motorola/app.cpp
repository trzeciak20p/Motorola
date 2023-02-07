#include "app.h"
#include "imgui/imgui.h"
#include <iostream>
#include "ImGuiFileDialog-0.6.4/ImGuiFileDialog.h"

using namespace ImGui;

ImVec4 decToVec4(int color[4]) {    // konwerter wartoœci z RGBA na akcepltowalne przez ImVec4
    return ImVec4((float)color[0] / 255, (float) color[1] / 255, (float)color[2] / 255, (float)color[3] / 255);
}

namespace App{

    int FilterDNALetters(ImGuiInputTextCallbackData* data){     // Pozwala na wprowadzanie tylko liter okreœlaj¹cych zasady azotowe
        if (data->EventChar < 256 && strchr("atgcuATGCU", (char)data->EventChar))
            return 0;
        return 1;
    }

    int screen = 0;
    char wprowadzona_sekwencja[64] = "";

    void RenderSequenceInputScreen(){

        int szerokosc = ImGui::GetIO().DisplaySize.x;
        SetCursorPosX(szerokosc * 0.43);        //œrodkowanie
        Text(u8"WprowadŸ Sekwencjê\n");
        SetCursorPosX(szerokosc * 0.47);
        TextColored(ImVec4(0, 0, 0, 1), "RNA/DNA");
        SetCursorPosX(szerokosc * 0.19);
        InputText("##", wprowadzona_sekwencja, 64, ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_CharsUppercase, FilterDNALetters);

        PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
        // Do wprowadzenia z pliku
        SetCursorPosX(szerokosc * 0.19);
        if (Button("Wybierz plik", ImVec2(200, 50))){ 
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", u8"Wybierz plik z sekwencj¹", ".txt,.h,.hpp", ".");
            ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, ".txt", ImVec4(0, 0.7, 0, 1));
        };
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")){
            if (ImGuiFileDialog::Instance()->IsOk()){
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                //std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            }
            ImGuiFileDialog::Instance()->Close();
        }
        SetCursorPosX(szerokosc * 0.19);
        if(Button(u8"WprowadŸ", ImVec2(200, 50) )){     //guzik potwierdzenia
            screen = 1;
        };

        PopStyleColor();

    }

    void RenderProteinScreen() {
        Text("Ekran 2");

        PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
        if (Button(">")) {
            screen = 2;
        };
        PopStyleColor();

    }

    void RenderProteinPropertiesScreen() {
        PushStyleColor(ImGuiCol_WindowBg, decToVec4(new int[4]{ 28, 28, 28, 1 }));
        // Top Bar

        PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
        //PushStyleColor(ImGuiCol_MenuBarBg, decToVec4(new int[4]{ 39, 39, 39, 1 }));
        if (ImGui::BeginMenuBar()) {
            if (Button("<")) {
                screen = 1;
            };
            Text("KWTKICSLHSLPPQS[stop]");

            ImGui::EndMenuBar();
        };

        PopStyleColor(2);
    }


    void RenderGUI() {

        // Style okna
        // ImVec4 przechowuje 4 parametry, ka¿dy ma wartoœæ od 0-1, gdzie 1 to 255
        ImGuiStyle& style = ImGui::GetStyle();
        style.FrameRounding = 5.3f;
        style.Colors[ImGuiCol_Text] = decToVec4(new int[4]{ 58, 72, 57, 255 });
        style.Colors[ImGuiCol_TextDisabled] = decToVec4(new int[4]{ 58, 72, 57, 255 });
        style.Colors[ImGuiCol_ChildBg] = decToVec4(new int[4]{ 218, 218, 218, 255 });
        style.Colors[ImGuiCol_WindowBg] = decToVec4(new int[4]{ 218, 218, 218, 255 });
        style.Colors[ImGuiCol_TitleBg] = decToVec4(new int[4]{ 200, 200, 200, 255 });
        style.Colors[ImGuiCol_TitleBgActive] = decToVec4(new int[4]{ 200, 200, 200, 255 });
        style.Colors[ImGuiCol_TitleBgCollapsed] = decToVec4(new int[4]{ 200, 200, 200, 255 });
        style.Colors[ImGuiCol_MenuBarBg] = decToVec4(new int[4]{ 39, 39, 39, 255 });
        style.Colors[ImGuiCol_Button] = decToVec4(new int[4]{ 58, 72, 57, 255 });
        style.Colors[ImGuiCol_ButtonHovered] = decToVec4(new int[4]{39, 39, 39, 255 });
        style.Colors[ImGuiCol_ButtonActive] = decToVec4(new int[4]{ 39, 39, 39, 255 });
        // drawList zobaczyæ

        // Ustawienia wewnêtrznego okna
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoScrollbar;
        //window_flags |= ImGuiWindowFlags_MenuBar;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        window_flags |= ImGuiWindowFlags_NoNav;
        //window_flags |= ImGuiWindowFlags_NoBackground;
        //window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        //window_flags |= ImGuiWindowFlags_UnsavedDocument;


        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();      
        ImGui::SetNextWindowPos(ImVec2(0,0));       // Startowa pozycja
        ImGui::SetNextWindowSize(ImVec2(main_viewport->Size.x, main_viewport->Size.y));     // Rozmiar wewnêtrznego okna dopasowany do zewnêtrznego
        //ImGui::SetNextWindowSize(ImVec2(500,300));



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


        End();
        //ShowDemoWindow();       // okienko, które moze pomóc
    }


}

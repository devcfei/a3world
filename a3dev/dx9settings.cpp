// a3dev.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "a3dev.h"


static void resetDrawSetting(dx9settings& settings)
{
    switch (settings.drawcase)
    {
    case CASE_TRIANGLE:
        settings.drawSet.lightOn = false;

        settings.drawSet.fillMode = D3DFILL_SOLID;
        settings.drawSet.cullMode = D3DCULL_NONE;
        settings.eyeX = 0.0f;
        settings.eyeY = 0.0f;
        settings.eyeZ = 5.0f;

        break;
    case CASE_RECTANGLE:
        settings.drawSet.lightOn = false;

        settings.drawSet.fillMode = D3DFILL_SOLID;
        settings.drawSet.cullMode = D3DCULL_CW;
        settings.eyeX = 0.0f;
        settings.eyeY = 0.0f;
        settings.eyeZ = 5.0f;
        break;
    case CASE_CUBE:
        settings.drawSet.lightOn = false;

        settings.drawSet.fillMode = D3DFILL_WIREFRAME;
        settings.drawSet.cullMode = D3DCULL_NONE;

        settings.eyeX = 0.0f;
        settings.eyeY = 4.0f;
        settings.eyeZ = 8.0f;


        break;

    case CASE_MESH:
        settings.drawSet.lightOn = false;

        settings.drawSet.fillMode = D3DFILL_SOLID;
        settings.drawSet.cullMode = D3DCULL_NONE;

        settings.eyeX = 0.0f;
        settings.eyeY = 4.0f;
        settings.eyeZ = 8.0f;


        break;

    case CASE_A3CHARA:


        settings.drawSet.lightOn = false;

        settings.drawSet.fillMode = D3DFILL_SOLID;
        settings.drawSet.cullMode = D3DCULL_CW;

        settings.eyeX = 0.0f;
        settings.eyeY = 0.0f;
        settings.eyeZ = 20.0f;

        break;



    }





    settings.camAngleX = 0.0f;
    settings.camAngleY = 0.0f;
    settings.camAngleZ = 0.0f;
}

static void DrawScenario(dx9settings& settings)
{
    
    // Using the _simplified_ one-liner Combo() api here
    // See "Combo" section for examples of how to use the more flexible BeginCombo()/EndCombo() api.
    const char* items[] = { "null","triangle", "rectangle", "cube", "mesh", "A3 character"};
    static int item_current = 0;
    ImGui::Combo("draw scenario", &item_current, items, IM_ARRAYSIZE(items));

    if (item_current != settings.drawcase)
    {
        if (settings.pdraw)
        {
            delete settings.pdraw;
            settings.pdraw = NULL;
            settings.drawcase = CASE_NULL;
        }

        switch (item_current)
        {
        case 0:
            break;

        case 1:
            settings.pdraw = new triangle();
            settings.pdraw->Create(settings.d3dDevcie);
            settings.drawcase = CASE_TRIANGLE;


            break;

        case 2:

            settings.pdraw = new rect();
            settings.pdraw->Create(settings.d3dDevcie);
            settings.drawcase = CASE_RECTANGLE;



            break;


        case 3:

            settings.pdraw = new cube();
            settings.pdraw->Create(settings.d3dDevcie);
            settings.drawcase = CASE_CUBE;


            break;


        case 4:

            settings.drawcase = CASE_MESH;
            break;

        case 5:
            settings.drawcase = CASE_A3CHARA;
            break;
        default:
            break;

        }


        resetDrawSetting(settings);
    }
}

static void DrawCullMode(dx9settings& settings)
{
    const char* items[] = { "D3DCULL_NONE","D3DCULL_CW","D3DCULL_CCW","D3DCULL_FORCE_DWORD" };
    static int item_current = 0;



    switch (settings.drawSet.cullMode)
    {
    case D3DCULL_NONE: item_current = 0; break;
    case D3DCULL_CW: item_current = 1; break;
    case D3DCULL_CCW: item_current = 2; break;
    case D3DCULL_FORCE_DWORD: item_current = 3; break;
    }


    ImGui::Combo("D3DRS_CULLMODE", &item_current, items, IM_ARRAYSIZE(items));


    switch (item_current)
    {
    case 0:
        settings.drawSet.cullMode = D3DCULL_NONE;
        break;
    case 1:
        settings.drawSet.cullMode = D3DCULL_CW;
        break;
    case 2:
        settings.drawSet.cullMode = D3DCULL_CCW;
        break;
    case 3:
        settings.drawSet.cullMode = D3DCULL_FORCE_DWORD;
        break;
    default:
        break;
    }

}



static void DrawFillMode(dx9settings& settings)
{
    const char* items[] = { "D3DFILL_POINT","D3DFILL_WIREFRAME","D3DFILL_SOLID","D3DFILL_FORCE_DWORD" };
    static int item_current = 0;

    switch (settings.drawSet.fillMode)
    {
    case D3DFILL_POINT: item_current = 0; break;
    case D3DFILL_WIREFRAME: item_current = 1; break;
    case D3DFILL_SOLID: item_current = 2; break;
    case D3DFILL_FORCE_DWORD: item_current = 3; break;
    }
    ImGui::Combo("D3DRS_FILLMODE", &item_current, items, IM_ARRAYSIZE(items));


    switch (item_current)
    {
    case 0:
        settings.drawSet.fillMode = D3DFILL_POINT;
        break;
    case 1:
        settings.drawSet.fillMode = D3DFILL_WIREFRAME;
        break;
    case 2:
        settings.drawSet.fillMode = D3DFILL_SOLID;
        break;
    case 3:
        settings.drawSet.fillMode = D3DFILL_FORCE_DWORD;
        break;
    default:
        break;
    }

}


void DrawMeshTree(dx9settings& settings)
{

}

void DrawSettings(dx9settings& settings)
{

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(main_viewport->WorkPos.x, 680), ImGuiCond_FirstUseEver);



    ImGui::Begin("Dx9 settings");
    //ImGui::Begin("Dx9 settings", 0, ImGuiWindowFlags_MenuBar);

    // show fps
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Checkbox("Demo Window", &settings.show_demo_window);


    if (ImGui::Button("Reset draw"))
    {
        resetDrawSetting(settings);
    }

    // draw settings
    ImGui::BulletText("Draw settings");
    ImGui::ColorEdit3("clear color", (float*)&settings.clear_color); // Edit 3 floats representing a color
    ImGui::SliderFloat("EyePT-X", &settings.eyeX, -100.0f, 100.0f, "ratio = %.5f");
    ImGui::SliderFloat("EyePT-Y", &settings.eyeY, -100.0f, 100.0f, "ratio = %.5f");
    ImGui::SliderFloat("EyePT-Z", &settings.eyeZ, -100.0f, 100.0f, "ratio = %.5f");
    ImGui::SliderFloat("Camera-X", &settings.camAngleX, -50.0f, 50.0f, "ratio = %.5f");
    ImGui::SliderFloat("Camera-Y", &settings.camAngleY, -50.0f, 50.0f, "ratio = %.5f");
    ImGui::SliderFloat("Camera-Z", &settings.camAngleZ, -50.0f, 50.0f, "ratio = %.5f");

    ImGui::Checkbox("D3DRS_LIGHTING", &settings.drawSet.lightOn);

    DrawCullMode(settings);
    DrawFillMode(settings);


    // scenarios
    ImGui::BulletText("Draw scenario");

    DrawScenario(settings);
    if (settings.drawcase == CASE_MESH)
    {

        ImGui::InputTextWithHint("mesh", "input mesh path...", settings.szMeshPath, IM_ARRAYSIZE(settings.szMeshPath));
        ImGui::SameLine();
        if (ImGui::Button("..."))
        {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".csv", ".");

        }

        // display
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
        {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                // action

                if (lstrcmpA(settings.szMeshPath, filePathName.c_str()))
                {
                    lstrcpyA(settings.szMeshPath, filePathName.c_str());

                    if (settings.pdraw)
                    {
                        delete settings.pdraw;

                        settings.pdraw = NULL;
                    }

                }


                USES_CONVERSION;
                LPCTSTR strPath = A2T(filePath.c_str());
                LPCTSTR strFile = A2T(filePathName.c_str());

                if (settings.pdraw == NULL)
                {
                    settings.pdraw = new mesh(strPath, strFile);
                    settings.pdraw->Create(settings.d3dDevcie);
                }
            }

            // close
            ImGuiFileDialog::Instance()->Close();
        }


    }
    else if (CASE_A3CHARA == settings.drawcase)
    {
        ImGui::InputTextWithHint("char", "char folder...", settings.szA3CharPath, IM_ARRAYSIZE(settings.szA3CharPath));
        ImGui::SameLine();
        if (ImGui::Button("..."))
        {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseDirDlgKey", "Choose a Directory", nullptr, ".");

        }


        // display
        if (ImGuiFileDialog::Instance()->Display("ChooseDirDlgKey"))
        {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                // action

                if (lstrcmpA(settings.szA3CharPath, filePath.c_str()))
                {
                    lstrcpyA(settings.szA3CharPath, filePath.c_str());


                    if (settings.pdraw)
                    {
                        delete settings.pdraw;

                        settings.pdraw = NULL;
                    }

                }


                USES_CONVERSION;
                LPCTSTR strPath = A2T(filePath.c_str());
                LPCTSTR strFile = A2T(filePathName.c_str());


                if (settings.pdraw == NULL)
                {
                    settings.pdraw = new chara(strPath);
                    settings.pdraw->Create(settings.d3dDevcie);


                }


            }

            // close
            ImGuiFileDialog::Instance()->Close();
        }
    }

    ImGui::End();

}
// a3dev.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "a3dev.h"




static void DrawScenario(dx9settings& settings)
{
    
    // Using the _simplified_ one-liner Combo() api here
    // See "Combo" section for examples of how to use the more flexible BeginCombo()/EndCombo() api.
    const char* items[] = { "null","triangle" };
    static int item_current = 0;
    ImGui::Combo("case", &item_current, items, IM_ARRAYSIZE(items));

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

        default:
            break;

        }

    }
}

static void DrawCullMode(dx9settings& settings)
{
    const char* items[] = { "D3DCULL_NONE","D3DCULL_CW","D3DCULL_CCW","D3DCULL_FORCE_DWORD" };
    static int item_current = 0;
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


void DrawSettings(dx9settings& settings)
{
    ImGui::Begin("Dx9 settings");
    //ImGui::Begin("Dx9 settings", 0, ImGuiWindowFlags_MenuBar);

    // show fps
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Checkbox("Demo Window", &settings.show_demo_window);

    ImGui::ColorEdit3("clear color", (float*)&settings.clear_color); // Edit 3 floats representing a color



    DrawScenario(settings);


    ImGui::SliderFloat("EyePT-X", &settings.eyeX, -10.0f, 10.0f, "ratio = %.5f");
    ImGui::SliderFloat("EyePT-Y", &settings.eyeY, -10.0f, 10.0f, "ratio = %.5f");
    ImGui::SliderFloat("EyePT-Z", &settings.eyeZ, -10.0f, 10.0f, "ratio = %.5f");
    ImGui::SliderFloat("Camera-Angle", &settings.camAngle, -50.0f, 50.0f, "ratio = %.5f");


    ImGui::Checkbox("D3DRS_LIGHTING", &settings.drawSet.lightOn);


    DrawCullMode(settings);
    DrawFillMode(settings);


    ImGui::End();

}
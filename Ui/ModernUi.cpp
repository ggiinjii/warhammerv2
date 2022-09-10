#include "ModernUi.h"
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_glfw.h"
#include "ImGui/backends/imgui_impl_opengl2.h"
#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>

#include "SOIL2.h"

//[Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
//To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
//Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


GLuint loadTexture(string filename)
{
    GLuint tex_2d = SOIL_load_OGL_texture
    (
        filename.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    return tex_2d;
}

void DisplayFighterProfile(GLuint texture, Character* fighter)
{
    ImTextureID my_tex_id = (void*)texture;

    float my_tex_w = (float)fighter->getImage().getWidth();
    float my_tex_h = (float)fighter->getImage().getHeight();
   /* float my_tex_w = (float)200;
    float my_tex_h = (float)200;*/
    {
        ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
        ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
        ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
        ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, tint_col, border_col);
        ImGui::Text("PV: %d/%d", fighter->GetPv().getPv(), fighter->GetPv().getPvMax());
        ImGui::Text("Nom: %s", fighter->GetName().c_str());
        ImGui::Text("Special Capacity: %s", fighter->GetNameCapacity().c_str());
        if (fighter->GetWeapon() != NULL)
            ImGui::Text("Weapon: %s", fighter->GetWeapon()->GetName().c_str());
        if (fighter->GetArmor() != NULL)
            ImGui::Text("Armor: %s", fighter->GetArmor()->GetName().c_str());
    }
}

ModernUi::ModernUi()
{
    _isGameStarted = false;
}

ModernUi::ModernUi(vector<Character*> allianceSide, vector<Character*> hordeSide)
    : _allianceSide(allianceSide), _hordeSide(hordeSide)
{
    _isGameStarted = false;
}


ModernUi::~ModernUi()
{
}


void ModernUi::displayModernUi()
{
    ModernGameGod modernGameGod;
    TurnInformation logTurn;

    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "WarHammer with a Modern UI", NULL, NULL);
    if (window == NULL)
        return;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();


    // variable definition for 
    bool showUi = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    static int goodguy_currentIndex = 0;
    static int horde_currentIndex = 0;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /* setup for display the UI in fullscreen mode*/
        static bool use_work_area = true;
        static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

        //UI Widget Definition
        ImGui::Begin("Azeroth's Arena", &showUi, flags);   //Create the main Windows of the UI
        ImGui::Text("Welcome to the Arena. Please select fighters");
        ImGui::Separator();

        static bool disable_all = false; // The Checkbox for that is inside the "Disabled" section at the bottom
        if (disable_all)
            ImGui::BeginDisabled();
       
        /**********************************Alliance Character Windows****************************************************/ 
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
        string fighterName = _allianceSide[goodguy_currentIndex]->GetName();
        const char* combo_preview_value = fighterName.c_str();

        ImGui::BeginChild("AllianceRegion", ImVec2(ImGui::GetContentRegionAvail().x * 0.35f, 400), false, window_flags); // creation of a child windows for alliance information

        if (ImGui::BeginCombo("Alliance Fighter", combo_preview_value))
        {
            // for each character on alliance side, we create the option in the comboBox
            for (int n = 0; n < _allianceSide.size(); n++)
            {
                const bool is_selected = (goodguy_currentIndex == n);
                if (ImGui::Selectable(_allianceSide[n]->GetName().c_str(), is_selected))
                    goodguy_currentIndex = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }


        /* Use Soil Library to load an image file directly as a new OpenGL texture */
        GLuint tex_2d = loadTexture(_allianceSide[goodguy_currentIndex]->getImage().getFileName());

        //GLuint tex_2d = loadTexture("..\\Ressources\\chevalier.jpg");
        DisplayFighterProfile(tex_2d, _allianceSide[goodguy_currentIndex]);

        ImGui::EndChild();


        /**********************************Horde Character Windows****************************************************/
        ImGui::SameLine(); // we put the second Child on the same line
        ImGui::BeginChild("HordeRegion", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 400), false, window_flags);


        string fighterName_horde = _hordeSide[horde_currentIndex]->GetName();
        const char* combo_preview_value_horde = fighterName_horde.c_str();

        if (ImGui::BeginCombo("Horde Fighter", combo_preview_value_horde))
        {
            for (int n = 0; n < _hordeSide.size(); n++)
            {
                const bool is_selected = (horde_currentIndex == n);
                if (ImGui::Selectable(_hordeSide[n]->GetName().c_str(), is_selected))
                    horde_currentIndex = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        GLuint tex_2d_Orc = loadTexture(_hordeSide[horde_currentIndex]->getImage().getFileName());
        /* load an image file directly as a new OpenGL texture */
       // GLuint tex_2d_Orc = loadTexture("..\\Ressources\\orc.jpg");

        DisplayFighterProfile(tex_2d_Orc, _hordeSide[horde_currentIndex]);

        ImGui::EndChild();

        if (disable_all)
        {
            ImGui::EndDisabled();
        }

        /*********Todo décoréller les tours pour les afficher ***********/
        if (!_isGameStarted)
        {
            if (ImGui::Button("Start Battle"))
            {
                logTurn = modernGameGod.StartModernBattle(_allianceSide[goodguy_currentIndex], _hordeSide[horde_currentIndex]);
                _isGameStarted = true;
                _isGameOver = false;
                disable_all = true;

                _allianceSide[goodguy_currentIndex]->SetPv(logTurn.getPvCharacter1());
                _hordeSide[horde_currentIndex]->SetPv(logTurn.getPvCharacter2());
                _battleLog = logTurn.getlog();
                _isGameOver = logTurn.getIsGameOver();

            }
        }
        else 
        {
            if (ImGui::Button("Next Turn"))
            {
                ResetTurnInfo();
                modernGameGod.ResetTurnInfo();

                logTurn= modernGameGod.NextTurn(_allianceSide[goodguy_currentIndex], _hordeSide[horde_currentIndex]);
                _allianceSide[goodguy_currentIndex]->SetPv(logTurn.getPvCharacter1());
                _hordeSide[horde_currentIndex]->SetPv(logTurn.getPvCharacter2());
                _battleLog = logTurn.getlog();
                _isGameOver = logTurn.getIsGameOver();
            }
        }

        if (_isGameOver)
        {
            ResetTurnInfo();
            if (!logTurn.getWinner().empty())
            {
                _battleLog = "The Game is Over. The Winner is " + logTurn.getWinner();
            }
           // _isGameStarted = false;
            disable_all = false;
        }

        //Log Fight Windows
        ImGuiWindowFlags Logwindow_flags = ImGuiWindowFlags_None | ImGuiWindowFlags_MenuBar;
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);



        /*****************Log Fight Windows **********************************/
        ImGui::BeginChild("ChildR", ImVec2(0, 260), true, Logwindow_flags);

        string testlog = GetLog();
        ImGui::Text(GetLog().c_str());

        ImGui::EndChild();
        ImGui::PopStyleVar();
        ImGui::SameLine();
        ImGui::End();


        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}


char* ModernUi::LoadHordeNameFighter()
{

    return nullptr;
}

char* ModernUi::LoadAllianceNameFighter()
{
    return nullptr;
}


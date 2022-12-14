#pragma once

#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_sdl.h"
#include "../include/imgui/imgui_impl_opengl3.h"

#include "../GraphicsEngine/renderer.h"
#include "../scene/scene.h"

#include "UIEngine.h"

namespace fs = std::filesystem;

void draw_main_menu_bar(Renderer *ren, Scene *scene);

void draw_ui(Renderer *ren, Scene *scene, Player *player, int *x, int *y, int *w, int *h, const char *devlevel);


// Scene tab
//----------------------------------------------------------------------------------
void draw_scene_tab(Renderer *ren, Scene *scene, int *selected_instance);
//----------------------------------------------------------------------------------



#include <stdio.h>
#include "ui.h"

#include "../include/imgui/imgui_stdlib.h"

int selected_dirlight = 0;    const char *dir_options[4] = {"1"};
int selected_pointlight = 0;  const char *point_options[4] = {"1", "2", "3", "4"};
int selected_spotlight = 0;   const char *spot_options[4] = {"1", "2"};
bool show = false;


void export_lighting_config(Renderer *ren)
{
  FILE *fh = fopen("config.txt", "w");
  
  for (int i=0; i<NUM_DIRLIGHTS; i++)
  {
    DirLight *light = &ren->dirlights[i];
    fprintf(fh, "DIRLIGHT AMBIENT: %f %f %f\n", light->ambient.x, light->ambient.y, light->ambient.z);
    fprintf(fh, "DIRLIGHT DIFFUSE: %f %f %f\n", light->diffuse.x, light->diffuse.y, light->diffuse.z);
    fprintf(fh, "DIRLIGHT DIRECTION: %f %f %f\n", light->direction.x, light->direction.y, light->direction.z);
    fprintf(fh, "DIRLIGHT BIAS: %f\n", ren->DIRBIAS);
  }

  for (int i=0; i<NUM_POINTLIGHTS; i++)
  {
    PointLight *light = &ren->pointlights[i];
    fprintf(fh, "POINTLIGHT ENABLED: %d\n", ren->pointlights_on[i]);
    fprintf(fh, "POINTLIGHT AMBIENT: %f %f %f\n", light->ambient.x, light->ambient.y, light->ambient.z);
    fprintf(fh, "POINTLIGHT DIFFUSE: %f %f %f\n", light->diffuse.x, light->diffuse.y, light->diffuse.z);
    fprintf(fh, "POINTLIGHT CONSTANT, LINEAR, QUADRATIC: %f %f %f\n", light->constant, light->linear, light->quadratic);
    fprintf(fh, "POINTLIGHT POSITION: %f %f %f\n", light->position.x, light->position.y, light->position.z);
  }

  fprintf(fh, "CLEAR COLOR: %f %f %f\n", ren->clearColor.x, ren->clearColor.y, ren->clearColor.z);
  fprintf(fh, "FOG START, STOP: %f %f\n", ren->fog_start, ren->fog_end);
  fprintf(fh, "FOV: %f\n", ren->fov);
  fprintf(fh, "EXPOSURE: %f\n", ren->exposure);
  fprintf(fh, "GAMMA: %f\n", ren->gamma);


  fclose(fh);
}

void import_lighting_config(Renderer *ren)
{
  FILE *fh = fopen("config.txt", "r");
  
  for (int i=0; i<NUM_DIRLIGHTS; i++)
  {
    DirLight *light = &ren->dirlights[i];
    fscanf(fh, "DIRLIGHT AMBIENT: %f %f %f\n", &light->ambient.x, &light->ambient.y, &light->ambient.z);
    fscanf(fh, "DIRLIGHT DIFFUSE: %f %f %f\n", &light->diffuse.x, &light->diffuse.y, &light->diffuse.z);
    fscanf(fh, "DIRLIGHT DIRECTION: %f %f %f\n", &light->direction.x, &light->direction.y, &light->direction.z);
    fscanf(fh, "DIRLIGHT BIAS: %f\n", &ren->DIRBIAS);
  }

  for (int i=0; i<NUM_POINTLIGHTS; i++)
  {
    PointLight *light = &ren->pointlights[i];
    fscanf(fh, "POINTLIGHT ENABLED: %d\n", &ren->pointlights_on[i]);
    fscanf(fh, "POINTLIGHT AMBIENT: %f %f %f\n", &light->ambient.x, &light->ambient.y, &light->ambient.z);
    fscanf(fh, "POINTLIGHT DIFFUSE: %f %f %f\n", &light->diffuse.x, &light->diffuse.y, &light->diffuse.z);
    fscanf(fh, "POINTLIGHT CONSTANT, LINEAR, QUADRATIC: %f %f %f\n", &light->constant, &light->linear, &light->quadratic);
    fscanf(fh, "POINTLIGHT POSITION: %f %f %f\n", &light->position.x, &light->position.y, &light->position.z);
  }

  fscanf(fh, "CLEAR COLOR: %f %f %f\n", &ren->clearColor.x, &ren->clearColor.y, &ren->clearColor.z);
  fscanf(fh, "FOG START, STOP: %f %f\n", &ren->fog_start, &ren->fog_end);
  fscanf(fh, "FOV: %f\n", &ren->fov);
  fscanf(fh, "EXPOSURE: %f\n", &ren->exposure);
  fscanf(fh, "GAMMA: %f\n", &ren->gamma);

  fclose(fh);
}

// void draw_transform_menu(Scene *scene, SceneGraph *handler, int selected_instance)
// {
//   if (handler->m_object_instances.size() == 0)
//     return;

//   GameObject *object = handler->objectPtr(selected_instance);

//   ImGui::InputText("Name", object->getGivenNamePtr());

//   ImGui::Separator();

//   ImGui::Text("Transform");
//   ImGui::Separator();
//   ImGui::DragFloat3("Position", &object->getPos()->x, 0.01f, 0, 0, "%0.01f", 0);
//   ImGui::DragFloat3("Velocity", &object->getVel()->x, 0.01f, 0, 0, "%0.01f", 0);
//   ImGui::DragFloat3("Rotation", &object->getRot()->x, 0.1f,  0, 0, "%0.1f", 0);

//   ImGui::Dummy(ImVec2(0.0f, 20.0f));
//   ImGui::Text("Other Stuff");
//   ImGui::Separator();
//   ImGui::Checkbox("Hidden", object->getHidden());

//   ImGui::Dummy(ImVec2(0.0f, 20.0f));
//   ImGui::Text("Info");
//   ImGui::Separator();

//   ImGui::Text("environmental:    %s", (object->isEnvironmental() ? "true" : "false"));
//   ImGui::Text("animated:         %s", (object->isAnimated() ? "true" : "false"));
//   ImGui::Text("physics_state:    %s", object->physicsStateString().c_str());
//   ImGui::Text("navigation_state: %s", object->navigationStateString().c_str());

//   if (object->isNPC())
//     if (ImGui::Button("Seek Player"))
//       object->setPath(scene->navmesh.path(object->pos_worldspace, scene->player->pos_worldspace));

// }

// void draw_new_instance_menu(SceneGraph *scenegraph, int *selected_instance)
// {
//   if (ImGui::BeginMenu("New Instance"))
//   {
//     if (ImGui::BeginMenu("Environment"))
//     {
//       int iterator = 0;
//       for (auto &objtemplate: scenegraph->m_object_templates)
//       {
//         if (objtemplate->isEnvironmental() == false)
//           continue;
        
//         if (ImGui::MenuItem(objtemplate->getName().c_str()))
//         {
//           scenegraph->newObjectInstance(objtemplate->getName());
//           *selected_instance = scenegraph->m_object_instances.size() - 1;
//         }

//         iterator += 1;
//       }
//       ImGui::EndMenu();
//     }

//     if (ImGui::BeginMenu("NPC"))
//     {
//       int iterator = 0;
//       for (auto &objtemplate: scenegraph->m_object_templates)
//       {
//         if (objtemplate->isNPC() == false)
//           continue;
        
//         if (ImGui::MenuItem(objtemplate->getName().c_str()))
//         {
//           scenegraph->newObjectInstance(objtemplate->getName());
//           *selected_instance = scenegraph->m_object_instances.size() - 1;
//         }

//         iterator += 1;
//       }
//       ImGui::EndMenu();
//     }

//     if (ImGui::BeginMenu("Misc"))
//     {
//       if (ImGui::MenuItem("Empty"))
//       {
//         scenegraph->newObjectInstance("empty");
//         *selected_instance = scenegraph->m_object_instances.size() - 1;
//       }

//       ImGui::EndMenu();
//     }

//     ImGui::EndMenu();
//   }
// }

// void draw_entity_childnodes(SceneGraph *scenegraph, GameObject *object, int *selected_instance)
// {
//   ImGui::PushID(object->getID());

//   int flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;

//   if (*selected_instance == object->getID())
//     flags |= ImGuiTreeNodeFlags_Selected;

//   if (ImGui::TreeNodeEx(object->getGivenName().c_str(), flags))
//   {
//     if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
//     {
//       ImGui::SetDragDropPayload("DND_DEMO_CELL", (const void *)object->getIDptr(), sizeof(int));

//       ImGui::EndDragDropSource();
//     }

//     if (ImGui::BeginDragDropTarget())
//     {
//       if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
//       {
//         IM_ASSERT(payload->DataSize == sizeof(int));
//         int selectedobj = *(int *)payload->Data;
//         object->giveChild(scenegraph->objectPtr(selectedobj));
//       }
//       ImGui::EndDragDropTarget();
//     }


//     if (ImGui::IsItemClicked())
//     {
//       *selected_instance = object->getID();
//     }

//     std::vector<GameObject *> children = object->getChildren();
//     for (int i=0; i<children.size(); i++)
//     {
//       draw_entity_childnodes(scenegraph, children[i], selected_instance);
//     }


//     ImGui::TreePop();
//   }

//   ImGui::PopID();
// }

// void draw_scene_tab(Renderer *ren, Scene *scene)
// {
//   static int selected_instance = 0;

//   ImGui::BeginChild("entity-child", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 50), false, 0);
//   {
//     ImGui::BeginChild("ChildL", ImVec2(ImGui::GetContentRegionAvail().x/3, 0), false, 0);
//     {
//       if (ImGui::TreeNodeEx("Scene Hierarchy", ImGuiTreeNodeFlags_DefaultOpen))
//       {
//         if (ImGui::BeginDragDropTarget())
//         {
//           if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
//           {
//             IM_ASSERT(payload->DataSize == sizeof(int));
//             int selectedobj = *(int *)payload->Data;
//             scene->object_handler->objectPtr(selected_instance)->clearParent();
//           }
//           ImGui::EndDragDropTarget();
//         }

//         for (auto &object: scene->object_handler->m_object_instances)
//           if (object.hasParent() == false)
//             draw_entity_childnodes(scene->object_handler, &object, &selected_instance);

//         ImGui::TreePop();
//       }

//       ImGui::EndChild();
//     }

//     ImGui::SameLine();

//     ImGui::BeginChild("ChildR", ImVec2(ImGui::GetContentRegionAvail().x, 0), true, 0);
//     {
//       draw_transform_menu(scene, scene->object_handler, selected_instance);  
//       ImGui::EndChild();
//     }

//     ImGui::EndChild();
//   }
//   draw_new_instance_menu(scene->object_handler, &selected_instance);
// }

void draw_lighting_tab(Renderer *ren)
{
  ImGui::Dummy(ImVec2(0.0f, 20.0f));

  char buffer[64];

  if (ImGui::TreeNode("Directional Lights"))
  {
    ImGui::ListBox("Directional light #", &selected_dirlight, dir_options, 1, -1);

    ImGui::PushID(1);
    ImGui::ColorEdit3("ambient", (float*)&ren->dirlights[selected_dirlight].ambient);
    ImGui::ColorEdit3("diffuse", (float*)&ren->dirlights[selected_dirlight].diffuse);
    
    ImGui::Text("Direction");
    ImGui::DragScalar("x", ImGuiDataType_Float, &ren->dirlights[selected_dirlight].direction.x, 0.05f, NULL);
    ImGui::DragScalar("y", ImGuiDataType_Float, &ren->dirlights[selected_dirlight].direction.y, 0.05f, NULL);
    ImGui::DragScalar("z", ImGuiDataType_Float, &ren->dirlights[selected_dirlight].direction.z, 0.05f, NULL);
    // ren->dirlights[0].direction = glm::normalize(ren->dirlights[0].direction);
    ImGui::Dummy(ImVec2(0.0f, 20.0f));

    ImGui::DragScalar("bias", ImGuiDataType_Float, &ren->DIRBIAS, 0.005f, NULL);
    ImGui::PopID();
    ImGui::TreePop();
  }

  if (ImGui::TreeNode("Point Lights"))
  {
    ImGui::ListBox("Point light #", &selected_pointlight, point_options, 4, -1);

    ImGui::PushID(1);
    
    ImGui::Checkbox("Enable", &ren->pointlights_on[selected_pointlight]);

    ImGui::ColorEdit3("ambient", (float*)&ren->pointlights[selected_pointlight].ambient);
    ImGui::ColorEdit3("diffuse", (float*)&ren->pointlights[selected_pointlight].diffuse);
    
    ImGui::SliderFloat("constant", &ren->pointlights[selected_pointlight].constant, 0.0f, 100.0f, "%0.4f", 0);
    ImGui::DragScalar("linear", ImGuiDataType_Float, &ren->pointlights[selected_pointlight].linear,       0.001f, 0);
    ImGui::DragScalar("quadratic", ImGuiDataType_Float, &ren->pointlights[selected_pointlight].quadratic, 0.001f, 0);
    ImGui::DragScalar("bias", ImGuiDataType_Float, &ren->pointlights[selected_pointlight].bias, 0.001f, 0);

    ImGui::Text("Position");
    ImGui::DragScalar("x", ImGuiDataType_Float, &ren->pointlights[selected_pointlight].position.x, 0.05f, 0);
    ImGui::DragScalar("y", ImGuiDataType_Float, &ren->pointlights[selected_pointlight].position.y, 0.05f, 0);
    ImGui::DragScalar("z", ImGuiDataType_Float, &ren->pointlights[selected_pointlight].position.z, 0.05f, 0);
    ImGui::PopID();
    ImGui::TreePop();
  }

  if (ImGui::TreeNode("Spot Lights"))
  {
    ImGui::ListBox("Point light #", &selected_spotlight, spot_options, 2, -1);

    ImGui::Checkbox("Enable", &ren->spotlights_on[selected_spotlight]);

    ImGui::PushID(3);
    ImGui::ColorEdit3("ambient", (float*)&ren->spotlights[selected_spotlight].ambient);
    ImGui::ColorEdit3("diffuse", (float*)&ren->spotlights[selected_spotlight].diffuse);

    // ImGui::DragScalar("constant", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].constant,   0.001f, NULL);
    ImGui::SliderFloat("constant", &ren->spotlights[selected_spotlight].constant, 0.0f, 100.0f, "%0.4f", 0);
    ImGui::DragScalar("linear", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].linear,       0.001f, 0);
    ImGui::DragScalar("quadratic", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].quadratic, 0.001f, 0);

    ImGui::DragScalar("intensity", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].intensity, 0.05f, 0);
    ImGui::DragScalar("inner cutoff", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].inner_cutoff, 0.05f, 0);
    ImGui::DragScalar("outer cutoff", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].outer_cutoff, 0.05f, 0);
    ImGui::DragScalar("fov", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].fov, 0.05f, 0);

    ImGui::Checkbox("follow", &ren->spotlights[selected_spotlight].follow);



    ImGui::PushID(4);
    ImGui::Text("Position");
    ImGui::DragScalar("x", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].position.x, 0.05f, 0);
    ImGui::DragScalar("y", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].position.y, 0.05f, 0);
    ImGui::DragScalar("z", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].position.z, 0.05f, 0);
    ImGui::PopID();
    
    ImGui::PushID(5);
    ImGui::Text("Direction");
    ImGui::DragScalar("x", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].direction.x, 0.05f, 0);
    ImGui::DragScalar("y", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].direction.y, 0.05f, 0);
    ImGui::DragScalar("z", ImGuiDataType_Float, &ren->spotlights[selected_spotlight].direction.z, 0.05f, 0);
    ren->spotlights[selected_spotlight].direction = glm::normalize(ren->spotlights[selected_spotlight].direction);
    ImGui::PopID();
    ImGui::PopID();
    ImGui::TreePop();
  }

  ImGui::Dummy(ImVec2(0.0f, 20.0f));

  if (ImGui::Button("Import"))
    import_lighting_config(ren);
  ImGui::SameLine(ImGui::GetWindowWidth()-60);
  if (ImGui::Button("Export"))
    export_lighting_config(ren);


}

void draw_render_tab(Renderer *ren)
{
  ImGui::Dummy(ImVec2(0.0f, 20.0f));

  ImGui::ColorEdit3("Clear colour", (float*)&ren->clearColor);
  ImGui::SliderFloat("Fog start", &ren->fog_start, 0.0f, 100.0f, "%0.1f", 0);
  ImGui::SliderFloat("Fog end",   &ren->fog_end,   0.0f, 1000.0f, "%0.1f", 0);

  ImGui::SliderFloat("near plane",  &ren->near_plane,  0.1f, 1.0f, "%0.1f", 0);
  ImGui::SliderFloat("Far plane",   &ren->far_plane,   1.0f, 1000.0f, "%0.1f", 0);


  ImGui::Dummy(ImVec2(0.0f, 20.0f));

  ImGui::SliderFloat("FOV", &ren->fov, 45.0f, 110.0f);
  ImGui::SliderFloat("Exposure", &ren->exposure, 0.0f, 10.0f);
  ImGui::SliderFloat("Gamma", &ren->gamma, 0.0f, 5.0f);

  ImGui::Dummy(ImVec2(0.0f, 20.0f));

  ImGui::Text("Image Kernel");

  if (ImGui::BeginTable("Image Kernel", 3))
  {
    char buffer[32];

    for (int row = 0; row < 3; row++)
    {
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::PushID(3*row+0);
      ImGui::DragScalar("", ImGuiDataType_Float, &ren->image_kernel[3*row+0], 1.0f, 0);
      ImGui::PopID();
      
      ImGui::TableNextColumn();
      ImGui::PushID(3*row+1);
      ImGui::DragScalar("", ImGuiDataType_Float, &ren->image_kernel[3*row+1], 1.0f, 0);
      ImGui::PopID();

      ImGui::TableNextColumn();
      ImGui::PushID(3*row+2);
      ImGui::DragScalar("", ImGuiDataType_Float, &ren->image_kernel[3*row+2], 1.0f, 0);
      ImGui::PopID();
    }
  }

  if (ImGui::Button("Invert"))
  {
    for (int i=0; i<9; i++)
      ren->image_kernel[i] = -ren->image_kernel[i];
  }
  if (ImGui::Button("Reset"))
  {
    for (int i=0; i<9; i++)
      ren->image_kernel[i] = 0.0f;
    ren->image_kernel[4] = 1.0f;
  }

  ImGui::EndTable();
  ImGui::DragScalar("Divisor", ImGuiDataType_Float, &ren->kernel_divisor, 1.0f, NULL);
  ImGui::DragScalar("Pixel offset divisor", ImGuiDataType_Float, &ren->kernel_offset_divisor, 1.0f, NULL);


  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void draw_physics_tab(Renderer *ren)
{
  ImGui::SliderFloat("Gravity", &ren->gravity, 0, 10);
  bool fly = false;
  ImGui::Checkbox("Fly", &fly);
}

void draw_dev_ui(Renderer *ren, Scene *scene)
{
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  // draw_main_menu_bar(ren, scene);

  ImGui::Begin("Hello, world!");

  if (ImGui::Button("Demo Window"))
    show = !show;
  if (show)
    ImGui::ShowDemoWindow(&show);

  if (ImGui::BeginTabBar("MyTabBar", 0))
  {
    // if (ImGui::BeginTabItem("Scene"))
    // {
    //   draw_scene_tab(ren, scene);
    //   ImGui::EndTabItem();
    // }

    if (ImGui::BeginTabItem("Lighting"))
    {
      draw_lighting_tab(ren);
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Render"))
    {
      draw_render_tab(ren);
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Physics"))
    {
      draw_physics_tab(ren);
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  ImGui::End();
  ImGui::Render();

}
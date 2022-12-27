#include "entitycomponent.h"
#include "../../GraphicsEngine/GraphicsEngine.h"
#include "../../ui/UIEngine.h"

namespace fs = std::filesystem;


EntityComponent::EntityComponent(EntityComponentType component_type)
{
  this->_component_type = component_type;
}

EntityComponent::EntityComponent(EntityComponentType component_type, PointLight *pointlight)
{
  this->_component_type = component_type;
  this->_pointlight = pointlight;
}

EntityComponent::EntityComponent(EntityComponentType component_type, SpotLight *spotlight)
{
  this->_component_type = component_type;
  this->_spotlight = spotlight;
}


void EntityComponent::_draw_pointlight(void)
{
  int selected_pointlight = 0;
  if (ImGui::CollapsingHeader("Pointlight"))
  {
    ImGui::Checkbox("Enable", &World::scene.pointlights_on[selected_pointlight]);

    ImGui::ColorEdit3("ambient", (float*)&World::scene.pointlights[selected_pointlight].ambient);
    ImGui::ColorEdit3("diffuse", (float*)&World::scene.pointlights[selected_pointlight].diffuse);

    ImGui::SliderFloat("constant", &World::scene.pointlights[selected_pointlight].constant, 0.0f, 100.0f, "%0.4f", 0);
    ImGui::DragScalar("linear", ImGuiDataType_Float, &World::scene.pointlights[selected_pointlight].linear,       0.001f, 0);
    ImGui::DragScalar("quadratic", ImGuiDataType_Float, &World::scene.pointlights[selected_pointlight].quadratic, 0.001f, 0);
    ImGui::DragScalar("bias", ImGuiDataType_Float, &World::scene.pointlights[selected_pointlight].bias, 0.001f, 0);
  }
}


void EntityComponent::_draw_spotlight(void)
{
  int selected_spotlight = 0;
  if (ImGui::CollapsingHeader("Spotlight"))
  {
    ImGui::Checkbox("Enable", &World::scene.pointlights_on[selected_spotlight]);

    ImGui::ColorEdit3("ambient", (float*)&World::scene.pointlights[selected_spotlight].ambient);
    ImGui::ColorEdit3("diffuse", (float*)&World::scene.pointlights[selected_spotlight].diffuse);

    ImGui::SliderFloat("constant", &World::scene.pointlights[selected_spotlight].constant, 0.0f, 100.0f, "%0.4f", 0);
    ImGui::DragScalar("linear", ImGuiDataType_Float, &World::scene.pointlights[selected_spotlight].linear,       0.001f, 0);
    ImGui::DragScalar("quadratic", ImGuiDataType_Float, &World::scene.pointlights[selected_spotlight].quadratic, 0.001f, 0);
    ImGui::DragScalar("bias", ImGuiDataType_Float, &World::scene.pointlights[selected_spotlight].bias, 0.001f, 0);
  }
}


void EntityComponent::_draw_lightsource(void)
{
  if (this->_pointlight != nullptr)
    this->_draw_pointlight();
  else if (this->_spotlight != nullptr)
    this->_draw_spotlight();
}


void EntityComponent::_draw_transform(GameObject *object)
{
  char buffer[128];
  sprintf(buffer, "Transform ##%d", object->getID());
  if (ImGui::CollapsingHeader(buffer))
  {
    EngineUI::vec3("Position", object->getPos(), 0.01f);
    EngineUI::vec3("Velocity", object->getVel(), 0.01f);
    EngineUI::vec3("Rotation", object->getRot(), 0.1f);
  }
}


void EntityComponent::_draw_script(GameObject *object)
{
  if (ImGui::CollapsingHeader(std::string("Script        " + this->script_path.filename().string()).c_str()))
  {
    if (ImGui::Button(std::string(this->script_name + ".lua").c_str()))
      ImGui::OpenPopup("Change Script");


    ImGui::SetNextWindowSize({300, 300});
    if (ImGui::BeginPopup("Change Script"))
    {
      bool changed = false;
      EngineUI::draw_directory_recursive(fs::current_path()/"LuaScripting/scripts", &this->script_path, &changed);
      if (changed)
      {
        fs::path filepath = fs::relative(this->script_path, ".");

        this->script_name = filepath.string();
        this->script_name.erase(this->script_name.size() - 4);
      }
      ImGui::EndPopup();
    }
  }
}




void EntityComponent::draw(GameObject *object)
{
  switch (this->_component_type)
  {
    case (COMPONENT_NONE):
      break;

    case (COMPONENT_TRANSFORM):
      this->_draw_transform(object);
      break;


    case (COMPONENT_LIGHTSOURCE):
      this->_draw_lightsource();
      break;


    case (COMPONENT_SCRIPT):
      this->_draw_script(object);
      break;
  }

}



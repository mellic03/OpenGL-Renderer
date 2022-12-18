#pragma once

#include "../include/glm/glm.hpp"
#include "gameobject.h"
#include "weapon.h"
#include "../transform.h"

class Player {
  
  private:

  //   GameObject m_default_gameobject;
  //   GameObject *m_gameobject = &this->m_default_gameobject;

  //   PhysicsState m_physics_state = PHYSICS_FALLING;
  //   PlayerState current_state = PSTATE_FALLING;
  //   glm::vec3 delta_pos = {0.0f, 0.0f, 0.0f};

  //   std::vector<Mesh *> m_collision_meshes;
  //   std::vector<Transform> m_collision_transforms;

  //   WeaponType m_active_weapon = WEAPON_SHOTGUN;
  //   Weapon m_weapons[1];
  //   Weapon *m_active_weapon_ptr;

  public:

    Camera *cam;

    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 vel = glm::vec3(0.0f);

  //   glm::vec3 pos_worldspace = glm::vec3(0.0f);
  //   glm::vec3 dir_worldspace = glm::vec3(0.0f);
  //   glm::vec3 vel_worldspace = {0.0f, 0.0f, 0.0f};


    float move_speed = 8.0f;
  //   float jump_force = 8.0f;
  //   float friction = 5.0f;

    Player(Renderer *ren);

  //   // Member Access
  //   //----------------------------------------------------

  //   void useWeapon(WeaponType weapon)   { this->m_active_weapon = weapon; this->m_active_weapon_ptr = &this->m_weapons[weapon]; };
  //   Weapon *getWeapon(void)             { return this->m_active_weapon_ptr; };


  //   GameObject *objectPtr(void)         { return this->m_gameobject; };
  //   void setObjectPtr(GameObject *ptr);
  //   Transform *getTransform(void)       { return this->objectPtr()->getTransform(); };
  //   glm::vec3 *getPos(void)             { return this->objectPtr()->getPos(); };
  //   glm::vec3 *getVel(void)             { return this->objectPtr()->getVel(); };
  //   glm::vec3 *getRot(void)             { return this->objectPtr()->getRot(); };
  //   //----------------------------------------------------

    glm::vec3 *getVel(void)  { return &this->vel; };

    void key_input(Renderer *ren);
    void mouse_input(Renderer *ren, SDL_Event *event);


  //   void draw(Renderer *ren);

};
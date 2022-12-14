#pragma once

#include "../../include/glm/glm.hpp"
#include "../gameobject/gameobject.h"
#include "weapon.h"

#include "../../keylog.h"
#include "../../transform.h"
#include "../../audio/AudioEngine.h"

class Player {
  
  private:
  //   WeaponType m_active_weapon = WEAPON_SHOTGUN;
  //   Weapon m_weapons[1];
  //   Weapon *m_active_weapon_ptr;
    AudioEngine::Sound footstepsound;


  public:

    KeyLog keylog;
    Camera *cam;
    GameObject *m_gameobject = nullptr;

    bool fly = false, fly_last = false, fly_changed = false;
    float move_speed = 32.0f;
    float jump_force = 32.0f;
    float friction = 5.0f;

    Player(Renderer *ren);

    // Member Access
    //----------------------------------------------------
    void useGameObject(GameObject *gameobject);
    Transform *getTransform(void)       { return this->m_gameobject->getTransform(); };
    glm::vec3 *getPos(void)             { return this->m_gameobject->getPos(); };
    glm::vec3 *getVel(void)             { return this->m_gameobject->getVel(); };
    //----------------------------------------------------

    void key_input(Renderer *ren);
    void mouse_input(Renderer *ren, SDL_Event *event);


};
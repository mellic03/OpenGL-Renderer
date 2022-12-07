#pragma once

#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/glu.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include "mesh.h"
#include "animation.h"
#include "renderer.h"

#include "../GameEngine/player.h"
class Player;

enum ModelState { MSTATE_NOANIM_PLAYING, MSTATE_ANIM_PLAYING };


class Model {

  private:

    bool use_staticmesh = true;
    Mesh m_staticmesh;
    Mesh m_collision_mesh;

    ModelState m_state = MSTATE_NOANIM_PLAYING;

    AnimationType m_active_animation = ANIM_REST;
    Animation animations[NUM_ANIMATION_TYPES];

    glm::vec3 m_default_position = glm::vec3(0.0f);

  public:

    glm::vec3 *position = &this->m_default_position;

    Model() { };
    
    bool load(std::string filepath);

    void activeAnimation(AnimationType id);
    void playAnimation(Renderer *ren);

    void collideWithPlayer(Player *player);

    void setPos(glm::vec3 *position);

    void drawStaticMesh(Renderer *ren);
    void drawAnimatedMesh(Renderer *ren);
    void draw(Renderer *ren);
};


class InstancedModel {

};

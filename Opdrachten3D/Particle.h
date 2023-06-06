#pragma once
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class Particle {
public:
    glm::vec3 position = glm::vec3(0, 2.1f, 0);                             // Particle position
    glm::vec3 velocity = glm::vec3(0, 0, 0);                                // Particle velocity
    glm::vec3 color = glm::vec3(225.f / 255, 159.f / 255, 0);               // Particle color

    Particle(float xPos, float yPos);

    void update(float dt);

    void render();
};
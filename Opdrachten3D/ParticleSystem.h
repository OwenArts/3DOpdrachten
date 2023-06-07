#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <GL/glew.h>
#include "Particle.h"
#include "Ball.h"

class ParticleSystem {
private:
    std::vector<Particle> particles;
    int numParticles;
    Ball* ball;
    std::vector<std::pair<float, float>> trail; // Object's trail positions

public:
    ParticleSystem(int numParticles, Ball& ball);
    ~ParticleSystem();

    void updateParticles(float dt);
    void updateTrail(float xPos, float zPos);
    void renderParticles();
};
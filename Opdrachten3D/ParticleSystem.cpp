#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int numParticles, Ball& ball) : numParticles(numParticles) {
	particles.reserve(numParticles);
	this->ball = &ball;
}

void ParticleSystem::updateParticles(float dt) {
	// Update all particles
	for (auto& particle : particles) {
		particle.update(dt);
	}
	if (ball->getSpeed() > 0.2)
		updateTrail(ball->position.x, ball->position.z);
}

void ParticleSystem::updateTrail(float xPos, float zPos) {
	particles.emplace_back(xPos, zPos);
	if (particles.size() > numParticles) {
		particles.erase(particles.begin());
	}
}

void ParticleSystem::renderParticles() {
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	for (auto& particle : particles) {
		particle.render();
		glColor3f(0.5f, 0.5f, 0.5f);
	}
	glEnd();
}
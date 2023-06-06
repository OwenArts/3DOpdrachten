#include "Particle.h"
#include <iostream>
Particle::Particle(float xPos, float yPos) {
	position.x = xPos + static_cast<float>(rand() % 100 - 50) / 500.0f;
	position.z = yPos + static_cast<float>(rand() % 100 - 50) / 500.0f;
	position.y = .1f;

	velocity.x = static_cast<float>(rand() % 100 - 50) / 500.0f; // Random initial velocity
	velocity.y = static_cast<float>(rand() % 100 - 50) / 500.0f;
	velocity.z = static_cast<float>(rand() % 100 - 50) / 500.0f;
	color = glm::vec3(225.f / 255, 159.f / 255, 0);
}

void Particle::update(float dt) {
	// Update particle position based on velocity and time
	position.x += velocity.x * dt;
	position.y += 0.05f * dt;
	position.z += velocity.z * dt;

	// Apply some simple physics, like gravity
	velocity.x -= 0.0001f * dt;
	velocity.z -= 0.0001f * dt;
}

void Particle::render() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0f,0.0f,0.0f);
	glVertex3f(position.x, position.y, position.z);
}
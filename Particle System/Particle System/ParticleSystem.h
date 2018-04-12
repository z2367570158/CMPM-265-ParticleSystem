#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Strategy.h"

using namespace sf;
using namespace std;

struct Particle
{
	float velocity, velocityMax;
	float angle, angleMax;
	float size, sizeMax;
	float rotateSpeed, rotateSpeedMax;
	Time lifetime, currentLifetime;
	RectangleShape rect;

	
};


class ParticleSystem
{
public:
	void resetParticle(size_t index);

	float startAngle, startVelocity, startLifetime,startRotation, startSize,startRotateSpeed;
	int angleRand, velocityRand, lifetimeRand, rotationRand, sizeRand, rotateSpeedRand;

	vector<Particle> particles;
	Vector2f emitterPosition;
	Texture texture;

	StrategyBase *angleStrategy = nullptr;
	StrategyBase *velocityStrategy = nullptr;
	StrategyBase *sizeStrategy = nullptr;
	StrategyBase *rotateStrategy = nullptr;

	ParticleSystem(unsigned int count);
	ParticleSystem(unsigned int count, float startAngle, float startVelocity, float startLifetime, float startRotation, float startSize, float startRotateSpeed, int angleRand, int velocityRand, int lifetimeRand, int rotationRand, int sizeRand, int rotateSpeedRand);
	
	
	void setEmitter(sf::Vector2f position);
	void update(sf::Time elapsed);
};

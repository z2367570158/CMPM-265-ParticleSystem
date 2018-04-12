#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(unsigned int count, float startAngle, float startVelocity, float startLifetime, float startRotation, float startSize, float startRotateSpeed, int angleRand, int velocityRand, int lifetimeRand, int rotationRand, int sizeRand, int rotateSpeedRand)
{
	particles = vector<Particle>(count);
	this->startAngle = startAngle;
	this->startVelocity = startVelocity;
	this->startLifetime = startLifetime;
	this->startRotation = startRotation;
	this->startSize = startSize;
	this->startRotateSpeed = startRotateSpeed;
	this->angleRand = angleRand;
	this->velocityRand = velocityRand;
	this->lifetimeRand = lifetimeRand;
	this->rotationRand = rotationRand;
	this->sizeRand = sizeRand;
	this->rotateSpeedRand = rotateSpeedRand;
	emitterPosition = Vector2f(0, 0);

}

ParticleSystem::ParticleSystem(unsigned int count)
{
	particles = vector<Particle>(count);
	this->startAngle = 270;
	this->startVelocity = 150;
	this->startLifetime = 2000;
	this->startRotation = 0;
	this->startSize = 60;
	this->startRotateSpeed = 0;
	this->angleRand = 360;
	this->velocityRand = 1;
	this->lifetimeRand = 2000;
	this->rotationRand = 1;
	this->sizeRand = 1;
	this->rotateSpeedRand = 1;
	emitterPosition = Vector2f(0, 0);

}

void ParticleSystem::resetParticle(std::size_t index)
{
	particles[index].angle = (std::rand() % angleRand+ startAngle - angleRand/2) * 3.14f / 180.f;
	particles[index].angleMax = particles[index].angle;
	particles[index].velocity = (std::rand() % velocityRand) + startVelocity - velocityRand/2;
	particles[index].velocityMax = particles[index].velocity;
	particles[index].lifetime = sf::milliseconds((std::rand() % lifetimeRand) + startLifetime - lifetimeRand/2);
	particles[index].currentLifetime = particles[index].lifetime;
	particles[index].rotateSpeed = rand() % rotateSpeedRand + startRotateSpeed - rotateSpeedRand / 2;
	particles[index].rotateSpeedMax = particles[index].rotateSpeed;
	particles[index].size = rand() % sizeRand + startSize - sizeRand / 2;
	particles[index].sizeMax = particles[index].size;
	particles[index].rect.setSize(Vector2f(particles[index].size, particles[index].size));
	particles[index].rect.setOrigin(Vector2f(particles[index].rect.getSize().x/2, particles[index].rect.getSize().y/2));
	particles[index].rect.setPosition(emitterPosition);
	particles[index].rect.setRotation(std::rand()% rotationRand + startRotation - rotationRand/2);
	particles[index].rect.setTexture(&texture);
}


void ParticleSystem::setEmitter(sf::Vector2f position)
{
	emitterPosition = position;
}





void ParticleSystem::update(sf::Time elapsed)
{
	for (std::size_t i = 0; i < particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = particles[i];
		p.currentLifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.currentLifetime <= sf::Time::Zero)
			resetParticle(i);


		float ratio = (p.lifetime.asSeconds()-p.currentLifetime.asSeconds()) / p.lifetime.asSeconds();
		float ratioAnti = p.currentLifetime.asSeconds() / p.lifetime.asSeconds();

		if(velocityStrategy!= nullptr)
			particles[i].velocity = velocityStrategy->update(ratio)*particles[i].velocityMax;
		if (angleStrategy != nullptr)
			particles[i].angle = angleStrategy->update(ratio)*particles[i].angleMax + particles[i].angle;
		if (rotateStrategy != nullptr)
			particles[i].rotateSpeed = rotateStrategy->update(ratio)*particles[i].rotateSpeedMax;
		if (sizeStrategy != nullptr)
			particles[i].size = sizeStrategy->update(ratio)*particles[i].sizeMax;


		// update the position of the corresponding vertex
		particles[i].rect.move(cos(p.angle) * p.velocity* elapsed.asSeconds(), sin(p.angle) * p.velocity* elapsed.asSeconds());
		particles[i].rect.rotate(particles[i].rotateSpeed * elapsed.asSeconds());
		particles[i].rect.setSize(Vector2f(particles[i].size, particles[i].size));


		// update the alpha (transparency) of the particle according to its lifetime
		Color c = Color(p.rect.getFillColor());
		c.b = static_cast<sf::Uint8>(ratio * 55+100);
		c.g = static_cast<sf::Uint8>(ratio * 55+100);
		c.a = static_cast<sf::Uint8>(ratioAnti * 255);
		p.rect.setFillColor(c);
	}
}

/*--------------------------------------------------------------
File Name: Particle.cpp
Project: Slimy Doodly
Author: Kevin Wright, Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Particle.h"

#include "../Engine/Engine.h"
#include "GameObjectManager.h"
#include "World.h"

ParticleEmitter::ParticleEmitter(std::string spriteFile, int totalParticles, double lifetime) : numParticles(totalParticles),
                                                                                                particles(numParticles, nullptr), lifetime(lifetime), particleToUse(0)
{
    GameObjectManager& gameObjectManager = World::GetObjects();
    for(Particle*& particlePtr : particles)
    {
        particlePtr = new Particle(spriteFile);
        gameObjectManager.Add(particlePtr);
    }
}

void ParticleEmitter::Emit(int toEmit, Vector2D emitterPosition, Vector2D emitterVelocity, Vector2D emitVector, double spread)
 {
    for(int index = 0; index < toEmit; ++index)
    {
        if(particles[particleToUse]->IsAlive() == true)
        {
            Engine::GetLogger().LogError("Particle is being overwritten");
        }

        double angleVariation = spread != 0 ? (static_cast<double>(rand() % static_cast<int>(spread * 1024)) / 1024.0f) - spread / 2 : 0;
        particles[particleToUse]->Revive(emitterPosition, emitterVelocity + RotateMatrix(angleVariation) * emitVector, lifetime);

        if(++particleToUse == numParticles)
        {
            particleToUse -= numParticles;
        }
    }
}

void ParticleEmitter::Emit(int toEmit, Vector2D emitterPosition, Vector2D emitterVelocity, Vector2D emitVector, double spread, double angle)
{
    for (int index = 0; index < toEmit; ++index)
    {
        if (particles[particleToUse]->IsAlive() == true)
        {
            Engine::GetLogger().LogError("Particle is being overwritten");
        }

        double angleVariation = spread != 0 ? (static_cast<double>(rand() % static_cast<int>(spread * 1024)) / 1024.0f) - spread / 2 : 0;
        particles[particleToUse]->SetRotation(angle);
        particles[particleToUse]->Revive(emitterPosition, emitterVelocity + RotateMatrix(angleVariation) * emitVector, lifetime);

        if (++particleToUse == numParticles)
        {
            particleToUse -= numParticles;
        }
    }
}

void ParticleEmitter::Clear()
{
    particles.clear();
}

ParticleEmitter::Particle::Particle(std::string spriteFile) : GameObject(Vector2D(), Vector2D(0, 0)) , life(0.)
{
    sprite.Load(spriteFile);
}

void ParticleEmitter::Particle::Revive(Vector2D newPosition, Vector2D newVelocity, double newLife)
{
    sprite.PlayAnimation(0);
    SetPosition(newPosition);
    velocity = newVelocity;
    life = newLife;
}

void ParticleEmitter::Particle::Update(double dt)
{
    if (IsAlive() == true)
    {
        life -= dt;
        currState->Update(this, dt);
        if (velocity.x != 0 || velocity.y != 0) {
            UpdatePosition(velocity * dt);
        }
        sprite.Update(dt);
        currState->TestForExit(this);
    }
}

void ParticleEmitter::Particle::Draw(TransformMatrix displayMatrix)
{
    if(IsAlive() == true)
    {
        GameObject::Draw(displayMatrix);
        //sprite.Draw(displayMatrix * GetMatrix());
    }
}

bool ParticleEmitter::Particle::IsAlive() const
{
    return life > 0;
}

//GameObjectType ParticleEmitter::Particle::GetObjectType()
//{
//    return GameObjectType::Particle;
//}

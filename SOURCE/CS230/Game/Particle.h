/*--------------------------------------------------------------
File Name: Particle.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <string>
#include <vector>
#include "..\Engine\BasicDataTypes.h"  //Vector2
#include "GameObject.h"

class TransformMatrix;

class ParticleEmitter {
public:
    ParticleEmitter(std::string spriteFile, int totalParticles, double lifetime);
    void Emit(int toEmit, Vector2D emitterPosition, Vector2D emitterVelocity, Vector2D emitVector, double spread);
    void Emit(int toEmit, Vector2D emitterPosition, Vector2D emitterVelocity, Vector2D emitVector, double spread, double angle);
    void Clear();

private:
    class Particle : public GameObject {
    public:
        Particle(std::string spriteFile);
        void Revive(Vector2D position, Vector2D velocity, double life);
        void Update(double dt) override;
        void Draw(TransformMatrix displayMatrix) override;
        [[nodiscard]] bool IsAlive() const;

        //GameObjectType GetObjectType() override;
        //std::string GetObjectTypeName() override { return "Particle"; }

    private:
        double life;
    };

    int numParticles;
    std::vector<Particle*> particles;
    int particleToUse;
    double lifetime;

public:
    std::vector<Particle*>::iterator begin() { return particles.begin(); }
    std::vector<Particle*>::iterator end() { return particles.end(); }
};

/*--------------------------------------------------------------
File Name: GameObject.h
Project: Slimy Doodly
Author: Kevin Wright, Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once

#include "..\Engine\BasicDataTypes.h"	//Vector2D
#include "..\Engine\Sprite.h"			//Sprite
#include "..\Engine\TransformMatrix.h"	//TransformMatrix

class Tile;
class GameObject {
public:
	GameObject(Vector2D position, Vector2D size);
	GameObject(Vector2D position, Vector2D size, double rotation, Vector2D scale);

	virtual void Update(double dt);
	virtual void Draw(TransformMatrix displayMatrix);

	const TransformMatrix& GetMatrix();
    [[nodiscard]] Vector2D GetPosition() const;
	[[nodiscard]] Vector2D GetScale() const;
	[[nodiscard]] double GetRotation() const;
	[[nodiscard]] Vector2D GetSize() const;
	[[nodiscard]] Rect GetCollisionBox() const;
	void AddVelocity(Vector2D anotherVelocity);
	void SetVelocity(Vector2D newVelocity);
	void MakeDead() { isDead = true; }
	bool GetIsDead() { return isDead; }
	void SetRotation(double newRotationAmount);

protected:
	void SetPosition(Vector2D newPosition);
	void SetPositionX(double newPosX);
	void SetPositionY(double newPosY);
	void UpdatePosition(Vector2D adjustPosition);
	void SetScale(Vector2D newScale);

	void UpdateRotation(double newRotationAmount);

	//Collision Stuffs
	void ApplyGravity(double dt);
	void ResolveMapCollision(double dt);
	void DrawHitBox(TransformMatrix displayMatrix) const;
    [[nodiscard]] bool IsOnGround() const;
	void updateIsOnGround();

	Sprite sprite;
	Vector2D velocity;
	bool isOnGround;
	bool isFlipped;
	
private:
	TransformMatrix objectMatrix;
	bool updateMatrix;
	Tile* tileOnGround;

	double rotation;
	Vector2D scale;
	Vector2D position;
	Vector2D size;
	bool isDead;
	
protected:
	class State {
	public:
		virtual void Enter(GameObject* object) = 0;
		virtual void Update(GameObject* object, double dt) = 0;
		virtual void TestForExit(GameObject* object) = 0;
		virtual std::string GetName() = 0;
	};
	class State_Nothing : public State {
	public:
		void Enter(GameObject*) override {};
		void Update(GameObject*, double) override {};
		void TestForExit(GameObject*) override {};
		std::string GetName() override { return ""; }
	};
	class State_Falling : public State {
	public:
		void Enter(GameObject*) override = 0 ;
		void Update(GameObject*, double) override;
		void TestForExit(GameObject*) override = 0;
		std::string GetName() override { return "State Falling(Base)"; }
	};

	State_Nothing state_nothing;
	State* currState;

public:
	void ChangeState(State* newState);
};
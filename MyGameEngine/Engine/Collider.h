#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Collider
{
	float radius_;

public:
	Collider(float radius);
	float GetRadius() { return radius_; }
};


#pragma once
#include "CollisionPrimitive.h"
#include <DirectXMath.h>
class Collision
{
protected: // エイリアス
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	static bool ChenkSphere2Sphere(XMFLOAT3 pos1, XMFLOAT3 pos2, float r1, float r2);
	static bool ChenkSphere2Plane(const Sphere &sphere, const Plane &plane, DirectX::XMVECTOR *inter = nullptr);
	static void Collision::ClosestPtPoint2Triangle(const DirectX::XMVECTOR &point, const Triangle &triangle, DirectX::XMVECTOR *closest);

	static bool CheckSpere2Triangle(const Sphere &sphere, const Triangle &triangle, DirectX::XMVECTOR *inter = nullptr);

	static bool CheckRay2Plane(const Ray &ray, const Plane &plane, float *distance = nullptr, DirectX::XMVECTOR *inter = nullptr);
	static bool CheckRay2Triangle(const Ray &ray, const Triangle &triangle,float *distance = nullptr, DirectX::XMVECTOR *inter = nullptr);
	static bool CheckRay2Sphere(const Ray &ray, const Sphere &sphere,float *distance = nullptr, DirectX::XMVECTOR *inter = nullptr);
};
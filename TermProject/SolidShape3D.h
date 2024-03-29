#pragma once

#include "Material.h"
#include "Vector3.h"

class SolidShape3D
{
public:
	SolidShape3D();
	SolidShape3D(const SolidShape3D& sh3d);

	void setCyan();
	void setGreen();
	void setRed();
	void setYellow();

	void setCenter(float x, float y, float z);
	void setCenter(const Vector3& c);
	Vector3 getCenter() const;
	void setVelocity(float x, float y, float z);
	void setVelocity(const Vector3& v);
	Vector3 getVelocity() const;
	void move();
	void setMTL();
	virtual void draw() const = 0;
	int getColor();

protected:
	enum { RED, GREEN, CYAN, YELLOW };
	Vector3 center;
	Vector3 velocity;
	Material mtl;
	int color;
};


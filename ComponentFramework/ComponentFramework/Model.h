#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "MMath.h"
#include "Mesh.h"
#include "Shader.h"
#include "Quaternion.h"
#include <iostream>

namespace GAME {
using namespace MATH;

class PhysicsModel {
	friend class Physics;		/// This a test of the idea I had about using
protected:						/// a static Physics class that is a friend 
	Vec3 pos;					/// of just the data in the PhysicsModel class
	Vec3 vel;
	Vec3 accel;
	Quaternion orientation;
	Vec3 angularVelocity;
	float mass;
	bool useGravity;
	Sphere boundingSphere;
};


class Model: public PhysicsModel {
protected:
	Matrix4 modelMatrix;
	const std::vector<Mesh*> meshes;
	const Shader*  shader;
public:

	inline void setPos(const Vec3& pos_){ pos = pos_; }
	inline void setVel(const Vec3& vel_){ vel = vel_; }
	inline void setAccel(const Vec3& accel_) { accel = accel_; }
	inline void setMass(const float& mass_) { mass = mass_; }
	void setAngularVelocity(Vec3& angularVelocity_) { angularVelocity = angularVelocity_;  }
	void setOrientation(Quaternion& orientation_) { orientation = orientation_; }
	//HERE'S THE TWO METHODS THAT *I* CHANGED 
	inline Vec3 getPos() { return pos; }
	void comparePos(Vec3 pos_,float deltaTime);
	inline void setBoundingSphere(const float r) { boundingSphere = pos;  boundingSphere.r = r; }
	Model(const Model&) = delete;
	Model(Model&&) = delete;
	Model& operator = (const Model&) = delete;
	Model& operator = (Model&&) = delete;

	Model(const std::vector<Mesh*> meshes_, const Shader* shader_);
	bool OnCreate();
	void OnDestroy();
	void Render() const;
	void Update(const float deltaTime);
	virtual ~Model();
	
};


} /// end of namespace

#endif
#include "Model.h"
#include "Physics.h"

using namespace GAME;
using namespace MATH;
//New Fancy method
void GAME::Model::comparePos(Vec3 pos_,float deltaTime)
{
	//The paramater is the incoming object.
	//This here program sets our initial velocity
	if (accel.x == 0.0f) {
		if (pos.x < pos_.x) {
			accel.x = 1.0f;
		}
		else {
			accel.x = -1.0f;
		}
	}
	//Does the third step of 4 when it comes to setting velocity.
	vel.x = vel.x + accel.x*deltaTime;
}

Model::Model(const std::vector<Mesh*> meshes_, const Shader*  shader_): meshes(meshes_), shader(shader_) {
	useGravity = false;
}

bool Model::OnCreate() {

	return true;
}

void Model::OnDestroy() {}


void Model::Render() const {

	int nbrOfVertices = meshes.at(0)->vertices.size();
	for (int i = 0; i < nbrOfVertices; i++) {

		Vec3 vertex = meshes.at(0)->vertices.at(i);
		Vec4 P_Local = Vec4(vertex.x, vertex.y, vertex.z, 1.0f);
		Vec4 P_World = modelMatrix * P_Local;
		std::cout << P_World.x << " " << P_World.y << " " << P_World.z << std::endl;

	}

	Quaternion q = orientation;
	Matrix4 rotationMatrix = q.toMatrix();
	Matrix4 modelMatrix = MMath::translate(pos) * rotationMatrix;
	GLint modelMatrixID = glGetUniformLocation(shader->getProgram(), "modelMatrix");
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix);
	for (Mesh* mesh : meshes) {
		mesh->Render();
	}
}

void Model::Update(const float deltaTime) {
	Physics::SimpleNewtonMotion( *this, deltaTime);
	boundingSphere = pos;
}

Model::~Model() {}
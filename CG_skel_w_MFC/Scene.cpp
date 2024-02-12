#include "stdafx.h"
#include "Scene.h"
#include "MeshModel.h"
#include <string>

using namespace std;

float radians(float degrees) {
	return degrees * (M_PI / 180.0f);
}

void Model::setShowNormals(bool show) {
	return;
}

void Camera::Perspective(float fovy, float aspect, float zNear, float zFar) {
	float tanHalfFovy = tan(fovy / 2.0f);

	projection = mat4(
		1.0f / (tanHalfFovy * aspect), 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / tanHalfFovy, 0.0f, 0.0f,
		0.0f, 0.0f, -(zFar + zNear) / (zFar - zNear), -2.0f * zFar * zNear / (zFar - zNear),
		0.0f, 0.0f, -1.0f, 0.0f
	);
}

void Camera::UpdateProjectionMatrix(float aspect_ratio)
{
	// Assuming you have member variables like fov, near_clip, and far_clip
	Perspective(radians(FOV), aspect_ratio, NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);
}

void Scene::loadOBJModel(string fileName)
{
	MeshModel* model = new MeshModel(fileName);
	models.push_back(model);
	num_of_models++;
}

void Scene::addMeshModel(Model* model)
{
	MeshModel* model_to_push = dynamic_cast<MeshModel*>(model);
	if (model_to_push) {
		models.push_back(model_to_push);
		num_of_models++;
	}
}

// Iterate over the models and call setShowNormals for MeshModels
void Scene::setShowNormalsForMeshModels(bool change) {
	for (Model* model : models) {
		// Check if the model is of type MeshModel
		MeshModel* meshModel = dynamic_cast<MeshModel*>(model);
		if (meshModel != nullptr) {
			// It's a MeshModel, call setShowNormals
			meshModel->setShowNormals(change);
		}
	}
}

void Scene::setShowBoxForMeshModels(bool change) {
	for (Model* model : models) {
		// Check if the model is of type MeshModel
		MeshModel* meshModel = dynamic_cast<MeshModel*>(model);
		if (meshModel != nullptr) {
			// It's a MeshModel, call setShowBox
			meshModel->setShowBox(change);
		}
	}
}

void Scene::translateObjects(GLfloat x_trans, GLfloat y_trans, GLfloat z_trans)
{
	for (Model* model : models) {
		// Check if the model is of type MeshModel
		MeshModel* meshModel = dynamic_cast<MeshModel*>(model);
		if (meshModel != nullptr) {
			// It's a MeshModel, call setShowBox
			meshModel->translate(x_trans, y_trans, z_trans);
		}
	}
}

void Scene::rescaleModels(GLfloat scale)
{
	for (Model* model : models) {
		// Check if the model is of type MeshModel
		MeshModel* meshModel = dynamic_cast<MeshModel*>(model);
		if (meshModel != nullptr) {
			// It's a MeshModel, call scale
			meshModel->scale(scale, scale, scale);
		}
	}
}
void Scene::rotateModels(GLfloat theta_angle, int mode)
{
	for (Model* model : models) {
		// Check if the model is of type MeshModel
		MeshModel* meshModel = dynamic_cast<MeshModel*>(model);
		if (meshModel != nullptr) {
			// It's a MeshModel, call rotate
			meshModel->rotate(theta_angle, mode);
		}
	}
}

void Scene::removeObjects()
{
	for (Model* model : models) {
		if (model != nullptr) {
			delete model;
		}
	}
	models.clear();
}

void Scene::draw()
{
	// 1. Send the renderer the current camera transform and the projection
	// 2. Tell all models to draw themselves
	for (Model* model : models) {
		// Check if the model is of type MeshModel
		MeshModel* meshModel = dynamic_cast<MeshModel*>(model);
		if (meshModel != nullptr) {
			meshModel->draw(m_renderer);
		}
		// You can handle other types of models here if needed
	}
	m_renderer->SwapBuffers();
}

void Scene::drawDemo()
{
	m_renderer->SetDemoBuffer();
	m_renderer->SwapBuffers();
}


void Camera::setTransformation(const mat4& transform) {
	cTransform = transform;
}
void Camera::setProjection(const mat4& perspective) {
	projection = perspective;
}
mat4 Camera::getProjection() {
	return projection;
}
mat4 Camera::getTransform() {
	return cTransform;
}

mat4 Camera::getTransformInverse() {
	return cTransformInverse;
}

void Camera::LookAt(const vec4& eye, const vec4& at, const vec4& up) {
	/* Create 3 directional vectors (Tut 3: slide 9)*/
	vec4 n = vec4(normalize(toVec3(eye - at)));	//I make it Vec3 because normalizing with W would be wrong
	vec4 u = vec4(cross(up, n), 0);
	vec4 v = vec4(cross(n, u), 0);

	mat4 rotate_inv = mat4(u, v, n, vec4(0, 0, 0, 1));

	// set the matrixes stored.
	cTransformInverse = rotate_inv * Translate(-eye);
	cTransform = Translate(eye) * transpose(rotate_inv);
}

void Camera::Ortho(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar) {
	projection = mat4(2 / (right - left), 0, 0, -(left + right) / (right - left),
		0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
		0, 0, -2 / (zFar - zNear), -(zFar + zNear) / (zFar - zNear),
		0, 0, 0, 1);
}

void Camera::Frustum(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar) {

}

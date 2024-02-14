#pragma once
#include "scene.h"
#include "vec.h"
#include "mat.h"
#include <string>

using namespace std;

class MeshModel : public Model
{
protected:
	MeshModel() {}
	vec3* vertex_positions;
	vec3* normals_to_vertices;
	int vertex_count;
	int face_count;

	bool show_vertex_normals;
	bool show_face_normals;
	bool show_box;

	bool vn_in_file;

	vec3* normals;
	vec3 bounding_box[8];
	//add more attributes
	mat4 _world_transform;
	mat3 _normal_transform;

public:

	MeshModel(string fileName);
	~MeshModel(void);
	void loadFile(string fileName);
	void draw(Renderer* renderer) override;

	void translate(GLfloat x_trans, GLfloat y_trans, GLfloat z_trans) override;
	vec3 translatePoint(vec3 point, GLfloat x_trans, GLfloat y_trans, GLfloat z_trans);
	void rotate(GLfloat theta_angle, int mode) override;
	void scale(GLfloat x_scale, GLfloat y_scale, GLfloat z_scale) override;
	void calculateBoundingBox();
	void CalculateVertexNormals();
	void normalToFace();

	void applyWorldTransformation(const mat4& transformation) override;
	void applyModelTransformation(const mat4& transformation) override;

	void setShowNormals(bool change) override;
	void setShowNormalsToVertices(bool change) override;
	void setShowBox(bool change) override;
};

class PrimMeshModel : public MeshModel
{
	bool draw_cube;
	bool draw_sphere;
public:
	PrimMeshModel(bool drawCube = false, bool drawSphere = false)
		: draw_cube(drawCube), draw_sphere(drawSphere)
	{
		if (draw_cube)
		{
			cube();
		}
		else if (draw_sphere)
		{
			Sphere();
		}
	}
	void cube()
	{
		// Hardcoded cube vertices
		vertex_count = 8;
		vertex_positions = new vec3[vertex_count];
		vertex_positions[0] = vec3(-0.5f, -0.5f, -0.5f);
		vertex_positions[1] = vec3(0.5f, -0.5f, -0.5f);
		vertex_positions[2] = vec3(0.5f, 0.5f, -0.5f);
		vertex_positions[3] = vec3(-0.5f, 0.5f, -0.5f);
		vertex_positions[4] = vec3(-0.5f, -0.5f, 0.5f);
		vertex_positions[5] = vec3(0.5f, -0.5f, 0.5f);
		vertex_positions[6] = vec3(0.5f, 0.5f, 0.5f);
		vertex_positions[7] = vec3(-0.5f, 0.5f, 0.5f);
	}

	void Sphere()
	{
		int latitudeDivisions = 20;
		int longitudeDivisions = 20;
		// Calculate sphere vertices
		vertex_count = (latitudeDivisions + 1) * (longitudeDivisions + 1);
		vertex_positions = new vec3[vertex_count];

		float deltaTheta = static_cast<float>(2.0 * M_PI) / static_cast<float>(latitudeDivisions);
		float deltaPhi = static_cast<float>(M_PI) / static_cast<float>(longitudeDivisions);

		int vertexIndex = 0;
		for (int i = 0; i <= longitudeDivisions; ++i)
		{
			float phi = static_cast<float>(i) * deltaPhi;
			for (int j = 0; j <= latitudeDivisions; ++j)
			{
				float theta = static_cast<float>(j) * deltaTheta;

				float x = std::sin(phi) * std::cos(theta);
				float y = std::cos(phi);
				float z = std::sin(phi) * std::sin(theta);

				vertex_positions[vertexIndex++] = vec3(x, y, z);
			}
		}

		// Calculate sphere faces (indices)
		face_count = 2 * latitudeDivisions * longitudeDivisions;
	}
	~PrimMeshModel()
	{
		// Clean up allocated memory
		delete[] vertex_positions;
	}
};

vec3 calculateNormal(vec3 first_point, vec3 second_point, vec3 third_point);
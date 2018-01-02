#ifndef CUBE_HEADER
#define CUBE_HEADER

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <ctime>

#include "../shaders/shprogram.h"

class Cubes
{
public:
	explicit Cubes(unsigned int numCubes)
		: m_radius(0.5f), m_color1(glm::vec3(0.0, 0.8, 0.9)), m_color2(glm::vec3(0.0, 0.0, 0.9)), m_numCubes(numCubes), 
		m_shprogram("res\\vsh.shader", "res\\fsh.shader"), m_MAX_DISTANCE_OF_CUBES(50), m_speed(0.05f), m_direction(0.0f, 0.0f, 1.0f),
		m_rotationDelta(1.0f)
	{
		srand(time(NULL));

		CreateVertices();
		CreateIndices();
		CreateBuffer();
		CreateIndexBuffer();
		CreateVertexArray();
		m_shprogram.Compile();
		m_shprogram.Link();
		InitializeTranslateVectors();
		InitializeRotation();
		CreateMatricesBuffer();
		InitializeDivisors();
	}
public:
	void Draw(glm::mat4 projectionMatrixWithCamera)
	{
		//glm::mat4 transformMatrix = projectionMatrixWithCamera * glm::translate(glm::vec3(0.0f, 3.0f, -10.0f));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
		glBindBuffer(GL_ARRAY_BUFFER, m_transformMatricesBufferID);
		glBindVertexArray(m_vertexArrayID);

//		unsigned int location = glGetUniformLocation(m_shprogram.ProgramID(), "transformMatrix");
//		glUniformMatrix4fv(location, 1, GL_FALSE, &transformMatrix[0][0]);

		for (unsigned int i = 0; i < m_numCubes; ++i)
		{
			m_transformMatrices[i] = projectionMatrixWithCamera * glm::translate(m_translateVectors[i]) *
				glm::rotate(glm::radians(m_rotationAngle[i]), m_rotationValues[i]);
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * m_numCubes, m_transformMatrices, GL_DYNAMIC_DRAW);

		glDrawElementsInstanced(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, 0, m_numCubes);

		UpdateTranslateVectors();
		UpdateRotations();
		CheckIfCubesSurpassedLimit();
	}
private:
	void CreateVertices(void)
	{
		// colors glm::vec3(0.0, 0.8, 0.9)
		//		  glm::vec3(0.0, 0.8, 0.7)
		glm::vec3 verts[]
		{
			// face 1 +z
			glm::vec3(-m_radius, +m_radius, +m_radius),		//1
			m_color1,
			glm::vec3(+m_radius, +m_radius, +m_radius),		//2
			m_color1,
			glm::vec3(+m_radius, -m_radius, +m_radius),		//3
			m_color1,

			glm::vec3(-m_radius, +m_radius, +m_radius),		//4
			m_color2,
			glm::vec3(+m_radius, -m_radius, +m_radius),		//5
			m_color2,
			
			glm::vec3(-m_radius, -m_radius, +m_radius),		//6
			m_color2,
			//face 2 +x
			glm::vec3(+m_radius, +m_radius, -m_radius),		//7
			m_color1 * 0.8f,
			glm::vec3(+m_radius, -m_radius, -m_radius),		//8
			m_color1 * 0.8f,
			glm::vec3(+m_radius, -m_radius, +m_radius),		//9
			m_color1 * 0.8f,

			glm::vec3(+m_radius, +m_radius, +m_radius),		//10
			m_color2 * 0.8f,
			glm::vec3(+m_radius, -m_radius, +m_radius),		//11
			m_color2 * 0.8f,
			glm::vec3(+m_radius, +m_radius, -m_radius),		//12
			m_color2 * 0.8f,
			//face 3 +y
			glm::vec3(+m_radius, +m_radius, +m_radius),		//13
			m_color1 * 0.7f,
			glm::vec3(+m_radius, +m_radius, -m_radius),		//14
			m_color1 * 0.7f,
			glm::vec3(-m_radius, +m_radius, -m_radius),		//15
			m_color1 * 0.7f,

			glm::vec3(+m_radius, +m_radius, +m_radius),		//16
			m_color2 * 0.7f,
			glm::vec3(-m_radius, +m_radius, -m_radius),		//17
			m_color2 * 0.7f,
			glm::vec3(-m_radius, +m_radius, +m_radius),		//18
			m_color2 * 0.7f,
			//face 4 -z
			glm::vec3(+m_radius, -m_radius, -m_radius),		//19
			m_color2 * 0.9f,
			glm::vec3(+m_radius, +m_radius, -m_radius),		//20
			m_color2 * 0.9f,
			glm::vec3(-m_radius, +m_radius, -m_radius),		//21
			m_color2 * 0.9f,

			glm::vec3(+m_radius, -m_radius, -m_radius),		//22
			m_color1 * 0.9f,
			glm::vec3(-m_radius, +m_radius, -m_radius),		//23
			m_color1 * 0.9f,
			glm::vec3(-m_radius, -m_radius, -m_radius),		//24
			m_color1 * 0.9f,
			//face 5 -x
			glm::vec3(-m_radius, +m_radius, -m_radius),		//25
			m_color2 * 0.7f,
			glm::vec3(-m_radius, -m_radius, -m_radius),
			m_color2 * 0.7f,
			glm::vec3(-m_radius, -m_radius, +m_radius),
			m_color2 * 0.7f,

			glm::vec3(-m_radius, +m_radius, +m_radius),
			m_color1 * 0.7f,
			glm::vec3(-m_radius, -m_radius, +m_radius),
			m_color1 * 0.7f,
			glm::vec3(-m_radius, +m_radius, -m_radius),
			m_color1 * 0.7f,
			//face 6 -y
			glm::vec3(-m_radius, -m_radius, -m_radius),
			m_color1 * 0.6f,
			glm::vec3(-m_radius, -m_radius, +m_radius),
			m_color1 * 0.6f,
			glm::vec3(+m_radius, -m_radius, +m_radius),
			m_color1 * 0.6f,

			glm::vec3(-m_radius, -m_radius, -m_radius),
			m_color2 * 0.6f,
			glm::vec3(+m_radius, -m_radius, +m_radius),
			m_color2 * 0.6f,
			glm::vec3(+m_radius, -m_radius, -m_radius),
			m_color2 * 0.6f
		};
		m_vertexDataSize = sizeof(verts);
		m_numVertices = m_vertexDataSize / sizeof(glm::vec3);
		m_verts = new glm::vec3[m_numVertices];
		memcpy(m_verts, verts, m_vertexDataSize);

		Log("created vertices");
	}
	void CreateIndices(void)
	{
		unsigned short indices[]
		{
			0, 1, 2, 3, 4, 5, 
			6, 7, 8, 9, 10, 11,
			12, 13, 14, 15, 16, 17, 
			18, 19, 20, 21, 22, 23, 
			24, 25, 26, 27, 28, 29,
			30, 31, 32, 33, 34, 35
		};
		m_indexDataSize = sizeof(indices);
		m_numIndices = m_indexDataSize / sizeof(unsigned short);
		m_indices = new unsigned short[m_numIndices];
		memcpy(m_indices, indices, m_indexDataSize);
		Log("created indices");
	}
	void CreateBuffer(void)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, m_vertexDataSize, m_verts, GL_STATIC_DRAW);
	}
	void CreateIndexBuffer(void)
	{
		glGenBuffers(1, &m_indexID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexDataSize, m_indices, GL_STATIC_DRAW);
	}
	void CreateVertexArray(void)
	{
		glGenVertexArrays(1, &m_vertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBindVertexArray(m_vertexArrayID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	void CreateMatricesBuffer(void)
	{
		m_transformMatrices = new glm::mat4[m_numCubes];
		glGenBuffers(1, &m_transformMatricesBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_transformMatricesBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * m_numCubes, 0, GL_DYNAMIC_DRAW);
	}
	void InitializeDivisors(void)
	{
		for (unsigned int i = 2; i < m_numCubes * 2 + 2; ++i)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * (i - 2) * 4));
			glVertexAttribDivisor(i, 1);
		}
	}
	void InitializeTranslateVectors(void)
	{
		m_translateVectors = new glm::vec3[m_numCubes];
		for (unsigned int i = 0; i < m_numCubes; ++i)
		{
			float x = rand() % 30 - 15;
			float y = rand() % 30 - 15;
			float z = rand() % 30 - 15;

			m_translateVectors[i] = glm::vec3(x, y, z);
		}
	}
	void InitializeRotation(void)
	{
		m_rotationAngle = new float[m_numCubes];
		m_rotationValues = new glm::vec3[m_numCubes];
		for (unsigned int i = 0; i < m_numCubes; ++i)
		{
			m_rotationAngle[i] = rand() % 90;

			m_rotationValues[i] = glm::vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
		}
	}
	void UpdateTranslateVectors(void)
	{
		for (unsigned int i = 0; i < m_numCubes; ++i)
		{
			m_translateVectors[i] += m_direction * m_speed;
		}
	}
	void UpdateRotations(void)
	{
		for (unsigned int i = 0; i < m_numCubes; ++i)
		{
			m_rotationAngle[i] += m_rotationDelta;
			if (m_rotationAngle[i] > 360)
			{
				m_rotationAngle[i] = 0;
			}
		}
	}
	void CheckIfCubesSurpassedLimit(void)
	{
		for (unsigned int i = 0; i < m_numCubes; ++i)
		{
			if (m_translateVectors[i].z > 15.0f)
			{
				m_translateVectors[i].z = -20.0f;
			}
		}
	}
private:
	const float m_radius;

	glm::vec3 m_color1;
	glm::vec3 m_color2;

	glm::vec3* m_verts;
	unsigned short* m_indices;

	unsigned int m_vertexDataSize;
	unsigned int m_indexDataSize;
	unsigned int m_totalBufferSize;

	unsigned int m_numVertices;
	unsigned int m_numIndices;

	unsigned int m_bufferID;
	unsigned int m_indexID;
	unsigned int m_transformMatricesBufferID;
	unsigned int m_vertexArrayID;

	unsigned int m_numCubes;
	
	SHProgram m_shprogram;

	glm::vec3* m_translateVectors;
	glm::mat4* m_transformMatrices;

	float* m_rotationAngle;
	float m_rotationDelta;
	glm::vec3* m_rotationValues;

	glm::vec3 m_direction;
	float m_speed;

	const int m_MAX_DISTANCE_OF_CUBES;
};

#endif
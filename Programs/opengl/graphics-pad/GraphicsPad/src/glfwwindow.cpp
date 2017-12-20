//INSTANCED GEOMETRY

#define GLM_ENABLE_EXPERIMENTAL

#include "glfwwindow.h"
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.h"
#include "ShapeGenerator.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>

extern std::string ReadShaderCode(const char*);

constexpr float	X_DELTA =							0.1f;
constexpr unsigned int MAX_TRIS =					20;
constexpr unsigned int NUM_VERTICES_PER_TRI =		3;
constexpr unsigned int NUM_FLOATS_PER_VERTICE =		6;
constexpr unsigned int TRI_SIZE =					NUM_VERTICES_PER_TRI * NUM_FLOATS_PER_VERTICE * sizeof(float);

unsigned int numTriangles =							0;

unsigned int numIndices = 0;

static GLuint programID;

inline void SendNewTriangle(void)
{
	if(numTriangles == MAX_TRIS) return;
	const GLfloat THIS_TRI_X = -1.0f + numTriangles * X_DELTA;
	GLfloat thisTri[] 
	{
		THIS_TRI_X, +1.0f, +0.0f,
		+1.0f, +0.0f, +0.0f,

		THIS_TRI_X + X_DELTA, +1.0f, +0.0f,
		+1.0f, +0.0f, +0.0f,

		THIS_TRI_X, +0.0f, +0.0f,
		+1.0f, +0.0f, +0.0f,
	};
	glBufferSubData(GL_ARRAY_BUFFER, numTriangles * TRI_SIZE, TRI_SIZE, thisTri);
	numTriangles++;
}

inline bool CheckStatus(GLuint objectID, 
	PFNGLGETSHADERIVPROC objectPropertyGetter,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetter(objectID,statusType,&status);
	if(status != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(objectID,GL_INFO_LOG_LENGTH,&infoLogLength);
		GLchar* buffer = (GLchar*)alloca(infoLogLength * sizeof(GLchar));

		GLsizei bufferSize;
		getInfoLogFunc(objectID,infoLogLength * sizeof(GLchar),&bufferSize,buffer);
		std::cout << buffer << std::endl;

		return false;
	}
	return true;
}

inline bool CheckShaderStatus(GLuint shaderID)
{
	return CheckStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}
inline bool CheckProgramStatus(GLuint programID)
{
	return CheckStatus(programID,glGetProgramiv,glGetProgramInfoLog,GL_LINK_STATUS);
}

inline void InstallShader(void)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* adapter[1];
	std::string temp = ReadShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);

	temp = ReadShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if(!CheckShaderStatus(vertexShaderID) || !CheckShaderStatus(fragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glBindAttribLocation(programID, 0, "position");
	glBindAttribLocation(programID, 1, "vertexColor");

	glLinkProgram(programID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	if(!CheckProgramStatus(programID))
		return;

	glUseProgram(programID);
}

void Window::SendDataToOpenGL(void)
{
	//get shape data of a cube e.g. vertices, colors etc
	ShapeData shape = ShapeGenerator::MakeCube();

	//id of the vertex buffer containing the vertices
	GLuint vertexBufferID;
	//genrating the buffers
	glGenBuffers(1,&vertexBufferID);
	//binding the buffer to the GL_ARRAY_BUFFER binding point
	glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);
	//filling the buffer with the vertices of the cube
	glBufferData(GL_ARRAY_BUFFER,shape.vertexBufferSize(),shape.vertices,GL_STATIC_DRAW);
	//enable the vertex attribute array 0 - idk why yet
	glEnableVertexAttribArray(0);
	//setting up the vertex attribute pointer saying that 
	//attribute 0 will contain the vertices with a stride of 6 floats
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float) * 6,0);
	//enable the vertex attribute array 1

	glEnableVertexAttribArray(1);
	//glVertexAttrib3f(1,0,1,1);

	//setting up the vertex attribute pointer saying that
	//attribute 1 will containt the contents of what's 3 floats in
	//in the buffer and will have a stride of 6 floats (it starts 3 floats in - last arg)
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float) * 6,(char*)(sizeof(float) * 3));

	//index array buffer ID
	GLuint indexArrayBufferID;
	//genrate the buffer for the index array buffer
	glGenBuffers(1,&indexArrayBufferID);
	//bind the buffer to the GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexArrayBufferID);
	//fill the buffer with the indices data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,shape.indexBufferSize(),shape.indices,GL_STATIC_DRAW);
	numIndices = shape.numIndices;

	//buffer ID of the transformation matrices
	GLuint transformationMatrixBufferID;
	//generate the buffer
	glGenBuffers(1, &transformationMatrixBufferID);
	//bind the buffer to the GL_ARRAY_BUFFER binding point
	glBindBuffer(GL_ARRAY_BUFFER, transformationMatrixBufferID);

	//projection matrix
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f),((float)m_width) / m_height,0.1f,10.0f);

	//the full transforms of each cube (2 cubes)
	glm::mat4 fullTransforms[] 
	{
		projectionMatrix * glm::translate(glm::vec3(-1.0f,0.0f,-4.0f)) * glm::rotate(glm::radians(30.0f),glm::vec3(1.0f,0.0f,0.0f)),
		projectionMatrix * glm::translate(glm::vec3(1.0f,0.0f,-4.75f)) * glm::rotate(glm::radians(30.0f),glm::vec3(0.0f,1.0f,0.0f)),
		projectionMatrix * glm::translate(glm::vec3(4.0f,1.0f,-5.0f)) * glm::rotate(glm::radians(30.0f),glm::vec3(0.0f,0.0f,1.0f)),
		projectionMatrix * glm::translate(glm::vec3(-6.0f,1.0f,-8.0f)) * glm::rotate(glm::radians(30.0f),glm::vec3(0.0f,0.5f,1.0f)),
		projectionMatrix * glm::translate(glm::vec3(-7.0f,1.0f,-4.0f)) * glm::rotate(glm::radians(30.0f),glm::vec3(1.0f,1.0f,1.0f))
	};

	//fill the buffer data size of 2 mat4s with fullTransforms array
	glBufferData(GL_ARRAY_BUFFER, 5 * sizeof(glm::mat4), fullTransforms, GL_STATIC_DRAW);
	
	//largest number of attributes per attribute pointer has to be <= 4 
	//that is why we need to create 4 pointers

	for(unsigned int attribPtr = 2; attribPtr < 12; ++attribPtr)
		glVertexAttribPointer(attribPtr,4,GL_FLOAT,GL_FALSE,
			sizeof(glm::mat4),(void*)(sizeof(float) * ((attribPtr -2) * 4)));

	for(unsigned int i = 2; i < 12; ++i)
		glEnableVertexAttribArray(i);

	for(unsigned int i = 2; i < 12; ++i)
		glVertexAttribDivisor(i, 1);
}

Window::Window(unsigned int width, unsigned int height, const char* name)
	: m_width(width), m_height(height), m_name(name)
{
	enum 
	{
		INIT_SUCCESS = true,

		INIT_FAIL = false
	};
	if(Initialize() == INIT_FAIL)
	{
		std::cerr << "error !" << std::endl;
	}
}

Window::~Window(void)
{
	glUseProgram(NULL);
	glDeleteProgram(programID);

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

const bool Window::Initialize(void)
{
	if(!glfwInit()) 
	{
		glfwTerminate();
		std::cerr << "failed to initialize GLFW!" << std::endl;
		return false;
	}
	m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);

	if(!m_window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);
	
	if(glewInit() != GLEW_OK)
	{
		glfwTerminate();
		std::cerr << "failed to initialize GLEW!" << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	SendDataToOpenGL();
	InstallShader();

	return true;
}

/*
float FOV = 50.0f;
float delta = 0.01f;

float angle = 40.0f;
float deltaA = 0.05f;
*/
void Window::Draw(void)
{
	//glViewport(0, 0, m_width, m_height);
	glClearColor(0.0f,0.0f,0.2f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glDrawElementsInstanced(GL_TRIANGLES,numIndices,GL_UNSIGNED_SHORT,0, 5);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}


const bool Window::IsWindowOpen(void)
{
	return !glfwWindowShouldClose(m_window);
}

void Window::Update(void)
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

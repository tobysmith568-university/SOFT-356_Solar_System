#include "Mesh.h"


#define BUFFER_OFFSET(a) ((void*)(a))

using namespace std;

Mesh::Mesh(GLuint& _program)
	: program(_program)
{
}

// OpenGL Setup
void Mesh::Init()
{
	CreateAndUseVAO();
	BindVertices();
	BindIndices();
	BindTexture();
}

// To be run every game tick
void Mesh::Update()
{
	glBindVertexArray(VAO);// Binds the VAO and re-draws the content

	//Pass this mesh's material's ambient light into the shader program
	glm::vec4 ambient = glm::vec4(material.ambientColour.x, material.ambientColour.y, material.ambientColour.z, 1.0f);
	//adding the Uniform to the shader
	GLuint aLoc = glGetUniformLocation(program, "ambient");
	glUniform4fv(aLoc, 1, glm::value_ptr(ambient));

	//Pass this mesh's material's diffuse light into the shader program
	GLuint dLightLoc = glGetUniformLocation(program, "dLight");
	glUniform3fv(dLightLoc, 1, glm::value_ptr(material.diffuseColour));

	//Pass this mesh's material's specular light into the shader program
	GLfloat shininess = NormaliseTo(material.specularColourWeight, 1000, 128);
	GLuint sLightLoc = glGetUniformLocation(program, "sLight");
	GLuint sShineLoc = glGetUniformLocation(program, "sShine");
	glUniform3fv(sLightLoc, 1, glm::value_ptr(material.specularColour));
	glUniform1fv(sShineLoc, 1, &shininess);

	glBindTexture(GL_TEXTURE_2D, textureBuffer);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

std::vector<Vertex> Mesh::GetVertices()
{
	return vertices;
}

void Mesh::SetVertices(std::vector<Vertex> _vertices)
{
	vertices = _vertices;
}

std::vector<GLuint> Mesh::GetIndicies()
{
	return indices;
}

void Mesh::SetIndicies(std::vector<GLuint> _indicies)
{
	indices = _indicies;
}

void Mesh::SetMaterial(Material& _material)
{
	material = _material;
}

Material& Mesh::GetMaterial()
{
	return material;
}

// Creates A VAO and binds it
void Mesh::CreateAndUseVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

// Binds vertex data to a buffer
void Mesh::BindVertices()
{
	glGenBuffers(1, &vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
}

// Binds index data to a buffer and enables shader variables for the vertex types
void Mesh::BindIndices()
{
	glGenBuffers(1, &indicesBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(offsetof(Vertex, position)));// Set where position is stored in a Vertex
	glEnableVertexAttribArray(vPosition);

	glVertexAttribPointer(tPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(offsetof(Vertex, texture)));// Set where texture coords are stored in a Vertex
	glEnableVertexAttribArray(tPosition);

	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(offsetof(Vertex, normal)));// Set where normal coords are stored in a Vertex
	glEnableVertexAttribArray(vNormal);

	glVertexAttribPointer(cPosition, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(offsetof(Vertex, colour)));// Set where colour data is stored in a Vertex
	glEnableVertexAttribArray(cPosition);
}

// Binds texture data to a buffer and sets a uniform variable in the shader
void Mesh::BindTexture()
{
	glGenTextures(1, &textureBuffer);
	glBindTexture(GL_TEXTURE_2D, textureBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Passes in the texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, material.diffuseTextureMap.GetWidth(), material.diffuseTextureMap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, material.diffuseTextureMap.GetData());
	glGenerateMipmap(GL_TEXTURE_2D);

	glUniform1i(glGetUniformLocation(program, "texture1"), 0);
}

GLfloat Mesh::NormaliseTo(GLfloat value, GLuint currentMax, GLuint wantedMax)
{
	return value / (currentMax / wantedMax);
}

#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verticesP, unsigned int nbVerticesP, const unsigned int* indicesP, unsigned int nbIndicesP) :
	nbVertices(nbVerticesP), nbIndices(nbIndicesP), vertexBuffer(0), indexBuffer(0), vertexArray(0)
{
	// Create vertex array
	glGenVertexArrays(1, &vertexArray);
	// Bind it so it is set as the one we are using
	glBindVertexArray(vertexArray);

	// Create vertex buffer
	glGenBuffers(1, &vertexBuffer);
	// Bind it so it is set as the one we are using
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// Transfer the data of the vertices to the buffer
	glBufferData(GL_ARRAY_BUFFER, nbVertices * 8.0 * sizeof(float), verticesP, GL_STATIC_DRAW);

	// Create index buffer
	glGenBuffers(1, &indexBuffer);
	// Bind it so it is set as the one we are using
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	// Transfer the data of the indices to the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbIndicesP * sizeof(unsigned int), indicesP, GL_STATIC_DRAW);

	// Specify the vertex attributes
	// (For now, assume one vertex format)
	// Position is 3 floats starting at offset 0
	// Create an attribute for position, using the index 0
	glEnableVertexAttribArray(0);
	// Set the attribute position as a 3 float data, stored ad fload, since we have 8 floats of data per vertices
	// the position will be found every sizeof(float) * 8, 0, and the offset is 0 since it is the first attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	// Create an attribute for normal, using the index 1
	glEnableVertexAttribArray(1);
	// Set the attribute normal as a 3 float data, stored ad fload, since we have 8 floats of data per vertices
	// the position will be found every sizeof(float) * 8, 0, and the offset is sizeof(float) * 3 since it is after the
	// position wich is a 3 float data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void*>(sizeof(float) * 3));
	// Create an attribute for uv, using the index 2
	glEnableVertexAttribArray(2);
	// Set the attribute uv as a 2 float data, stored ad fload, since we have 8 floats of data per vertices
	// the position will be found every sizeof(float) * 8, 0, and the offset is sizeof(float) * 6 since it is after the
	// position and the normal wich are 3 float datas
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void*>(sizeof(float) * 6));
}

VertexArray::~VertexArray()
{
	// Delete the buffers to free memory
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}

void VertexArray::setActive()
{
	glBindVertexArray(vertexArray);
}
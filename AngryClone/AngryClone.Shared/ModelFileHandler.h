#pragma once

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace AngryClone;

class ModelFileHandler
{
	std::fstream* ModelFile;
	AngryClone::VertexPositionColor* Vertices;
	AngryClone::VertexPositionTextureCoord* TexturedVertices;
	long VerticesBufferSize;
	unsigned short* Indices;
	long IndicesBufferSize;

	std::vector<btVector3> VerticesVeñtor;
	std::vector<unsigned short> IndicesVector;
public:
	ModelFileHandler(std::wstring fileName);
	ModelFileHandler(std::wstring fileName, bool bullet);
	ModelFileHandler(std::wstring fileName, char tex);
	~ModelFileHandler();

	AngryClone::VertexPositionColor* getVertices();
	AngryClone::VertexPositionTextureCoord* getTexturedVertices();
	unsigned short* getIndices();
	long getIndicesBufferSize();
	long getVerticesBufferSize();
	int getIndicesCount();

	std::vector<btVector3>* getVerticesVeñtor();
	std::vector<unsigned short>* getIndicesVector();
};


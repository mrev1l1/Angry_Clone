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

	vector<btVector3> VerticesVeñtor;
	vector<unsigned short> IndicesVector;
public:
	ModelFileHandler(char* fileName);
	ModelFileHandler(char* fileName, bool bullet);
	ModelFileHandler(char* fileName, char tex);
	~ModelFileHandler();

	AngryClone::VertexPositionColor* getVertices();
	AngryClone::VertexPositionTextureCoord* getTexturedVertices();
	unsigned short* getIndices();
	long getIndicesBufferSize();
	long getVerticesBufferSize();
	int getIndicesCount();

	vector<btVector3>* getVerticesVeñtor();
	vector<unsigned short>* getIndicesVector();
};


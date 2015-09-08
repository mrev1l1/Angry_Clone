#include "ModelFileHandler.h"
#include <windows.h>

ModelFileHandler::ModelFileHandler(std::wstring fileName, bool bullet)
{
	void parseLine(char* line, std::vector<btVector3>* vertice);

	this->ModelFile = new std::fstream(fileName, std::ios_base::in);

	std::string* line;
	char buffer[64];

	if (ModelFile->is_open())
	{
		while (!ModelFile->eof())
		{
			ModelFile->getline(buffer, 64);
			line = new std::string(buffer);

			int VerticesCount = std::stoi(*line);
			const int n = VerticesCount;
			
			for (int i = VerticesCount; i > 0; i--)
			{
				ModelFile->getline(buffer, 64);

				parseLine(buffer, &this->VerticesVeñtor);

			}

			delete line;

			ModelFile->getline(buffer, 64);
			line = new std::string(buffer);

			int IndicesCount = std::stoi(*line);

			for (int i = IndicesCount; i > 0; i--)
			{
				ModelFile->getline(buffer, 64);

				char *nextToken = NULL;
				this->IndicesVector.push_back(std::stoi(strtok_s(buffer, ",", &nextToken)));

				int iteration = 2;
				while (iteration > 0)
				{
					this->IndicesVector.push_back(std::stoi(strtok_s(NULL, ",", &nextToken)));
					iteration--;
				}
			}
		}

		ModelFile->close();
	}
}

void parseLine(char* line, std::vector<btVector3>* vertice)
{
	char* nextToken = NULL;

	btVector3* data = new btVector3();
	data->setX(std::atof(strtok_s(line, " ", &nextToken)));
	data->setY(std::atof(strtok_s(NULL, " ", &nextToken)));
	data->setZ(std::atof(strtok_s(NULL, " ", &nextToken)));

	vertice->push_back(*data);
}

ModelFileHandler::ModelFileHandler(std::wstring filename, char texture)
{
	void parseLine(char* line, AngryClone::VertexPositionTextureCoord* result, int);

	this->ModelFile = new std::fstream(filename, std::ios_base::in);

	std::string* line;
	char buffer[64];

	if (ModelFile->is_open())
	{
		while (!ModelFile->eof())
		{
			ModelFile->getline(buffer, 64);
			line = new std::string(buffer);

			int VerticesCount = std::stoi(*line);
			const int n = VerticesCount;

			this->TexturedVertices = new AngryClone::VertexPositionTextureCoord[VerticesCount];

			for (int i = VerticesCount; i > 0; i--)
			{
				ModelFile->getline(buffer, 64);

				parseLine(buffer, &this->TexturedVertices[VerticesCount - i], i);
			}

			this->VerticesBufferSize = sizeof(AngryClone::VertexPositionTextureCoord) * VerticesCount;

			delete line;

			ModelFile->getline(buffer, 64);
			line = new std::string(buffer);

			int IndicesCount = std::stoi(*line);

			this->Indices = new unsigned short[IndicesCount * 3];

			int j = 0;
			for (int i = IndicesCount; i > 0; i--)
			{
				ModelFile->getline(buffer, 64);

				char *nextToken = NULL;
				this->Indices[j] = std::stoi(strtok_s(buffer, ",", &nextToken));
				j++;

				int iteration = 2;
				while (iteration > 0)
				{
					this->Indices[j] = std::stoi(strtok_s(NULL, ",", &nextToken));
					j++;
					iteration--;
				}
			}

			this->IndicesBufferSize = sizeof(unsigned short) * IndicesCount * 3;
		}

		ModelFile->close();
	}
	else
	{
		this->Indices = nullptr;
		this->Vertices = nullptr;
	}

}

ModelFileHandler::ModelFileHandler(std::wstring fileName)
{
	void parseLine(char* line, AngryClone::VertexPositionColor* result);

	this->ModelFile = new std::fstream(fileName, std::ios_base::in);
	
	std::string* line;
	char buffer[64];

	if (ModelFile->is_open())
	{
		while (!ModelFile->eof())
		{
			ModelFile->getline(buffer, 64);
			line = new std::string(buffer); 

			int VerticesCount = std::stoi(*line);
			const int n = VerticesCount;
			
			this->Vertices = new AngryClone::VertexPositionColor[VerticesCount];
			
			for (int i = VerticesCount; i > 0; i--)
			{
				ModelFile->getline(buffer, 64);

				parseLine(buffer, &this->Vertices[VerticesCount - i]);

			}

			this->VerticesBufferSize = sizeof(AngryClone::VertexPositionColor) * VerticesCount;
			
			delete line;

			ModelFile->getline(buffer, 64);
			line = new std::string(buffer);

			int IndicesCount = std::stoi(*line);

			this->Indices = new unsigned short[IndicesCount*3];

			int j = 0;
			for (int i = IndicesCount; i > 0; i--)
			{
				ModelFile->getline(buffer, 64);
				
				char *nextToken = NULL;
				this->Indices[j] = std::stoi(strtok_s(buffer, ",", &nextToken));
				j++;

				int iteration = 2;
				while (iteration > 0)
				{
					this->Indices[j] = std::stoi(strtok_s(NULL, ",", &nextToken));
					j++;
					iteration--;
				}
			}

			this->IndicesBufferSize = sizeof(unsigned short) * IndicesCount * 3;
		}

		ModelFile->close();
	}
	else
	{
		this->Indices = nullptr;
		this->Vertices = nullptr;
	}
	
}

void parseLine(char* line, AngryClone::VertexPositionTextureCoord* result,int i)
{
	char* nextToken = NULL;

	result->pos.x = std::atof(strtok_s(line, " ", &nextToken));
	result->pos.y = std::atof(strtok_s(NULL, " ", &nextToken));
	result->pos.z = std::atof(strtok_s(NULL, " ", &nextToken));

	result->tex.x = std::atof(strtok_s(NULL, " ", &nextToken));
	result->tex.y = std::atof(strtok_s(NULL, " ", &nextToken));
}

void parseLine(char* line, AngryClone::VertexPositionColor* result)
{
	char* nextToken = NULL;
	
	result->pos.x = std::atof(strtok_s(line, " ", &nextToken));
	result->pos.y = std::atof(strtok_s(NULL, " ", &nextToken));
	result->pos.z = std::atof(strtok_s(NULL, " ", &nextToken));
	
	result->color.x = std::atof(strtok_s(NULL, " ", &nextToken));
	result->color.y = std::atof(strtok_s(NULL, " ", &nextToken));
	result->color.z = std::atof(strtok_s(NULL, " ", &nextToken));
}

AngryClone::VertexPositionColor* ModelFileHandler::getVertices()
{
	return this->Vertices;
}

AngryClone::VertexPositionTextureCoord* ModelFileHandler::getTexturedVertices()
{
	return this->TexturedVertices;
}

unsigned short* ModelFileHandler::getIndices()
{
	return this->Indices;
}

int ModelFileHandler::getIndicesCount()
{
	return this->IndicesBufferSize / sizeof(unsigned short);
}

long ModelFileHandler::getIndicesBufferSize()
{
	return this->IndicesBufferSize;
}

long ModelFileHandler::getVerticesBufferSize()
{
	return this->VerticesBufferSize;
}

std::vector<btVector3>* ModelFileHandler::getVerticesVeñtor()
{
	return &(this->VerticesVeñtor);
}

std::vector<unsigned short>* ModelFileHandler::getIndicesVector()
{
	return &this->IndicesVector;
}

ModelFileHandler::~ModelFileHandler()
{
	/*delete ModelFile;
	delete[] Vertices;
	delete[] Indices;
	delete[] TexturedVertices;*/
}

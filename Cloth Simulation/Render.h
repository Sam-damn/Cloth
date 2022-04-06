#pragma once

class Render
{
public:
	virtual void initCloth(float * vertexData, int size) = 0;

	virtual void initClothIndexed(float *vertexData, int vertexDataSize, int *indexData, int indexDataSize) = 0;

	virtual void updateCloth(float * vertexData, int size) = 0;
};

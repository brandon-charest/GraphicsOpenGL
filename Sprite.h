#pragma once
#include <GL/glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x , float y, float width, float height);

	//draw sprite
	void draw();

private:
	float _x;
	float _y;
	float _width;
	float _height;

	/* vboID = Vertex buffer object ID 
	**  using Gluint is the same as using unsigned int 
	** except while using GLunit you are garentueed a 32bit unsigned could be 8 */
	GLuint _vboID; 



};


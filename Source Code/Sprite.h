#pragma once
class Sprite
{
private:
	GLuint VBO, EBO, texture;
	GLuint fVBO;
	mat4 model;
	vec2 spriteSize;
	vec2 spritePosition;
	vec2 centre;
	vec2 distance;
	float width;
	float height;
	float rotation;
	float X, Y, R, B;
	bool isXAxis, isYAxis;
	bool flip;
public:
	Sprite();
	~Sprite();
	bool RectangleCollision(Sprite sprite);
	bool CircleCollision(Sprite sprite);
	bool CentreCollision(Sprite sprite);
	bool WindowCollision(Window window);
	bool& setFlip();
	float& setRotation();
	void CreateBuffers(float width, float height);
	void LoadTexture(const char* filename);
	void Draw(Shader shader);
	void Update(Shader shader);
	vec2 getSize();
	vec2 getPosition();
	vec2 getCenter();
	vec2 &setPosition();
};


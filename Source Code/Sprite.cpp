#include "Common.h"
Sprite::Sprite() {
	this->VBO = NULL;
	this->EBO = NULL;
	this->fVBO = NULL;
	this->texture = NULL;
	this->model = mat4(0.0f);
	this->spriteSize = vec2(0, 0);
	this->spritePosition = vec2(NULL, NULL);
	this->width = 0;
	this->height = 0;
	this->X = NULL;
	this->Y = NULL;
	this->R = NULL;
	this->B = NULL;
	this->isXAxis = false;
	this->isYAxis = false;
	this->centre = vec2(this->width / 2, this->height / 2);
	this->distance = vec2(0.0f, 0.0f);
	this->rotation = NULL;
}
Sprite::~Sprite() {

}
bool Sprite::RectangleCollision(Sprite sprite) {
	//checking x axis
	this->isXAxis = this->X < sprite.R&& this->R > sprite.X;
	//checking y axis
	this->isYAxis = this->Y < sprite.B&& this->B > sprite.Y;
	if (this->isXAxis && this->isYAxis) {
		return true;
	}
	else {
		return false;
	}
}
bool Sprite::CircleCollision(Sprite sprite) {
	this->distance = this->centre - sprite.centre;
	if (length(this->distance) <= ((this->width + sprite.width) / 2)) {
		return true;
	}
	else {
		return false;
	}
}
bool Sprite::CentreCollision(Sprite sprite) {
	this->distance = this->centre - sprite.centre;
	if (length(this->distance) <= (sprite.width) / 2) {
		return true;
	}
	else{
		return false;
	}
}
bool Sprite::WindowCollision(Window window) {
	//checking x axis
	this->isXAxis = this->X < window.R&& this->R > window.X;
	//checking y axis
	this->isYAxis = this->Y < window.B&& this->B > window.Y;
	if (this->isXAxis && this->isYAxis) {
		return true;
	}
	else {
		return false;
	}
}
bool& Sprite::setFlip() {
	return this->flip;
}
float& Sprite::setRotation() {
	return this->rotation;
}
void Sprite::CreateBuffers(float width, float height) {
	this->width = width;
	this->height = height;
	GLfloat textureData[] = {
		//texture vertices				//texture coords
		this->width, this->height,		1.0f, 0.0f,
		this->width, 0.0f,				1.0f, 1.0f,
		0.0f, 0.0f,						0.0f, 1.0f,
		0.0f, this->height, 			0.0f, 0.0f
	};

	this->spriteSize = vec2(this->width, this->height);
	this->centre = vec2(this->width / 2, this->height / 2);

	//generating vbo
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureData), textureData, GL_STATIC_DRAW);

	GLfloat fdata[] = {
		// texture vertices				// texture coords
		this->width,  this->height,		-1.0f, -1.0f,
		this->width, 0.0f,				-1.0f, 0.0f,
		0.0f, 0.0f,						0.0f, 0.0f,
		0.0f, this->height,				0.0f, -1.0f

	};

	glGenBuffers(1, &(this->fVBO));
	glBindBuffer(GL_ARRAY_BUFFER, this->fVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fdata), fdata, GL_STATIC_DRAW);

	//triangle index order
	GLuint indices[] = {
		0, 1, 2,	// triangle 1
		2, 3, 0		// triangle 2
	};

	//generating ebo
	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}
void Sprite::LoadTexture(const char* filename) {
	glGenTextures(1, &this->texture);
	this->texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		4
	);
}
void Sprite::Draw(Shader shader) {
	if (this->flip) {
		glBindBuffer(GL_ARRAY_BUFFER, this->fVBO);
	}
	else {
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	}

	glVertexAttribPointer(shader.vertexAttribute, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	/*out of five column's of each row's
	take first two column values
	for vertices*/

	glVertexAttribPointer(shader.uvAttribute, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	/*out of five column's of each row's
	take last two column values
	for uv coords*/

	glEnableVertexAttribArray(shader.vertexAttribute);
	glEnableVertexAttribArray(shader.uvAttribute);

	glBindTexture(GL_TEXTURE_2D, this->texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
void Sprite::Update(Shader shader) {
	this->X = spritePosition.x;
	this->Y = spritePosition.y;
	this->R = spritePosition.x + this->width;
	this->B = spritePosition.y + this->height;
	this->centre.x = spritePosition.x + this->width / 2;
	this->centre.y = spritePosition.y + this->height / 2;
	mat4 translator, rotator, scalar;
	translator = translate(mat4(1.0f), vec3(spritePosition.x, spritePosition.y, 0.0f));
	rotator = rotate(mat4(1.0f), radians(rotation), vec3(0.0f, 1.0f, 0.0f));// works with playerRotate = 180.0f;
	scalar = scale(mat4(1.0f), vec3(1.0f, 1.0f, 0.0f));
	this->model = translator * rotator * scalar;
	/*translate method is from glm namespace*/
	glUniformMatrix4fv(shader.modelAttribute, 1, GL_FALSE, value_ptr(this->model));
}
vec2 Sprite::getSize() {
	return this->spriteSize;
}
vec2 Sprite::getPosition() {
	return this->spritePosition;
}
vec2 Sprite::getCenter() {
	return this->centre;
}
vec2& Sprite::setPosition() {
	return this->spritePosition;
}

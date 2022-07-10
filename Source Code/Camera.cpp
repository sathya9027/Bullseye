#include "Common.h"
Camera::Camera() {
	this->position = vec3(0.0f, 0.0f, 1.0f);		//z axis for depth (+z is out, -z is in)
	this->target = vec3(0.0f, 0.0f, 0.0f);
	this->orientation = vec3(0.0f, 1.0f, 0.0f);		//y axis for landscape or protrait
	this->projection = mat4(0.0f);
	this->view = mat4(0.0f);
}
Camera::~Camera() {

}
void Camera::Update(Window window, Shader shader) {
	this->view = mat4(1.0f);
	this->view = lookAt(this->position, this->target, this->orientation);
	glUniformMatrix4fvARB(shader.viewAttribute, 1, GL_FALSE, value_ptr(this->view));

	this->projection = mat4(1.0f);
	this->projection = ortho(0.0f, window.windowWidth, 0.0f, window.windowHeight, 1.0f, 10.0f);
	/*left, right, bottom, top, znear, zfar*/
	glUniformMatrix4fvARB(shader.projectionAttribute, 1, GL_FALSE, value_ptr(this->projection));
}
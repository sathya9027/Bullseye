#pragma once
class Camera
{
private:
	mat4 view, projection;
	vec3 position, target, orientation;
public:
	Camera();
	~Camera();
	void Update(Window window, Shader shader);
};
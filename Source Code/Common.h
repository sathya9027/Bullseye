#pragma once
/*There are three package need
to be install inorder to
work with opengl fully....

Tools->NuGet Package Manager->Package Manager Console

1.) Install Opengl Package - install-package nupengl.core
2.) Install Soil Package - install-package soil
3.) Install GLM Package - install-package glm
4.) Install FreeType Package - install-package freetype
5.) Install Openal Package - Install-Package OpenAL.Soft -Version 1.19.1*/

//opengl lib
#pragma warning (disable : 4996)
#pragma comment(lib,"OpenGL32.lib")

//openal
#include<AL/al.h>
#include <AL/alc.h>

//glfw include's
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//soil include's
#include <soil.h>

//glm include's
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//FreeType include's
#include <ft2build.h>
#include FT_FREETYPE_H

//common include's
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <time.h>
#include <map>
#include <array>
#include <string>

//namespace
using namespace std;
using namespace glm;

//including header files
/*Framework header files*/
#include "Window.h"
#include "Shader.h"
#include "Sprite.h"
#include "Camera.h"
#include "DeltaTime.h"
#include "Font.h"
#include "Audio.h"

/*Gameplay Header files*/
#include "Define.h"
#include "Targets.h"
#include "Timer.h"
#include "CoreGame.h"
#include "SpawnPickups.h"
#include "MainMenu.h"
#include "GameOver.h"
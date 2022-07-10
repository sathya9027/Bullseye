#pragma once
class Font {
private:
	FT_Library ft;
	FT_Face face;
	FT_GlyphSlot glyph;
	GLuint texture, VBO;
	mat4 model;
public:
	void Init(const char* filePath);
	void DrawFontText(const string& str, vec2 pos, vec2 scale, vec3 color, Shader shader);

};


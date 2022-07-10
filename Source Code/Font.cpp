#include "Common.h"
void Font::Init(const char* filePath) {
	FT_Init_FreeType(&this->ft);
	FT_New_Face(this->ft, filePath, 0, &this->face);
	FT_Set_Pixel_Sizes(this->face, 50, 50);
	this->glyph = this->face->glyph;
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glGenTextures(1, &this->texture);
}
void Font::DrawFontText(const string& str, vec2 modelPos, vec2 scale, vec3 color, Shader shader) {

	vec2 origin = vec2(1, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	for (auto ch : str) {

		if (FT_Load_Char(this->face, ch, FT_LOAD_RENDER) != 0)
		{
			continue;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, this->glyph->bitmap.width, this->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, this->glyph->bitmap.buffer);


		//calculating glyph elements values
		const float x = origin.x + this->glyph->bitmap_left * scale.x;
		const float y = origin.y + this->glyph->bitmap_top * scale.y;
		const float w = this->glyph->bitmap.width * scale.x;
		const float h = this->glyph->bitmap.rows * scale.y;

		GLfloat textData[] = {
			x    ,		y    ,		0, 0 ,
			x    ,		y - h,		0, 1,//
			x + w,		y    ,		1, 0 ,//

			x + w,		y    ,		1, 0 ,//
			x    ,		y - h,		0, 1 ,//
			x + w,		y - h,		1, 1
		};


		//Generate text vbo & draw text 
		glBufferData(GL_ARRAY_BUFFER, sizeof(textData), textData, GL_STATIC_DRAW);
		glVertexAttribPointer(shader.vertexAttribute, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glVertexAttribPointer(shader.uvAttribute, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(shader.vertexAttribute);
		glEnableVertexAttribArray(shader.uvAttribute);
		glUniform3f(shader.fontColorAttribute, color.x, color.y, color.z);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		//Draw the character in model space
		this->model = mat4(1.0f);
		this->model = translate(this->model, vec3(modelPos.x, modelPos.y, 0.0f));
		glUniformMatrix4fv(shader.modelAttribute, 1, GL_FALSE, value_ptr(this->model));


		//setting origin to draw next character 
		origin.x += (this->glyph->advance.x >> 6) * scale.x;
		origin.y += (this->glyph->advance.y >> 6) * scale.y;
	}

}
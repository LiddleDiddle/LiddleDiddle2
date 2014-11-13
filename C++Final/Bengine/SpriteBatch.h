#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

namespace Bengine{

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class Glyph{
public:

	Glyph() {}
	Glyph(const glm::vec4& destRect, float rotation, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color) :
	texture(Texture),
	depth(Depth) {

		//tl bl br tr
		glm::vec2 verts[4] = { glm::vec2(-destRect.z / 2, destRect.w / 2), glm::vec2(-destRect.z / 2, -destRect.w / 2), glm::vec2(destRect.z / 2, -destRect.w / 2), glm::vec2(destRect.z / 2, destRect.w / 2) };
		//glm::mat2 rotationMatrix(cos(rotation*PI/180),-sin(rotation*PI/180),sin(rotation*PI/180),cos(rotation*PI/180));
		glm::mat2 rotationMatrix(cos(rotation), sin(rotation), -sin(rotation), cos(rotation));
		for (int i = 0; i < 4; i++)
		{
			verts[i] = rotationMatrix * verts[i];
		}

		topLeft.color = color;
		topLeft.setPosition(verts[0].x + destRect.x, verts[0].y + destRect.y);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(verts[1].x + destRect.x, verts[1].y + destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		bottomRight.setPosition(verts[2].x + destRect.x, verts[2].y + destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;
		topRight.setPosition(verts[3].x + destRect.x, verts[3].y + destRect.y);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	}
	GLuint texture;
	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

class RenderBatch {
public:
	RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
		numVertices(NumVertices), texture(Texture) {
	}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch
{
public:
	SpriteBatch(void);
	~SpriteBatch(void);

	void init();

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();

	void draw(const glm::vec4& destRect, float rotation, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);

	void renderBatch();
private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();
	

	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

	GLuint _vbo;
	GLuint _vao;

	GlyphSortType _sortType;

	std::vector<Glyph*> _glyphPointers; //this is for sorting
	std::vector<Glyph> _glyphs; /// these are the actual glyphs
	std::vector<RenderBatch> _renderBatches;
};

}
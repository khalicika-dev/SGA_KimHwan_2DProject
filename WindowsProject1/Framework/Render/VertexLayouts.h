#pragma once

struct Vertex
{
	XMFLOAT3 pos;

	Vertex()
		: pos(0, 0, 0)
	{

	}

	Vertex(float x, float y)
		: pos(x, y, 0)
	{

	}
};

struct VertexUV
{
	XMFLOAT3 pos;
	XMFLOAT2 uv;

	VertexUV()
	: pos(0, 0, 0),
	uv(0, 0)
	{

	}

	VertexUV(float x, float y, float u, float v)
		: pos(x,y,0)
		, uv(u,v)
	{

	}
};

struct VertexColor
{
	XMFLOAT3 pos;
	XMFLOAT4 color;

	VertexColor()
		: pos(0, 0, 0)
		, color(1, 1, 1, 1)
	{

	}

	VertexColor(float x, float y, XMFLOAT4 color)
		: pos({ x,y,0 })
		, color(color)
	{

	}
};
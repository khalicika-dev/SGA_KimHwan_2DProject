#pragma once

inline void IASetPT(D3D_PRIMITIVE_TOPOLOGY type = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	DEVICE_CONTEXT->IASetPrimitiveTopology(type);
}

class MatrixBuffer : public ConstantBuffer
{
private:
	struct Data
	{
		Matrix matrix;
	};

	Data m_data;

public:
	MatrixBuffer()
		: ConstantBuffer(&m_data, sizeof(Data))
	{
		m_data.matrix = XMMatrixIdentity();
	}

	void Set(Matrix value)
	{
		m_data.matrix = XMMatrixTranspose(value);
	}
};

class ColorBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		Float4 color;
	}data;

	ColorBuffer()
		: ConstantBuffer(&data, sizeof(Data))
	{
		data.color = { 1,1,1,1 };
	}
};

class FrameBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		Float2 maxFrame;
		Float2 curFrame;
	}data;

	FrameBuffer()
		: ConstantBuffer(&data, sizeof(Data))
	{
		data.maxFrame = { 1,1 };
		data.curFrame = { 1,1 };
	}
};

class ActionBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		// GPU정보를 전달할 때 16의 배수로 전달
		Float2 startPos;	// 8
		Float2 size;		// 8
		Float2 maxSize;		// 8

		float alpha;		// 4
		float padding;		// 4
		// 총 32바이트
	}data;

	ActionBuffer()
		: ConstantBuffer(&data, sizeof(Data))
	{
		data.startPos = { 0,0 };
		data.size = { 0,0 };
		data.maxSize = { 0,0 };
		data.alpha = 1.0f;
	}
};

class SelectBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int selectNum = 0;
		int padding[3] = { 0 };
	}data;

	SelectBuffer() 
		: ConstantBuffer(&data, sizeof(Data))
	{
		data.selectNum = 0;
		for (auto num : data.padding)
			num = 0;
	}
};

class InfoBuffer : public ConstantBuffer
{
	struct Data
	{
		int selectNum;
		int value;
		int value2;
		int value3;
	}data;

	InfoBuffer()
		: ConstantBuffer(&data, sizeof(Data))
	{
		data.selectNum = 0;
		data.value = 0;
		data.value2 = 0;
		data.value3 = 0;
	}
};

class ImageSizeBuffer : public ConstantBuffer
{
	struct Data
	{
		Float2 imageSize;
		Float2 padding;
	}data;

	ImageSizeBuffer()
		: ConstantBuffer(&data, sizeof(Data))
	{
		data.imageSize = { 0,0 };
		data.padding = { 0,0 };
	}
};
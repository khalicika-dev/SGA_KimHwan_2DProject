#pragma once
class Texture
{
	// 이 작업의 의미

public:
	// 텍스처가 하는 일
	// 1. 정점 n개를 갖고 버텍스 쉐이더에 정점 정보들을 전달
	// 2.직접 Resource파일에 가서 이미지를 갖고와서 픽셀쉐이더한테 정보를 전달
	Texture(ID3D11ShaderResourceView* shaderResourceView, ScratchImage& image);
	~Texture();

	static Texture* Add(wstring file);
	static void Delete();
	void Set(UINT slot);
	class Vector2 GetSize();

	// 왜 Quad와 Texture클래스 두개로 나눌까
	// 1. 정점이 일단 4개로 세팅했는데 그게 말이 안됨
	// 2. 텍스처에서 그냥 정점도 다 관리하면 되는 문제 아닌가?
	// => 정점이 필요가 없는 텍스처도 있을 것 아닌가?
	// => 그런 애들도 지금 이렇게 클래스를 만들면 울며 겨자먹기로 정점들을 다 배치해줘야되는 문제가 발생
	//
	// ==> 그래서 일단 나눠야되긴함
private:
	static map<wstring, Texture*> m_texturesMap;

	wstring m_file;
	ScratchImage m_image;

	ID3D11ShaderResourceView*	m_shaderResourceView;
};


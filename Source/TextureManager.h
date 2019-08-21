#pragma once
class TextureManager : public SingleInstance<TextureManager>
{
	map<string, shared_ptr<Texture>> mTextureMap;
public:
	TextureManager();
	~TextureManager();

	shared_ptr<Texture> QueryTexture(string nameWithPath);
};
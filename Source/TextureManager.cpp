#include "stdafx.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	for (auto iter : mTextureMap) {
		iter.second.reset();
	}
}

shared_ptr<Texture> TextureManager::QueryTexture(string nameWithPath)
{
	if (mTextureMap[nameWithPath] != NULL)
	{
		return mTextureMap[nameWithPath];
	}
	Texture* pTexture = new Texture();
	if (FAILED(D3DXCreateTextureFromFileExA(DirectX::GetInstance()->g_pd3dDevice, nameWithPath.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0, &pTexture->Info, 0, &pTexture->pTexture
	)))
	{
		OutputDebugStringA(nameWithPath.c_str());
		return nullptr;
	}
	mTextureMap[nameWithPath] = shared_ptr<Texture>(pTexture);
	return mTextureMap[nameWithPath];
}

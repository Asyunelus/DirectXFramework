#pragma once

struct CUSTOMVERTEX {
	float x, y, z;
	D3DCOLOR color;
	float uv, ux;
	void SetVtx(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	
	void SetUV(float _uv, float _ux) {
		uv = _uv;
		ux = _ux;
	}

	void SetColor(D3DCOLOR _color) {
		color = _color;
	}

	void SetARGB(int a, int r, int g, int b) {
		color = a << 24 | r << 16 | g << 8 | b;
	}
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX2)
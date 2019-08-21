#pragma once

extern bool GetIntersectPoint(const D3DXVECTOR2& AP1, const D3DXVECTOR2& AP2, const D3DXVECTOR2& BP1, const D3DXVECTOR2& BP2, D3DXVECTOR2* IP);

struct BoxRect {
	float minX = 0.f, minY = 0.f, maxX = 0.f, maxY = 0.f;

	bool IsCollision(const D3DXVECTOR2& point);
	bool IsCollision(const BoxRect& rect);
	bool IsCollision(const BoxRect& rect, BoxRect* Overlap);
	BoxRect GetOverlapRect(const BoxRect& rect);

	void SetBox(float _minX, float _minY, float _maxX, float _maxY, bool isReverse = false);

	bool operator ==(const BoxRect& rc) {
		return minX == rc.minX
			&& maxX == rc.maxX
			&& minY == rc.minY
			&& maxY == rc.maxY;
	}

	bool operator !=(const BoxRect& rc) {
		return not (*this == rc);
	}

	BoxRect& operator +(const BoxRect& rc) {
		BoxRect res;
		res.minX = minX + rc.minX;
		res.minY = minY + rc.minY;
		res.maxX = maxX + rc.maxX;
		res.maxY = maxY + rc.maxY;
		return res;
	}

	BoxRect& operator +(const D3DXVECTOR2& vec) {
		BoxRect res;
		res.minX = minX + vec.x;
		res.maxX = maxX + vec.x;
		res.minY = minY + vec.y;
		res.maxY = maxY + vec.y;
		return res;
	}

	void operator +=(const BoxRect& rc) {
		minX += rc.minX;
		maxX += rc.maxX;
		minY += rc.minY;
		maxY += rc.maxY;
	}
};

struct LineRect {
	D3DXVECTOR2 p1;
	D3DXVECTOR2 p2;

	void SetLine(D3DXVECTOR2 Point1, D3DXVECTOR2 Point2);

	bool IsCollision(const LineRect& rhs);
	bool IsCollision(const BoxRect& rhs, D3DXVECTOR2* overlap);
	bool IsCollision(const LineRect& rhs, D3DXVECTOR2* overlap);

	LineRect& operator +(const D3DXVECTOR2& vec) {
		LineRect res;
		res.p1 = p1 + vec;
		res.p2 = p2 + vec;
		return res;
	}

	LineRect& operator +(const LineRect& rc) {
		LineRect res;
		res.p1 = p1 + rc.p1;
		res.p2 = p2 + rc.p2;
		return res;
	}

	bool operator ==(const LineRect& rc) {
		return p1 == rc.p1
			&& p2 == rc.p2;
	}

	bool operator !=(const LineRect& rc) {
		return not (*this == rc);
	}
};
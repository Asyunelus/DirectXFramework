#include "stdafx.h"

bool BoxRect::IsCollision(const D3DXVECTOR2& point)
{
	return minX < point.x && maxX > point.x
		&& minY < point.y && maxY > point.y;
}

bool BoxRect::IsCollision(const BoxRect& rect)
{
	return minX < rect.maxX && maxX > rect.minX
		&& minY < rect.maxY && maxY > rect.minY;
}

bool BoxRect::IsCollision(const BoxRect & rect, BoxRect * Overlap)
{
	*Overlap = GetOverlapRect(rect);
	return IsCollision(rect);
}

BoxRect BoxRect::GetOverlapRect(const BoxRect& rect)
{
	if (IsCollision(rect)) {
		return BoxRect{
			max(minX, rect.minX),
			max(minY, rect.minY),
			min(maxX, rect.maxX),
			min(maxY, rect.maxY),
		};
	}
	return BoxRect{
		0, 0, 0, 0
	};
}

void BoxRect::SetBox(float _minX, float _minY, float _maxX, float _maxY, bool isReverse)
{
	if (isReverse) {
		_minX = -_minX;
		_maxX = -_maxX;
	}

	minX = min(_minX, _maxX);
	minY = min(_minY, _maxY);
	maxX = max(_minX, _maxX);
	maxY = max(_minY, _maxY);
}

void LineRect::SetLine(D3DXVECTOR2 Point1, D3DXVECTOR2 Point2) {
	p1 = Point1;
	p2 = Point2;
}

bool LineRect::IsCollision(const BoxRect& rhs, D3DXVECTOR2* overlap)
{
	D3DXVECTOR2 vec[4];
	vec[0] = D3DXVECTOR2(rhs.minX, rhs.minY);
	vec[1] = D3DXVECTOR2(rhs.minX, rhs.maxY);
	vec[2] = D3DXVECTOR2(rhs.maxX, rhs.maxY);
	vec[3] = D3DXVECTOR2(rhs.maxX, rhs.minY);
	
	for (int i = 0; i < 4; i++) {
		if (GetIntersectPoint(p1, p2, vec[(i) % 4], vec[(i + 1) % 4], overlap))
			return true;
	}
	return false;
}

bool LineRect::IsCollision(const LineRect& rhs) {
	D3DXVECTOR2 ret;
	return IsCollision(rhs, &ret);
}

bool LineRect::IsCollision(const LineRect& rhs, D3DXVECTOR2* overlap) {
	return GetIntersectPoint(p1, p2, rhs.p1, rhs.p2, overlap);
}

bool GetIntersectPoint(const D3DXVECTOR2& AP1, const D3DXVECTOR2& AP2, const D3DXVECTOR2& BP1, const D3DXVECTOR2& BP2, D3DXVECTOR2* IP)
{
	float t;
	float s;
	float under = (BP2.y - BP1.y) * (AP2.x - AP1.x) - (BP2.x - BP1.x) * (AP2.y - AP1.y);
	if (under == 0) return false;

	float _t = (BP2.x - BP1.x) * (AP1.y - BP1.y) - (BP2.y - BP1.y) * (AP1.x - BP1.x);
	float _s = (AP2.x - AP1.x) * (AP1.y - BP1.y) - (AP2.y - AP1.y) * (AP1.x - BP1.x);

	t = _t / under;
	s = _s / under;

	if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0) return false;
	if (_t == 0 && _s == 0) return false;

	IP->x = AP1.x + t * (float)(AP2.x - AP1.x);
	IP->y = AP1.y + t * (float)(AP2.y - AP1.y);

	return true;
}
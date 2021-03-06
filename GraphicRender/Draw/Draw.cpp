#include "Draw.h"

// old for DrawLine
/*float GetYLinearEquation(const Vector2& v1, const Vector2& v2, const float x)
{
	return (v2.GetY() - v1.GetY()) / (v2.GetX() - v1.GetX()) * (x - v1.GetX()) + v1.GetY();
}

float GetXLinearEquation(const Vector2& v1, const Vector2& v2, const float y)
{
	return (v2.GetX() - v1.GetX()) / (v2.GetY() - v1.GetY()) * (y - v1.GetY()) + v1.GetX();
}*/

void SetLineCoord(std::vector<Vector2>* const outData, const Vector2& v1, const Vector2& v2)
{
	float dx = std::abs(v2.GetX() - v1.GetX());
	float dy = std::abs(v2.GetY() - v1.GetY());

	if (dx > dy)
	{
		outData->resize((int)dx);

		float y = v1.GetY();
		float m = (v2.GetY() - v1.GetY()) / (v2.GetX() - v1.GetX());
		float xRatio = (v2.GetX() - v1.GetX()) / std::abs(dx);

		for (std::vector<int>::size_type x = 0; x < outData->size(); x++)
		{
			(*outData)[x].SetVector(v1.GetX() + x * xRatio, y);
			y += m * xRatio;
		}
	}
	else
	{
		outData->resize((int)dy);

		float x = v1.GetX();
		float m = (v2.GetX() - v1.GetX()) / (v2.GetY() - v1.GetY());
		float yRatio = (v2.GetY() - v1.GetY()) / std::abs(dy);;

		for (std::vector<int>::size_type y = 0; y < outData->size(); y++)
		{
			(*outData)[y].SetVector(x, v1.GetY() + y * yRatio);
			x += m * yRatio;
		}
	}
}

void SetCircleCoord(std::vector<Vector2>* const outData, const Vector2& center, float radius)
{
	for (std::vector<int>::size_type degree = 0; degree < outData->size(); degree++)
	{
		(*outData)[degree].SetX(center.GetX() + radius * cos(Deg2Rad((float)degree)));
		(*outData)[degree].SetY(center.GetY() + radius * sin(Deg2Rad((float)degree)));
	}
}

void DrawLine(HDC hDC, const Vector2& v1, const Vector2& v2, COLORREF color)
{
	std::vector<Vector2> lineData;
	SetLineCoord(&lineData, v1, v2);
	for (const auto& v : lineData)
	{
		SetPixel(hDC, (int)v.GetX(), (int)v.GetY(), color);
	}
}

void DrawLine(HDC hDC, const float x1, const float y1, const float x2, const float y2, COLORREF color)
{
	std::vector<Vector2> lineData;
	Vector2 v1(x1, y1);
	Vector2 v2(x2, y2);
	SetLineCoord(&lineData, v1, v2);
	for (const auto& v : lineData)
	{
		SetPixel(hDC, (int)v.GetX(), (int)v.GetY(), color);
	}
}

void DrawCircle(HDC hDC, const Vector2& center, const float radius, COLORREF color)
{
	std::vector<Vector2> circleData(360);
	SetCircleCoord(&circleData, center, radius);

	if (radius >= 100)
	{
		for (int i = 0; i < circleData.size() - 1; i++)
		{
			DrawLine(hDC, circleData[i], circleData[i + 1], 0);
		}
	}
	else
	{
		for (const auto& c : circleData)
		{
			SetPixel(hDC, (int)c.GetX(), (int)c.GetY(), 0);
		}
	}
}

void DrawCircle(HDC hDC, const float x, const float y, const float radius, COLORREF color)
{
	std::vector<Vector2> circleData(360);
	Vector2 center(x, y);
	SetCircleCoord(&circleData, center, radius);

	if (radius >= 100)
	{
		for (int i = 0; i < circleData.size() - 1; i++)
		{
			DrawLine(hDC, circleData[i], circleData[i + 1], 0);
		}
	}
	else
	{
		for (const auto& c : circleData)
		{
			SetPixel(hDC, (int)c.GetX(), (int)c.GetY(), 0);
		}
	}
}

void DrawRectangle(HDC hDC, const Vector2& lb, const Vector2& rt, const Vector2& lt, const Vector2& rb, COLORREF color)
{
	DrawLine(hDC, lb.GetX(), lb.GetY(), rb.GetX(), rb.GetY(), color);
	DrawLine(hDC, lb.GetX(), lb.GetY(), lt.GetX(), lt.GetY(), color);
	DrawLine(hDC, rt.GetX(), rt.GetY(), lt.GetX(), lt.GetY(), color);
	DrawLine(hDC, rt.GetX(), rt.GetY(), rb.GetX(), rb.GetY(), color);
}

void DrawRectangle(HDC hDC, const Vector2& leftBottom, const Vector2& rightTop, COLORREF color)
{
	DrawLine(hDC, leftBottom.GetX(), leftBottom.GetY(), rightTop.GetX(), leftBottom.GetY(), color);
	DrawLine(hDC, leftBottom.GetX(), leftBottom.GetY(), leftBottom.GetX(), rightTop.GetY(), color);
	DrawLine(hDC, rightTop.GetX(), rightTop.GetY(), leftBottom.GetX(), rightTop.GetY(), color);
	DrawLine(hDC, rightTop.GetX(), rightTop.GetY(), rightTop.GetX(), leftBottom.GetY(), color);
}

void DrawRectangle(HDC hDC, const float left, const float bottom, const float right, const float top, COLORREF color)
{
	DrawLine(hDC, left, bottom, right, bottom, color);
	DrawLine(hDC, left, bottom, left, top, color);
	DrawLine(hDC, right, top, left, top, color);
	DrawLine(hDC, right, top, right, bottom, color);
}

void DrawCoordinate(HDC hDC, int leftX, int rightX, int upY, int downY, COLORREF color)
{
	DrawLine(hDC, (float)leftX, 0, (float)rightX, 0, color);
	DrawLine(hDC, 0, (float)upY, 0, (float)downY, color);
}
#pragma once
#include "Vector2.h"
class Sphere
{
public:

	// 初期処理
	void Init(void);

	// 更新ステップ
	void Update(void);

	// 描画処理
	void Draw(void);

	// 解放処理
	void Release(void);

	void SetSize(int size);
	Vector2 GetPos(void);
	void SetPos(Vector2 pos);
	void SetColor(int color);

	int Lerp(int start, int end, float t);

	bool InRange(Vector2 pos);

private:

	int mSize;
	Vector2 mPos;
	int mColor;

};


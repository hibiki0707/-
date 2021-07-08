#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <map>
#include "Vector2.h"
#include "Unit.h"
#include "Smoke.h"
#include "Enemy.h"
#include "JumpMan.h"
#include "SceneBase.h"
class SceneManager;
class Star;
class Sphere;
class StarDustManager;

// 描画領域
#define DRAW_AREA_X 0
#define DRAW_AREA_Y 20

// ブロックの画像サイズ
#define BLOCK_IMG_SIZE_X 16
#define BLOCK_IMG_SIZE_Y 16

// pngの画像数
#define IMG_NUM_X 8
#define IMG_NUM_Y 106
#define IMG_NUM_ALL 848

// 画面分割数
#define SPLIT_X 1
#define SPLIT_Y 1

// タイトル表示の余白
#define TITLE_MARGIN 5

// テスト用背景の余白
#define GROUND_MARGIN 40

// マップサイズ
#define MAP_SIZE_X 56
#define MAP_SIZE_Y 32

// 最大ページ数
#define MAX_PAGES 6

class TestScene : public SceneBase
{

public:

	static constexpr int CHR_HEIGHT = 15;

	TestScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void DrawBackGround(void);
	void Release(void) override;

	int GetPage(void);

private:

	// 演習のページ番号
	int mPage;

	int mImgBlockGreen;
	int mImgBlockBlue;
	int mImgPlanePurple;
	int mImgPlaneRed;
	int mImgPlaneGreen;
	int mImgPlaneWhite;
	
	int mImages[IMG_NUM_ALL];
	int mWidth;
	int mHeight;

	int mImgBackGround;

	// ■描画する際に使用する２次元配列
	int mData[MAP_SIZE_Y][MAP_SIZE_X];

	// ■ポインタ用変数
	int mPower;
	int mSpeed;
	int* mSpeedPtr;

	// ■Lerp用変数
	Star* mStar;
	Star* mStarChildren[3];
	Vector2 mMvSPos;
	Vector2 mMvEPos;
	float mMoveStep;
	Sphere* mSphere;
	
	// ■検索用変数
	int mArray01[5] = { 10, 30, 50, 80, 130 };
	
	int mArray02[5] = { 10, 30, 50, 80, 130 };
	std::vector<int> mAns02;

	Unit mUnits[4] = { 
		Unit(80, "戦士", {15, 15}),
		Unit(20, "魔法使い", {10, 10}),
		Unit(50, "武闘家", {20, 20}),
		Unit(10, "無職", {50, 50}),
	};
	std::vector<std::string> mAnsUnits;

	Vector2 mTraps[6] = {
		{10, 10},
		{15, 15},
		{20, 20},
		{25, 25},
		{30, 30},
		{35, 35},
	};

	std::vector<Unit> mUnitsVec;
	std::map<int, Unit> mUnitsMap;

	// ■色
	float mStep;
	Enemy mEnemy;
	JumpMan mJumpMan;
	std::vector<Smoke> mSmokesVecL;
	std::vector<Smoke> mSmokesVecR;
	StarDustManager* mStarDustManager;

	void UpdateTest01(int no);
	void UpdateTest02(int no);
	void UpdateTest03(int no);
	void UpdateTest04(int no);
	void UpdateTest05(int no);
	void UpdateTest06(int no);

	void DrawTest01(int no);
	void DrawTest02(int no);
	void DrawTest03(int no);
	void DrawTest04(int no);
	void DrawTest05(int no);
	void DrawTest06(int no);

	void DrawTitle(int no, const char* title);
	void DrawTestGround(int no, int meshSize);

	void DrawData(int no, int imgHandle);

	Vector2 GetDrawAnsPos(int no, int lineY);
	void DrawAnsString(int no, int lineY, const char* fmt, int value);
	void DrawAnsString(int no, int lineY, const char* fmt, int* value);
	void DrawAnsString(int no, int lineY, const char* fmt, const char* value);

};


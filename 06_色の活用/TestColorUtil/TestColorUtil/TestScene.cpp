#include "DxLib.h"
#include "Utility.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "GameCommon.h"
#include "Star.h"
#include "Sphere.h"
#include "Unit.h"
#include "StarDustManager.h"
#include "TestScene.h"

TestScene::TestScene(SceneManager* manager) : SceneBase(manager)
{
	mWidth = SCREEN_SIZE_X / SPLIT_X;
	mHeight = SCREEN_SIZE_Y / SPLIT_Y;
}

void TestScene::Init(void)
{

	mPage = 1;

	mImgBackGround = LoadGraph("Image/BackGround.png");

	// ブロック画像の読み込み
	LoadDivGraph(
		"Image/Blocks.png",
		IMG_NUM_ALL,
		IMG_NUM_X, IMG_NUM_Y,
		BLOCK_IMG_SIZE_X, BLOCK_IMG_SIZE_Y,
		&mImages[0],
		true);

	// 配列の初期化
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			mData[y][x] = 0;
		}
	}

	// ブロック描画に使用する
	mImgBlockGreen	= mImages[0];
	mImgBlockBlue	= mImages[104];
	mImgPlanePurple = mImages[528];
	mImgPlaneRed	= mImages[425];
	mImgPlaneGreen	= mImages[8];
	mImgPlaneWhite	= mImages[739];

	// ■ポインタ用変数
	mPower = 120;
	mSpeedPtr = &mSpeed;
	*mSpeedPtr = 881;
	mData[1][3] = 777;

	mStar = new Star();
	mStar->Init();
	mStar->SetSizeRate(0.5f);

	for (int i = 0; i < 3; i++)
	{
		mStarChildren[i] = new Star();
		mStarChildren[i]->Init();
		mStarChildren[i]->SetSizeRate(0.2f);
	}

	mSphere = new Sphere();
	mSphere->Init();

	mMoveStep = 0.0f;

	// ■検索用
	mUnitsVec.push_back(Unit(80, "戦士", { 15, 15 }));
	mUnitsVec.push_back(Unit(20, "魔法使い", { 10, 10 }));
	mUnitsVec.push_back(Unit(50, "武闘家", { 20, 20 }));
	mUnitsVec.push_back(Unit(10, "無職", { 50, 50 }));
	mUnitsVec.push_back(Unit(70, "勇者", { 5, 5 }));

	mUnitsMap.emplace(0, Unit(80, "戦士", { 15, 15 }));
	mUnitsMap.emplace(1, Unit(20, "魔法使い", { 10, 10 }));
	mUnitsMap.emplace(2, Unit(50, "武闘家", { 20, 20 }));
	mUnitsMap.emplace(3, Unit(10, "無職", { 50, 50 }));
	mUnitsMap.emplace(4, Unit(70, "勇者", { 5, 5 }));

	// ■色
	mStep = 0.0f;
	mEnemy.Init();
	mJumpMan.Init();
	int img = LoadGraph("Image/Smoke.png");

	int cx = SCREEN_SIZE_X / 4;
	int cy = SCREEN_SIZE_Y / 2;
	int max = 200;
	int r = 0;
	int x = 0;
	int y = 0;
	for (int i = 0; i < 20; i++)
	{
		x = cx + (max / 2) - GetRand(max);
		y = cy + (max / 2) - GetRand(max);
		mSmokesVecL.push_back(Smoke(img, { x, y }));
	}
	for (int i = 0; i < 20; i++)
	{
		x = (cx * 3) + (max / 2) - GetRand(max);
		y = cy + (max / 2) - GetRand(max);
		mSmokesVecR.push_back(Smoke(img, { x, y }));
	}

	mStarDustManager = new StarDustManager(mSceneManager);
	mStarDustManager->Init();

}

void TestScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mStep = 0.0f;
		mMoveStep = 0.0f;
		mPage += 1;
		if (mPage > MAX_PAGES)
		{
			mPage = 1;
		}
		switch (mPage)
		{
		case 5:
			mStarDustManager->Create(
				{ SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 }, 2.0f, 25);
			break;
		}
	}

	switch (mPage)
	{
	case 1:
		// 演習①
		UpdateTest01(1);
		break;
	case 2:
		// 演習②
		UpdateTest02(1);
		break;
	case 3:
		// 演習③
		UpdateTest03(1);
		break;
	case 4:
		// 演習④
		UpdateTest04(1);
		break;
	case 5:
		// 演習⑤
		UpdateTest05(1);
		break;
	case 6:
		// 演習⑥
		UpdateTest06(1);
		break;
	default:
		break;
	}

}

void TestScene::Draw(void)
{

	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// 背景の描画
	DrawBackGround();

	switch (mPage)
	{
	case 1:
		// 演習①
		DrawTest01(1);
		break;
	case 2:
		// 演習②
		DrawTest02(1);
		break;
	case 3:
		// 演習③
		DrawTest03(1);
		break;
	case 4:
		// 演習④
		DrawTest04(1);
		break;
	case 5:
		// 演習⑤
		DrawTest05(1);
		break;
	case 6:
		// 演習⑥
		DrawTest06(1);
		break;
	case 7:
		break;
	default:
		break;
	}

	// タイトルの表示
	DrawFormatString(
		0, 0,
		0x000000,
		"色の活用");

}

void TestScene::DrawBackGround(void)
{

	// 白
	//DrawBox(
	//	0, 0, 
	//	SCREEN_SIZE_X, SCREEN_SIZE_Y, 
	//	0xFFFFFF, true
	//);
	DrawGraph(0, 0, mImgBackGround, false);

	for (int x = 0; x < SPLIT_X; x++)
	{
		for (int y = 0; y < SPLIT_Y; y++)
		{

			DrawBox(
				DRAW_AREA_X + (x * mWidth), DRAW_AREA_Y + (y * mHeight),
				DRAW_AREA_X + ((x + 1) * mWidth), DRAW_AREA_Y + ((y + 1) * mHeight),
				0x000000, false
			);

		}
	}

}

void TestScene::Release(void)
{

	// 画像の解放
	for (int i = 0; i < (IMG_NUM_X * IMG_NUM_Y); i++)
	{
		DeleteGraph(mImages[i]);
	}

	mStar->Release();
	delete mStar;

}

int TestScene::GetPage(void)
{
	return mPage;
}

void TestScene::DrawTest01(int no)
{

	DrawTitle(no, "演習①黒い正方形を、右に描画するに連れて、徐々に透明化しましょう。");
	DrawAnsString(no, 0, "%s", "　　　Hint : SetDrawBlendModeのDX_BLENDMODE_ALPHAを使用");

	int startY = 200;
	int boxSize = 60;
	int num = 15;

	for (int i = 1; i < (num + 1); i++)
	{

		int alpha = 255 - (255 / num * i);

		// ここからコーディングしていこう
		//------------------------------------------
		// 描画空間を作成
		int img01 = MakeScreen(boxSize, boxSize, false);
		// 描画空間を作成
		int img02 = MakeScreen(boxSize, boxSize, false);
		// 合成その①　色の乗算
		int imgMix01 = MakeScreen(boxSize, boxSize, false);
		SetDrawScreen(imgMix01);
		DrawGraph(0, 0, img01, true);

		// DxLibの色の乗算
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawGraph(0, 0, img02, true);

		// ブレンドモードをオフ
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//------------------------------------------

		int x = (boxSize * i);
		DrawBox(x, startY, x + boxSize, startY + boxSize, 0x000000, true);

	}
}

void TestScene::DrawTest02(int no)
{

	DrawTitle(no, "演習②敵キャラクターを、時間(３秒)が進むに連れて徐々に透明化しましょう。");
	DrawAnsString(no, 0, "%s", "　　　Hint : SetDrawBlendModeのDX_BLENDMODE_ALPHAを使用");

	float sec = 3.0f;

	// デルタタイム
	mStep += mSceneManager->GetDeltaTime();

	float t = mStep / sec;
	
	// ここからコーディングしていこう
	//------------------------------------------
	sec += 3.0f;
		// DxLibの色の乗算
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	//------------------------------------------

	// 敵キャラクターの描画
	mEnemy.Draw();

	// ブレンドモードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void TestScene::DrawTest03(int no)
{

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000, true);
	DrawBox(0, 0, SCREEN_SIZE_X, 100, 0xffffff, true);

	DrawTitle(no, "演習③回避ジャンプのイメージで、残像を透明化させてみよう。");
	DrawAnsString(no, 0, "%s", "　　　Hint : SetDrawBlendModeのDX_BLENDMODE_ALPHAを使用");
	DrawAnsString(no, 1, "%s", "　　　※JumpManクラスのDrawJump関数内に記述してください。");
	
	// キャラクター
	mJumpMan.Draw();

	//mJumpMan.DrawJump();

	// DxLibの色の乗算
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	// ブレンドモードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TestScene::DrawTest04(int no)
{

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000, true);
	DrawBox(0, 0, SCREEN_SIZE_X, 100, 0xffffff, true);

	DrawTitle(no, "演習④右側の雲だけ、色の加算合成を使用して雷雲のように明るくしてみよう。");
	DrawAnsString(no, 0, "%s", "　　　Hint : SetDrawBlendModeのDX_BLENDMODE_ADDを使用");

	int size;

	// ここからコーディングしていこう
	//------------------------------------------
	// 左側
	size = mSmokesVecL.size();
	for (int i = 0; i < size; i++)
	{
		mSmokesVecL[i].Draw();
	}

	// 右側
	size = mSmokesVecR.size();
	for (int i = 0; i < size; i++)
	{
		mSmokesVecR[i].Draw();

		// 描画空間を作成
		int img01 = MakeScreen(size, size, false);
		// 描画空間を作成
		int img02 = MakeScreen(size, size, false);

		int imgMix03 = MakeScreen(size, size, false);
		SetDrawScreen(imgMix03);
		DrawGraph(0, 0, img01, true);

		// DxLibの色の乗算
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		DrawGraph(0, 0, img02, true);

		// ブレンドモードをオフ
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//------------------------------------------
	
}

void TestScene::DrawTest05(int no)
{

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000, true);
	DrawBox(0, 0, SCREEN_SIZE_X, 100, 0xffffff, true);

	DrawTitle(no, "演習⑤円の中に入った星屑のみを明るくしてみよう。");
	DrawAnsString(no, 0, "%s", "　　　Hint : SetDrawBlendModeのDX_BLENDMODE_ADDを使用");
	DrawAnsString(no, 1, "%s", "　　　※StarDustManagerクラスのDraw関数内に記述してください。");

	// 円
	mSphere->SetPos({ 350, 300 });
	mSphere->SetSize(100);
	mSphere->SetColor(0x696969);
	mSphere->Draw();

	// ここからコーディングしていこう
	//------------------------------------------
	mStarDustManager->Draw(mSphere);
	//------------------------------------------

	// DxLibの色の乗算
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// ブレンドモードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void TestScene::DrawTest06(int no)
{

	DrawTitle(no, "演習⑥スポットライトのようなイメージで、");
	DrawAnsString(no, 0, "%s", "　　　クリックした箇所を透過で可視化できるようにしましょう。");

	// 新しく描画領域を作り、描画対象にする
	int startY = 80;
	int screen = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y - startY, true);
	SetDrawScreen(screen);
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y - startY, 0x000000, true);

	// 円
	mSphere->SetSize(100);
	mSphere->SetColor(GetColor(255, 0, 255));
	
	// 左クリック
	if (GetMouseInput() == MOUSE_INPUT_LEFT)
	{

		// クリックされた座標
		int x, y;
		GetMousePoint(&x, &y);

		mSphere->SetPos({ x, y });

	}

	// ここからコーディングしていこう
	//------------------------------------------


	//DX_BLENDMODE_NOBLEND      描画後の色 =  Src * 1.0 + Dest * 0.0
	//DX_BLENDMODE_ALPHA        描画後の色 =  Src * SrcAlpha + Dest * InvSrcAlpha
	//DX_BLENDMODE_ADD          描画後の色 =  Src * SrcAlpha + Dest * 1.0
	//DX_BLENDMODE_SUB          描画後の色 = -Src * SrcAlpha + Dest * 1.0
	//DX_BLENDMODE_MUL          描画後の色 =  Src * 0.0 + Dest * Src
	//DX_BLENDMODE_DESTCOLOR    描画後の色 =  Src * 0.0 + Dest * 1.0
	//DX_BLENDMODE_INVDESTCOLOR 描画後の色 =  Src * InvDestColor + Dest * 0.0
	//
	//Src　　　　　: 描画元のＲＧＢ値(0～255 で 0.0～1.0 と考える)
	//SrcAlpha　　 : 描画元のアルファ値(0～255 で 0.0～1.0 と考える)
	//InvSrcAlpha　: 描画元のアルファ値を反転(1.0 - SrcAlpha)したもの
	//Dest　　　　 : 描画先のＲＧＢ値(0～255 で 0.0～1.0 と考える)
	//InvDestColor : 描画先のＲＧＢ値を反転(1.0 - Dest)したもの(RGB各要素単位)
	//------------------------------------------

	// 円を描画
	mSphere->Draw();

	// ブレンドモードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 描画対象を元に戻す
	SetDrawScreen(DX_SCREEN_BACK);

	// 円形にくり抜かれている(はず)画像を描画
	DrawGraph(0, startY, screen, true);

	// 描画領域解放
	DeleteGraph(screen);

}


void TestScene::DrawTitle(int no, const char* title)
{

	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;
	
	int x = DRAW_AREA_X + (mWidth * tmpX) + TITLE_MARGIN;
	int y = DRAW_AREA_Y + (mHeight * tmpY) + TITLE_MARGIN;

	DrawFormatString(x, y, 0x000000, title);

}

void TestScene::DrawTestGround(int no, int meshSize)
{

	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;

	int x1 = DRAW_AREA_X + (mWidth * tmpX) + GROUND_MARGIN;
	int y1 = DRAW_AREA_Y + (mHeight * tmpY) + GROUND_MARGIN;
	int w = MAP_SIZE_X * BLOCK_IMG_SIZE_X;
	int h = MAP_SIZE_Y * BLOCK_IMG_SIZE_Y;
	int x2 = x1 + w;
	int y2 = y1 + h;
	DrawBox(
		x1, y1,
		x2, y2,
		0x696969, true);

	if (meshSize == 0)
	{
		return;
	}

	int cntY = h / meshSize;
	for (int y = 1; y < cntY; y++)
	{
		DrawLine(
			x1, y1 + (y * meshSize), 
			x2, y1 + (y * meshSize), 0x66cdaa, true);
	}

	int cntX = w / meshSize;
	for (int x = 1; x < cntX; x++)
	{
		DrawLine(
			x1 + (x * meshSize), y1,
			x1 + (x * meshSize), y2, 0x66cdaa, true);
	}

}

void TestScene::DrawData(int no, int imgHandle)
{

	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;

	int marginX = (mWidth * tmpX) + GROUND_MARGIN;
	int marginY = (mHeight * tmpY) + GROUND_MARGIN;
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			if (mData[y][x] == 1)
			{
				DrawGraph(
					DRAW_AREA_X + marginX + (x * BLOCK_IMG_SIZE_X),
					DRAW_AREA_Y + marginY + (y * BLOCK_IMG_SIZE_Y),
					imgHandle, true);
			}
		}
	}

}

Vector2 TestScene::GetDrawAnsPos(int no, int lineY)
{
	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;

	int x = DRAW_AREA_X + (mWidth * tmpX) + TITLE_MARGIN;
	int y = DRAW_AREA_Y + (mHeight * tmpY) + TITLE_MARGIN;

	y += TestScene::CHR_HEIGHT;
	y += (lineY * TestScene::CHR_HEIGHT);

	return Vector2(x, y);
}

void TestScene::DrawAnsString(int no, int lineY, const char* fmt, int value)
{
	Vector2 v = GetDrawAnsPos(no, lineY);
	DrawFormatString(v.x, v.y, 0x000000, fmt, value);
}

void TestScene::DrawAnsString(int no, int lineY, const char* fmt, int* value)
{
	Vector2 v = GetDrawAnsPos(no, lineY);
	DrawFormatString(v.x, v.y, 0x000000, fmt, value);
}

void TestScene::DrawAnsString(int no, int lineY, const char* fmt, const char* value)
{
	Vector2 v = GetDrawAnsPos(no, lineY);
	DrawFormatString(v.x, v.y, 0x000000, fmt, value);
}

void TestScene::UpdateTest01(int no)
{
}

void TestScene::UpdateTest02(int no)
{
}

void TestScene::UpdateTest03(int no)
{
	mJumpMan.Update();
}

void TestScene::UpdateTest04(int no)
{
}

void TestScene::UpdateTest05(int no)
{
	mStarDustManager->Update();
}

void TestScene::UpdateTest06(int no)
{
}

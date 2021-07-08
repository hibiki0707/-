#include <DxLib.h>
#include<vector>
#include<string>
#include<fstream>
#include<stack>
#include "KeyCheck.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Unit.h"
#include "Box.h"
#include "Storage.h"
#include "Vector2.h"
#include"Fader.h"
#include"Utility.h"
#include"TimeLimit.h"
#include "GameScene.h"

GameScene::GameScene(SceneManager* manager) : SceneBase(manager){
	mStageNo = 1;
	ChangeState(STATE::GAME);
	mFader = new Fader();
	mFader->Init();

	mTimeLimit = new TimeLimit(manager);
	
}

/// <summary>
/// ������
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Init(void){

	// �X�e�[�W
	mStage = new Stage(this);
	mStage->Init(mStageNo);
	
	// �X�e�[�W
	//SetStage();

	// �O���t�@�C�����g�p���A�X�e�[�W�ݒ�
	LoadGimmickData();

	mImageClear = LoadGraph("Image/Congratulations.png");
	mStepClear = 0.0f;

	// ���Ԑ���
	mTimeLimit->Start(mStageNo * 60);

	// �ړ�����
	mCntMove = 0;
}

/// <summary>
/// �X�V�X�e�b�v
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Update(void){

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::GAMEOVER, true);
	}

	switch (mState)
	{
	case GameScene::STATE::GAME: 
		UpdateGame();
		break;
	case GameScene::STATE::CLEAR:
		UpdateClear();
		break;
	case GameScene::STATE::CHANGE_STAGE:
		UpdateChangeStge();
		break;
	
	}
}

void GameScene::UpdateGame(void){
	// �X�e�[�W
	mStage->Update();
	// Unit
	mUnit->Update();

	// ���I�z��
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		mBoxes[i]->Update();
	}

	int sizes = mStorages.size();
	for (int i = 0; i < sizes; i++) {
		mStorages[i]->Update();
	}

	// �����߂�N�L�[
	if (keyTrgDown[ KEY_P1_A ] && mHistoryBack.size() > 0
		&& mUnit->IsEnableBack()) {

		// �Ō�̑�������擾
		History his = mHistoryBack.top();

		if (his.box != nullptr) {
			// �ו����ړ�������
			his.box->BackMove(his);
		}

		// �Ō�̑���������j�b�g�ɓn���Ċ����߂�������������
		mUnit->BackMove(his);
	
		// �Ō�̑�������폜
		mHistoryBack.pop();
	}

	// ���Ԑ���
	mTimeLimit->Update();
	if (mTimeLimit->IsTimeOver() == true) {
		mSceneManager->ChangeScene(SCENE_ID::GAMEOVER,true);
		return;
	}

	// �N���A����
	bool isClear = true;
	size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		if (mBoxes[i]->IsStayStorage() == false) {
			isClear = false;
			break;
		}
	}

	if (isClear == true) {
		if (mStageNo >= MAX_STAGE_NO) {
			// �Q�[���I�[�o�[��ʂ֑J��
			mSceneManager->ChangeScene(SCENE_ID::GAMEOVER, true);
		}
		else {
			// ���̃X�e�[�W��
			//ChangeStage();
			ChangeState(STATE::CLEAR);
			return;
		}

	}
}

void GameScene::UpdateClear(void){
	mStepClear+= mSceneManager->GetDeltaTime();
	if (mStepClear > TIME_CLEAR_) {
		
		ChangeState(STATE::CHANGE_STAGE);
		return;
	}
}

void GameScene::UpdateChangeStge(void){
	mFader->Update();

	Fader::FADE_STATE state = mFader->GetState();

	switch (state)
	{
	case Fader::FADE_STATE::FADE_OUT:
		// �i�X�Â�����
		if (mFader->IsEnd() == true) {
			// �X�e�[�W�؂�ւ�
			ChangeStage();
			// ���X�ɖ��邭����
			mFader->SetFade(Fader::FADE_STATE::FADE_IN);
		}

		break;
	case Fader::FADE_STATE::FADE_IN:
		// �i�X���邭����
		if (mFader->IsEnd() == true) {
			mFader->SetFade(Fader::FADE_STATE::NONE);
			ChangeState(STATE::GAME);
		}
		break;
	
	}

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name=""></param>
void GameScene::Draw(void){

	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ̃N���A
	ClearDrawScreen();

	switch (mState)
	{
	case GameScene::STATE::GAME:
		DrawGame();
		break;
	case GameScene::STATE::CLEAR:
		DrawClear();
		break;
	case GameScene::STATE::CHANGE_STAGE:
		DrawChangeStge();
		break;

	}
}

void GameScene::DrawGame(void){
	// �X�e�[�W
	mStage->Draw();

	int sizes = mStorages.size();
	for (int i = 0; i < sizes; i++) {
		mStorages[i]->Draw();
	}
	// Unit
	mUnit->Draw();

	// ���I�z��
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		mBoxes[i]->Draw();
	}

	// ���Ԑ���
	mTimeLimit->Draw();

	// �X�R�A�\��
	DrawScore();
}

void GameScene::DrawClear(void) {
	DrawGame();

	// �X�e�[�W�N���A�̉�ʕ\��
	DrawGraph(SCREEN_SIZE_X / 2 - (500 / 2)
		, SCREEN_SIZE_Y / 2
		, mImageClear, true);

}

void GameScene::DrawChangeStge(void){
	DrawGame();
}

void GameScene::DrawScore(void){
	// �v���C���[������ɉ����āA�X�R�A�𑝉�������
	// �ړ������������������A�߂��������������
	DrawFormatString(20, 20, 0xffffff, "%d",mCntMove);
	
}

/// <summary>
/// ���\�[�X���
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Release(void){
	// �X�e�[�W
	mStage->Release();
	delete mStage;
	// Unit
	mUnit->Release();
	delete mUnit;

	// ���I�z��
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		mBoxes[i]->Release();
		delete mBoxes[i];
	}
	// ���I�z��̃T�C�Y���[���ɂ���
	mBoxes.clear();

	int sizes = mStorages.size();
	for (int i = 0; i < sizes; i++) {
		mStorages[i]->Release();
		delete mStorages[i];
	}
	mStorages.clear();

	DeleteGraph(mImageClear);

	// ���엚��
	//while (mHistoryBack.size > 0) {
	//	/*auto tmp = mHistoryBack.top;
	//	delete tmp;*/

	//	mHistoryBack.pop();
	//}
	//mHistoryBack = std::stack<History>();

}

Stage* GameScene::GetStage(void){

	return mStage;
}

Box* GameScene::GetCollisionBox(Vector2 pos){
	Box* ret = nullptr;

	Vector2 boxPos;
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		boxPos = mBoxes[i]->GetPos();
		// ���W�̔�r
		if (pos.x == boxPos.x && pos.y == boxPos.y) {
			// ���W����v������Box��߂�l�ɂ���
			ret = mBoxes[i];
			break;
		}
		
	}

	return ret;
}

Storage* GameScene::GetCollisionStorage(Vector2 pos){
	// �����̍��W�ƈ�v����ו��u���������
	// ������Ȃ���΁Anullptr��Ԃ�
	Storage* ret = nullptr;

	Vector2 storagePos;
	int size = mStorages.size();
	for (int i = 0; i < size; i++) {
		storagePos = mStorages[i]->GetPos();
		// ���W�̔�r
		if (pos.x == storagePos.x && pos.y == storagePos.y) {
			// ���W����v������Box��߂�l�ɂ���
			ret = mStorages[i];
			break;
		}

	}
	return ret;
}

std::string GameScene::GetCsvPathGround(int StageNo){
	std::string ret = "";

	ret += FILE_PATH_CSV;
	ret += std::to_string(StageNo);
	ret += "/";
	ret += FILE_NAME_GROUND;

	return ret;
}

std::string GameScene::GetCsvPathGimmick(int StageNo){
	std::string ret = "";

	ret += FILE_PATH_CSV;
	ret += std::to_string(StageNo);
	ret += "/";
	ret += FILE_NAME_GIMMICK;

	return ret;
}

void GameScene::RegisHistory(DIR dir, Vector2 pos, Box* box){
	Vector2 boxPos = { 0,0 };
	if (box != nullptr) {
		boxPos = box->GetPos();

	}

	History his = {dir,pos,box,boxPos};
	mHistoryBack.push(his);
}

void GameScene::PlusCntMove(void){
	mCntMove++;
}

void GameScene::MinusCntMove(void){
	mCntMove--;
}

void GameScene::ChangeStage(void){
	Release();

	// ���̃X�e�[�W�֍s������
	mStageNo++;
	Init();
}

void GameScene::SetStage(void){

	// �ו�
	Box* tmpBox;

	// �ו��u����
	Storage* tmpStorage;


	switch (mStageNo)
	{
	case 1:
		// Unit
		mUnit = new Unit(this);
		mUnit->Init({ 10,10 });

		tmpBox = new Box(this);
		tmpBox->Init({ 11,10 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init({ 18,10 });
		mBoxes.push_back(tmpBox);
		
		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,10 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init({ 11,11 });
		mStorages.push_back(tmpStorage);
		break;
	case 2:
		// Unit
		mUnit = new Unit(this);
		mUnit->Init({ 10,6 });

		// �ו�
		tmpBox = new Box(this);
		tmpBox->Init({ 11,7 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init({ 18,8 });
		mBoxes.push_back(tmpBox);

		// �ו��u����
		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,10 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,11 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,12 });
		mStorages.push_back(tmpStorage);
		break;
	default:
		break;
	}
}

void GameScene::LoadGimmickData(void){
	
	// �t�@�C���p�X���擾
	std:: string filePath = GetCsvPathGimmick(mStageNo);

	// �t�@�C����ǂݍ���
	std::ifstream ifs(filePath);

	// 1�s���ǂݍ���
	int y = 0;
	std::string line;

	// �ו�
	Box* tmpBox;

	// �ו��u����
	Storage* tmpStorage;

	while (getline(ifs, line)) {

		// Y�ŕ������ꂽline
		std::vector<std::string> strvec = Utility::Split(line, ',');

		// X�ŕ������ꂽstrvec

		// mMap�ɒl�������āA
		// �X�e�[�W���쐬
		for (int x = 0; x < strvec.size(); x++) {
			int chipNo = stoi(strvec[x]);
			switch (chipNo)
			{

			case 4:
				// �ו�
				tmpBox = new Box(this);
				tmpBox->Init({ x,y });
				mBoxes.push_back(tmpBox);
				break;

			case 5:
				// �ו��u����
				tmpStorage = new Storage(this);
				tmpStorage->Init({ x,y });
				mStorages.push_back(tmpStorage);
				break;
			case 6:
				// ���j�b�g
				// Unit
				mUnit = new Unit(this);
				mUnit->Init({ x,y });
				break;
			}
		}
		y++;
	}

	if (true) {}
}

void GameScene::ChangeState(STATE state){
	mState = state;
	switch (state)
	{
	case GameScene::STATE::GAME:
		break;
	case GameScene::STATE::CLEAR:
		mStepClear = 0.0f;
		break;
	case GameScene::STATE::CHANGE_STAGE:
		// ���񂾂�Â�����
		mFader->SetFade(Fader::FADE_STATE::FADE_OUT);
		break;

	}

}

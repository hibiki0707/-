#pragma once

/// <summary>
/// シングルチンクラス
/// このクラスの「オブジェクトが一つしかない」事を
/// 保証するクラス
/// </summary>
class Singleton
{
private:
	Singleton() {};
	// コピーと代入の禁止
	Singleton(const Singleton&)=delete; // コピーコンストラクタ
	void operator=(const Singleton&)=delete; // 代入
	int counter = 0;
public:
	// インスタンス取得関数
	static Singleton& Instance() {
		static Singleton instance;	// 唯一のオブジェクト
		return instance;
	}
	void Out();
};


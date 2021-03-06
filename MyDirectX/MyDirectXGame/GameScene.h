#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugText.h"
#include "Audio.h"
#include "Collision.h"
#include "ParticleManager.h"
#include "DebugCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	Light *light = nullptr;
private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon *dxCommon, Input *input, Audio *audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// パーティクル生成
	/// </summary>
	void ParticlesCreate(XMFLOAT3 Pos);

private: // メンバ変数
	DirectXCommon *dxCommon = nullptr;
	Input *input = nullptr;
	Audio *audio = nullptr;
	DebugText debugText;
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	DebugCamera *camera = nullptr;
	Sprite *spriteBG = nullptr;

	Model *modelSkydome = nullptr;
	Object3d *objSkydome = nullptr;

	Model *modelGround = nullptr;
	Object3d *objGround = nullptr;

	Model *modelBom = nullptr;
	Object3d *objBom = nullptr;
	ParticleManager *particle3d = nullptr;

	/*Object3d *playerObj = nullptr;
	Model *playerModel = nullptr;

	Sphere sphere;
	Plane plane;
	Triangle triangle;
	Ray ray;*/

	float collision;

	const float speedX = 9;
	float speedY = 15;
	const float gravity = -9.8 / 60.0f;
	XMFLOAT3 pos = { 0,0,0 };
	bool bomFlag = false;
};
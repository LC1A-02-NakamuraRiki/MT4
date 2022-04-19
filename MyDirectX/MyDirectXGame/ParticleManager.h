#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include<forward_list>

#include "Camera.h"

class ParticleManager
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	//// 頂点データ構造体
	//struct VertexPosNormalUv
	//{
	//	XMFLOAT3 pos; // xyz座標
	//	XMFLOAT3 normal; // 法線ベクトル
	//	XMFLOAT2 uv;  // uv座標
	//};
	struct Particle
	{
		// Microsoft::WRL::を省略
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
		// DirectX::を省略
		using XMFLOAT3 = DirectX::XMFLOAT3;
		using XMFLOAT4 = DirectX::XMFLOAT4;
	public:
		XMFLOAT3 position = {};
		XMFLOAT3 velosity = {};
		XMFLOAT3 accel = {};
		int frame = 0;
		int num_frame = 0;
		float scale = 1.0f;
		float s_scale = 1.0f;
		float e_scale = 0.0f;

		XMFLOAT4 color = {};
	};

	struct VertexPos
	{
		XMFLOAT3 pos; // xyz座標
		float scale;
		XMFLOAT4 color;
	};

	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		//XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
		XMMATRIX matBillboard;
	};

private: // 定数
	static const int vertexCount = 65536;		// 頂点数
	//static const int indexCount = 3*2;		// 頂点数

public: // 静的メンバ関数


	/// 3Dオブジェクト生成
	static ParticleManager* Create(ID3D12Device *device, Camera *camera);

private: // 静的メンバ変数
	// デバイス
	ID3D12Device *device = nullptr;
	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize = 0u;
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	ComPtr<ID3D12PipelineState> pipelinestate;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// パーティクル配列
	std::forward_list<Particle> particles;
	// カメラ
	Camera *camera = nullptr;;

public:// メンバ関数
	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	/// <returns></returns>
	void InitializeDescriptorHeap();

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	void InitializeGraphicsPipeline();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <returns>成否</returns>
	void LoadTexture();

	/// <summary>
	/// モデル作成
	/// </summary>
	void CreateModel();

public: // メンバ関数
	void Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList *cmdList);

	void Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel,float start_scale,float end_scale, XMFLOAT4 color);

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	//const XMFLOAT3& GetPosition() { return position; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	//void SetPosition(XMFLOAT3 position) { this->position = position; }

private: // メンバ変数
	// 色
	/*XMFLOAT4 color = { 1,1,1,1 };*/
	// ローカルスケール
	//XMFLOAT3 scale = { 1,1,1 };
	//XMFLOAT4 color = { 1,1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	//XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	//XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	//XMMATRIX matWorld;
	// 親オブジェクト
	//ParticleManager* parent = nullptr;
	ParticleManager(ID3D12Device *device, Camera *camera);
};


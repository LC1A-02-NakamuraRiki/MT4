#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

#include "Model.h"
#include "Camera.h"
#include "Light.h"
class Object3d
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	static Light *light;
public: // サブクラス
// 頂点データ構造体
	//struct VertexPosNormalUv
	//{
	//	XMFLOAT3 pos; // xyz座標
	//	XMFLOAT3 normal; // 法線ベクトル
	//	XMFLOAT2 uv;  // uv座標
	//};

	// 定数バッファ用データ構造体
	struct ConstBufferDataB0
	{
		//XMMATRIX mat;	// ３Ｄ変換行列
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};

	// パイプラインセット
	struct PipelineSet
	{
		// ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootsignature;
		// パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState> pipelinestate;
	};
private: // 定数
	//static const int division = 50;					// 分割数
	//static const float radius;				// 底面の半径
	//static const float prizmHeight;			// 柱の高さ
	//static const int planeCount = division * 2 + division * 2;		// 面の数
	//static const int vertexCount = 8 * 6;		// 頂点数
	//static const int indexCount = (3 * 2) * 6;

public: // 静的メンバ関数

	//静的初期化
	static void StaticInitialize(ID3D12Device *device,Camera *camera = nullptr);

	//グラフィックパイプラインの生成
	static void InitializeGraphicsPipeline();

	//描画前処理
	static void PreDraw(ID3D12GraphicsCommandList *cmdList);

	//描画後処理
	static void PostDraw();

	/// カメラのセット
	static void SetCamera(Camera *camera) {
		Object3d::camera = camera;
	}

	//3Dオブジェクト生成
	static Object3d *Create(Model *model = nullptr);

	//ライトの位置設定
	static void SetLight(Light *light) { Object3d::light = light; }
	
private: // 静的メンバ変数
// デバイス
	static ID3D12Device *device;
	// デスクリプタサイズ
	//static UINT descriptorHandleIncrementSize;
	// コマンドリスト
	static ID3D12GraphicsCommandList *cmdList;
	// ルートシグネチャ
	//static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプライン
	static PipelineSet pipelineSet;
	// デスクリプタヒープ
	//static ComPtr<ID3D12DescriptorHeap> descHeap;
	// 頂点バッファ
	//static ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	//static ComPtr<ID3D12Resource> indexBuff;
	// テクスチャバッファ
	//static ComPtr<ID3D12Resource> texbuff;
	// シェーダリソースビューのハンドル(CPU)
	//static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	//static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// ビュー行列
	//static XMMATRIX matView;
	//// 射影行列
	//static XMMATRIX matProjection;
	//// 視点座標
	//static XMFLOAT3 eye;
	//// 注視点座標
	//static XMFLOAT3 target;
	//// 上方向ベクトル
	//static XMFLOAT3 up;
	// 頂点バッファビュー
	//static D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	//static D3D12_INDEX_BUFFER_VIEW ibView;
	// 頂点データ配列
	//static VertexPosNormalUv vertices[vertexCount];
	// 頂点インデックス配列
	//static unsigned short indices[indexCount];
	// カメラ
	static Camera *camera;
private:// 静的メンバ関数
	
	//デスクリプタヒープの初期化
	//static bool InitializeDescriptorHeap();

public: 
	//メンバ関数
	bool Initialize();
	
	//毎フレーム処理
	void Update();

	//描画
	void Draw();

	//座標の取得
	const XMFLOAT3 &GetPosition() { return position; }
	//座標の設定
	void SetPosition(XMFLOAT3 position) { this->position = position; }

	// 回転角の取得
	const XMFLOAT3 &GetRotation() { return rotation; }
	// 回転角の設定
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }

	// モデルスケールの取得
	const XMFLOAT3 &GetScale() { return scale; }
	// モデルスケールの設定
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

	// モデルとの連携
	void LinkModel(Model *model) { this->model = model; };

	/// ビルボードフラグのセット
	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }

	private: // メンバ変数
	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ
		// 色
	XMFLOAT4 color = { 1,1,1,1 };
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	Object3d *parent = nullptr;
	// モデル
	Model *model = nullptr;
	// ビルボード
	bool isBillboard = false;
};
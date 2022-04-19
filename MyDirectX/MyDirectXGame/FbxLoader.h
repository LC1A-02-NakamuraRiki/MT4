#pragma once

#include "fbxsdk.h"
#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include "Model.h"

class FbxLoader
{
private:
	using string = std::string;
public:
	static const string baseDirectory;
public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

	void Initialize(ID3D12Device *device);

	void Finalize();

	void LoadModelFromFile(const string &m0delName);

	void ParseNodeRecursive(Model *model, FbxNode *fbxNode,Node *parent = nullptr);
private:
	ID3D12Device *device = nullptr;
	FbxManager *fbxManager = nullptr;
	FbxImporter *fbxImporter = nullptr;
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;
};
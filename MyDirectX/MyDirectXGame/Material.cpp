#include "Material.h"
#include <DirectXTex.h>
#include <cassert>

using namespace DirectX;
using namespace std;

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
ID3D12Device *Material::device = nullptr;

void Material::StaticInitialize(ID3D12Device *device)
{
	//初期化チェック
	assert(!Material::device);

	Material::device = device;
}

Material *Material::Create()
{
	Material *instance = new Material;
	instance->Initialize();
	return instance;
}

void Material::Initialize()
{
	//定数バッファの生成
	CreateConstantBuffer();
}

void Material::CreateConstantBuffer()
{
	HRESULT result;
	// 定数バッファの生成
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB1) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));
	if (FAILED(result)) {
		assert(0);
	}
}

void Material::LoadTexture(const std::string &directoryPath, CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle, CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle)
{
	// テクスチャなし
	if (filename.size() == 0) {
		filename = "white1x1.png";
	}

	cpuDescHandleSRV = cpuHandle;
	gpuDescHandleSRV = gpuHandle;

	HRESULT result = S_FALSE;

	// WICテクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	//ファイルパスを結合
	string filepath = directoryPath + filename;

	//ユニコード文字列に変換する
	wchar_t wfilepath[128];
	int iBufferSize = MultiByteToWideChar
	(
		CP_ACP,
		0,
		filepath.c_str(),
		-1,
		wfilepath,
		_countof(wfilepath)
	);

	/*result = LoadFromWICFile(
		L"Resources/texture.png", WIC_FLAGS_NONE,
		&metadata, scratchImg);*/
	result = LoadFromWICFile
	(
		wfilepath, WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	/*if (FAILED(result)) {
		return result;
	}*/

	const Image *img = scratchImg.GetImage(0, 0, 0); // 生データ抽出

	// リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	// テクスチャ用バッファの生成
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // テクスチャ用指定
		nullptr,
		IID_PPV_ARGS(&texbuff));
	//if (FAILED(result)) {
	//	return result;
	//}

	// テクスチャバッファにデータ転送
	result = texbuff->WriteToSubresource(
		0,
		nullptr, // 全領域へコピー
		img->pixels,    // 元データアドレス
		(UINT)img->rowPitch,  // 1ラインサイズ
		(UINT)img->slicePitch // 1枚サイズ
	);
	/*if (FAILED(result)) {
		return result;
	}*/

	// シェーダリソースビュー作成
	cpuDescHandleSRV = cpuHandle;
	gpuDescHandleSRV = gpuHandle;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // 設定構造体
	D3D12_RESOURCE_DESC resDesc = texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView(texbuff.Get(), //ビューと関連付けるバッファ
		&srvDesc, //テクスチャ設定情報
		cpuDescHandleSRV
	);
}

void Material::Update()
{
	HRESULT result;
	// 定数バッファへデータ転送
	ConstBufferDataB1 *constMap1 = nullptr;
	result = constBuff->Map(0, nullptr, (void **)&constMap1);
	if (SUCCEEDED(result)) {
		constMap1->ambient = ambient;
		constMap1->diffuse = diffuse;
		constMap1->specular = specular;
		constMap1->alpha = alpha;
		constBuff->Unmap(0, nullptr);
	}
}

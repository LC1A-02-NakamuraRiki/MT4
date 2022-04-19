#include"Light.h"

using namespace DirectX;

ID3D12Device *Light::device = nullptr;

void Light::StaticInitialize(ID3D12Device *device)
{
	assert(!Light::device);
	assert(device);
	Light::device = device;
}

void Light::Initialize()
{
	HRESULT result;
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) &~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));

	if (FAILED(result)){assert(0);}
	TransferConstBuffer();
}

void Light::TransferConstBuffer()
{
	HRESULT result;
	ConstBufferData *constMap = nullptr;

	result = constBuff->Map(0, nullptr, (void **)&constMap);
	if (SUCCEEDED(result)) {
		constMap->lightv = -lightdir;
		constMap->lightcolor = lightcolor;
		constBuff->Unmap(0, nullptr);
	}
}

void Light::SetLightDir(const XMVECTOR &lightdir)
{
	this->lightdir = XMVector3Normalize(lightdir);
	dirty = true;
}

void Light::SetLightColor(const XMFLOAT3 &lightcolor)
{
	this->lightcolor = lightcolor;
	dirty = true;
}

void Light::Update()
{
	if (dirty) {
		TransferConstBuffer();
		dirty = false;
	}
}

void Light::Draw(ID3D12GraphicsCommandList *cmdList, UINT rootParameterindex)
{
	cmdList->SetGraphicsRootConstantBufferView(rootParameterindex,
	constBuff->GetGPUVirtualAddress());
}

Light *Light::Create()
{
	Light *instance = new Light();
	instance->Initialize();
	return instance;
}

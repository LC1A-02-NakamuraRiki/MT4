﻿#pragma once
#include "Camera.h"
#include "input.h"

/// <summary>
/// デバッグ用カメラ
/// </summary>
class DebugCamera :
	public Camera
{
	using XMMATRIX = DirectX::XMMATRIX;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	/// <param name="input">入力</param>
	DebugCamera(int window_width, int window_height,Input *input);
	
	void Update();
private:
	Input *input;
	// スケーリング
	float scaleX = 1.0f;
	float scaleY = 1.0f;
};

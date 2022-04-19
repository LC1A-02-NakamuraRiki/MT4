#include "GameScene.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "FbxLoader.h"
using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteBG);
	safe_delete(particle3d);
	safe_delete(objSkydome);
	safe_delete(modelSkydome);
	safe_delete(objGround);
	safe_delete(modelGround);
	safe_delete(objBom);
	safe_delete(modelBom);
	safe_delete(light);
}

void GameScene::Initialize(DirectXCommon *dxCommon, Input *input, Audio *audio)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText.Initialize(debugTextTexNumber);

	particle3d = ParticleManager::Create(dxCommon->GetDevice(), camera);
	
	//�X�v���C�g
	// �e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
		assert(0);
		return;
	}
	//// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	
	// 3D�I�u�W�F�N�g����
	modelSkydome = Model::CreateFromObject("skydome", false);
	objSkydome = Object3d::Create(modelSkydome);
	objSkydome->SetScale({ 9.0f, 9.0f, 9.0f });
	modelGround = Model::CreateFromObject("ground", true);
	objGround = Object3d::Create(modelGround);
	objGround->SetScale({ 12.0f, 12.0f, 12.0f });
	modelBom = Model::CreateFromObject("bom", true);
	objBom = Object3d::Create(modelBom);
	objBom->SetPosition({-890.0f,10.0f,0.0f });
	//FbxLoader::GetInstanc9e()->LoadModelFromFile(
	//"cube");

	light = Light::Create();
	light->SetLightColor({ 1.0f,0.8f,0.8f});
	
	Object3d::SetLight(light);

	////�T�E���h�Đ�
	//audio->PlayBGM("Resources/Alarm01.wav", true);
	//audio->PlaySE("Resources/Alarm01.wav", false);
	//audio->StopBGM();
}

void GameScene::Update()
{
	////�}�E�X�̍��W
	///*POINT mousePos;
	//GetCursorPos(&mousePos);*/

	//debugText.Print(20, 20, 1.5f,"ObjectMove:ArrowKey");
	//debugText.Print(20, 50, 1.5f,"EyeMove:W A S D");
	
	XMFLOAT3 cameraEye = camera->GetEye();
	XMFLOAT3 cameraTarget = camera->GetTarget();
	
	//���Z�b�g
	if (input->PushKey(DIK_R))
	{
		speedY = 15;
		objBom->SetPosition({ -890.0f,10.0f,0.0f });
		bomFlag = false;
		camera->SetEye({ -890.0f,10.0f ,pos.z - 100.0f });
		camera->SetTarget({ -890.0f,10.0f ,pos.z });
	}

	//�C�e����
	if (input->PushKey(DIK_SPACE))
	{
		bomFlag = true;
	}
	
	if (bomFlag)
	{
		pos = objBom->GetPosition();
		speedY += gravity;
		pos.x += speedX;
		pos.y += speedY;
		objBom->SetPosition(pos);
		camera->SetEye({ pos.x,pos.y ,pos.z - 100.0f });
		camera->SetTarget({ pos.x,pos.y ,pos.z });
	}
	
	// �I�u�W�F�N�g�ړ�
	//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT) || input->PushKey(DIK_SPACE) || input->PushKey(DIK_LCONTROL))
	//{
	//	// ���݂̍��W���擾
	//	XMFLOAT3 pos = objFighter->GetPosition();

	//	// �ړ���̍��W���v�Z
	//	if (input->PushKey(DIK_SPACE)) { pos.y += 0.1f;}
	//	else if (input->PushKey(DIK_LCONTROL)) { pos.y -= 0.1f;}

	//	if (input->PushKey(DIK_RIGHT)) { pos.x += 0.1f;}
	//	else if (input->PushKey(DIK_LEFT)) { pos.x -= 0.1f;}
	//	
	//	if (input->PushKey(DIK_UP)) { pos.z += 0.1f; }
	//	else if (input->PushKey(DIK_DOWN)) { pos.z -= 0.1f; }

	//	ParticlesCreate({ pos.x - 2.0f,pos.y,pos.z });
	//	// ���W�̕ύX�𔽉f
	//	objFighter->SetPosition(pos);
	//}

	// �J�����ړ�
	/*if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
	{
		if (input->PushKey(DIK_W)) { cameraEye.y += 1.0f; }
		else if (input->PushKey(DIK_S)) { cameraEye.y -= 1.0f; }
		if (input->PushKey(DIK_D)) { cameraEye.x += 1.0f; }
		else if (input->PushKey(DIK_A)) { cameraEye.x -= 1.0f; }

		camera->SetEye(cameraEye);
	}*/

	//// �J�����ړ�
	/*if (input->PushKey(DIK_Q) || input->PushKey(DIK_E) || input->PushKey(DIK_LCONTROL) || input->PushKey(DIK_SPACE))
	{
		if (input->PushKey(DIK_SPACE)) { camera->CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_LCONTROL)) { camera->CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_E)) { camera->CameraMoveVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_Q)) { camera->CameraMoveVector({ -1.0f,0.0f,0.0f }); }
	}*/

	//�J�����p�x�ύX
	/*if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
	{
		if (input->PushKey(DIK_W)) { cameraTarget.y += 1.0f; }
		else if (input->PushKey(DIK_S)) { cameraTarget.y -= 1.0f; }
		if (input->PushKey(DIK_D)) { cameraTarget.x += 1.0f; }
		else if (input->PushKey(DIK_A)) { cameraTarget.x -= 1.0f; }
		camera->SetTarget(cameraTarget);
	}*/
	
	//���C�g
	/*static XMVECTOR lightDir = { 0, 1, 5, 0 };
	if (input->PushKey(DIK_W)) { lightDir.m128_f32[1] += 1.0f; }
	else if (input->PushKey(DIK_S)) { lightDir.m128_f32[1] -= 1.0f; }
	if (input->PushKey(DIK_D)) { lightDir.m128_f32[0] += 1.0f; }
	else if (input->PushKey(DIK_A)) { lightDir.m128_f32[0] -= 1.0f; }
	light->SetLightDir(lightDir);*/
	
	particle3d->Update();
	camera->Update();
	objSkydome->Update();
	objGround->Update();
	objBom->Update();
	light->Update();
}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	//-------------------------------------------------------------//


	spriteBG->Draw();


	//-------------------------------------------------------------//
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();
#pragma endregion
	
#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(cmdList);
	//-------------------------------------------------------------//

	//playerObj->Draw();
	objSkydome->Draw();
	objGround->Draw();
	objBom->Draw();
	
	//-------------------------------------------------------------//
	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	particle3d->Draw(cmdList);
#pragma endregion

	
#pragma region �O�i�X�v���C�g�`��
	//// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//
	debugText.Print(20, 30, 2.0f, "Space : Start");
	debugText.Print(20, 80, 2.0f, "R : ReStart");
	debugText.Print(20, 130, 1.5f, "bom Pos  X:%f Y:%f Z:%f", pos.x, pos.y, pos.z);
	debugText.Print(20, 160, 1.5f, "bom speed  X:%f Y:%f", speedX, speedY);

	//-------------------------------------------------------------//
	// �f�o�b�O�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::ParticlesCreate(XMFLOAT3 Pos)
{
	for (int i = 0; i < 1; i++)
	{
		//X,Y,Z�S��{-5.0f,+5.0f}�Ń����_���ɕ��z
		const float md_pos = 0.5f;
		XMFLOAT3 pos = Pos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		////X,Y,Z�S��{-0.05f,+0.05f}�Ń����_���ɕ��z
		const float md_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		//�d�͂Ɍ����Ă�Y�̂�{-0.001f,0}�Ń����_�����z
		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y = (float)rand() / RAND_MAX * md_acc;

		// �ǉ�
		particle3d->Add(60, pos, vel, acc, 1.0f, 1.0f, {1,1,1,1});
	}
}
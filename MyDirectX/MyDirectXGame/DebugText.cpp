#include "DebugText.h"

DebugText::DebugText()
{
}

DebugText::~DebugText()
{
	for (int i = 0; i < _countof(spriteDatas); i++) {
		delete spriteDatas[i];
	}
}

void DebugText::Initialize(UINT texnumber)
{
	for (int i = 0; i < _countof(spriteDatas); i++)
	{
		spriteDatas[i] = Sprite::Create(texnumber, { 0,0 });
	}
}

void DebugText::Print(float x, float y, float size, std::string text, ...)
{
	bool parsentFlag = false;
	va_list args;
	va_start(args, text);
	text.push_back(' ');
	for (size_t i = 0; text[i] != '\0'; ++i)
	{
		printf("%c:", text[i]);
		if (text[i] == '%')
		{
			parsentFlag = true;
		}
		if (parsentFlag == true)
		{
			int temp;
			double tempF = NULL;
			switch (text[i])
			{
			case 'd':
				temp = va_arg(args, int);
				text.replace((size_t)i - 1, 2, std::to_string(temp));
				parsentFlag = false;
				break;
			case 'f':
				tempF = va_arg(args, double);
				tempF = round(tempF * 100);
				tempF = tempF / 100;
				text.replace((size_t)i - 1, 2, std::to_string(tempF));
				parsentFlag = false;
				break;
			default:
				break;
			}
		}
	}
	va_end(args);
	//全ての文字について
	for (size_t i = 0; text[i] != '\0'; i++)
	{
		//最大文字数超過
		if (spriteIndex >= maxCharCount)
		{
			break;
		}

		//1文字取り出す(ASCIIコードでしか成り立たない)
		const unsigned char &character = text[i];

		//ASCIIコードの2段分飛ばした番号を計算
		int fontIndex = character - 32;
		if (character >= 0x7f)
		{
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		//座標計算
		spriteDatas[spriteIndex]->SetPosition({ x + fontWidth * size * i, y });
		spriteDatas[spriteIndex]->SetTextureRect({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight }, { (float)fontWidth, (float)fontHeight });
		spriteDatas[spriteIndex]->SetSize({ fontWidth * size, fontHeight * size });

		// 文字を１つ進める
		spriteIndex++;
	}
}

void DebugText::DrawAll(ID3D12GraphicsCommandList *cmdList)
{
	//全ての文字のスプライトについて
	for (int i = 0; i < spriteIndex; i++)
	{
		//スプライト描画
		spriteDatas[i]->Draw();
	}

	spriteIndex = 0;
}

#pragma once

/// <summary>
/// �㉺���E�̃����o�[�ϐ�����\����
/// </summary>
struct Box
{
	int Left;
	int Top;
	int Right;
	int Bottom;
};


/// <summary>
/// xy���W�\���́@x,y
/// </summary>
struct Point
{
	int x;
	int y;
};

/// <summary>
/// �~�\���́@x,y,���a
/// </summary>
struct circle
{
	int x;
	int y;
	int radius;
};

/// <summary>
/// level�I��box�p�\����
/// </summary>
struct Level
{
	int x;
	int y;
	int width;
	int height;
	int level;
};

/// <summary>
/// Level������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="level"></param>
//Level LevelInit(int x,int y,int width,int height,int level)
//{
//	Level temp;
//	temp.x = x;
//	temp.y = y;
//	temp.width = width;
//	temp.height = height;
//	temp.level = level;
//
//	return temp;
//};
#pragma once

/// <summary>
/// 上下左右のメンバー変数入り構造体
/// </summary>
struct Box
{
	int Left;
	int Top;
	int Right;
	int Bottom;
};


/// <summary>
/// xy座標構造体　x,y
/// </summary>
struct Point
{
	int x;
	int y;
};

/// <summary>
/// 円構造体　x,y,半径
/// </summary>
struct circle
{
	int x;
	int y;
	int radius;
};

/// <summary>
/// level選択box用構造体
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
/// Level初期化
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
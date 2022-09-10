#pragma once

struct Box
{
	int Left;
	int Top;
	int Right;
	int Bottom;
};

struct Point
{
	int x;
	int y;
};

struct circle
{
	int x;
	int y;
	int radius;
};

struct Level
{
	int x;
	int y;
	int width;
	int height;
	int level;
};

/// <summary>
/// Level‰Šú‰»
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
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
	Point operator=(Point other) {
		this->x = other.x;
		this->y = other.y;
		return *this;
	}
	bool operator==(const Point &other) {
		if (this->x == other.x && this->y == other.y)return true;
		else return false;
	}

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

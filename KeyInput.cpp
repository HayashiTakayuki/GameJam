#include "KeyInput.h"
#include "DxLib.h"

KeyInput::KeyInput() : keys{ 0 }, oldkeys{ 0 }
{
}

void KeyInput::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldkeys[i] = keys[i];
	}

	GetHitKeyStateAll(keys);
}

bool KeyInput::IsKeyDown(char key)
{
	return keys[key];
}

bool KeyInput::IsKeyTrigger(char key)
{
	return keys[key] && !oldkeys[key];
}
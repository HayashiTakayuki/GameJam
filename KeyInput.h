#pragma once

/// <summary>
/// �L�[���͊Ǘ��N���X
/// </summary>
class KeyInput
{
private:
	char keys[256];
	char oldkeys[256];

public:
	KeyInput();
	void Update();

	bool IsKeyDown(char key);
	bool IsKeyTrigger(char key);
};
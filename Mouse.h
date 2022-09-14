#pragma once
#include"Struct.h"
class Mouse final
{
private:
	Mouse();
	~Mouse();

	Mouse(const Mouse& obj) = delete;
	Mouse& operator=(const Mouse& obj) = delete;
	Point mousePoint;
	bool click;
	bool oldclick;
	int sound_;

	bool markerClick = false;
	bool markerOldClick = false;
	//マーカ用
	static const int markerNum_ = 4;
	Point drawPos_[markerNum_];
	bool isDrawMarker_[markerNum_] = { false };
	int changeMarker_ = 0;
public:
	void MouseUpdate();
	Point GetMousePos();
	bool MouseInput(int b);
	bool MouseOutput(int b);
	bool MouseKeepput(int b);
	bool MouseCheckHitBox(Box box, Point mousePos);
	void SetSound(int sound) { sound_ = sound; }
	void DrawMarker(int *graphMarker);
	void Initialize();
	void Reset();
	
	static Mouse* GetInstance();

};

#pragma once
#include "ModeBase.h"
#include "ModeChanger.h"
#include "..\single\Key.h"
#include "..\single\Image.h"
#include <memory>
#include <stack>

class Mode : public  ModeChanger {
private:
	Parameter param;
	NextMode next; //次の画面
	bool blackout_flag; //暗転中か
	int blackout_time; //暗転時間
	bool erase; //今のモードを終了するか

	bool change; //ウィンドウを変えるか
	bool full_screen; //フルスクリーンにするか(falseならする)

	std::stack<std::shared_ptr<ModeBase>> scene_stack; //シーンのスタック

	void Blackout(); //暗転
	
public:
	Mode(); //コンストラクタ
	~Mode(); //デストラクタ
	void ChangeMode(NextMode nmode, bool erase_now = false, bool change_window = false, bool full = true); //次のモードにする(現在モードを消去するか、ウィンドウを変えるか、フルスクリーンにするか)
	void ChangeMode(NextMode nmode, Parameter &parameter, bool erase_now = false); //次のモードにする(現在モードを消去するか)
	void BackMode(); //前のモードに戻る
	void Update(); //更新
	void Draw(); //描画
};
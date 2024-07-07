#pragma once
#include "DxLib.h"
#include "TalkEvent.h"

using namespace std;

//コンストラクタ
TalkEvent::TalkEvent(EventManager* man, char* name, char *str, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	chara_name = (std::string)name;
	message = (std::string)str;
}

//デストラクタ
TalkEvent::~TalkEvent() {

}

//更新
void TalkEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {
	
	//決定が押されているなら終了
	if (Key::Get_Instance()->KeyCheckOnce(Jump)) {
		end_flag = true;
	}
}

//描画
void TalkEvent::Draw() {
	int font = manager->GetFont();
	int image = Image::Get_Instance()->GetEffectImage(12, 0);
	Display::Get_Instance()->FixedDraw(320.f, 80.f, LEFT, 0.f, image);
	DrawStringToHandle(16, 10, chara_name.c_str(), GetColor(236, 236, 236), font, GetColor(21, 169, 175));
	vector<string> v;
	string s;
	stringstream ss{ message };
	int i = 0;

	//:で改行する
	while (getline(ss, s, ':')) {
		v.push_back(s);
	}

	for (const string& s : v) {
		DrawStringToHandle(16, 40 + (32 * i), s.c_str(), GetColor(236, 236, 236), font, GetColor(21, 169, 175));
		i++;
	}
}
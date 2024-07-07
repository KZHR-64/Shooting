#pragma once
#include "DxLib.h"
#include "Player.h"
#include <math.h>

using namespace std;

Player::Player(){
	//Image::Get_Instance()->LoadPlayerImage(); //画像をロード

	body.def_angle = atan2f(-8.f, -4.f);
	body.def_distance = sqrtf((4.f * 4.f) + (8.f * 8.f));
	body.spin_angle = 0.f;
	body.spin_distance = 0.f;

	right_thigh.def_angle = atan2f(13.f, 6.f);
	right_thigh.def_distance = sqrtf((6.f * 6.f) + (13.f * 13.f));
	right_thigh.spin_angle = atan2f(8.f, 0.f);
	right_thigh.spin_distance = sqrtf(8.f * 8.f);

	right_leg.def_angle = atan2f(7.f, 0.f);
	right_leg.def_distance = sqrtf(7.f * 7.f);
	right_leg.spin_angle = atan2f(12.f, 0.f);
	right_leg.spin_distance = sqrtf(12.f * 12.f);

	left_thigh.def_angle = atan2f(13.f, -6.f);
	left_thigh.def_distance = sqrtf((6.f * 6.f) + (13.f * 13.f));
	left_thigh.spin_angle = atan2f(8.f, 0.f);
	left_thigh.spin_distance = sqrtf(8.f * 8.f);

	left_leg.def_angle = atan2f(7.f, 0.f);
	left_leg.def_distance = sqrtf(7.f * 7.f);
	left_leg.spin_angle = atan2f(12.f, 0.f);
	left_leg.spin_distance = sqrtf(12.f * 12.f);

	right_shoulder.def_angle = atan2f(-4.f, 12.f);
	right_shoulder.def_distance = sqrtf((12.f * 12.f) + (4.f * 4.f));
	right_shoulder.spin_angle = atan2f(0.f, 0.f);
	right_shoulder.spin_distance = sqrtf(0.f * 0.f);

	right_arm.def_angle = atan2f(11.f, 0.f);
	right_arm.def_distance = sqrtf((11.f * 11.f) + (0.f * 0.f));
	right_arm.spin_angle = atan2f(6.f, 14.f);
	right_arm.spin_distance = sqrtf((6.f * 6.f) + (14.f * 14.f));

	left_shoulder.def_angle = atan2f(-4.f, -12.f);
	left_shoulder.def_distance = sqrtf((12.f * 12.f) + (4.f * 4.f));
	left_shoulder.spin_angle = atan2f(0.f, 0.f);
	left_shoulder.spin_distance = sqrtf(0.f * 0.f);

	left_arm.def_angle = atan2f(11.f, 0.f);
	left_arm.def_distance = sqrtf(11.f * 11.f);
	left_arm.spin_angle = atan2f(12.f, 0.f);
	left_arm.spin_distance = sqrtf(12.f * 12.f);

	Reset(); //初期化
	hp = 6;
}

Player::~Player(){
	//Image::Get_Instance()->DeletePlayerImage();
}

//初期化
void Player::Reset(){
	if(hp <= 0) hp = 6; //HPを初期化
	sx = 0.f; //速度を初期化
	sy = 0.f; //速度を初期化
	angle = 0.f; //角度を初期化
	sangle = 0.f; //回転速度を初期化
	move_time = 0;
	move_type = Move_Stand; //静止状態に設定
	lr = RIGHT; //最初は右向き
	damaged = false; //ダメージを受けたフラグを初期化
	damage_time = false; //ダメージ動作の時間を初期化
	handle = 0; //表示する画像の番号を初期化
	inv_time = 0; //無敵時間を初期化
	draw_flag = true; //描画フラグを初期化

	body.angle = angle;
	right_thigh.angle = angle;
	right_leg.angle = angle;
	left_thigh.angle = angle;
	left_leg.angle = angle;
	right_shoulder.angle = angle;
	left_shoulder.angle = angle;
	right_arm.angle = 0.f;
	left_arm.angle = angle;

	SetParts();

	//catch_enemy = NULL;
	catch_effect = NULL;

	attack.flag = false; //攻撃フラグを初期化
	attack.push_time = 0; //押した時間を初期化

	catch_arm.flag = false; //つかみビーム発生フラグを初期化
	catch_arm.catch_flag = false; //つかんでいるフラグを初期化
	catch_arm.x = x; //座標を初期化
	catch_arm.y = false;
	
}

//入力履歴の確認(渡す列、探し始める点)
bool Player::RecordCheck(bool record[], int point){
	int i;
	for (i = point; i < RECORD; i++){
		//前に押されているか
		if (record[i]) return true; //押されていたらtrue
	}
	return false; //なかったらfalse
}

//自機の操作
void Player::Control() {
	float ini_sx = 0.f; //計算用の速度
	float ini_sy = 0.f;

	//左が押されていたら
	if (Key::Get_Instance()->KeyCheck(Left)){
		//攻撃状態でない場合
		if (!attack.flag) {
			//lr = LEFT; //向きを左に
			move_type = Move_Walk; //動作を歩行状態に
		}
		// 直前に左が押されていなかったら
		if (!commando[Left][0]){
			//その前に押されていた場合
			if (RecordCheck(commando[Left], 1)){
			}
		}
		ini_sx -= move_speed;
	}
	//右が押されていたら
	if (Key::Get_Instance()->KeyCheck(Right)){
		//攻撃状態でない場合
		if (!attack.flag) {
			//lr = RIGHT; //向きを右に
			move_type = Move_Walk; //動作を歩行状態に
		}
		// 直前に右が押されていなかったら
		if (!commando[Right][0]){
			//その前に押されていた場合
			if (RecordCheck(commando[Right], 1)){
			}
		}
		ini_sx += move_speed;
	}
	//上が押されていたら
	if (Key::Get_Instance()->KeyCheck(Up)) {
		// 直前に上が押されていなかったら
		if (!commando[Up][0]) {
			//その前に押されていた場合
			if (RecordCheck(commando[Up], 1)) {
			}
		}
		ini_sy -= move_speed;
	}
	//下が押されていたら
	if (Key::Get_Instance()->KeyCheck(Down)) {
		// 直前に上が押されていなかったら
		if (!commando[Down][0]) {
			//その前に押されていた場合
			if (RecordCheck(commando[Down], 1)) {
			}
		}
		ini_sy += move_speed;
	}

	if (ini_sx && ini_sy) {
		ini_sx /= sqrtf(2.f);
		ini_sy /= sqrtf(2.f);
	}

	sx = ini_sx;
	sy = ini_sy;

}

//ダメージ動作
void Player::DamageAction() {
	//ダメージを受けたばかりなら
	if (damage_time == DAMAGE_TIME_MAX) {
		sx = 0.0; //x速度を初期化
		sy = 0.0; //y速度を初期化
		move_type = Move_Stand; //動作を静止状態に
	}
	damage_time--; //動作時間が減少
	//動作時間が完了したら
	if (damage_time == 0) {
		damaged = false; //フラグをfalseに
	}
}

//移動
void Player::Move() {
	//ダメージを受けていたら
	if (damaged) {
		DamageAction(); //ダメージ動作
	}
	//受けていなかったら
	else {
		Control(); //通常の操作
	}
}

//位置の調節
void Player::AdjustPosition(std::shared_ptr<MapChipManager> map, bool event_flag) {
	//取得用クラス
	shared_ptr<AbstractMapChip> mapchip;

	bool left_hit = false; //左側が当たっているか
	bool right_hit = false; //右側が当たっているか
	bool top_hit = false; //上側が当たっているか
	bool bottom_hit = false; //下側が当たっているか

	//加速度
	float accel = 0.3f;

	float left = (float)Display::Get_Instance()->GetScrollX(); //画面左端
	float right = (float)(Display::Get_Instance()->GetScrollX() + WINDOW_X); //画面右端
	float top = (float)Display::Get_Instance()->GetScrollY(); //画面上
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + WINDOW_Y); //画面底

	//左右の判定から行う
	//現在の座標を設定
	fx = x;
	fy = y;

	//行く予定の座標を決定
	fx += sx + (float)map->GetScrollSpeedX();

	//イベント中でなければ画面内に収める
	if (!event_flag) {
		if (fx < left + hit_size) {
			fx = left + hit_size;
			left_hit = true; //左側が当たったことに
		}
		if (right - hit_size < fx) {
			fx = right - hit_size;
			right_hit = true; //右側が当たったことに
		}
	}

	//マップチップとの接触判定
	mapchip = map->HitCheckLeft(fx, fy, hit_size);
	while (mapchip != NULL) {
		left_hit = true; //左側が当たったことに
		fx = mapchip->GetX() + 4.f * mapchip->GetSizeX() + hit_size;
		sx = 0.f;
		mapchip = map->HitCheckLeft(fx, fy, hit_size);
	}
	mapchip = map->HitCheckRight(fx, fy, hit_size);
	while (mapchip != NULL) {
		right_hit = true; //右側が当たったことに
		fx = mapchip->GetX() - 4.f * mapchip->GetSizeX() - hit_size;
		sx = 0.f;
		mapchip = map->HitCheckRight(fx, fy, hit_size);
	}

	//両側が当たっていたら
	if (left_hit && right_hit) {
		hp = 0; //HPを0に
		damaged = true;
		//速度を初期化
		sx = 0.f;
		sy = 0.f;
		return;
	}

	//次に上下の判定
	//角度を設定
	angle += sangle;

	//行く予定の座標を決定
	fy += sy + (float)map->GetScrollSpeedY();

	//イベント中でなければ画面内に収める
	if (!event_flag) {
		if (fy < top + hit_size) {
			fy = top + hit_size;
			top_hit = true; //上側が当たったことに
		}
		if (bottom - hit_size < fy) {
			fy = bottom - hit_size;
			bottom_hit = true; //下側が当たったことに
		}
	}

	//マップチップとの接触判定
	//頭上
	mapchip = map->HitCheckTop(fx, fy, hit_size);
	while (mapchip != NULL) {
		top_hit = true; //上側が当たったことに
		fy = mapchip->GetY() + 8.f * mapchip->GetSizeY() + hit_size;
		sy = 0.f;
		mapchip = map->HitCheckTop(fx, fy, hit_size);
	}
	//足下
	mapchip = map->HitCheckBottom(fx, fy, hit_size);
	if (mapchip != NULL) bottom_hit = true; //下側が当たったことに
	while (mapchip != NULL) {
		fy = mapchip->GetY() - hit_size;
		sy = 0.f;
		mapchip = map->HitCheckBottom(fx, fy, hit_size);
	}

	//両側が当たっていたら
	if (top_hit && bottom_hit) {
		hp = 0; //HPを0に
		damaged = true;
		//速度を初期化
		sx = 0.f;
		sy = 0.f;
		return;
	}

	

	//次の座標を決定
	x = fx;
	y = fy;

	SetParts(); //パーツの配置
}

//攻撃
void Player::AttackCheck(shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect) {
	shared_ptr<AbstractBullet> bul;
	float shoot_angle = (lr ? 0.f : PI); //向きによって撃つ角度を決定
	//攻撃(決定)のボタンが押されていたら
	if (Key::Get_Instance()->KeyCheck(Jump) && !catch_arm.flag && !catch_arm.catch_flag) {
		attack.push_time++; //押している時間を増加
		//初めて攻撃ボタンを押したか押してしばらくしたら
		if (attack.push_time == 1 || attack.push_time % 6 == 1) {
			bul = bullet->SetBullet(0, x, y, 16.f, shoot_angle); //弾を発射
			//bul = bullet->SetBullet(1, x, y, 16.f, shoot_angle + (PI / 6.66f)); //弾を発射
			//bul = bullet->SetBullet(1, x, y, 16.f, shoot_angle - (PI / 6.66f)); //弾を発射
			Sound::Get_Instance()->PlaySoundEffect(7); //効果音を鳴らす
		}
	}
	else {
		attack.push_time = 0; //押している時間を初期化
	}

	//つかみ(戻る)のボタンが押されたら
	if (Key::Get_Instance()->KeyCheckOnce(Attack)) {
		//つかみビームが出ていないなら
		if (!catch_arm.flag && !catch_arm.catch_flag) {
			catch_arm.flag = true; //ビームを発生
			catch_arm.x = right_arm.x + 32.f; //座標を設定
			catch_arm.y = right_arm.y;
			catch_effect = effect->SetEffect(0, catch_arm.x, catch_arm.y); //エフェクトを発生
			Sound::Get_Instance()->PlaySoundEffect(8); //効果音を鳴らす
		}
		//敵をつかんでいたら
		if (catch_arm.catch_flag) {
			catch_arm.catch_flag = false; //つかみを解除
			//catch_enemy->SetSpinSpeed(PI / 30.f);
			//catch_enemy->SetXSpeed(16.f); //敵を投げる
			//catch_enemy.reset(); //権利を破棄
			bullet->SetBullet(1, catch_arm.x, catch_arm.y, 16.f, shoot_angle); //弾を発射
			Sound::Get_Instance()->PlaySoundEffect(5); //効果音を鳴らす
		}
	}

	//つかみ(戻る)のボタンが押されていたら
	if (Key::Get_Instance()->KeyCheck(Attack) && catch_arm.flag) {
		//敵をつかんでいなかったら
		if (!catch_arm.catch_flag) {
			catch_arm.x += 32.f; //ビームは直進
			catch_arm.y = right_arm.y;
		}
	}
	//放されたら
	else {
		catch_arm.flag = false; //ビームを消す
	}

	//敵をつかんでいたら
	if (catch_arm.catch_flag) {
		//自機よりビームが離れていたら
		if (64.f < fabsf(right_arm.x - catch_arm.x)) {
			catch_arm.x -= 32.f; //自機の方へ引っ張る
		}
		//近いなら
		if (fabsf(right_arm.x - catch_arm.x) < 64.f) {
			catch_arm.x = right_arm.x + 64.f; //座標を合わせる
		}
		catch_arm.y = right_arm.y;
		//つかんだ敵が生きているなら
		/*if (2 <= catch_enemy.use_count()) {
			catch_enemy->SetX(catch_arm.x); //座標をつかみビームに合わせる
			catch_enemy->SetY(catch_arm.y);
		}*/
	}

	//エフェクトがあれば
	if (2 <= catch_effect.use_count()) {
		catch_effect->SetX(catch_arm.x);
		catch_effect->SetY(catch_arm.y);
		catch_effect->SetBaseX(right_arm.x + 32.f);
	}

	//ビームが画面外に出たら
	if (Display::Get_Instance()->GetScrollX() + WINDOW_X + 64 < (int)catch_arm.x && !catch_arm.catch_flag) {
		catch_arm.flag = false; //ビームを消す
	}

	//ビームがなければ
	if (!catch_arm.flag && 1 <= catch_effect.use_count() && !catch_arm.catch_flag) {
		catch_effect->SetEndFlag(true); //エフェクトを消す
		catch_effect.reset(); //エフェクトの権利を破棄
	}

}

//表示する画像を決定
void Player::SetGraphic() {
	//ダメージを受けている場合
	if (0 < damage_time || hp <= 0) {
		handle = 21;
		return;
	}

	//撃ち状態の場合
	
}

//キーの履歴を更新
void Player::SetKeyRecord() {
	//入力履歴の更新
	for (int i = 0; i < BUTTON; i++){
		for (int j = RECORD - 1; j > 0; j--){
			commando[i][j] = commando[i][j - 1]; //前のキーを取得
		}
	}
	for (int i = 0; i < BUTTON; i++) commando[i][0] = Key::Get_Instance()->KeyCheck(i); //今押されているのを挿入

}

//パーツをそろえる
void Player::SetParts() {
	//進む向きによって体を傾ける
	if (sx < 0.f) {
		body.angle = PartsSpin(body.angle, -PI * 0.025f, 0.125f * PI, -0.125f * PI);
		right_thigh.angle = PartsSpin(right_thigh.angle, -PI * 0.025f, 0.5f * PI, -0.175f * PI);
		right_leg.angle = PartsSpin(right_leg.angle, -PI * 0.025f, 0.5f * PI, 0.f);
		left_thigh.angle = PartsSpin(left_thigh.angle, -PI * 0.025f, 0.5f * PI, -0.125f * PI);
		left_leg.angle = PartsSpin(left_leg.angle, -PI * 0.025f, 0.5f * PI, 0.f);
		right_shoulder.angle = PartsSpin(right_shoulder.angle, -PI * 0.025f, 0.5f * PI, 0.f);
		left_shoulder.angle = PartsSpin(left_shoulder.angle, -PI * 0.025f, 0.5f * PI, 0.f);
		left_arm.angle = PartsSpin(left_arm.angle, -PI * 0.025f, 0.f, -0.25f * PI);
	}
	else if (0.f < sx) {
		body.angle = PartsSpin(body.angle, PI * 0.025f, 0.125f * PI, -0.125f * PI);
		right_thigh.angle = PartsSpin(right_thigh.angle, -PI * 0.025f, 0.5f * PI, -0.25f * PI);
		right_leg.angle = PartsSpin(right_leg.angle, PI * 0.025f, 0.25f * PI, 0.f);
		left_thigh.angle = PartsSpin(left_thigh.angle, PI * 0.025f, 0.125f * PI, 0.f);
		left_leg.angle = PartsSpin(left_leg.angle, PI * 0.025f, 0.f, 0.f);
		right_shoulder.angle = PartsSpin(right_shoulder.angle, PI * 0.025f, 0.f, 0.f);
		left_shoulder.angle = PartsSpin(left_shoulder.angle, PI * 0.025f, 0.f, 0.f);
		left_arm.angle = PartsSpin(left_arm.angle, -PI * 0.025f, 0.f, -0.125f * PI);
	}
	else {
		body.angle *= 0.9f;
		right_thigh.angle *= 0.9f;
		right_leg.angle *= 0.9f;
		left_thigh.angle *= 0.9f;
		left_leg.angle *= 0.9f;
		right_shoulder.angle *= 0.9f;
		left_shoulder.angle *= 0.9f;
		left_arm.angle *= 0.9f;
	}

	float sum_angle = 0.f;

	//胴体
	body.total_angle = body.angle;
	sum_angle = body.def_angle + body.total_angle;
	body.x = x + (body.def_distance * cosf(sum_angle));
	body.y = y + (body.def_distance * sinf(sum_angle));

	//右足
	right_thigh.total_angle = body.total_angle + right_thigh.angle;
	sum_angle = right_thigh.def_angle + body.total_angle;
	right_thigh.x = body.x + (right_thigh.def_distance * cosf(sum_angle)) + (right_thigh.spin_distance * cosf(right_thigh.spin_angle + right_thigh.total_angle));
	right_thigh.y = body.y + (right_thigh.def_distance * sinf(sum_angle)) + (right_thigh.spin_distance * sinf(right_thigh.spin_angle + right_thigh.total_angle));
	right_leg.total_angle = right_thigh.total_angle + right_leg.angle;
	sum_angle = right_leg.def_angle + right_thigh.total_angle;
	right_leg.x = right_thigh.x + (right_leg.def_distance * cosf(sum_angle)) + (right_leg.spin_distance * cosf(right_leg.spin_angle + right_leg.total_angle));
	right_leg.y = right_thigh.y + (right_leg.def_distance * sinf(sum_angle)) + (right_leg.spin_distance * sinf(right_leg.spin_angle + right_leg.total_angle));

	//左足
	left_thigh.total_angle = body.total_angle + left_thigh.angle;
	sum_angle = left_thigh.def_angle + body.angle;
	left_thigh.x = body.x + (left_thigh.def_distance * cosf(sum_angle)) + (left_thigh.spin_distance * cosf(left_thigh.spin_angle + left_thigh.total_angle));
	left_thigh.y = body.y + (left_thigh.def_distance * sinf(sum_angle)) + (left_thigh.spin_distance * sinf(left_thigh.spin_angle + left_thigh.total_angle));
	left_leg.total_angle = left_thigh.total_angle + left_leg.angle;
	sum_angle = left_leg.def_angle + left_thigh.total_angle;
	left_leg.x = left_thigh.x + (left_leg.def_distance * cosf(sum_angle)) + (left_leg.spin_distance * cosf(left_leg.spin_angle + left_leg.total_angle));
	left_leg.y = left_thigh.y + (left_leg.def_distance * sinf(sum_angle)) + (left_leg.spin_distance * sinf(left_leg.spin_angle + left_leg.total_angle));

	//右腕
	right_shoulder.total_angle = body.total_angle + right_shoulder.angle;
	sum_angle = right_shoulder.def_angle + body.total_angle;
	right_shoulder.x = body.x + (right_shoulder.def_distance * cosf(sum_angle)) + (right_shoulder.spin_distance * cosf(right_shoulder.spin_angle + right_shoulder.total_angle));
	right_shoulder.y = body.y + (right_shoulder.def_distance * sinf(sum_angle)) + (right_shoulder.spin_distance * sinf(right_shoulder.spin_angle + right_shoulder.total_angle));
	right_arm.total_angle = right_arm.angle;
	sum_angle = right_arm.def_angle + right_shoulder.total_angle;
	right_arm.x = right_shoulder.x + (right_arm.def_distance * cosf(sum_angle)) + (right_arm.spin_distance * cosf(right_arm.spin_angle + right_arm.total_angle));
	right_arm.y = right_shoulder.y + (right_arm.def_distance * sinf(sum_angle)) + (right_arm.spin_distance * sinf(right_arm.spin_angle + right_arm.total_angle));

	//左腕
	left_shoulder.total_angle = body.total_angle + left_shoulder.angle;
	sum_angle = left_shoulder.def_angle + body.total_angle;
	left_shoulder.x = body.x + (left_shoulder.def_distance * cosf(sum_angle)) + (left_shoulder.spin_distance * cosf(left_shoulder.spin_angle + left_shoulder.total_angle));
	left_shoulder.y = body.y + (left_shoulder.def_distance * sinf(sum_angle)) + (left_shoulder.spin_distance * sinf(left_shoulder.spin_angle + left_shoulder.total_angle));
	left_arm.total_angle = left_shoulder.total_angle + left_arm.angle;
	sum_angle = left_arm.def_angle + left_shoulder.total_angle;
	left_arm.x = left_shoulder.x + (left_arm.def_distance * cosf(sum_angle)) + (left_arm.spin_distance * cosf(left_arm.spin_angle + left_arm.total_angle));
	left_arm.y = left_shoulder.y + (left_arm.def_distance * sinf(sum_angle)) + (left_arm.spin_distance * sinf(left_arm.spin_angle + left_arm.total_angle));
}

//パーツを回転させる
float Player::PartsSpin(float parts_angle, float spin_speed, float spin_max, float spin_min) {
	float set_angle = parts_angle;

	set_angle += spin_speed; //パーツを回転させる

	//上限に達したら
	if (spin_max < set_angle) {
		set_angle = spin_max;
	}
	//下限に達したら
	if (set_angle < spin_min) {
		set_angle = spin_min;
	}

	return set_angle;
}

//吸い込めるか確認
void Player::InhaleCheck(shared_ptr<MapChipManager> map, shared_ptr<EnemyManager> enemy) {
	if (!catch_arm.flag || catch_arm.catch_flag) return; //つかみ状態でないかすでにつかんでいるなら戻る

	std::shared_ptr<AbstractEnemy> catch_enemy = enemy->InhaleCheck(catch_arm.x, catch_arm.y, 32.f, false); //つかんだ敵

	//敵をつかんだら
	if (catch_enemy != NULL) {
		catch_arm.catch_flag = true; //つかみフラグをtrueに
		//catch_enemy->SetInhaledFlag(true); //敵をつかみ状態に
		//catch_enemy->SetHitFlag(false); //敵の当たり判定を消す
		catch_enemy->SetEndFlag(true); //敵を消す
		Sound::Get_Instance()->PlaySoundEffect(6); //効果音を鳴らす
	}
}

//敵に当たっているか
void Player::HitCheckEnemy(shared_ptr<EnemyManager> enemy) {
	if (0 < inv_time) return; //無敵時間中なら終了

	//敵に当たっていたら
	if (enemy->HitCheckChara(x, y, hit_size)) {
		hp--; //HPを減少
		damaged = true; //ダメージ状態
		damage_time = DAMAGE_TIME_MAX; //ダメージ時間を設定
		inv_time = DAMAGE_INV_TIME; //無敵時間を設定
		Sound::Get_Instance()->PlaySoundEffect(9); //効果音を鳴らす
	}
}

//弾に当たっているか
void Player::HitCheckBullet(shared_ptr<BulletManager> bullet) {
	if (0 < inv_time) return; //無敵時間中なら終了
	
	//弾に当たっていたら
	if (0 < bullet->HitCheckChara(x, y, hit_size, true, false)) {
		hp--; //HPを減少
		damaged = true; //ダメージ状態
		damage_time = DAMAGE_TIME_MAX; //ダメージ時間を設定
		inv_time = DAMAGE_INV_TIME; //無敵時間を設定
		Sound::Get_Instance()->PlaySoundEffect(9); //効果音を鳴らす
	}
}

//HPを返す
int Player::GetHp() {
	return hp;
}

//x座標を返す
float Player::GetX() {
	return x;
}

//x座標を設定
void Player::SetX(float px) {
	x = px;
}

//y座標を返す
float Player::GetY() {
	return y;
}

//y座標を設定
void Player::SetY(float py) {
	y = py;
}

//横の速度を返す
float Player::GetXSpeed() {
	return sx;
}

//横の速度を設定
void Player::SetXSpeed(float px) {
	sx = px;
}

//縦の速度を返す
float Player::GetYSpeed() {
	return sy;
}

//縦の速度を設定
void Player::SetYSpeed(float py) {
	sy = py;
}

//描画するか設定
void Player::SetDrawFlag(bool flag) {
	draw_flag = flag;
}

//更新
void Player::Update(){
	Move();
	SetKeyRecord(); //キーの履歴を更新
	
	//無敵時間中なら
	if (0 < inv_time) {
		inv_time--; //無敵時間を減少
	}
}

//描画
void Player::Draw(){
	int image = Image::Get_Instance()->GetCharaImage(0, 0); //自機の画像を取得
	int image2 = Image::Get_Instance()->GetCharaImage(1, 0); //自機の画像を取得
	int image3 = Image::Get_Instance()->GetCharaImage(2, 0); //自機の画像を取得
	int image4 = Image::Get_Instance()->GetCharaImage(3, 0); //自機の画像を取得
	int image5 = Image::Get_Instance()->GetCharaImage(4, 0); //自機の画像を取得
	int image6 = Image::Get_Instance()->GetCharaImage(5, 0); //自機の画像を取得
	int image7 = Image::Get_Instance()->GetCharaImage(6, 0); //自機の画像を取得

	//HP周りの画像を取得
	int life = Image::Get_Instance()->GetEffectImage(9, 0);
	int life_bar = Image::Get_Instance()->GetEffectImage(8, 0);

	int trance = 255; //透明度

	//HP周りの描画
	Display::Get_Instance()->FixedDraw(64.f, 448.f, LEFT, 0.f, life_bar);
	for (int i = 0; i < hp; i++) {
		Display::Get_Instance()->FixedDraw(34.f + (12.f * i), 448.f, LEFT, 0.f, life);
	}

	//無敵時間中は点滅する
	if (0 < inv_time) {
		if (inv_time % 10 < 5) {
			trance = 96;
		}
		else {
			trance = 192;
		}
	}

	//自機の描画
	if (draw_flag) {

		Display::Get_Instance()->Draw(right_arm.x, right_arm.y, lr, right_arm.total_angle, image7, DX_BLENDMODE_ALPHA, trance); //右腕を描画
		Display::Get_Instance()->Draw(right_shoulder.x, right_shoulder.y, lr, right_shoulder.total_angle, image5, DX_BLENDMODE_ALPHA, trance);
		Display::Get_Instance()->Draw(right_thigh.x, right_thigh.y, lr, right_thigh.total_angle, image2, DX_BLENDMODE_ALPHA, trance); //右足を描画
		Display::Get_Instance()->Draw(right_leg.x, right_leg.y, lr, right_leg.total_angle, image3, DX_BLENDMODE_ALPHA, trance);
		Display::Get_Instance()->Draw(body.x, body.y, lr, body.total_angle, image, DX_BLENDMODE_ALPHA, trance); //自機を描画
		Display::Get_Instance()->Draw(left_thigh.x, left_thigh.y, lr, left_thigh.total_angle, image2, DX_BLENDMODE_ALPHA, trance); //左足を描画
		Display::Get_Instance()->Draw(left_leg.x, left_leg.y, lr, left_leg.total_angle, image3, DX_BLENDMODE_ALPHA, trance);
		Display::Get_Instance()->Draw(left_shoulder.x, left_shoulder.y, lr, left_shoulder.total_angle, image4, DX_BLENDMODE_ALPHA, trance); //左腕を描画
		Display::Get_Instance()->Draw(left_arm.x, left_arm.y, lr, left_arm.total_angle, image6, DX_BLENDMODE_ALPHA, trance);

		Display::Get_Instance()->HitDraw(x, y, hit_size);
	}

	//DrawString(0, 40, "プレイヤー", GetColor(255, 255, 255));
	//DrawFormatString(0, 100, GetColor(0, 0, 255), "%d", Display::Get_Instance()->GetScrollXMin());
	//DrawFormatString(0, 128, GetColor(0, 0, 255), "%d %d", catch_effect.use_count(), catch_arm.flag);
	
}

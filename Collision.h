#pragma once
//#include "Src/Application/TextureManager.h"
//using namespace TextureManagement;
#include "Src/Application/Calculation/Calculation.h"



class Collision : public Calculation
{
public:
	Collision() {};
	~Collision() {};

	//現在座標判定を使う時の流れ
	// 移動処理 → 座標更新  →  現在座標判定 → 最終更新
	//(m_move+=5)(m_pos+=m_move)(m_move=修正値) (m_pos+=m_move)

	//未来座標判定を使う時の流れ
	// 移動処理 → 未来座標判定 → 座標更新
	//(m_move+=5)(m_move+=修正値)(m_pos+=m_move)


	///////////////////////////////////////////////////////////////
	// 円と円の当たり判定
	///////////////////////////////////////////////////////////////

	//円と円の当たり判定（現在/未来）
	//　当たってるか当たってないかを返す
	// a_xPos		...座標1
	// a_xRadius	...半径1(画像サイズ * 拡大縮小率)
	// a_yPos		...座標2
	// a_yRadius	...半径2(画像サイズ * 拡大縮小率)
	virtual bool CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2 a_yPos, float a_yRadius)final;

	//円と円の当たり判定（現在/未来）
	// !! ぶつかってるときだけ !!
	//　跳ね返し処理する場合の跳ね返し値を返す
	// a_xPos		...動く円の座標
	// a_xRadius	...動く円の半径(画像サイズ * 拡大縮小率)
	// a_yPos		...固定円の座標
	// a_yRadius	...固定円の半径(画像サイズ * 拡大縮小率)
	virtual Math::Vector2 ModifyCircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2 a_yPos, float a_yRadius)final;

	//円と円の当たり判定（現在）円が一つ動く
	//　当たってるか当たってないかを返す
	// a_xPos		...座標1
	// a_xRadius	...半径1(画像サイズ * 拡大縮小率)
	// a_xMove		...押し戻す値を入れる 当たってないときは0,0を代入 nullptrのときは当たってるかどうかだけ返す
	// a_yPos		...座標2
	// a_yRadius	...半径2(画像サイズ * 拡大縮小率)
	virtual bool CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius)final;

	//円と円の当たり判定（現在）円二つとも動く
	//　当たってるか当たってないかを返す
	// a_xPos		...座標1
	// a_xRadius	...半径1(画像サイズ * 拡大縮小率)
	// a_xMove		...押し戻す値を入れる 当たってないときは0,0を代入 nullptrのときは当たってるかどうかだけ返す
	// a_yPos		...座標2
	// a_yRadius	...半径2(画像サイズ * 拡大縮小率)
	// a_yMove		...押し戻す値を入れる 当たってないときは0,0を代入 nullptrのときは当たってるかどうかだけ返す
	virtual bool CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius, Math::Vector2* a_yMove)final;

	//円と円の当たり判定（未来）押し戻し処理あり
	//　当たってるか当たってないかを返す
	// a_xPos		...座標1
	// a_xRadius	...半径1(画像サイズ * 拡大縮小率)
	// a_xMove		...移動量1 nullptrのとき現在座標で判定する&押し戻し処理なし
	// a_yPos		...座標2
	// a_yRadius	...半径2(画像サイズ * 拡大縮小率)
	// a_yMove		...移動量2 nullptrのとき現在座標で判定する&押し戻し処理なし
	virtual bool NextCircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius, Math::Vector2* a_yMovebool ,bool b_xMove = true, bool b_yMove = true)final;


	///////////////////////////////////////////////////////////////
	// 円と線分の当たり判定
	///////////////////////////////////////////////////////////////

	// 円と線分の当たり判定（現在/未来）
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_startPoint		...線分の始点座標
	// a_endPoint		...線分の終点座標
	virtual bool CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)final;

	// 円と線分の当たり判定（現在）円だけ動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_circleMove		...円の移動量
	// a_startPoint		...線分の始点座標
	// a_endPoint		...線分の終点座標
	virtual bool CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)final;

	// 円と線分の当たり判定
	// !! ぶつかってるときだけ !!
	//　円が跳ね返し処理する場合の跳ね返し値を返す
	// a_circlePos		...動く円の座標
	// a_circleRadius	...動く円の半径(画像サイズ * 拡大縮小率)
	// a_startPoint		...線分の始点座標
	// a_endPoint		...線分の終点座標
	virtual Math::Vector2 ModifyCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)final;

	// 円と線分の当たり判定（未来）円だけ動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_circleMove		...円の移動量 nullptrのとき現在座標で判定する
	// a_startPoint		...線分の始点座標
	// a_endPoint		...線分の終点座標
	virtual bool NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)final;

	// 円と線分の当たり判定（現在）線分(一つの点は固定)も円も動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_circleMove		...円の移動量 当たってないときは0,0を代入 nullptrのときは当たってるかどうかだけ返す
	// a_startPoint		...線分の始点座標
	// a_startMove		...線分の始点の移動量 当たってないときは0,0を代入 nullptrのときは当たってるかどうかだけ返す
	// a_endPoint		...線分の終点座標
	// changeLength		...円の動きによって線分の長さ変えれるようにするか
	virtual bool CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint,bool a_changeLength = false)final;

	// 円と線分の当たり判定（現在）線分も円も動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_circleMove		...円の移動量 当たってないときは0,0を代入 nullptrのときは当たってるかどうかだけ返す
	// a_startPoint		...線分の始点座標
	// a_startMove		...線分の始点の移動量 当たってないときは0,0を代入 nullptrのときは当たってるかどうかだけ返す
	// a_endPoint		...線分の終点座標
	// a_endMove		...線分の始点の移動量 当たってないときは0,0を代入 nullptrのときは当たってるかどうかだけ返す
	// a_changeLength		...円の動きによって線分の長さ変えれるようにするか
	virtual bool CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, Math::Vector2* a_endMove, bool a_changeLength = false)final;

	// 円と線分の当たり判定（未来）線分(一つの点は固定)も円も動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_circleMove		...円の移動量 nullptrのとき現在座標で判定する
	// a_startPoint		...線分の始点座標
	// a_startMove		...線分の始点の移動量 nullptrのとき始点は動かず未来座標判定
	// a_endPoint		...線分の終点座標
	// a_changeLength		...円の動きによって線分の長さ変えれるようにするか
	virtual bool NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, bool a_changeLength = false)final;

	// 円と線分の当たり判定（未来）線分も円も動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_circleMove		...円の移動量 nullptrのとき現在座標で判定する
	// a_startPoint		...線分の始点座標
	// a_startMove		...線分の始点の移動量 nullptrのとき始点は動かず未来座標判定
	// a_endPoint		...線分の終点座標
	// a_endMove		...線分の始点の移動量 nullptrのとき終点は動かず未来座標判定
	// a_changeLength	...円の動きによって線分の長さ変えれるようにするか
	virtual bool NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, Math::Vector2* a_endMove, bool a_changeLength = false)final;


	///////////////////////////////////////////////////////////////
	// 円と四角の当たり判定
	///////////////////////////////////////////////////////////////

	// 円と四角の当たり判定（現在/未来）
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_rectPos		...四角の座標
	// a_rectRadius		...四角の半径(画像サイズ * 拡大縮小率) 
	virtual bool CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius)final;
	
	// 円と四角の当たり判定（現在）円だけ動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_circleMove		...円の移動量 当たってないときは0,0を代入 nullptrのときは当たってるかどうかだけ返す
	// a_rectPos		...四角の座標
	// a_rectRadius		...四角の半径(画像サイズ * 拡大縮小率) 
	virtual bool CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius)final;

	// 円と四角の当たり判定（未来）円だけ動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_circleMove		...円の移動量 当たってないときは0,0を代入 nullptrのときは当たってるかどうかだけ返す
	// a_rectPos		...四角の座標
	// a_rectRadius		...四角の半径(画像サイズ * 拡大縮小率) 
	virtual bool NextCircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius)final;

	// 円と四角の当たり判定（現在）四角だけ動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_rectPos		...四角の座標
	// a_rectRadius		...四角の半径(画像サイズ * 拡大縮小率) 
	// a_rectMove		...四角の移動量 当たってないときは0,0を代入 nullptrのときは当たってるかどうかだけ返す
	virtual bool CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)final;

	// 円と四角の当たり判定（現在）円も四角も動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_circleMove		...円の移動量 当たってないときは0,0を代入 nullptrのときは四角だけがうごく
	// a_rectPos		...四角の座標
	// a_rectRadius		...四角の半径(画像サイズ * 拡大縮小率) 
	// a_rectMove		...四角の移動量 当たってないときは0,0を代入 nullptrのときは円だけが動く
	virtual bool CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)final;

	// 円と四角の当たり判定（未来）四角だけ動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_rectPos		...四角の座標
	// a_rectRadius		...四角の半径(画像サイズ * 拡大縮小率) 
	// a_rectMove		...四角の移動量 nullptrのときは当たってるかどうかだけ返す
	virtual bool NextCircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)final;

	// 円と四角の当たり判定（未来）円も四角も動く
	//　当たってるか当たってないかを返す
	// a_circlePos		...円の座標
	// a_circleRadius	...円の半径(画像サイズ * 拡大縮小率)
	// a_circleMove		...円の移動量 nullptrのときは四角だけがうごく（未来）
	// a_rectPos		...四角の座標
	// a_rectRadius		...四角の半径(画像サイズ * 拡大縮小率) 
	// a_rectMove		...四角の移動量 nullptrのときは円だけが動く（未来）
	virtual bool NextCircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)final;

	///////////////////////////////////////////////////////////////
	// その他
	///////////////////////////////////////////////////////////////


private:
	//定数にセットしたかどうかフラグ


	//おじょうくんとこからもらってくるor定数マネージャーからもらう
	//const float increaseRatio = 0.5f;
	//const float split = 5.0f;
	//const int SCREEN_Y = 720;
	//const int SCREEN_HALF_Y = SCREEN_Y / 2;
};


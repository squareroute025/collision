#include "Collision.h"

//当たってるかどうかだけわかる
bool Collision::CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2 a_yPos, float a_yRadius)
{
	bool result = false;

	//二点のベクトルを求める
	Math::Vector2 v_x_y = a_yPos - a_xPos;

	//当たってる場合の距離（条件となる距離）
	float checkDistance = (a_xRadius + a_yRadius) * (a_xRadius + a_yRadius);

	//判定する
	if (v_x_y.LengthSquared() < checkDistance) { result = true; }

	return result;
}

//押し戻し処理
Math::Vector2 Collision::ModifyCircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2 a_yPos, float a_yRadius)
{
	Math::Vector2 result = { 0.0f,0.0f };

	//押し戻し処理
	Math::Vector2 v_y_x = a_xPos - a_yPos;										//yからxに向かうベクトル
	float checkDistance = (a_xRadius + a_yRadius) * (a_xRadius + a_yRadius);
	float moveDistance = sqrt(checkDistance) - sqrt(v_y_x.LengthSquared());		//かさなってる距離求める
	v_y_x.Normalize();					//単位ベクトルにする（方向だけを持つベクトル）
	result = moveDistance * v_y_x;	//跳ね返す値代入

	return result;
}

//当たってたら押し返し分をmoveにいれる
bool Collision::CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius)
{
	bool result = false;

	//当たり判定する
	result = CircleAndCircle(a_xPos, a_xRadius, a_yPos, a_yRadius);

	//a_moveがnullptrの時　当たってるかどうかだけを返す
	if (a_xMove == nullptr) { return result; }

	//当たってない場合　移動量初期化して当たってるか返す
	if (!result)
	{
		*a_xMove = { 0.0f,0.0f };
		return result;
	}

	//押し戻し処理
	*a_xMove = ModifyCircleAndCircle(a_xPos, a_xRadius, a_yPos, a_yRadius);

	return result;
}

//当たってたら押し返し分二つに割ってをmoveにいれる
bool Collision::CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius, Math::Vector2* a_yMove)
{
	bool result = false;

	//当たり判定する
	result = CircleAndCircle(a_xPos, a_xRadius, a_yPos, a_yRadius);

	//どちらもnullptrの時　当たってるかどうかだけを返す
	if (a_xMove == nullptr && a_yMove == nullptr) { return result; }

	//当たってない場合　移動量初期化して当たってるか返す
	if (!result)
	{
		*a_xMove = { 0.0f,0.0f };
		*a_yMove = { 0.0f,0.0f };
		return result;
	}

	//押し戻し処理
	Math::Vector2 modify = ModifyCircleAndCircle(a_xPos, a_xRadius, a_yPos, a_yRadius);

	//どちらもnullptrじゃなければ
	if (a_xMove != nullptr && a_yMove != nullptr)
	{
		*a_xMove = modify * 0.5f;	//跳ね返す値代入
		*a_yMove = modify * -0.5f;	//跳ね返す値代入
	}
	else if (a_xMove != nullptr)
	{
		*a_xMove = modify;	//跳ね返す値代入
	}
	else if (a_yMove != nullptr)
	{
		*a_yMove = -modify;	//跳ね返す値代入
	}

	return result;
}

//未来座標で判定する　
bool Collision::NextCircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius, Math::Vector2* a_yMove, bool b_xMove, bool b_yMove)
{
	bool result = false;

	//どちらもnullptrの時　現在判定で当たってるかどうかだけを返す
	if (a_xMove == nullptr && a_yMove == nullptr)
	{
		result = CircleAndCircle(a_xPos, a_xRadius, a_yPos, a_yRadius);
		return result;
	}
	//どちらかだけがnullptrの時
	else if (a_xMove == nullptr || a_yMove == nullptr)
	{
		if (a_xMove == nullptr)
		{
			//当たり判定する
			if (CircleAndCircle(a_xPos, a_xRadius, a_yPos + *a_yMove, a_yRadius))
			{
				result = true;

				//押し戻し処理
				*a_yMove += ModifyCircleAndCircle(a_yPos + *a_yMove, a_yRadius, a_xPos, a_xRadius);	//移動量補正
			}
			return result;
		}
		if (a_yMove == nullptr)
		{
			//当たり判定する		
			if (CircleAndCircle(a_xPos + *a_xMove, a_xRadius, a_yPos, a_yRadius))
			{
				result = true;

				//押し戻し処理
				*a_xMove += ModifyCircleAndCircle(a_xPos + *a_xMove, a_xRadius, a_yPos, a_yRadius);	//移動量補正
			}
			return result;
		}
	}
	//どっちもアドレスが入っているとき
	else
	{
		//当たり判定する
		if (CircleAndCircle(a_xPos + *a_xMove, a_xRadius, a_yPos + *a_yMove, a_yRadius))
		{
			result = true;

			//押し戻し処理
			Math::Vector2 modify = ModifyCircleAndCircle(a_xPos + *a_xMove, a_xRadius, a_yPos + *a_yMove, a_yRadius);
			if (b_xMove && b_yMove)
			{
				*a_xMove += modify * 0.5f;	//移動量補正
				*a_yMove += modify * -0.5f;	//移動量補正
			}
			else if (b_xMove)
			{
				*a_xMove += modify;	//移動量補正
			}
			else if (b_yMove)
			{
				*a_yMove += -1 * modify;	//移動量補正
			}

		}
		return result;
	}

	return result;
}

//円と線分の当たり判定
bool Collision::CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)
{
	bool result = false;

	//ベクトルの宣言
	Math::Vector2 v_s_e = a_endPoint - a_startPoint;
	Math::Vector2 v_s_c = a_circlePos - a_startPoint;
	Math::Vector2 v_e_c = a_circlePos - a_endPoint;

	//線分と円の距離
	if (abs(Cross(v_s_c, v_s_e) / sqrt(v_s_e.LengthSquared())) <= a_circleRadius)
	{
		//線分の間に円がある
		if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
		{
			result = true;
		}
		//始点・終点の近く
		else if (v_s_c.LengthSquared() <= a_circleRadius * a_circleRadius || v_e_c.LengthSquared() <= a_circleRadius * a_circleRadius)
		{
			result = true;
		}
	}

	return result;
}

//円だけ動く
bool Collision::CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)
{
	bool result = false;

	//nullptrの場合　判定だけ返す
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}

	//当たってるかどうか
	if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
	else { result = false; *a_circleMove = { 0.0f,0.0f }; return result; }

	//跳ね返し値代入
	*a_circleMove = ModifyCircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint);
	return result;
}

//押し戻し処理　円が動く
Math::Vector2 Collision::ModifyCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)
{
	Math::Vector2 result = { 0.0f,0.0f };

	//ベクトルの宣言
	Math::Vector2 v_s_e = a_endPoint - a_startPoint;
	Math::Vector2 nv_s_e = { -v_s_e.y,v_s_e.x };	//法線ベクトル 始点中心に90度
	Math::Vector2 v_s_c = a_circlePos - a_startPoint;
	Math::Vector2 v_e_c = a_circlePos - a_endPoint;

	//線分の間に円がある
	if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
	{
		float distance = abs(Cross(v_s_c, v_s_e)) / sqrt(v_s_e.LengthSquared());	//円の中心と線分の距離
		float moveDistance = a_circleRadius - distance;								//円と線分の距離
		nv_s_e.Normalize();															//単位ベクトルにする（方向だけを持つベクトル）

		//線分と円の距離
		if (Cross(v_s_c, v_s_e) < 0)
		{
			result = moveDistance * nv_s_e;		//跳ね返す値代入
			return result;
		}
		else
		{
			result = moveDistance * nv_s_e * -1;//跳ね返す値代入
			return result;
		}
	}

	Math::Vector2 addResult = { 0.0f,0.0f };
	//円と始点の跳ね返し処理
	if (CircleAndPoint(a_circlePos, a_circleRadius, &addResult, a_startPoint))
	{
		result += addResult;
		return result;
	}

	//円と始点の跳ね返し処理
	if (CircleAndPoint(a_circlePos, a_circleRadius, &addResult, a_endPoint))
	{
		result += addResult;
		return result;
	}

	return result;
}

//円だけ動く
bool Collision::NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)
{
	bool result = false;

	//nullptrの場合　判定だけ返す
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}

	//当たってるかどうか
	if (CircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
	else { result = false; return result; }

	//押し戻し処理
	*a_circleMove += ModifyCircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, a_startPoint, a_endPoint);
	return result;
}

//円と線分の一点（始点/終点）が動く
bool Collision::CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, bool a_changeLength)
{
	bool result = false;

	//nullptrの場合　判定だけ返す
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}
	//線分の移動量がnullptrの場合
	else if (a_startMove == nullptr)
	{
		result = CircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, a_startPoint, a_endPoint);
		return result;
	}

	//当たってるかどうか
	if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
	else { result = false; *a_circleMove = { 0.0f,0.0f }; return result; }

	//ベクトルの宣言
	Math::Vector2 v_s_e = a_endPoint - a_startPoint;
	Math::Vector2 nv_s_e = { -v_s_e.y,v_s_e.x };	//法線ベクトル 始点中心に90度
	Math::Vector2 v_s_c = a_circlePos - a_startPoint;
	Math::Vector2 v_e_c = a_circlePos - a_endPoint;

	//線分の間に円がある
	if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
	{
		float distance = abs(Cross(v_s_c, v_s_e)) / sqrt(v_s_e.LengthSquared());	//円の中心と線分の距離
		float moveDistance = a_circleRadius - distance;								//円と線分の距離
		nv_s_e.Normalize();															//単位ベクトルにする（方向だけを持つベクトル）

		//比を求める　→　てこの原理ぽく値代入
		float startRatio = abs(v_s_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());
		float endRatio = abs(v_e_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());

		//線分と円の距離
		if (Cross(v_s_c, v_s_e) < 0)
		{
			*a_circleMove = moveDistance * startRatio * nv_s_e;		//跳ね返す値代入
			*a_startMove = moveDistance * endRatio * nv_s_e * -1;		//跳ね返す値代入
			return result;
		}
		else
		{
			*a_circleMove = moveDistance * startRatio * nv_s_e * -1;		//跳ね返す値代入
			*a_startMove = moveDistance * endRatio * nv_s_e;		//跳ね返す値代入
			return result;
		}
	}

	//円と始点の跳ね返し処理
	if (v_s_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_s_c.LengthSquared());	//円と線分の距離
		v_s_c.Normalize();													//単位ベクトルにする（方向だけを持つベクトル）
		if (a_changeLength)
		{
			*a_circleMove = moveDistance / 2.0f * v_s_c;					//跳ね返す値代入
			*a_startMove = moveDistance / 2.0f * v_s_c * -1;				//跳ね返す値代入
		}
		else { *a_circleMove = moveDistance * v_s_c; }						//跳ね返す値代入
		return result;
	}

	//円と終点の跳ね返し処理
	if (v_e_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_e_c.LengthSquared());	//円と線分の距離
		v_e_c.Normalize();													//単位ベクトルにする（方向だけを持つベクトル）
		*a_circleMove = moveDistance * v_e_c;								//跳ね返す値代入
		return result;
	}

	return result;
}

//円と線分どちらも動く
bool Collision::CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, Math::Vector2* a_endMove, bool a_changeLength)
{
	bool result = false;

	//nullptrの場合　判定だけ返す
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}
	//線分の移動量がどちらもnullptrの場合
	else if (a_startMove == nullptr && a_endMove == nullptr)
	{
		result = CircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, a_startPoint, a_endPoint);
		return result;
	}
	else if (a_startMove == nullptr)
	{
		result = CircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, a_startPoint, a_startMove, a_endPoint);
		return result;
	}
	else if (a_endMove == nullptr)
	{
		result = CircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, a_endPoint, a_endMove, a_startPoint);
		return result;
	}

	//当たってるかどうか
	if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
	else { result = false; *a_circleMove = { 0.0f,0.0f }; return result; }

	//ベクトルの宣言
	Math::Vector2 v_s_e = a_endPoint - a_startPoint;
	Math::Vector2 nv_s_e = { -v_s_e.y,v_s_e.x };	//法線ベクトル 始点中心に90度
	Math::Vector2 v_s_c = a_circlePos - a_startPoint;
	Math::Vector2 v_e_c = a_circlePos - a_endPoint;

	//線分の間に円がある
	if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
	{
		float distance = abs(Cross(v_s_c, v_s_e)) / sqrt(v_s_e.LengthSquared());	//円の中心と線分の距離
		float moveDistance = a_circleRadius - distance;								//円と線分の距離
		nv_s_e.Normalize();															//単位ベクトルにする（方向だけを持つベクトル）

		//比を求める　→　てこの原理ぽく値代入
		float startRatio = abs(v_s_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());
		float endRatio = abs(v_e_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());

		moveDistance = moveDistance / 2.0f;

		//線分と円の距離
		if (Cross(v_s_c, v_s_e) < 0)
		{
			*a_circleMove = moveDistance * nv_s_e;							//跳ね返す値代入
			*a_endMove = moveDistance * startRatio * nv_s_e * -1;
			*a_startMove = moveDistance * endRatio * nv_s_e * -1;
			return result;
		}
		else
		{
			*a_circleMove = moveDistance * nv_s_e * -1;
			*a_endMove = moveDistance * startRatio * nv_s_e;
			*a_startMove = moveDistance * endRatio * nv_s_e;
			return result;
		}
	}



	//円と始点の跳ね返し処理
	if (v_s_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_s_c.LengthSquared());	//円と線分の距離
		v_s_c.Normalize();													//単位ベクトルにする（方向だけを持つベクトル）
		if (a_changeLength)
		{
			*a_circleMove = moveDistance / 2.0f * v_s_c;					//跳ね返す値代入
			*a_startMove = moveDistance / 2.0f * v_s_c * -1;				//跳ね返す値代入
		}
		else
		{
			*a_circleMove = moveDistance * v_s_c;							//跳ね返す値代入
		}
		return result;
	}

	//円と終点の跳ね返し処理
	if (v_e_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_e_c.LengthSquared());	//円と線分の距離
		v_e_c.Normalize();													//単位ベクトルにする（方向だけを持つベクトル）
		if (a_changeLength)
		{
			*a_circleMove = moveDistance / 2.0f * v_e_c;					//跳ね返す値代入
			*a_endMove = moveDistance / 2.0f * v_e_c * -1;					//跳ね返す値代入
		}
		else
		{
			*a_circleMove = moveDistance * v_e_c;								//跳ね返す値代入
		}
		return result;
	}

	return result;
}

//円と線分の一点（始点/終点）が動く
bool Collision::NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, bool a_changeLength)
{
	bool result = false;

	//nullptrの場合　判定だけ返す
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}
	//線分の移動量がnullptrの場合
	else if (a_startMove == nullptr)
	{
		result = NextCircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, a_startPoint, a_endPoint);
		return result;
	}

	//当たってるかどうか
	if (CircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, a_startPoint + *a_startMove, a_endPoint)) { result = true; }
	else { result = false; return result; }

	//ベクトルの宣言
	Math::Vector2 v_s_e = a_endPoint - a_startPoint + *a_startMove;
	Math::Vector2 nv_s_e = { -v_s_e.y,v_s_e.x };	//法線ベクトル 始点中心に90度
	Math::Vector2 v_s_c = a_circlePos + *a_circleMove - a_startPoint + *a_startMove;
	Math::Vector2 v_e_c = a_circlePos + *a_circleMove - a_endPoint;

	//線分の間に円がある
	if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
	{
		float distance = abs(Cross(v_s_c, v_s_e)) / sqrt(v_s_e.LengthSquared());	//円の中心と線分の距離
		float moveDistance = a_circleRadius - distance;								//円と線分の距離
		nv_s_e.Normalize();															//単位ベクトルにする（方向だけを持つベクトル）

		//比を求める　→　てこの原理ぽく値代入
		float startRatio = abs(v_s_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());
		float endRatio = abs(v_e_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());

		//線分と円の距離
		if (Cross(v_s_c, v_s_e) < 0)
		{
			*a_circleMove += moveDistance * nv_s_e;							//移動量補正
			*a_startMove += moveDistance * endRatio * nv_s_e * -1;
			return result;
		}
		else
		{
			*a_circleMove += moveDistance * nv_s_e * -1;
			*a_startMove += moveDistance * endRatio * nv_s_e;
			return result;
		}
	}

	//円と始点の跳ね返し処理
	if (v_s_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_s_c.LengthSquared());	//円と線分の距離
		v_s_c.Normalize();													//単位ベクトルにする（方向だけを持つベクトル）
		if (a_changeLength)
		{
			*a_circleMove += moveDistance / 2.0f * v_s_c;					//移動量補正
			*a_startMove += moveDistance / 2.0f * v_s_c * -1;				//移動量補正
		}
		else
		{
			*a_circleMove += moveDistance * v_s_c;							//移動量補正
		}
		return result;
	}

	//円と終点の跳ね返し処理
	if (v_e_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_e_c.LengthSquared());	//円と線分の距離
		v_e_c.Normalize();													//単位ベクトルにする（方向だけを持つベクトル）
		*a_circleMove += moveDistance * v_e_c;								//移動量補正
		return result;
	}

	return result;
}

//円と線分どちらも動く
bool Collision::NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, Math::Vector2* a_endMove, bool a_changeLength)
{
	bool result = false;

	//nullptrの場合　判定だけ返す
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}
	//線分の移動量がどちらもnullptrの場合
	else if (a_startMove == nullptr && a_endMove == nullptr)
	{
		result = NextCircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, a_startPoint, a_endPoint);
		return result;
	}
	else if (a_startMove == nullptr)
	{
		result = NextCircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, a_endPoint, a_endMove, a_startPoint, a_changeLength);
		return result;
	}
	else if (a_endMove == nullptr)
	{
		result = NextCircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, a_startPoint, a_startMove, a_endPoint, a_changeLength);
		return result;
	}

	//当たってるかどうか
	if (CircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, a_startPoint + *a_startMove, a_endPoint + *a_endMove)) { result = true; }
	else { result = false; return result; }

	//ベクトルの宣言
	Math::Vector2 v_s_e = a_endPoint + *a_endMove - a_startPoint + *a_startMove;
	Math::Vector2 nv_s_e = { -v_s_e.y,v_s_e.x };	//法線ベクトル 始点中心に90度
	Math::Vector2 v_s_c = a_circlePos + *a_circleMove - a_startPoint + *a_startMove;
	Math::Vector2 v_e_c = a_circlePos + *a_circleMove - a_endPoint + *a_endMove;

	//線分の間に円がある
	if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
	{
		float distance = abs(Cross(v_s_c, v_s_e)) / sqrt(v_s_e.LengthSquared());	//円の中心と線分の距離
		float moveDistance = a_circleRadius - distance;								//円と線分の距離
		nv_s_e.Normalize();															//単位ベクトルにする（方向だけを持つベクトル）

		//比を求める　→　てこの原理ぽく値代入
		float startRatio = abs(v_s_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());
		float endRatio = abs(v_e_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());

		moveDistance = moveDistance / 2.0f;

		//線分と円の距離
		if (Cross(v_s_c, v_s_e) < 0)
		{
			*a_circleMove += moveDistance * nv_s_e;					//移動量補正
			*a_endMove += moveDistance * startRatio * nv_s_e * -1;	//移動量補正
			*a_startMove += moveDistance * endRatio * nv_s_e * -1;	//移動量補正
			return result;
		}
		else
		{
			*a_circleMove += moveDistance * nv_s_e * -1;		//移動量補正
			*a_endMove += moveDistance * startRatio * nv_s_e;	//移動量補正
			*a_startMove += moveDistance * endRatio * nv_s_e;	//移動量補正
			return result;
		}
	}



	//円と始点の跳ね返し処理
	if (v_s_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_s_c.LengthSquared());	//円と線分の距離
		v_s_c.Normalize();													//単位ベクトルにする（方向だけを持つベクトル）
		if (a_changeLength)
		{
			*a_circleMove += moveDistance / 2.0f * v_s_c;					//跳ね返す値代入
			*a_startMove += moveDistance / 2.0f * v_s_c * -1;				//跳ね返す値代入
		}
		else
		{
			*a_circleMove += moveDistance * v_s_c;							//跳ね返す値代入
		}
		return result;
	}

	//円と終点の跳ね返し処理
	if (v_e_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_e_c.LengthSquared());	//円と線分の距離
		v_e_c.Normalize();													//単位ベクトルにする（方向だけを持つベクトル）
		if (a_changeLength)
		{
			*a_circleMove += moveDistance / 2.0f * v_e_c;					//跳ね返す値代入
			*a_endMove += moveDistance / 2.0f * v_e_c * -1;					//跳ね返す値代入
		}
		else
		{
			*a_circleMove += moveDistance * v_e_c;								//跳ね返す値代入
		}
		return result;
	}

	return result;
}

// 円と四角の当たり判定（現在/未来）
bool Collision::CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_rectPos, Math::Vector2 a_reRactdius)
{
	bool result = false;

	//四角の四点を求める
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos, a_reRactdius);

	//四辺と当たり判定
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]とvertices[i+1]の線分の判定
		if (i < 3)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[i], vertices[i + 1]))
			{
				result = true;
				return result;
			}
		}
		//vertices[SQUARE_VERTEX - 1]とvertices[0]の線分の判定
		else if (i == SQUARE_VERTEX - 1)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[SQUARE_VERTEX - 1], vertices[0]))
			{
				result = true;
				return result;
			}
		}
	}

	//点と四角の判定
	result = PointAndRect(a_circlePos, a_rectPos, a_reRactdius);

	return result;
}

//円だけ動く
bool Collision::CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius)
{
	bool result = false;

	if (a_circleMove == nullptr)
	{
		result = CircleAndRectangle(a_circlePos, a_circleRadius, a_rectPos, a_rectRadius);
		return result;
	}

	//四角の四点を求める
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos, a_rectRadius);

	//四辺と当たり判定
	*a_circleMove = { 0.0f,0.0f };
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]とvertices[i+1]の線分の判定
		if (i < 3)
		{
			if (CircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[i], vertices[i + 1]))
			{
				*a_circleMove += ModifyCircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[i], vertices[i + 1]);
				result = true;
			}
		}
		//vertices[SQUARE_VERTEX - 1]とvertices[0]の線分の判定
		else if (i == SQUARE_VERTEX - 1)
		{
			if (CircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[SQUARE_VERTEX - 1], vertices[0]))
			{
				*a_circleMove += ModifyCircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[SQUARE_VERTEX - 1], vertices[0]);
				result = true;
			}
		}
	}

	return result;
}

bool Collision::NextCircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius)
{
	bool result = false;

	if (a_circleMove == nullptr)
	{
		result = CircleAndRectangle(a_circlePos, a_circleRadius, a_rectPos, a_rectRadius);
		return result;
	}

	//四角の四点を求める
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos, a_rectRadius);

	//四辺と当たり判定
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]とvertices[i+1]の線分の判定
		if (i < 3)
		{
			if (NextCircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, vertices[i], vertices[i + 1]))
			{
				result = true;
			}
		}
		//vertices[SQUARE_VERTEX - 1]とvertices[0]の線分の判定
		else if (i == SQUARE_VERTEX - 1)
		{
			if (NextCircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, vertices[SQUARE_VERTEX - 1], vertices[0]))
			{
				result = true;
			}
		}
	}

	return result;
}

//四角だけ動く
bool Collision::CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)
{
	bool result = false;

	if (a_rectMove == nullptr)
	{
		result = CircleAndRectangle(a_circlePos, a_circleRadius, a_rectPos, a_rectRadius);
		return result;
	}

	//四角の四点を求める
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos, a_rectRadius);

	//四辺と当たり判定
	*a_rectMove = { 0.0f,0.0f };
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]とvertices[i+1]の線分の判定
		if (i < 3)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[i] + *a_rectMove, vertices[i + 1] + *a_rectMove))
			{
				*a_rectMove += -1 * ModifyCircleAndSegment(a_circlePos, a_circleRadius, vertices[i] + *a_rectMove, vertices[i + 1] + *a_rectMove);
				result = true;
			}
		}
		//vertices[SQUARE_VERTEX - 1]とvertices[0]の線分の判定
		else if (i == SQUARE_VERTEX - 1)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[SQUARE_VERTEX - 1] + *a_rectMove, vertices[0] + *a_rectMove))
			{
				*a_rectMove += -1 * ModifyCircleAndSegment(a_circlePos, a_circleRadius, vertices[SQUARE_VERTEX - 1] + *a_rectMove, vertices[0] + *a_rectMove);
				result = true;
			}
		}
	}

	return result;
}

//円も四角も動く
bool Collision::CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)
{
	bool result = false;

	if (a_rectMove == nullptr && a_circleMove == nullptr)
	{
		result = CircleAndRectangle(a_circlePos, a_circleRadius, a_rectPos, a_rectRadius);
		return result;
	}
	else if (a_rectMove == nullptr)
	{
		result = CircleAndRectangle(a_circlePos, a_circleRadius, a_circleMove, a_rectPos, a_rectRadius);
		return result;
	}
	else if (a_circleMove == nullptr)
	{
		result = CircleAndRectangle(a_circlePos, a_circleRadius, a_rectPos, a_rectRadius, a_rectMove);
		return result;
	}

	//四角の四点を求める
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos, a_rectRadius);

	//四辺と当たり判定
	*a_rectMove = { 0.0f,0.0f };
	*a_circleMove = { 0.0f,0.0f };
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]とvertices[i+1]の線分の判定
		if (i < 3)
		{
			if (CircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[i] + *a_rectMove, vertices[i + 1] + *a_rectMove))
			{
				Math::Vector2 Modify = ModifyCircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[i] + *a_rectMove, vertices[i + 1] + *a_rectMove);
				*a_rectMove += -0.5 * Modify;
				*a_circleMove += 0.5 * Modify;
				result = true;
			}
		}
		//vertices[SQUARE_VERTEX - 1]とvertices[0]の線分の判定
		else if (i == SQUARE_VERTEX - 1)
		{
			if (CircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[SQUARE_VERTEX - 1] + *a_rectMove, vertices[0] + *a_rectMove))
			{
				Math::Vector2 Modify = ModifyCircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[SQUARE_VERTEX - 1] + *a_rectMove, vertices[0] + *a_rectMove);
				*a_rectMove += -0.5 * Modify;
				*a_circleMove += 0.5 * Modify;
				result = true;
			}
		}
	}

	return result;
}

bool Collision::NextCircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)
{
	bool result = false;

	if (a_rectMove == nullptr)
	{
		result = CircleAndRectangle(a_circlePos, a_circleRadius, a_rectPos, a_rectRadius);
		return result;
	}

	//四角の四点を求める
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos + *a_rectMove, a_rectRadius);

	//四辺と当たり判定
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]とvertices[i+1]の線分の判定
		if (i < 3)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[i], vertices[i + 1]))
			{
				*a_rectMove += -1 * ModifyCircleAndSegment(a_circlePos, a_circleRadius, vertices[i], vertices[i + 1]);
				result = true;
			}
		}
		//vertices[SQUARE_VERTEX - 1]とvertices[0]の線分の判定
		else if (i == SQUARE_VERTEX - 1)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[SQUARE_VERTEX - 1], vertices[0]))
			{
				*a_rectMove += -1 * ModifyCircleAndSegment(a_circlePos, a_circleRadius, vertices[SQUARE_VERTEX - 1], vertices[0]);
				result = true;
			}
		}
	}

	return result;
}

bool Collision::NextCircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)
{
	bool result = false;

	if (a_rectMove == nullptr)
	{
		result = CircleAndRectangle(a_circlePos, a_circleRadius, a_rectPos, a_rectRadius);
		return result;
	}
	else if (a_rectMove == nullptr)
	{
		result = NextCircleAndRectangle(a_circlePos, a_circleRadius, a_circleMove, a_rectPos, a_rectRadius);
		return result;
	}
	else if (a_circleMove == nullptr)
	{
		result = NextCircleAndRectangle(a_circlePos, a_circleRadius, a_rectPos, a_rectRadius, a_rectMove);
		return result;
	}

	//四角の四点を求める
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos + *a_rectMove, a_rectRadius);

	//四辺と当たり判定
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]とvertices[i+1]の線分の判定
		if (i < 3)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[i], vertices[i + 1]))
			{
				Math::Vector2 Modify = ModifyCircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[i] + *a_rectMove, vertices[i + 1] + *a_rectMove);
				*a_rectMove += -0.5 * Modify;
				*a_circleMove += 0.5 * Modify;
				result = true;
			}
		}
		//vertices[SQUARE_VERTEX - 1]とvertices[0]の線分の判定
		else if (i == SQUARE_VERTEX - 1)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[SQUARE_VERTEX - 1], vertices[0]))
			{
				Math::Vector2 Modify = ModifyCircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[SQUARE_VERTEX - 1] + *a_rectMove, vertices[0] + *a_rectMove);
				*a_rectMove += -0.5 * Modify;
				*a_circleMove += 0.5 * Modify;
				result = true;
			}
		}
	}

	return result;
}



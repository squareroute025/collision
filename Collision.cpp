#include "Collision.h"

//�������Ă邩�ǂ��������킩��
bool Collision::CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2 a_yPos, float a_yRadius)
{
	bool result = false;

	//��_�̃x�N�g�������߂�
	Math::Vector2 v_x_y = a_yPos - a_xPos;

	//�������Ă�ꍇ�̋����i�����ƂȂ鋗���j
	float checkDistance = (a_xRadius + a_yRadius) * (a_xRadius + a_yRadius);

	//���肷��
	if (v_x_y.LengthSquared() < checkDistance) { result = true; }

	return result;
}

//�����߂�����
Math::Vector2 Collision::ModifyCircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2 a_yPos, float a_yRadius)
{
	Math::Vector2 result = { 0.0f,0.0f };

	//�����߂�����
	Math::Vector2 v_y_x = a_xPos - a_yPos;										//y����x�Ɍ������x�N�g��
	float checkDistance = (a_xRadius + a_yRadius) * (a_xRadius + a_yRadius);
	float moveDistance = sqrt(checkDistance) - sqrt(v_y_x.LengthSquared());		//�����Ȃ��Ă鋗�����߂�
	v_y_x.Normalize();					//�P�ʃx�N�g���ɂ���i�������������x�N�g���j
	result = moveDistance * v_y_x;	//���˕Ԃ��l���

	return result;
}

//�������Ă��牟���Ԃ�����move�ɂ����
bool Collision::CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius)
{
	bool result = false;

	//�����蔻�肷��
	result = CircleAndCircle(a_xPos, a_xRadius, a_yPos, a_yRadius);

	//a_move��nullptr�̎��@�������Ă邩�ǂ���������Ԃ�
	if (a_xMove == nullptr) { return result; }

	//�������ĂȂ��ꍇ�@�ړ��ʏ��������ē������Ă邩�Ԃ�
	if (!result)
	{
		*a_xMove = { 0.0f,0.0f };
		return result;
	}

	//�����߂�����
	*a_xMove = ModifyCircleAndCircle(a_xPos, a_xRadius, a_yPos, a_yRadius);

	return result;
}

//�������Ă��牟���Ԃ�����Ɋ����Ă�move�ɂ����
bool Collision::CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius, Math::Vector2* a_yMove)
{
	bool result = false;

	//�����蔻�肷��
	result = CircleAndCircle(a_xPos, a_xRadius, a_yPos, a_yRadius);

	//�ǂ����nullptr�̎��@�������Ă邩�ǂ���������Ԃ�
	if (a_xMove == nullptr && a_yMove == nullptr) { return result; }

	//�������ĂȂ��ꍇ�@�ړ��ʏ��������ē������Ă邩�Ԃ�
	if (!result)
	{
		*a_xMove = { 0.0f,0.0f };
		*a_yMove = { 0.0f,0.0f };
		return result;
	}

	//�����߂�����
	Math::Vector2 modify = ModifyCircleAndCircle(a_xPos, a_xRadius, a_yPos, a_yRadius);

	//�ǂ����nullptr����Ȃ����
	if (a_xMove != nullptr && a_yMove != nullptr)
	{
		*a_xMove = modify * 0.5f;	//���˕Ԃ��l���
		*a_yMove = modify * -0.5f;	//���˕Ԃ��l���
	}
	else if (a_xMove != nullptr)
	{
		*a_xMove = modify;	//���˕Ԃ��l���
	}
	else if (a_yMove != nullptr)
	{
		*a_yMove = -modify;	//���˕Ԃ��l���
	}

	return result;
}

//�������W�Ŕ��肷��@
bool Collision::NextCircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius, Math::Vector2* a_yMove, bool b_xMove, bool b_yMove)
{
	bool result = false;

	//�ǂ����nullptr�̎��@���ݔ���œ������Ă邩�ǂ���������Ԃ�
	if (a_xMove == nullptr && a_yMove == nullptr)
	{
		result = CircleAndCircle(a_xPos, a_xRadius, a_yPos, a_yRadius);
		return result;
	}
	//�ǂ��炩������nullptr�̎�
	else if (a_xMove == nullptr || a_yMove == nullptr)
	{
		if (a_xMove == nullptr)
		{
			//�����蔻�肷��
			if (CircleAndCircle(a_xPos, a_xRadius, a_yPos + *a_yMove, a_yRadius))
			{
				result = true;

				//�����߂�����
				*a_yMove += ModifyCircleAndCircle(a_yPos + *a_yMove, a_yRadius, a_xPos, a_xRadius);	//�ړ��ʕ␳
			}
			return result;
		}
		if (a_yMove == nullptr)
		{
			//�����蔻�肷��		
			if (CircleAndCircle(a_xPos + *a_xMove, a_xRadius, a_yPos, a_yRadius))
			{
				result = true;

				//�����߂�����
				*a_xMove += ModifyCircleAndCircle(a_xPos + *a_xMove, a_xRadius, a_yPos, a_yRadius);	//�ړ��ʕ␳
			}
			return result;
		}
	}
	//�ǂ������A�h���X�������Ă���Ƃ�
	else
	{
		//�����蔻�肷��
		if (CircleAndCircle(a_xPos + *a_xMove, a_xRadius, a_yPos + *a_yMove, a_yRadius))
		{
			result = true;

			//�����߂�����
			Math::Vector2 modify = ModifyCircleAndCircle(a_xPos + *a_xMove, a_xRadius, a_yPos + *a_yMove, a_yRadius);
			if (b_xMove && b_yMove)
			{
				*a_xMove += modify * 0.5f;	//�ړ��ʕ␳
				*a_yMove += modify * -0.5f;	//�ړ��ʕ␳
			}
			else if (b_xMove)
			{
				*a_xMove += modify;	//�ړ��ʕ␳
			}
			else if (b_yMove)
			{
				*a_yMove += -1 * modify;	//�ړ��ʕ␳
			}

		}
		return result;
	}

	return result;
}

//�~�Ɛ����̓����蔻��
bool Collision::CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)
{
	bool result = false;

	//�x�N�g���̐錾
	Math::Vector2 v_s_e = a_endPoint - a_startPoint;
	Math::Vector2 v_s_c = a_circlePos - a_startPoint;
	Math::Vector2 v_e_c = a_circlePos - a_endPoint;

	//�����Ɖ~�̋���
	if (abs(Cross(v_s_c, v_s_e) / sqrt(v_s_e.LengthSquared())) <= a_circleRadius)
	{
		//�����̊Ԃɉ~������
		if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
		{
			result = true;
		}
		//�n�_�E�I�_�̋߂�
		else if (v_s_c.LengthSquared() <= a_circleRadius * a_circleRadius || v_e_c.LengthSquared() <= a_circleRadius * a_circleRadius)
		{
			result = true;
		}
	}

	return result;
}

//�~��������
bool Collision::CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)
{
	bool result = false;

	//nullptr�̏ꍇ�@���肾���Ԃ�
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}

	//�������Ă邩�ǂ���
	if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
	else { result = false; *a_circleMove = { 0.0f,0.0f }; return result; }

	//���˕Ԃ��l���
	*a_circleMove = ModifyCircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint);
	return result;
}

//�����߂������@�~������
Math::Vector2 Collision::ModifyCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)
{
	Math::Vector2 result = { 0.0f,0.0f };

	//�x�N�g���̐錾
	Math::Vector2 v_s_e = a_endPoint - a_startPoint;
	Math::Vector2 nv_s_e = { -v_s_e.y,v_s_e.x };	//�@���x�N�g�� �n�_���S��90�x
	Math::Vector2 v_s_c = a_circlePos - a_startPoint;
	Math::Vector2 v_e_c = a_circlePos - a_endPoint;

	//�����̊Ԃɉ~������
	if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
	{
		float distance = abs(Cross(v_s_c, v_s_e)) / sqrt(v_s_e.LengthSquared());	//�~�̒��S�Ɛ����̋���
		float moveDistance = a_circleRadius - distance;								//�~�Ɛ����̋���
		nv_s_e.Normalize();															//�P�ʃx�N�g���ɂ���i�������������x�N�g���j

		//�����Ɖ~�̋���
		if (Cross(v_s_c, v_s_e) < 0)
		{
			result = moveDistance * nv_s_e;		//���˕Ԃ��l���
			return result;
		}
		else
		{
			result = moveDistance * nv_s_e * -1;//���˕Ԃ��l���
			return result;
		}
	}

	Math::Vector2 addResult = { 0.0f,0.0f };
	//�~�Ǝn�_�̒��˕Ԃ�����
	if (CircleAndPoint(a_circlePos, a_circleRadius, &addResult, a_startPoint))
	{
		result += addResult;
		return result;
	}

	//�~�Ǝn�_�̒��˕Ԃ�����
	if (CircleAndPoint(a_circlePos, a_circleRadius, &addResult, a_endPoint))
	{
		result += addResult;
		return result;
	}

	return result;
}

//�~��������
bool Collision::NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)
{
	bool result = false;

	//nullptr�̏ꍇ�@���肾���Ԃ�
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}

	//�������Ă邩�ǂ���
	if (CircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
	else { result = false; return result; }

	//�����߂�����
	*a_circleMove += ModifyCircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, a_startPoint, a_endPoint);
	return result;
}

//�~�Ɛ����̈�_�i�n�_/�I�_�j������
bool Collision::CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, bool a_changeLength)
{
	bool result = false;

	//nullptr�̏ꍇ�@���肾���Ԃ�
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}
	//�����̈ړ��ʂ�nullptr�̏ꍇ
	else if (a_startMove == nullptr)
	{
		result = CircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, a_startPoint, a_endPoint);
		return result;
	}

	//�������Ă邩�ǂ���
	if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
	else { result = false; *a_circleMove = { 0.0f,0.0f }; return result; }

	//�x�N�g���̐錾
	Math::Vector2 v_s_e = a_endPoint - a_startPoint;
	Math::Vector2 nv_s_e = { -v_s_e.y,v_s_e.x };	//�@���x�N�g�� �n�_���S��90�x
	Math::Vector2 v_s_c = a_circlePos - a_startPoint;
	Math::Vector2 v_e_c = a_circlePos - a_endPoint;

	//�����̊Ԃɉ~������
	if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
	{
		float distance = abs(Cross(v_s_c, v_s_e)) / sqrt(v_s_e.LengthSquared());	//�~�̒��S�Ɛ����̋���
		float moveDistance = a_circleRadius - distance;								//�~�Ɛ����̋���
		nv_s_e.Normalize();															//�P�ʃx�N�g���ɂ���i�������������x�N�g���j

		//������߂�@���@�Ă��̌����ۂ��l���
		float startRatio = abs(v_s_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());
		float endRatio = abs(v_e_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());

		//�����Ɖ~�̋���
		if (Cross(v_s_c, v_s_e) < 0)
		{
			*a_circleMove = moveDistance * startRatio * nv_s_e;		//���˕Ԃ��l���
			*a_startMove = moveDistance * endRatio * nv_s_e * -1;		//���˕Ԃ��l���
			return result;
		}
		else
		{
			*a_circleMove = moveDistance * startRatio * nv_s_e * -1;		//���˕Ԃ��l���
			*a_startMove = moveDistance * endRatio * nv_s_e;		//���˕Ԃ��l���
			return result;
		}
	}

	//�~�Ǝn�_�̒��˕Ԃ�����
	if (v_s_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_s_c.LengthSquared());	//�~�Ɛ����̋���
		v_s_c.Normalize();													//�P�ʃx�N�g���ɂ���i�������������x�N�g���j
		if (a_changeLength)
		{
			*a_circleMove = moveDistance / 2.0f * v_s_c;					//���˕Ԃ��l���
			*a_startMove = moveDistance / 2.0f * v_s_c * -1;				//���˕Ԃ��l���
		}
		else { *a_circleMove = moveDistance * v_s_c; }						//���˕Ԃ��l���
		return result;
	}

	//�~�ƏI�_�̒��˕Ԃ�����
	if (v_e_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_e_c.LengthSquared());	//�~�Ɛ����̋���
		v_e_c.Normalize();													//�P�ʃx�N�g���ɂ���i�������������x�N�g���j
		*a_circleMove = moveDistance * v_e_c;								//���˕Ԃ��l���
		return result;
	}

	return result;
}

//�~�Ɛ����ǂ��������
bool Collision::CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, Math::Vector2* a_endMove, bool a_changeLength)
{
	bool result = false;

	//nullptr�̏ꍇ�@���肾���Ԃ�
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}
	//�����̈ړ��ʂ��ǂ����nullptr�̏ꍇ
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

	//�������Ă邩�ǂ���
	if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
	else { result = false; *a_circleMove = { 0.0f,0.0f }; return result; }

	//�x�N�g���̐錾
	Math::Vector2 v_s_e = a_endPoint - a_startPoint;
	Math::Vector2 nv_s_e = { -v_s_e.y,v_s_e.x };	//�@���x�N�g�� �n�_���S��90�x
	Math::Vector2 v_s_c = a_circlePos - a_startPoint;
	Math::Vector2 v_e_c = a_circlePos - a_endPoint;

	//�����̊Ԃɉ~������
	if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
	{
		float distance = abs(Cross(v_s_c, v_s_e)) / sqrt(v_s_e.LengthSquared());	//�~�̒��S�Ɛ����̋���
		float moveDistance = a_circleRadius - distance;								//�~�Ɛ����̋���
		nv_s_e.Normalize();															//�P�ʃx�N�g���ɂ���i�������������x�N�g���j

		//������߂�@���@�Ă��̌����ۂ��l���
		float startRatio = abs(v_s_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());
		float endRatio = abs(v_e_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());

		moveDistance = moveDistance / 2.0f;

		//�����Ɖ~�̋���
		if (Cross(v_s_c, v_s_e) < 0)
		{
			*a_circleMove = moveDistance * nv_s_e;							//���˕Ԃ��l���
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



	//�~�Ǝn�_�̒��˕Ԃ�����
	if (v_s_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_s_c.LengthSquared());	//�~�Ɛ����̋���
		v_s_c.Normalize();													//�P�ʃx�N�g���ɂ���i�������������x�N�g���j
		if (a_changeLength)
		{
			*a_circleMove = moveDistance / 2.0f * v_s_c;					//���˕Ԃ��l���
			*a_startMove = moveDistance / 2.0f * v_s_c * -1;				//���˕Ԃ��l���
		}
		else
		{
			*a_circleMove = moveDistance * v_s_c;							//���˕Ԃ��l���
		}
		return result;
	}

	//�~�ƏI�_�̒��˕Ԃ�����
	if (v_e_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_e_c.LengthSquared());	//�~�Ɛ����̋���
		v_e_c.Normalize();													//�P�ʃx�N�g���ɂ���i�������������x�N�g���j
		if (a_changeLength)
		{
			*a_circleMove = moveDistance / 2.0f * v_e_c;					//���˕Ԃ��l���
			*a_endMove = moveDistance / 2.0f * v_e_c * -1;					//���˕Ԃ��l���
		}
		else
		{
			*a_circleMove = moveDistance * v_e_c;								//���˕Ԃ��l���
		}
		return result;
	}

	return result;
}

//�~�Ɛ����̈�_�i�n�_/�I�_�j������
bool Collision::NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, bool a_changeLength)
{
	bool result = false;

	//nullptr�̏ꍇ�@���肾���Ԃ�
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}
	//�����̈ړ��ʂ�nullptr�̏ꍇ
	else if (a_startMove == nullptr)
	{
		result = NextCircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, a_startPoint, a_endPoint);
		return result;
	}

	//�������Ă邩�ǂ���
	if (CircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, a_startPoint + *a_startMove, a_endPoint)) { result = true; }
	else { result = false; return result; }

	//�x�N�g���̐錾
	Math::Vector2 v_s_e = a_endPoint - a_startPoint + *a_startMove;
	Math::Vector2 nv_s_e = { -v_s_e.y,v_s_e.x };	//�@���x�N�g�� �n�_���S��90�x
	Math::Vector2 v_s_c = a_circlePos + *a_circleMove - a_startPoint + *a_startMove;
	Math::Vector2 v_e_c = a_circlePos + *a_circleMove - a_endPoint;

	//�����̊Ԃɉ~������
	if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
	{
		float distance = abs(Cross(v_s_c, v_s_e)) / sqrt(v_s_e.LengthSquared());	//�~�̒��S�Ɛ����̋���
		float moveDistance = a_circleRadius - distance;								//�~�Ɛ����̋���
		nv_s_e.Normalize();															//�P�ʃx�N�g���ɂ���i�������������x�N�g���j

		//������߂�@���@�Ă��̌����ۂ��l���
		float startRatio = abs(v_s_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());
		float endRatio = abs(v_e_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());

		//�����Ɖ~�̋���
		if (Cross(v_s_c, v_s_e) < 0)
		{
			*a_circleMove += moveDistance * nv_s_e;							//�ړ��ʕ␳
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

	//�~�Ǝn�_�̒��˕Ԃ�����
	if (v_s_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_s_c.LengthSquared());	//�~�Ɛ����̋���
		v_s_c.Normalize();													//�P�ʃx�N�g���ɂ���i�������������x�N�g���j
		if (a_changeLength)
		{
			*a_circleMove += moveDistance / 2.0f * v_s_c;					//�ړ��ʕ␳
			*a_startMove += moveDistance / 2.0f * v_s_c * -1;				//�ړ��ʕ␳
		}
		else
		{
			*a_circleMove += moveDistance * v_s_c;							//�ړ��ʕ␳
		}
		return result;
	}

	//�~�ƏI�_�̒��˕Ԃ�����
	if (v_e_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_e_c.LengthSquared());	//�~�Ɛ����̋���
		v_e_c.Normalize();													//�P�ʃx�N�g���ɂ���i�������������x�N�g���j
		*a_circleMove += moveDistance * v_e_c;								//�ړ��ʕ␳
		return result;
	}

	return result;
}

//�~�Ɛ����ǂ��������
bool Collision::NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, Math::Vector2* a_endMove, bool a_changeLength)
{
	bool result = false;

	//nullptr�̏ꍇ�@���肾���Ԃ�
	if (a_circleMove == nullptr)
	{
		if (CircleAndSegment(a_circlePos, a_circleRadius, a_startPoint, a_endPoint)) { result = true; }
		else { result = false; }
		return result;
	}
	//�����̈ړ��ʂ��ǂ����nullptr�̏ꍇ
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

	//�������Ă邩�ǂ���
	if (CircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, a_startPoint + *a_startMove, a_endPoint + *a_endMove)) { result = true; }
	else { result = false; return result; }

	//�x�N�g���̐錾
	Math::Vector2 v_s_e = a_endPoint + *a_endMove - a_startPoint + *a_startMove;
	Math::Vector2 nv_s_e = { -v_s_e.y,v_s_e.x };	//�@���x�N�g�� �n�_���S��90�x
	Math::Vector2 v_s_c = a_circlePos + *a_circleMove - a_startPoint + *a_startMove;
	Math::Vector2 v_e_c = a_circlePos + *a_circleMove - a_endPoint + *a_endMove;

	//�����̊Ԃɉ~������
	if (v_s_c.Dot(v_s_e) * v_e_c.Dot(v_s_e) <= 0)
	{
		float distance = abs(Cross(v_s_c, v_s_e)) / sqrt(v_s_e.LengthSquared());	//�~�̒��S�Ɛ����̋���
		float moveDistance = a_circleRadius - distance;								//�~�Ɛ����̋���
		nv_s_e.Normalize();															//�P�ʃx�N�g���ɂ���i�������������x�N�g���j

		//������߂�@���@�Ă��̌����ۂ��l���
		float startRatio = abs(v_s_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());
		float endRatio = abs(v_e_c.Dot(v_s_e)) / sqrt(v_s_e.LengthSquared()) / sqrt(v_s_e.LengthSquared());

		moveDistance = moveDistance / 2.0f;

		//�����Ɖ~�̋���
		if (Cross(v_s_c, v_s_e) < 0)
		{
			*a_circleMove += moveDistance * nv_s_e;					//�ړ��ʕ␳
			*a_endMove += moveDistance * startRatio * nv_s_e * -1;	//�ړ��ʕ␳
			*a_startMove += moveDistance * endRatio * nv_s_e * -1;	//�ړ��ʕ␳
			return result;
		}
		else
		{
			*a_circleMove += moveDistance * nv_s_e * -1;		//�ړ��ʕ␳
			*a_endMove += moveDistance * startRatio * nv_s_e;	//�ړ��ʕ␳
			*a_startMove += moveDistance * endRatio * nv_s_e;	//�ړ��ʕ␳
			return result;
		}
	}



	//�~�Ǝn�_�̒��˕Ԃ�����
	if (v_s_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_s_c.LengthSquared());	//�~�Ɛ����̋���
		v_s_c.Normalize();													//�P�ʃx�N�g���ɂ���i�������������x�N�g���j
		if (a_changeLength)
		{
			*a_circleMove += moveDistance / 2.0f * v_s_c;					//���˕Ԃ��l���
			*a_startMove += moveDistance / 2.0f * v_s_c * -1;				//���˕Ԃ��l���
		}
		else
		{
			*a_circleMove += moveDistance * v_s_c;							//���˕Ԃ��l���
		}
		return result;
	}

	//�~�ƏI�_�̒��˕Ԃ�����
	if (v_e_c.LengthSquared() < a_circleRadius * a_circleRadius)
	{
		float moveDistance = a_circleRadius - sqrt(v_e_c.LengthSquared());	//�~�Ɛ����̋���
		v_e_c.Normalize();													//�P�ʃx�N�g���ɂ���i�������������x�N�g���j
		if (a_changeLength)
		{
			*a_circleMove += moveDistance / 2.0f * v_e_c;					//���˕Ԃ��l���
			*a_endMove += moveDistance / 2.0f * v_e_c * -1;					//���˕Ԃ��l���
		}
		else
		{
			*a_circleMove += moveDistance * v_e_c;								//���˕Ԃ��l���
		}
		return result;
	}

	return result;
}

// �~�Ǝl�p�̓����蔻��i����/�����j
bool Collision::CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_rectPos, Math::Vector2 a_reRactdius)
{
	bool result = false;

	//�l�p�̎l�_�����߂�
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos, a_reRactdius);

	//�l�ӂƓ����蔻��
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]��vertices[i+1]�̐����̔���
		if (i < 3)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[i], vertices[i + 1]))
			{
				result = true;
				return result;
			}
		}
		//vertices[SQUARE_VERTEX - 1]��vertices[0]�̐����̔���
		else if (i == SQUARE_VERTEX - 1)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[SQUARE_VERTEX - 1], vertices[0]))
			{
				result = true;
				return result;
			}
		}
	}

	//�_�Ǝl�p�̔���
	result = PointAndRect(a_circlePos, a_rectPos, a_reRactdius);

	return result;
}

//�~��������
bool Collision::CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius)
{
	bool result = false;

	if (a_circleMove == nullptr)
	{
		result = CircleAndRectangle(a_circlePos, a_circleRadius, a_rectPos, a_rectRadius);
		return result;
	}

	//�l�p�̎l�_�����߂�
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos, a_rectRadius);

	//�l�ӂƓ����蔻��
	*a_circleMove = { 0.0f,0.0f };
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]��vertices[i+1]�̐����̔���
		if (i < 3)
		{
			if (CircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[i], vertices[i + 1]))
			{
				*a_circleMove += ModifyCircleAndSegment(a_circlePos + *a_circleMove, a_circleRadius, vertices[i], vertices[i + 1]);
				result = true;
			}
		}
		//vertices[SQUARE_VERTEX - 1]��vertices[0]�̐����̔���
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

	//�l�p�̎l�_�����߂�
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos, a_rectRadius);

	//�l�ӂƓ����蔻��
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]��vertices[i+1]�̐����̔���
		if (i < 3)
		{
			if (NextCircleAndSegment(a_circlePos, a_circleRadius, a_circleMove, vertices[i], vertices[i + 1]))
			{
				result = true;
			}
		}
		//vertices[SQUARE_VERTEX - 1]��vertices[0]�̐����̔���
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

//�l�p��������
bool Collision::CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)
{
	bool result = false;

	if (a_rectMove == nullptr)
	{
		result = CircleAndRectangle(a_circlePos, a_circleRadius, a_rectPos, a_rectRadius);
		return result;
	}

	//�l�p�̎l�_�����߂�
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos, a_rectRadius);

	//�l�ӂƓ����蔻��
	*a_rectMove = { 0.0f,0.0f };
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]��vertices[i+1]�̐����̔���
		if (i < 3)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[i] + *a_rectMove, vertices[i + 1] + *a_rectMove))
			{
				*a_rectMove += -1 * ModifyCircleAndSegment(a_circlePos, a_circleRadius, vertices[i] + *a_rectMove, vertices[i + 1] + *a_rectMove);
				result = true;
			}
		}
		//vertices[SQUARE_VERTEX - 1]��vertices[0]�̐����̔���
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

//�~���l�p������
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

	//�l�p�̎l�_�����߂�
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos, a_rectRadius);

	//�l�ӂƓ����蔻��
	*a_rectMove = { 0.0f,0.0f };
	*a_circleMove = { 0.0f,0.0f };
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]��vertices[i+1]�̐����̔���
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
		//vertices[SQUARE_VERTEX - 1]��vertices[0]�̐����̔���
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

	//�l�p�̎l�_�����߂�
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos + *a_rectMove, a_rectRadius);

	//�l�ӂƓ����蔻��
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]��vertices[i+1]�̐����̔���
		if (i < 3)
		{
			if (CircleAndSegment(a_circlePos, a_circleRadius, vertices[i], vertices[i + 1]))
			{
				*a_rectMove += -1 * ModifyCircleAndSegment(a_circlePos, a_circleRadius, vertices[i], vertices[i + 1]);
				result = true;
			}
		}
		//vertices[SQUARE_VERTEX - 1]��vertices[0]�̐����̔���
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

	//�l�p�̎l�_�����߂�
	const int SQUARE_VERTEX = 4;
	Math::Vector2 vertices[SQUARE_VERTEX];
	RectVertices(vertices, a_rectPos + *a_rectMove, a_rectRadius);

	//�l�ӂƓ����蔻��
	for (int i = 0; i < SQUARE_VERTEX; i++)
	{
		//vertices[i]��vertices[i+1]�̐����̔���
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
		//vertices[SQUARE_VERTEX - 1]��vertices[0]�̐����̔���
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



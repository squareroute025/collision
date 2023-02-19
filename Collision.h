#pragma once
//#include "Src/Application/TextureManager.h"
//using namespace TextureManagement;
#include "Src/Application/Calculation/Calculation.h"



class Collision : public Calculation
{
public:
	Collision() {};
	~Collision() {};

	//���ݍ��W������g�����̗���
	// �ړ����� �� ���W�X�V  ��  ���ݍ��W���� �� �ŏI�X�V
	//(m_move+=5)(m_pos+=m_move)(m_move=�C���l) (m_pos+=m_move)

	//�������W������g�����̗���
	// �ړ����� �� �������W���� �� ���W�X�V
	//(m_move+=5)(m_move+=�C���l)(m_pos+=m_move)


	///////////////////////////////////////////////////////////////
	// �~�Ɖ~�̓����蔻��
	///////////////////////////////////////////////////////////////

	//�~�Ɖ~�̓����蔻��i����/�����j
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_xPos		...���W1
	// a_xRadius	...���a1(�摜�T�C�Y * �g��k����)
	// a_yPos		...���W2
	// a_yRadius	...���a2(�摜�T�C�Y * �g��k����)
	virtual bool CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2 a_yPos, float a_yRadius)final;

	//�~�Ɖ~�̓����蔻��i����/�����j
	// !! �Ԃ����Ă�Ƃ����� !!
	//�@���˕Ԃ���������ꍇ�̒��˕Ԃ��l��Ԃ�
	// a_xPos		...�����~�̍��W
	// a_xRadius	...�����~�̔��a(�摜�T�C�Y * �g��k����)
	// a_yPos		...�Œ�~�̍��W
	// a_yRadius	...�Œ�~�̔��a(�摜�T�C�Y * �g��k����)
	virtual Math::Vector2 ModifyCircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2 a_yPos, float a_yRadius)final;

	//�~�Ɖ~�̓����蔻��i���݁j�~�������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_xPos		...���W1
	// a_xRadius	...���a1(�摜�T�C�Y * �g��k����)
	// a_xMove		...�����߂��l������ �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	// a_yPos		...���W2
	// a_yRadius	...���a2(�摜�T�C�Y * �g��k����)
	virtual bool CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius)final;

	//�~�Ɖ~�̓����蔻��i���݁j�~��Ƃ�����
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_xPos		...���W1
	// a_xRadius	...���a1(�摜�T�C�Y * �g��k����)
	// a_xMove		...�����߂��l������ �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	// a_yPos		...���W2
	// a_yRadius	...���a2(�摜�T�C�Y * �g��k����)
	// a_yMove		...�����߂��l������ �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	virtual bool CircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius, Math::Vector2* a_yMove)final;

	//�~�Ɖ~�̓����蔻��i�����j�����߂���������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_xPos		...���W1
	// a_xRadius	...���a1(�摜�T�C�Y * �g��k����)
	// a_xMove		...�ړ���1 nullptr�̂Ƃ����ݍ��W�Ŕ��肷��&�����߂������Ȃ�
	// a_yPos		...���W2
	// a_yRadius	...���a2(�摜�T�C�Y * �g��k����)
	// a_yMove		...�ړ���2 nullptr�̂Ƃ����ݍ��W�Ŕ��肷��&�����߂������Ȃ�
	virtual bool NextCircleAndCircle(Math::Vector2 a_xPos, float a_xRadius, Math::Vector2* a_xMove, Math::Vector2 a_yPos, float a_yRadius, Math::Vector2* a_yMovebool ,bool b_xMove = true, bool b_yMove = true)final;


	///////////////////////////////////////////////////////////////
	// �~�Ɛ����̓����蔻��
	///////////////////////////////////////////////////////////////

	// �~�Ɛ����̓����蔻��i����/�����j
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_startPoint		...�����̎n�_���W
	// a_endPoint		...�����̏I�_���W
	virtual bool CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)final;

	// �~�Ɛ����̓����蔻��i���݁j�~��������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_circleMove		...�~�̈ړ���
	// a_startPoint		...�����̎n�_���W
	// a_endPoint		...�����̏I�_���W
	virtual bool CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)final;

	// �~�Ɛ����̓����蔻��
	// !! �Ԃ����Ă�Ƃ����� !!
	//�@�~�����˕Ԃ���������ꍇ�̒��˕Ԃ��l��Ԃ�
	// a_circlePos		...�����~�̍��W
	// a_circleRadius	...�����~�̔��a(�摜�T�C�Y * �g��k����)
	// a_startPoint		...�����̎n�_���W
	// a_endPoint		...�����̏I�_���W
	virtual Math::Vector2 ModifyCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)final;

	// �~�Ɛ����̓����蔻��i�����j�~��������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_circleMove		...�~�̈ړ��� nullptr�̂Ƃ����ݍ��W�Ŕ��肷��
	// a_startPoint		...�����̎n�_���W
	// a_endPoint		...�����̏I�_���W
	virtual bool NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2 a_endPoint)final;

	// �~�Ɛ����̓����蔻��i���݁j����(��̓_�͌Œ�)���~������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_circleMove		...�~�̈ړ��� �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	// a_startPoint		...�����̎n�_���W
	// a_startMove		...�����̎n�_�̈ړ��� �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	// a_endPoint		...�����̏I�_���W
	// changeLength		...�~�̓����ɂ���Đ����̒����ς����悤�ɂ��邩
	virtual bool CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint,bool a_changeLength = false)final;

	// �~�Ɛ����̓����蔻��i���݁j�������~������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_circleMove		...�~�̈ړ��� �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	// a_startPoint		...�����̎n�_���W
	// a_startMove		...�����̎n�_�̈ړ��� �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	// a_endPoint		...�����̏I�_���W
	// a_endMove		...�����̎n�_�̈ړ��� �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	// a_changeLength		...�~�̓����ɂ���Đ����̒����ς����悤�ɂ��邩
	virtual bool CircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, Math::Vector2* a_endMove, bool a_changeLength = false)final;

	// �~�Ɛ����̓����蔻��i�����j����(��̓_�͌Œ�)���~������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_circleMove		...�~�̈ړ��� nullptr�̂Ƃ����ݍ��W�Ŕ��肷��
	// a_startPoint		...�����̎n�_���W
	// a_startMove		...�����̎n�_�̈ړ��� nullptr�̂Ƃ��n�_�͓������������W����
	// a_endPoint		...�����̏I�_���W
	// a_changeLength		...�~�̓����ɂ���Đ����̒����ς����悤�ɂ��邩
	virtual bool NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, bool a_changeLength = false)final;

	// �~�Ɛ����̓����蔻��i�����j�������~������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_circleMove		...�~�̈ړ��� nullptr�̂Ƃ����ݍ��W�Ŕ��肷��
	// a_startPoint		...�����̎n�_���W
	// a_startMove		...�����̎n�_�̈ړ��� nullptr�̂Ƃ��n�_�͓������������W����
	// a_endPoint		...�����̏I�_���W
	// a_endMove		...�����̎n�_�̈ړ��� nullptr�̂Ƃ��I�_�͓������������W����
	// a_changeLength	...�~�̓����ɂ���Đ����̒����ς����悤�ɂ��邩
	virtual bool NextCircleAndSegment(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_startPoint, Math::Vector2* a_startMove, Math::Vector2 a_endPoint, Math::Vector2* a_endMove, bool a_changeLength = false)final;


	///////////////////////////////////////////////////////////////
	// �~�Ǝl�p�̓����蔻��
	///////////////////////////////////////////////////////////////

	// �~�Ǝl�p�̓����蔻��i����/�����j
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_rectPos		...�l�p�̍��W
	// a_rectRadius		...�l�p�̔��a(�摜�T�C�Y * �g��k����) 
	virtual bool CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius)final;
	
	// �~�Ǝl�p�̓����蔻��i���݁j�~��������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_circleMove		...�~�̈ړ��� �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	// a_rectPos		...�l�p�̍��W
	// a_rectRadius		...�l�p�̔��a(�摜�T�C�Y * �g��k����) 
	virtual bool CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius)final;

	// �~�Ǝl�p�̓����蔻��i�����j�~��������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_circleMove		...�~�̈ړ��� �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	// a_rectPos		...�l�p�̍��W
	// a_rectRadius		...�l�p�̔��a(�摜�T�C�Y * �g��k����) 
	virtual bool NextCircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius)final;

	// �~�Ǝl�p�̓����蔻��i���݁j�l�p��������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_rectPos		...�l�p�̍��W
	// a_rectRadius		...�l�p�̔��a(�摜�T�C�Y * �g��k����) 
	// a_rectMove		...�l�p�̈ړ��� �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	virtual bool CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)final;

	// �~�Ǝl�p�̓����蔻��i���݁j�~���l�p������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_circleMove		...�~�̈ړ��� �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͎l�p������������
	// a_rectPos		...�l�p�̍��W
	// a_rectRadius		...�l�p�̔��a(�摜�T�C�Y * �g��k����) 
	// a_rectMove		...�l�p�̈ړ��� �������ĂȂ��Ƃ���0,0���� nullptr�̂Ƃ��͉~����������
	virtual bool CircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)final;

	// �~�Ǝl�p�̓����蔻��i�����j�l�p��������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_rectPos		...�l�p�̍��W
	// a_rectRadius		...�l�p�̔��a(�摜�T�C�Y * �g��k����) 
	// a_rectMove		...�l�p�̈ړ��� nullptr�̂Ƃ��͓������Ă邩�ǂ��������Ԃ�
	virtual bool NextCircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)final;

	// �~�Ǝl�p�̓����蔻��i�����j�~���l�p������
	//�@�������Ă邩�������ĂȂ�����Ԃ�
	// a_circlePos		...�~�̍��W
	// a_circleRadius	...�~�̔��a(�摜�T�C�Y * �g��k����)
	// a_circleMove		...�~�̈ړ��� nullptr�̂Ƃ��͎l�p�������������i�����j
	// a_rectPos		...�l�p�̍��W
	// a_rectRadius		...�l�p�̔��a(�摜�T�C�Y * �g��k����) 
	// a_rectMove		...�l�p�̈ړ��� nullptr�̂Ƃ��͉~�����������i�����j
	virtual bool NextCircleAndRectangle(Math::Vector2 a_circlePos, float a_circleRadius, Math::Vector2* a_circleMove, Math::Vector2 a_rectPos, Math::Vector2 a_rectRadius, Math::Vector2* a_rectMove)final;

	///////////////////////////////////////////////////////////////
	// ���̑�
	///////////////////////////////////////////////////////////////


private:
	//�萔�ɃZ�b�g�������ǂ����t���O


	//�����傤����Ƃ����������Ă���or�萔�}�l�[�W���[������炤
	//const float increaseRatio = 0.5f;
	//const float split = 5.0f;
	//const int SCREEN_Y = 720;
	//const int SCREEN_HALF_Y = SCREEN_Y / 2;
};


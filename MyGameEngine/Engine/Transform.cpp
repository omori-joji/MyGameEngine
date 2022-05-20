#include "Transform.h"

//�R���X�g���N�^
Transform::Transform():
	matTranslate_(XMMatrixIdentity()),	//�ړ��s��̌���
	matRotate_(XMMatrixIdentity()),		//��]�s��̌���
	matScale_(XMMatrixIdentity()),		//�g��s��̌���
	position_(XMFLOAT3(0,0,0)),			//�ʒu
    rotate_(XMFLOAT3(0, 0, 0)),			//��]
	scale_(XMFLOAT3(1, 1, 1))			//�g��
{
}

//�f�X�g���N�^
Transform::~Transform()
{
}

//�ړ��A��]�A�g��s��(���[���h�s��)��������֐�
void Transform::Calclation()
{
	//�ړ��s��
	matTranslate_ = XMMatrixTranslation(position_.x,position_.y,position_.z);

	//��]
	XMMATRIX mX, mY, mZ;
	mX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));   
	mY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));   
	mZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = mX * mY * mZ;

	//�g��k��
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

//���[���h�s���n���Q�b�^�[
//�߂�l�͍s��̌��ʂ�Ԃ��̂�XMMATRIX�ɂ���
XMMATRIX Transform::GetWorldMatrix()
{
	//���[���h�s���Ԃ�
	return  matScale_ * matRotate_ * matTranslate_;
}

//���K�s���n���Q�b�^�[
//�߂�l�͍s��̌��ʂ�Ԃ��̂�XMMATRIX�ɂ���
XMMATRIX Transform::GetNormalmatrix()
{
	XMVECTOR det;
	return matRotate_ * XMMatrixInverse(&det, matScale_);
}

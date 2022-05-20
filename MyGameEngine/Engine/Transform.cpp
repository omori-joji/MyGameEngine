#include "Transform.h"

Transform::Transform():
	matTranslate_(XMMatrixIdentity()),
	matRotate_(XMMatrixIdentity()),
	matScale_(XMMatrixIdentity()),

	position_(XMFLOAT3(0,0,0)),
    rotate_(XMFLOAT3(0, 0, 0)),
	scale_(XMFLOAT3(1, 1, 1))
{
}

Transform::~Transform()
{
}

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

XMMATRIX Transform::GetWorldMatrix()
{
	return  matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::GetNormalmatrix()
{
	XMVECTOR det;
	return matRotate_ * XMMatrixInverse(&det, matScale_);
}

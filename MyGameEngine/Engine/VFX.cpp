#include "VFX.h"
#include "VisualEffect.h"
#include "Camera.h"

//�R���X�g���N�^
VFX::VFX() : pTexData_(nullptr), frame_(0), isLoop_(false), speed_(0)
{
}

//�G�t�F�N�g���P�쐬
void VFX::Create(VFXTextureData* data, Transform transform, float speed, bool isLoop)
{
	pTexData_ = data;
	speed_ = speed;
	isLoop_ = isLoop;
	transform_ = transform;
	transform_.Calclation();
}

//�A�j���[�V������i�߂�
bool VFX::Update()
{
	frame_ += speed_;

	//�Ō�܂ŃA�j���[�V��������
	if ((DWORD)frame_ >= pTexData_->width * pTexData_->height)
	{
		//���[�v�A�j���[�V�����̏ꍇ
		if (isLoop_)
		{
			//�ŏ��̃R�}�ɖ߂�
			frame_ = 0.0f;
		}

		//�񃋁[�v
		else
		{
			return true;
		}
	}
	return false;
}


//�`��
void VFX::Draw()
{
	//�摜�̒��ŁA����`�悷��̍����牽�ԖځA�ォ�牽�Ԗڂ�
	int x = (DWORD)frame_ % pTexData_->width;
	int y = (DWORD)frame_ / pTexData_->width;


	//�R���X�^���g�o�b�t�@�ɓn�����
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform_.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix()); //���C������󂯎����worldMatrix�Ɉړ��s��Ɖ�]�s��������Ă���
	cb.uvLeft = (float)x / pTexData_->width;	//����̒��_��U���W
	cb.uvTop = (float)y / pTexData_->height;	//����̒��_��V���W
	cb.uvWidth = 1.0f / pTexData_->width;		//�摜�̕���1�Ƃ������̂P�R�}�̕�
	cb.uvHeight = 1.0f / pTexData_->height;		//�摜�̍�����1�Ƃ������̂P�R�}�̍���;

	//�f�[�^���V�F�[�_�[�ɓn��
	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(VisualEffect::pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));
	ID3D11SamplerState* pSampler = pTexData_->pTexture->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexData_->pTexture->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);
	Direct3D::pContext->Unmap(VisualEffect::pConstantBuffer_, 0);



	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &VisualEffect::pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(VisualEffect::pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &VisualEffect::pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &VisualEffect::pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

	//�`��
	Direct3D::pContext->DrawIndexed(6, 0, 0);
}

#include "VFX.h"
#include "VisualEffect.h"
#include "Camera.h"

VFX::VFX() : pTexData_(nullptr), frame_(0), isLoop_(false), speed_(0)
{

}

void VFX::Create(VFXTextureData* data, Transform transform, float speed, bool isLoop)
{
	pTexData_ = data;
	transform_ = transform;
	speed_ = speed;
	isLoop_ = isLoop;
}

bool VFX::Update()
{
	frame_ += speed_;

	//最後までアニメーションした
	if ((DWORD)frame_ >= pTexData_->width * pTexData_->height)
	{
		if (isLoop_)
		{
			frame_ = 0.0f;
		}

		else
		{
			return true;
		}
	}
	return false;
}

void VFX::Draw()
{
	//画像の中で、今回描画するの左から何番目、上から何番目か
	int x = (DWORD)frame_ % pTexData_->width;
	int y = (DWORD)frame_ / pTexData_->width;


	//コンスタントバッファに渡す情報
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform_.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix()); //メインから受け取ったworldMatrixに移動行列と回転行列をかけている
	cb.uvLeft = (float)x / pTexData_->width;
	cb.uvTop = (float)y / pTexData_->height;
	cb.uvWidth = 1.0f / pTexData_->width;
	cb.uvHeight = 1.0f / pTexData_->height;


	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(VisualEffect::pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを送る

	ID3D11SamplerState* pSampler = pTexData_->pTexture->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexData_->pTexture->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext->Unmap(VisualEffect::pConstantBuffer_, 0);	//再開



	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &VisualEffect::pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(VisualEffect::pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &VisualEffect::pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &VisualEffect::pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext->DrawIndexed(6, 0, 0);

}

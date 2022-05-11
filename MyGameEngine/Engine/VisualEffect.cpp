#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <list>


#include "VisualEffect.h"
#include "Texture.h"
#include "Direct3D.h"
#include "Common.h"


using namespace DirectX;


namespace VisualEffect
{
    //�摜�f�[�^�z��i�\���̂�VFX.h�Ő錾�j
	std::vector<VFXTextureData*> textureDatas;
    
    //�\�����̃G�t�F�N�g���X�g�i�\���̂�VFX.h�Ő錾�j
    std::list<VFX*> vfxs;

    //�|���S���E�V�F�[�_�[�֘A
	ID3D11Buffer*       pVertexBuffer_;	        //���_�o�b�t�@
	ID3D11Buffer*       pIndexBuffer_;          //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer*       pConstantBuffer_;       //�R���X�^���g�o�b�t�@
    ID3D11VertexShader*     pVertexShader = nullptr;	    //���_�V�F�[�_�[
    ID3D11PixelShader*      pPixelShader = nullptr;		    //�s�N�Z���V�F�[�_�[
    ID3D11InputLayout*      pVertexLayout = nullptr;	    //���_�C���v�b�g���C�A�E�g
    ID3D11RasterizerState*  pRasterizerState = nullptr;	    //���X�^���C�U�[
}


//������
void VisualEffect::Initialize()
{
    CreatePolygon();
    ShaderSetup();
}

//�|���S�����\������f�[�^�̏���
void VisualEffect::CreatePolygon()
{
    // ���_���
    VERTEX vertices[] =
    {
        { XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f)}, // �l�p�`�̒��_�i����j
        { XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f,  0.0f, 0.0f, 0.0f)}, // �l�p�`�̒��_�i�E��j
        { XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f)}, // �l�p�`�̒��_�i�E���j
        { XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f,  1.0f, 0.0f, 0.0f)}  // �l�p�`�̒��_�i�����j
    };

    // ���_�f�[�^�p�o�b�t�@�̐ݒ�
    D3D11_BUFFER_DESC bd_vertex;
    bd_vertex.ByteWidth = sizeof(vertices);
    bd_vertex.Usage = D3D11_USAGE_DEFAULT;
    bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd_vertex.CPUAccessFlags = 0;
    bd_vertex.MiscFlags = 0;
    bd_vertex.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA data_vertex;
    data_vertex.pSysMem = vertices;
    Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);

    //�C���f�b�N�X���
    int index[] = { 0,2,3, 0,1,2, };

    //�C���f�b�N�X�o�b�t�@�𐶐�����
    D3D11_BUFFER_DESC   bd;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(index);
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = index;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;
    Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);

    //�R���X�^���g�o�b�t�@�쐬
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CONSTANT_BUFFER);
    cb.Usage = D3D11_USAGE_DYNAMIC;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;

    // �R���X�^���g�o�b�t�@�̍쐬
    Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
}

//�V�F�[�_�[�̃R���p�C����
void VisualEffect::ShaderSetup()
{
    // ���_�V�F�[�_�̍쐬�i�R���p�C���j
    ID3DBlob* pCompileVS = nullptr;
    D3DCompileFromFile(L"VFX.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
    assert(pCompileVS != nullptr);
    Direct3D::pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader);
    assert(pVertexShader != nullptr);

    //���_�C���v�b�g���C�A�E�g
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�ʒu
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, sizeof(XMVECTOR), D3D11_INPUT_PER_VERTEX_DATA, 0 },//UV���W

    };
    Direct3D::pDevice->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout);
    SAFE_RELEASE(pCompileVS);;//�ꎞ�I�Ɏg�����ϐ�������



    // �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
    ID3DBlob* pCompilePS = nullptr;
    D3DCompileFromFile(L"VFX.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
    assert(pCompilePS != nullptr);
    Direct3D::pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader);
    pCompilePS->Release();

    //���X�^���C�U�쐬
    D3D11_RASTERIZER_DESC rdc = {};
    rdc.CullMode = D3D11_CULL_BACK;
    rdc.FillMode = D3D11_FILL_SOLID;
    rdc.FrontCounterClockwise = FALSE;
    Direct3D::pDevice->CreateRasterizerState(&rdc, &pRasterizerState);
}

//�g�p����摜�̃��[�h
int VisualEffect::Load(std::string fileName, DWORD width, DWORD height)
{
    //�@�\���̂̃C���X�^���X���쐬�B
    VFXTextureData* pData = new VFXTextureData;

    //�A���̃����o�̃t�@�C�����Ɉ����̓��e����
    pData->fileName = fileName;
    pData->width = width;
    pData->height = height;

    //���łɃ��[�h���Ă��Ȃ������ׂ�
    bool isExit = false;
    for (int i = 0; i < textureDatas.size(); i++)
    {
        if (textureDatas[i]->fileName == fileName)
        {
            pData->pTexture = textureDatas[i]->pTexture;
            isExit = true;
            break;
        }
    }


    if (isExit == false)
    {
        //�BFbx�I�u�W�F�N�g���쐬���A���[�h����
        pData->pTexture = new Texture;
        pData->pTexture->Load(fileName);
    }


    //�C�\���̂̒��g�����܂����̂œ��I�z��ɓ˂�����
    textureDatas.push_back(pData);

    //�D�ԍ��i�z��̗v�f��-1�j��Ԃ�
    return (int)textureDatas.size() - 1;
}


//�G�t�F�N�g��ǉ�
void VisualEffect::Add(int hVfx, Transform transform, float speed, bool isLoop)
{
    VFX* pVFX = new VFX();
    pVFX->Create(textureDatas[hVfx], transform, speed, isLoop);
    vfxs.push_back(pVFX);
}


//�\�����̃G�t�F�N�g�̃A�j���[�V������i�߂�
void VisualEffect::Update()
{
    //�S�G�t�F�N�g���X�V
    for (auto i = vfxs.begin(); i != vfxs.end(); )
    {
        //�X�V
        bool isDestroy = (*i)->Update();

        //�A�j���[�V�������Ō�܂Ŋ�������
        if (isDestroy)
        {
            //���̃G�t�F�N�g���폜
            SAFE_DELETE(*i);
            i = vfxs.erase(i);
        }
        else
        {
            i++;
        }
    }
}


//�S�G�t�F�N�g�̕`��
void VisualEffect::Draw()
{
    //���ꂼ����f�o�C�X�R���e�L�X�g�ɃZ�b�g
    Direct3D::pContext->VSSetShader(pVertexShader, NULL, 0);	//���_�V�F�[�_�[
    Direct3D::pContext->PSSetShader(pPixelShader, NULL, 0);	    //�s�N�Z���V�F�[�_�[
    Direct3D::pContext->IASetInputLayout(pVertexLayout);	    //���_�C���v�b�g���C�A�E�g
    Direct3D::pContext->RSSetState(pRasterizerState);		    //���X�^���C�U�[

    //�S�G�t�F�N�g��`��
    for (auto i = vfxs.begin(); i != vfxs.end(); i++)
    {
        (*i)->Draw();
    }
}


//�������
void VisualEffect::Release()
{
    //��ʂɎc���Ă�G�t�F�N�g��S�폜
    for (auto i = vfxs.begin(); i != vfxs.end(); i++)
    {
        SAFE_DELETE(*i);
    }
    vfxs.clear();

    //���[�h�����摜�����폜
    for (int i = 0; i < textureDatas.size(); i++)
    {
        SAFE_DELETE(textureDatas[i]->pTexture);
    }
    textureDatas.clear();
}

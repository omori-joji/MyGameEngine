#include "Model.h"
#include "Common.h"

namespace Model
{
    std::vector<ModelData*> datas;
}

int Model::Load(std::string fileName)
{
    //�@�\���̂̃C���X�^���X���쐬�B
    ModelData* pData = new ModelData;

    //�A���̃����o�̃t�@�C�����Ɉ����̓��e����
    pData->fileName = fileName;

    //���łɃ��[�h���Ă��Ȃ������ׂ�
    bool isExit = false;
    for (int i = 0; i < datas.size(); i++)
    {
        if (datas[i]->fileName == fileName)
        {
            pData->pFbx = datas[i]->pFbx;
            isExit = true;
            break;
        }
    }


    if (isExit == false)
    {
        //�BFbx�I�u�W�F�N�g���쐬���A���[�h����
        pData->pFbx = new Fbx;
        pData->pFbx->Load(fileName);
    }


    //�C�\���̂̒��g�����܂����̂œ��I�z��ɓ˂�����
    datas.push_back(pData);

    //�D�ԍ��i�z��̗v�f��-1�j��Ԃ�
    return datas.size()-1;
}

void Model::SetTransform(int hModele, Transform transform)
{
    datas[hModele]->transform = transform;
}

void Model::Draw(int hModele)
{
    datas[hModele]->pFbx->Draw(datas[hModele]->transform, 0);
}

void Model::AllRelease()
{
    for (int i = 0; i < datas.size(); i++)
    {
        //����FBX�I�u�W�F�N�g�����Ă������邩�T��
        bool isExit = false;
        for (int j = i+1; j < datas.size(); j++)
        {
            if (datas[i]->fileName == datas[j]->fileName)
            {
                isExit = true;
                break;
            }
        }
        if(isExit == false)
        {
            SAFE_DELETE(datas[i]->pFbx);
        }
    }

    //�Ō�ɔz����폜
    datas.clear();
}

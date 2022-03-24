#pragma once
#include "GameObject.h"
class Rootjob :
    public GameObject
{
public:
    Rootjob();
    ~Rootjob();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void Release() override;
};


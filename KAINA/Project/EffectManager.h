#pragma once

#include	"Effect.h"

//�Ǘ��G�t�F�N�g�̐�
#define		EFFECTCOUNT						10

class CEffectManager {
private:
	//�G�t�F�N�g
	CEffect		m_Effect[EFFECTCOUNT][EFC_TYPECOUNT];
	//�G�t�F�N�g�摜
	CTexture	m_Texture[EFC_TYPECOUNT];

public:
	CEffectManager();
	~CEffectManager();
	bool Load(void);
	void Initialize(void);
	CEffect* Start(float px,float py,int type);
	CEffect* Start(Vector2 p,int type);
	void Stop(int type);
	void Update(void);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
};
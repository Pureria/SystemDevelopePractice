#include "CEnemy_Base.h"

CEnemy_Base::CEnemy_Base() :
m_pTexture(),
m_pEffectManager(),
m_SrcRect(),
m_Motion(),
m_Pos(),
m_Move(),
m_CurrentMove(),
m_bShow(false),
m_bDead(false),
m_bKnockback(false),
m_bReverse(false),
m_bWidthOut(false),
m_Type(),
m_EnemyType(),
m_HP(),
m_DamageWait(),
m_Deffence(),
m_EneTime(),
m_KnockbackTime(),
m_AbState(),
m_AbStateWait(),
m_Color()
{};

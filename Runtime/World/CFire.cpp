#include "CFire.hpp"
#include "Particle/CElementGen.hpp"
#include "CActorParameters.hpp"
#include "CStateManager.hpp"
#include "CPlayer.hpp"
#include "GameGlobalObjects.hpp"
#include "Graphics/CBooRenderer.hpp"
#include "TCastTo.hpp"

namespace urde
{
CFire::CFire(TToken<CGenDescription> effect, TUniqueId uid, TAreaId aId, bool active, TUniqueId owner,
             const zeus::CTransform& xf, const CDamageInfo& dInfo, const zeus::CAABox& aabox, const zeus::CVector3f& vec,
             bool b1, CAssetId visorEffect, bool b2, bool b3, bool b4, float f1, float f2, float f3, float f4)
: CActor(uid, active, "Fire"sv, CEntityInfo(aId, NullConnectionList), xf, CModelData::CModelDataNull(),
         CMaterialList(EMaterialTypes::Projectile), CActorParameters::None(), owner)
 , xe8_(new CElementGen(effect))
 , xec_ownerId(owner)
 , xf0_damageInfo(dInfo)
 , x10c_damageInfo(dInfo)
 , x128_(aabox)
 , x144_(f1)
 , x148_24_(b2)
 , x148_25_(b3)
 , x148_26_(b4)
 , x148_27_(b4 && b3 && b2)
 , x148_28_(false)
 , x148_29_(b1)
 , x14c_(f2)
 , x150_(visorEffect)
 , x154_(f3)
 , x158_(f4)
{
    xe8_->SetGlobalScale(vec);
    xe8_->SetTranslation(xf.origin);
}

void CFire::Accept(IVisitor& visitor)
{
    visitor.Visit(this);
}

void CFire::AcceptScriptMsg(EScriptObjectMessage msg, TUniqueId uid, CStateManager& mgr)
{
    CActor::AcceptScriptMsg(msg, uid, mgr);

    if (msg == EScriptObjectMessage::Registered)
    {
        xe8_->SetParticleEmission(true);
        SetActive(true);
    }
}

void CFire::Think(float dt, CStateManager& mgr)
{
    float particleCount = xe8_->GetParticleCount() / xe8_->GetMaxParticles();
    if (GetActive())
    {
        xe8_->Update(dt * x144_);
        float f0;
        if (particleCount <= 0.5f)
            f0 = 0.5f;
        else
            f0 = particleCount;

        x10c_damageInfo = CDamageInfo(xf0_damageInfo, dt * f0);
    }

    bool doFree = false;
    if (xe8_->IsSystemDeletable())
        doFree = true;

    if (x148_29_)
    {
        auto playerBounds = mgr.GetPlayer().GetTouchBounds();
        auto bounds = GetTouchBounds();
        if (playerBounds->intersects(*bounds) && doFree && particleCount > 0.5f)
            mgr.GetPlayer().SetVisorSteam(particleCount * x14c_, x154_, x158_, x150_, true);
        else
            mgr.GetPlayer().SetVisorSteam(0.f, 1.f, 1.f, {}, true);
    }

    x15c_ += dt;

    if (x15c_ > 45.f)
        doFree = true;

    if (doFree)
        mgr.FreeScriptObject(GetUniqueId());
}

void CFire::Touch(CActor& act, CStateManager& mgr)
{
    if (act.GetUniqueId() == xec_ownerId)
        return;

    mgr.ApplyDamage(GetUniqueId(), act.GetUniqueId(), GetUniqueId(), x10c_damageInfo,
                    CMaterialFilter::MakeIncludeExclude({EMaterialTypes::Solid}, {}), {});
}

void CFire::AddToRenderer(const zeus::CFrustum& frustum, const CStateManager& mgr) const
{
    printf("AddToRenderer\n");
    bool r31 = true;
    if (!x148_27_)
    {
        using EPlayerVisor = CPlayerState::EPlayerVisor;
        CPlayerState::EPlayerVisor visor = mgr.GetPlayerState()->GetActiveVisor(mgr);
        if (visor == EPlayerVisor::Combat || visor == EPlayerVisor::Scan)
            r31 = x148_24_;
        else if (visor == EPlayerVisor::XRay)
            r31 = x148_26_;
        else if (visor == EPlayerVisor::Thermal)
            r31 = x148_25_;
    }

    if (r31)
        g_Renderer->AddParticleGen(*xe8_);
    CActor::AddToRenderer(frustum, mgr);
}

}
#ifndef __URDE_CPLAYER_HPP__
#define __URDE_CPLAYER_HPP__

#include "CPhysicsActor.hpp"
#include "zeus/CAABox.hpp"
#include "zeus/CTransform.hpp"
#include "Weapon/CWeaponMgr.hpp"
#include "CPlayerEnergyDrain.hpp"
#include "Weapon/CPlayerGun.hpp"
#include "CMorphBall.hpp"

namespace urde
{
class CMaterialList;
class CMorphBall;
class CPlayerGun;
class CDamageInfo;
class CScriptWater;
class IVisitor;
class CFinalInput;
class CPlayerCameraBob;
class CFirstPersonCamera;

class CPlayer : public CPhysicsActor
{
    friend class CStateManager;
    friend class CFirstPersonCamera;
    friend class CPlayerCameraBob;
    friend class CMorphBall;

public:
    enum class EPlayerScanState
    {
        NotScanning,
        Scanning,
        ScanComplete
    };
    enum class EPlayerOrbitType
    {
    };
    enum class EPlayerOrbitState
    {
        Zero,
        One,
        Two,
        Three,
        Four,
        Five
    };
    enum class EPlayerZoneInfo
    {
    };
    enum class EPlayerZoneType
    {
    };
    enum class EPlayerMovementState
    {
    };

    enum class EPlayerMorphBallState
    {
        Unmorphed,
        Morphed,
        Morphing,
        Unmorphing
    };

    enum class EPlayerCameraState
    {
        Zero,
        One,
        Two,
        Three,
        Four
    };

private:
    struct CVisorSteam
    {
        float x0_;
        float x4_;
        float x8_;
        ResId xc_tex;
        float x10_ = 0.f;
        float x14_ = 0.f;
        float x18_ = 0.f;
        ResId x1c_ = -1;
        float x20_alpha = 0.f;
        float x24_ = 0.f;
        bool x28_ = false;

    public:
        CVisorSteam(float a, float b, float c, ResId tex) : x0_(a), x4_(b), x8_(c), xc_tex(tex) {}
        ResId GetTextureId() const;
        void SetSteam(float a, float b, float c, ResId d, bool e);
        void Update(float dt);
        float GetAlpha() const { return x20_alpha; }
    };
    zeus::CVector3f x1b4_;
    TUniqueId x1c4_ = kInvalidUniqueId;
    u32 x258_jumpState = 0;
    TUniqueId x26c_ = kInvalidUniqueId;
    float x270_ = 0.f;
    CPlayerEnergyDrain x274_energyDrain = CPlayerEnergyDrain(4);
    float x288_ = 0.f;
    float x28c_sjTimer = 0.f;
    float x290_ = 0.f;
    float x294_ = 0.f;
    u32 x298_ = 0;
    float x29c_ = 0.f;
    float x2a0_ = 0.f;
    u8 x2a4_ = 0;
    float x2a8_ = 1000.f;
    u32 x2ac_ = 0;
    u32 x2b0_ = 2;
    u32 x2b4_ = 0;
    u32 x2d0_ = 3;
    float x2d4_ = 0.f;
    zeus::CAABox x2d8_;
    float x2f0_ = 0.f;
    EPlayerCameraState x2f4_cameraState = EPlayerCameraState::Zero;
    EPlayerMorphBallState x2f8_morphTransState = EPlayerMorphBallState::Unmorphed;
    u32 x2fc_ = 0;
    float x300_ = 0.f;
    EPlayerOrbitState x304_orbitState = EPlayerOrbitState::Zero;
    u32 x308_ = 0;
    u32 x30c_ = 0;
    TUniqueId x310_lockonObjectId = kInvalidUniqueId;
    float x314_ = 0.f;
    float x318_ = 0.f;
    float x31c_ = 0.f;
    float x320_ = 0.f;
    float x324_ = 0.f;
    float x328_ = 0.f;
    float x32c_ = 0.f;
    u32 x330_ = 0;
    u32 x334_ = 1;
    u32 x338_ = 1;
    TUniqueId x33c_ = kInvalidUniqueId;
    float x340_ = 0.f;
    // std::vector<> x344_;
    // std::vector<> x354_;
    // std::vector<> x364_;
    bool x374_ = false;
    float x378_ = 0.f;
    u8 x37c_ = 0;
    float x380_ = 0.f;
    float x384_ = 0.f;
    float x388_ = 0.f;
    bool x38c_ = false;
    u32 x390_ = 2;
    u8 x394_ = 0;
    float x398_ = 1.5f;
    u8 x39c_ = 0;
    float x3a0_ = 0.5f;
    float x3a4_ = 0.449f;
    EPlayerScanState x3a8_scanState = EPlayerScanState::NotScanning;
    float x3ac_scanningTime = 0.f;
    float x3b0_ = 0.f;
    TUniqueId x3b4_scanningObject = kInvalidUniqueId;
    u32 x3b8_ = 0;
    float x3bc_ = 0.f;
    float x3c0_ = 1.0f;
    float x3c4_ = 0.f;
    float x3c8_ = 0.f;
    float x3cc_ = 0.f;
    float x3d0_ = 0.f;
    float x3d4_ = 0.f;
    float x3d8_ = 0.f;
    bool x3dc_inFreeLook = 0;
    bool x3dd_ = 0;
    bool x3de_lookControlHeld = 0;
    float x3e4_ = 0.f;
    float x3e8_ = 0.f;
    float x3ec_ = 0.f;
    float x3f0_ = 0.f;
    TUniqueId x3f4_ = kInvalidUniqueId;
    zeus::CVector3f x3f8_ = zeus::CVector3f::skZero;
    TReservedAverage<zeus::CVector3f, 20> x404_;
    zeus::CVector3f x480_ = zeus::CVector3f::skZero;
    float x48c_ = 0.f;
    std::unique_ptr<CPlayerGun> x490_gun;
    float x494_mapAlpha = 1.f;
    float x49c_; /* Value retrieved from TweakPlayerGun */
    // std::unqiue_ptr<> x4a0_;
    u32 x4a4_ = 0;
    float x4f8_ = 0.f;
    float x4fc_ = 0.f;
    float x53c_ = 0.f;
    bool x558_ = false;
    float x55c_ = 0.f;
    float x560_ = 0.f;
    zeus::CVector3f x564_;
    float x570_ = 0.f;
    float x574_morphTime = 0.f;
    float x578_morphDuration = 0.f;
    u32 x57c_ = 0;
    u32 x580_ = 0;
    float x588_alpha = 1.f;
    u32 x594_ = 0;
    u32 x658_ = 0;
    u32 x71c_ = 0;
    u32 x734_ = 0;
    u32 x738_ = 0;
    u32 x73c_ = 0;
    float x740_ = 0.f;
    float x744_ = 0.f;
    float x748_ = 0.f;
    float x74c_visorStaticAlpha = 1.f;
    float x750_ = 0.f;
    u32 x754_ = 0;
    float x758_ = 0.f;
    u32 x75c_ = 0;
    u32 x760_ = 0;
    float x764_ = 0.f;
    std::unique_ptr<CMorphBall> x768_morphball;
    std::unique_ptr<CPlayerCameraBob> x76c_cameraBob;
    CSfxHandle x770_;
    float x774_ = 0.f;
    u32 x778_ = 0;
    u32 x77c_ = 0;
    u32 x780_ = 0;
    float x784_ = 0.f;
    u16 x788_ = 0;
    float x78c_ = 0.f;
    u32 x790_ = 0;
    zeus::CVector3f x794_;
    CVisorSteam x7a0_visorSteam = CVisorSteam(0.f, 0.f, 0.f, -1);
    ResId x7cc_ = -1;
    CAnimRes x7d0_animRes;
    CPlayerState::EBeamId x7ec_ = CPlayerState::EBeamId::Power;
    std::unique_ptr<CModelData> x7f0_ballTransitionBeamModel;
    zeus::CTransform x7f4_;
    float x824_ = 0.f;
    float x828_ = 0.f;
    bool x82c_ = false;
    TUniqueId x82e_ = kInvalidUniqueId;
    TUniqueId x830_ = kInvalidUniqueId;
    u32 x834_ = 1000;
    u32 x838_ = 0;
    u32 x93c_ = 0;
    u32 x980_ = 0;

    union
    {
        struct
        {
            bool x9c4_24_ : 1;
            bool x9c4_25_ : 1;
            bool x9c4_26_ : 1;
            bool x9c4_27_ : 1;
            bool x9c4_28_ : 1;
            bool x9c4_29_ : 1;
            bool x9c4_30_ : 1;
            bool x9c4_31_ : 1;
            bool x9c5_24_ : 1;
            bool x9c5_25_ : 1;
            bool x9c5_26_ : 1;
            bool x9c5_27_ : 1;
            bool x9c5_28_ : 1;
            bool x9c5_29_ : 1;
            bool x9c5_30_ : 1;
            bool x9c5_31_ : 1;
            bool x9c6_24_ : 1;
            bool x9c6_25_ : 1;
            bool x9c6_26_ : 1;
            bool x9c6_27_ : 1;
            bool x9c6_28_ : 1;
            bool x9c6_29_disableInput : 1;
            bool x9c6_30_newScanScanning : 1;
            bool x9c6_31_overrideRadarRadius : 1;
            bool x9c7_24_ : 1;
            bool x9c7_25_ : 1;
        };
        u32 _dummy = 0;
    };

    float x9c8_ = 0.f;
    float x9cc_ = 0.f;
    u32 x9d0_ = 0;
    u32 x9d4_ = 0;
    float x9d8_ = 0.f;
    float x9dc_ = 1.f;
    float x9e0_ = 0.f;
    u32 x9e4_ = 0;

    float x9f4_deathTime = 0.f;
    float x9f8_ = 0.f;
    float x9fc_ = 0.f;
    TUniqueId xa00_ = kInvalidUniqueId;
    float xa04_ = 0.f;
    ResId xa08_steamTextureId = -1;
    ResId xa0c_;
    u32 xa10_ = 0;
    float xa14_ = 0.f;
    float xa18_ = 0.f;
    float xa1c_threatOverride = 0.f;
    float xa20_radarXYRadiusOverride = 1.f;
    float xa24_radarZRadiusOverride = 1.f;
    float xa28_ = 0.f;
    u32 xa2c_ = 2;
    float xa30_ = 4.f;

public:
    CPlayer(TUniqueId, const zeus::CTransform&, const zeus::CAABox&, unsigned int w1, const zeus::CVector3f&, float, float,
            float, float, const CMaterialList&);

    bool IsTransparent() const;
    void Update(float, CStateManager& mgr);
    bool IsPlayerDeadEnough() const;
    void AsyncLoadSuit(CStateManager& mgr);
    void LoadAnimationTokens();
    virtual bool CanRenderUnsorted(CStateManager& mgr) const;
    virtual const CDamageVulnerability* GetDamageVulnerability(const zeus::CVector3f& v1, const zeus::CVector3f& v2,
                                                               const CDamageInfo& info) const;
    virtual const CDamageVulnerability* GetDamageVulnerability() const;
    virtual zeus::CVector3f GetHomingPosition(CStateManager& mgr, float) const;
    zeus::CVector3f GetAimPosition(CStateManager& mgr, float) const;
    virtual void FluidFXThink(CActor::EFluidState, CScriptWater& water, CStateManager& mgr);
    zeus::CVector3f GetDamageLocationWR() const;
    float GetPrevDamageAmount() const;
    float GetDamageAmount() const;
    bool WasDamaged() const;
    void TakeDamage(bool, const zeus::CVector3f&, float, EWeaponType, CStateManager& mgr);
    void Accept(IVisitor& visitor);
    static CHealthInfo* HealthInfo(const CStateManager& mgr);
    bool IsUnderBetaMetroidAttack(CStateManager& mgr) const;
    rstl::optional_object<zeus::CAABox> GetTouchBounds() const;
    void Touch(CActor&, CStateManager& mgr);
    void DoPreThink(float dt, CStateManager& mgr);
    void DoThink(float dt, CStateManager& mgr);
    void UpdateScanningState(const CFinalInput& input, CStateManager& mgr, float);
    void ValidateScanning(const CFinalInput& input, CStateManager& mgr);
    void SetScanningState(EPlayerScanState, CStateManager& mgr);
    void SetSpawnedMorphBallState(EPlayerMorphBallState, CStateManager&);
    bool GetExplorationMode() const;
    bool GetCombatMode() const;
    void RenderGun(const CStateManager& mgr, const zeus::CVector3f&) const;
    void Render(const CStateManager& mgr) const;
    void RenderReflectedPlayer(CStateManager& mgr) const;
    void PreRender(CStateManager& mgr, const zeus::CFrustum&);
    void CalculateRenderBounds();
    void AddToRenderer(const zeus::CFrustum&, const CStateManager&);
    void ComputeFreeLook(const CFinalInput& input);
    void UpdateFreeLook(float dt);
    float GetMaximumPlayerPositiveVerticalVelocity(CStateManager&) const;
    void ProcessInput(const CFinalInput&, CStateManager&);
    void Stop(CStateManager& stateMgr);
    bool GetFrozenState() const;
    void Think(float, CStateManager&);
    void PreThink(float, CStateManager&);
    void AcceptScriptMsg(EScriptObjectMessage, TUniqueId, CStateManager&);
    void SetVisorSteam(float, float, float, u32, bool);
    void UpdateFootstepBounds(const CFinalInput& input, CStateManager&, float);
    u16 GetMaterialSoundUnderPlayer(CStateManager& mgr, const u16*, int, u16);
    u16 SfxIdFromMaterial(const CMaterialList&, const u16*, u32, u16);
    void UpdateCrosshairsState(const CFinalInput&);
    void UpdateVisorTransition(float, CStateManager& mgr);
    void UpdateVisorState(const CFinalInput&, float, CStateManager& mgr);
    void ForceGunOrientation(const zeus::CTransform&, CStateManager& mgr);
    void UpdateDebugCamera(CStateManager& mgr);
    CFirstPersonCamera& GetFirstPersonCamera(CStateManager& mgr);
    void UpdateGunTransform(const zeus::CVector3f&, float, CStateManager& mgr, bool);
    void DrawGun(CStateManager& mgr);
    void HolsterGun(CStateManager& mgr);
    EPlayerCameraState GetCameraState() const { return x2f4_cameraState; }
    EPlayerMorphBallState GetMorphballTransitionState() const { return x2f8_morphTransState; }
    void UpdateGrappleArmTransform(const zeus::CVector3f&, CStateManager& mgr, float);
    void ApplyGrappleForces(const CFinalInput& input, CStateManager& mgr, float);
    bool ValidateFPPosition(const zeus::CVector3f& pos, CStateManager& mgr);
    void UpdateGrappleState(const CFinalInput& input, CStateManager& mgr);
    void ApplyGrappleJump(CStateManager& mgr);
    void BeginGrapple(zeus::CVector3f&, CStateManager& mgr);
    void BreakGrapple(CStateManager& mgr);
    void PreventFallingCameraPitch();
    void OrbitCarcass(CStateManager&);
    void OrbitPoint(EPlayerOrbitType, CStateManager& mgr);
    zeus::CVector3f GetHUDOrbitTargetPosition() const;
    void SetOrbitState(EPlayerOrbitState, CStateManager& mgr);
    void SetOrbitTargetId(TUniqueId);
    void UpdateOrbitPosition(float, CStateManager& mgr);
    void UpdateOrbitZPosition();
    void UpdateOrbitFixedPosition();
    void SetOrbitPosition(float, CStateManager& mgr);
    void UpdateAimTarget(CStateManager& mgr);
    void UpdateAimTargetTimer(float);
    bool ValidateAimTargetId(TUniqueId, CStateManager& mgr);
    bool ValidateObjectForMode(TUniqueId, CStateManager& mgr) const;
    TUniqueId FindAimTargetId(CStateManager& mgr);
    TUniqueId CheckEnemiesAgainstOrbitZone(const std::vector<TUniqueId>&, EPlayerZoneInfo, EPlayerZoneType,
                                           CStateManager& mgr) const;
    TUniqueId FindOrbitTargetId(CStateManager& mgr);
    void UpdateOrbitableObjects(CStateManager& mgr);
    TUniqueId FindBestOrbitableObject(const std::vector<TUniqueId>&, EPlayerZoneInfo, CStateManager& mgr) const;
    void FindOrbitableObjects(const std::vector<TUniqueId>&, std::vector<TUniqueId>&, EPlayerZoneInfo, EPlayerZoneType,
                              CStateManager& mgr, bool) const;
    bool WithinOrbitScreenBox(const zeus::CVector3f&, EPlayerZoneInfo, EPlayerZoneType) const;
    bool WithinOrbitScreenEllipse(const zeus::CVector3f&, EPlayerZoneInfo) const;
    void CheckOrbitDisableSourceList(CStateManager& mgr);
    void CheckOrbitDisableSourceList() const;
    void RemoveOrbitDisableSource(TUniqueId);
    void AddOrbitDisableSource(CStateManager& mgr, TUniqueId);
    void UpdateOrbitPreventionTimer(float);
    void UpdateOrbitModeTimer(float);
    void UpdateOrbitZone(CStateManager& mgr);
    void UpdateOrbitInput(const CFinalInput& input, CStateManager& mgr);
    void UpdateOrbitSelection(const CFinalInput& input, CStateManager& mgr);
    void UpdateOrbitOrientation(CStateManager& mgr);
    void UpdateOrbitTarget(CStateManager& mgr);
    float GetOrbitMaxLockDistance(CStateManager& mgr) const;
    float GetOrbitMaxTargetDistance(CStateManager& mgr) const;
    bool ValidateOrbitTargetId(TUniqueId, CStateManager& mgr) const;
    bool ValidateCurrentOrbitTargetId(CStateManager& mgr);
    bool ValidateOrbitTargetIdAndPointer(TUniqueId, CStateManager& mgr) const;
    zeus::CVector3f GetBallPosition() const;
    zeus::CVector3f GetEyePosition() const;
    float GetEyeHeight() const;
    float GetStepUpHeight() const;
    float GetStepDownHeight() const;
    void Teleport(const zeus::CTransform& xf, CStateManager& mgr, bool);
    void BombJump(const zeus::CVector3f& pos, CStateManager& mgr);
    zeus::CTransform CreateTransformFromMovementDirection() const;
    const CCollisionPrimitive* GetCollisionPrimitive() const;
    zeus::CTransform GetPrimitiveTransform() const;
    bool CollidedWith(TUniqueId, const CCollisionInfoList&, CStateManager& mgr);
    float GetActualFirstPersonMaxVelocity() const;
    void SetMoveState(EPlayerMovementState, CStateManager& mgr);
    float JumpInput(const CFinalInput& input, CStateManager& mgr);
    float TurnInput(const CFinalInput& input) const;
    float StrafeInput(const CFinalInput& input) const;
    float ForwardInput(const CFinalInput& input, float) const;
    void ComputeMovement(const CFinalInput& input, CStateManager& mgr, float);
    float GetWeight() const;
    float GetDampedClampedVelocityWR() const;
    const CVisorSteam& GetVisorSteam() const { return x7a0_visorSteam; }
    float GetVisorStaticAlpha() const { return x74c_visorStaticAlpha; }
    float GetMapAlpha() const { return x494_mapAlpha; }
    void UpdateCinematicState(CStateManager& mgr);
    void SetCameraState(EPlayerCameraState camState, CStateManager& stateMgr);
    bool IsEnergyLow(const CStateManager& mgr) const;
    EPlayerOrbitState GetOrbitState() const { return x304_orbitState; }
    EPlayerScanState GetScanningState() const { return x3a8_scanState; }
    float GetScanningTime() const { return x3ac_scanningTime; }
    TUniqueId GetLockonObjectId() const { return x310_lockonObjectId; }
    TUniqueId GetScanningObjectId() const { return x3b4_scanningObject; }
    bool IsNewScanScanning() const { return x9c6_30_newScanScanning; }
    float GetThreatOverride() const { return xa1c_threatOverride; }
    bool IsOverrideRadarRadius() const { return x9c6_31_overrideRadarRadius; }
    float GetRadarXYRadiusOverride() const { return xa20_radarXYRadiusOverride; }
    float GetRadarZRadiusOverride() const { return xa24_radarZRadiusOverride; }
    bool ObjectInScanningRange(TUniqueId id, const CStateManager& mgr) const;
    float GetMorphTime() const { return x574_morphTime; }
    float GetMorphDuration() const { return x578_morphDuration; }
    bool IsInFreeLook() const { return x3dc_inFreeLook; }
    bool IsLookControlHeld() const { return x3de_lookControlHeld; }
    CPlayerGun* GetPlayerGun() const { return x490_gun.get(); }
    CMorphBall* GetMorphBall() const { return x768_morphball.get(); }
    CPlayerCameraBob* GetCameraBob() const { return x76c_cameraBob.get(); }
    float GetDeathTime() const { return x9f4_deathTime; }
    const CPlayerEnergyDrain& GetEnergyDrain() const { return x274_energyDrain; }

    void Touch();

    void DecrementPhazon();
    void IncrementPhazon();
};
}

#endif // __URDE_CPLAYER_HPP__

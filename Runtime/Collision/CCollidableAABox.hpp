#ifndef __URDE_CCOLLIDABLEAABOX_HPP__
#define __URDE_CCOLLIDABLEAABOX_HPP__

#include "CCollisionPrimitive.hpp"

namespace urde
{
namespace Collide
{
bool AABox_AABox(const CInternalCollisionStructure&, CCollisionInfoList&);
bool AABox_AABox_Bool(const CInternalCollisionStructure&, CCollisionInfoList&);
}

class CCollidableAABox : public CCollisionPrimitive
{
    static const Type sType;
    static u32 sTableIndex;

    zeus::CAABox x10_aabox;
public:
    CCollidableAABox();

    zeus::CAABox Transform(const zeus::CTransform&) const;
    virtual u32 GetTableIndex() const;
    virtual zeus::CAABox CalculateAABox(const zeus::CTransform&) const;
    virtual zeus::CAABox CalculateLocalAABox() const;
    virtual FourCC GetPrimType() const;
    virtual CRayCastResult CastRayInternal(const CInternalRayCastStructure&) const;

    static const CCollisionPrimitive::Type& GetType();
    static void SetStaticTableIndex(u32 index);
};
}

#endif // __URDE_CCOLLIDABLEAABOX_HPP__

#pragma once

#include "../../DNACommon/DNACommon.hpp"
#include "IScriptObject.hpp"
#include "Parameters.hpp"

namespace DataSpec::DNAMP1 {
struct Trigger : IScriptObject {
  AT_DECL_DNA_YAMLV
  String<-1> name;
  Value<atVec3f> location;
  Value<atVec3f> volume;
  DamageInfo damageInfo;
  Value<atVec3f> force;
  Value<atUint32> flags;
  Value<bool> active;
  Value<bool> deactivateOnEntered;
  Value<bool> deactivateOnExited;

  zeus::CAABox getVISIAABB(hecl::blender::Token& btok) const override {
    zeus::CVector3f halfExtent = zeus::CVector3f(volume) / 2.f;
    zeus::CVector3f loc(location);
    return zeus::CAABox(loc - halfExtent, loc + halfExtent);
  }
};
} // namespace DataSpec::DNAMP1

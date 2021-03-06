#include "Runtime/Particle/CColorElement.hpp"

#include "Runtime/CRandom16.hpp"
#include "Runtime/Particle/CElementGen.hpp"
#include "Runtime/Particle/CGenDescription.hpp"
#include "Runtime/Particle/CParticleGlobals.hpp"

#include <zeus/Math.hpp>

/* Documentation at: https://wiki.axiodl.com/w/Particle_Script#Color_Elements */

namespace urde {

CCEKeyframeEmitter::CCEKeyframeEmitter(CInputStream& in) {
  x4_percent = in.readUint32Big();
  x8_unk1 = in.readUint32Big();
  xc_loop = in.readBool();
  xd_unk2 = in.readBool();
  x10_loopEnd = in.readUint32Big();
  x14_loopStart = in.readUint32Big();

  u32 count = in.readUint32Big();
  x18_keys.reserve(count);
  for (u32 i = 0; i < count; ++i)
    x18_keys.push_back(in.readVec4fBig());
}

bool CCEKeyframeEmitter::GetValue(int frame, zeus::CColor& valOut) const {
  if (!x4_percent) {
    int emitterTime = CParticleGlobals::instance()->m_EmitterTime;
    int calcKey = emitterTime;
    if (xc_loop) {
      if (emitterTime >= x10_loopEnd) {
        int v1 = emitterTime - x14_loopStart;
        int v2 = x10_loopEnd - x14_loopStart;
        calcKey = v1 % v2;
        calcKey += x14_loopStart;
      }
    } else {
      int v1 = x10_loopEnd - 1;
      if (v1 < emitterTime)
        calcKey = v1;
    }
    valOut = x18_keys[calcKey];
  } else {
    int ltPerc = CParticleGlobals::instance()->m_ParticleLifetimePercentage;
    float ltPercRem = CParticleGlobals::instance()->m_ParticleLifetimePercentageRemainder;
    if (ltPerc == 100)
      valOut = x18_keys[100];
    else
      valOut = ltPercRem * x18_keys[ltPerc + 1] + (1.0f - ltPercRem) * x18_keys[ltPerc];
  }
  return false;
}

bool CCEConstant::GetValue(int frame, zeus::CColor& valOut) const {
  float r, g, b, a;
  x4_r->GetValue(frame, r);
  x8_g->GetValue(frame, g);
  xc_b->GetValue(frame, b);
  x10_a->GetValue(frame, a);
  valOut = zeus::CColor(r, g, b, a);
  return false;
}

bool CCEFastConstant::GetValue(int frame, zeus::CColor& valOut) const {
  valOut = x4_val;
  return false;
}

bool CCETimeChain::GetValue(int frame, zeus::CColor& valOut) const {
  int v;
  xc_swFrame->GetValue(frame, v);
  if (frame >= v)
    return x8_b->GetValue(frame, valOut);
  else
    return x4_a->GetValue(frame, valOut);
}

bool CCEFadeEnd::GetValue(int frame, zeus::CColor& valOut) const {
  float c;
  xc_startFrame->GetValue(frame, c);

  if (frame < c) {
    x4_a->GetValue(frame, valOut);
    return false;
  }

  float d;
  x10_endFrame->GetValue(frame, d);

  zeus::CColor colA;
  zeus::CColor colB;
  x4_a->GetValue(frame, colA);
  x8_b->GetValue(frame, colB);

  float t = (frame - c) / (d - c);
  valOut = zeus::CColor::lerp(colA, colB, t);
  return false;
}

bool CCEFade::GetValue(int frame, zeus::CColor& valOut) const {
  float c;
  xc_endFrame->GetValue(frame, c);

  float t = frame / c;
  if (t > 1.f) {
    x8_b->GetValue(frame, valOut);
    return false;
  }

  zeus::CColor colA;
  zeus::CColor colB;
  x4_a->GetValue(frame, colA);
  x8_b->GetValue(frame, colB);

  valOut = zeus::CColor::lerp(colA, colB, t);
  return false;
}

bool CCEPulse::GetValue(int frame, zeus::CColor& valOut) const {
  int a, b;
  x4_aDuration->GetValue(frame, a);
  x8_bDuration->GetValue(frame, b);
  int cv = zeus::max(1, a + b + 1);

  if (b >= 1) {
    int cv2 = frame % cv;
    if (cv2 >= a)
      x10_bVal->GetValue(frame, valOut);
    else
      xc_aVal->GetValue(frame, valOut);
  } else
    xc_aVal->GetValue(frame, valOut);

  return false;
}

bool CCEParticleColor::GetValue(int /*frame*/, zeus::CColor& colorOut) const {
  colorOut = CElementGen::g_currentParticle->x34_color;
  return false;
}

} // namespace urde

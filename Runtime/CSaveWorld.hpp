#pragma once

#include <vector>

#include "DNACommon/SAVWCommon.hpp"

#include "Runtime/CFactoryMgr.hpp"
#include "Runtime/RetroTypes.hpp"

namespace urde {

class CSaveWorld {
public:
  using EScanCategory = DataSpec::SAVWCommon::EScanCategory;
  struct SScanState {
    CAssetId x0_id;
    EScanCategory x4_category;
  };

  struct SLayerState {
    TAreaId x0_area;
    u32 x4_layer;
  };

private:
  u32 x0_areaCount;
  std::vector<TEditorId> x4_cinematics;
  std::vector<TEditorId> x14_relays;
  std::vector<SLayerState> x24_layers;
  std::vector<TEditorId> x34_doors;
  std::vector<SScanState> x44_scans;

public:
  CSaveWorld(CInputStream& in);
  u32 GetAreaCount() const;
  u32 GetCinematicCount() const;
  s32 GetCinematicIndex(const TEditorId& id) const;
  const std::vector<TEditorId>& GetCinematics() const { return x4_cinematics; }
  const std::vector<TEditorId>& GetDoors() const { return x34_doors; }
  const std::vector<SScanState>& GetScans() const { return x44_scans; }
  u32 GetRelayCount() const;
  s32 GetRelayIndex(const TEditorId& id) const;
  TEditorId GetRelayEditorId(u32 idx) const;
  u32 GetDoorCount() const;
  s32 GetDoorIndex(const TEditorId& id) const;
};

CFactoryFnReturn FSaveWorldFactory(const SObjectTag& tag, CInputStream& in, const CVParamTransfer& param,
                                   CObjectReference* selfRef);

} // namespace urde

#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "IControls.h"

const int kNumPresets = 1;

enum EParams
{
  kParamDummy = 0,
  kNumParams
};

using namespace iplug;
using namespace igraphics;

class ChordRecogniser final : public Plugin
{
public:
  ChordRecogniser(const InstanceInfo& info);
};

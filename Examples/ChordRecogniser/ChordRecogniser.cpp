#include "ChordRecogniser.h"
#include "IPlug_include_in_plug_src.h"
#include "LFO.h"

ChordRecogniser::ChordRecogniser(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
    mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
    };
    mLayoutFunc = [&](IGraphics* pGraphics) {
        // background.
        pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
        pGraphics->AttachPanelBackground(COLOR_GRAY);
        pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
        
        // bounds for keyboard/chord.
        const IRECT b = pGraphics->GetBounds().GetPadded(-20.f);
        IRECT keyboardBounds = b.GetFromBottom(300);
        IRECT chordBounds = b.GetFromTop(300);
        
        // create and attach controls for keyboard/chord.
        auto keyboardControl = new IVKeyboardControl(keyboardBounds,24,96);
        auto chordControl = new IChordTextControl(chordBounds,"No chord",IText(50));
        pGraphics->AttachControl(keyboardControl);
        pGraphics->AttachControl(chordControl);
    };
}

#ifndef __URDE_CPAUSESCREENBASE_HPP__
#define __URDE_CPAUSESCREENBASE_HPP__

#include "RetroTypes.hpp"
#include "zeus/CVector3f.hpp"
#include "GuiSys/CGuiFrame.hpp"

namespace urde
{
class CStateManager;
class CGuiWidget;
class CGuiTableGroup;
class CGuiModel;
class CGuiTextPane;
class CGuiSliderGroup;
class CAuiImagePane;
class CStringTable;
namespace MP1
{

class CPauseScreenBase
{
    const CStateManager& x4_mgr;
    const CGuiFrame& x8_frame;
    const CStringTable& xc_pauseStrg;
    ResId x10_ = -1;
    float x14_ = 0.f;
    u32 x18_ = 0;
    u32 x1c_ = 0;
    zeus::CVector3f x20_;
    zeus::CVector3f x2c_;
    float x38_ = 0.f;
    zeus::CVector3f x3c_;
    zeus::CVector3f x48_;
    zeus::CVector3f x54_;
    CGuiWidget* x60_basewidget_pivot;
    CGuiWidget* x64_basewidget_bgframe;
    CGuiWidget* x68_basewidget_leftside = nullptr;
    CGuiWidget* x6c_basewidget_leftlog = nullptr;
    CGuiTableGroup* x70_tablegroup_leftlog = nullptr;
    CGuiWidget* x74_basewidget_leftguages = nullptr;
    CGuiModel* x78_model_lefthighlight = nullptr;
    CGuiWidget* x7c_basewidget_rightside = nullptr;
    CGuiWidget* x80_basewidget_rightlog = nullptr;
    CGuiTableGroup* x84_tablegroup_rightlog = nullptr;
    CGuiWidget* x88_basewidget_rightguages = nullptr;
    CGuiModel* x8c_model_righthighlight = nullptr;
    CGuiModel* x90_model_textarrowtop;
    CGuiModel* x94_model_textarrowbottom;
    CGuiModel* x98_model_scrollleftup;
    CGuiModel* x9c_model_scrollleftdown;
    CGuiModel* xa0_model_scrollrightup;
    CGuiModel* xa4_model_scrollrightdown;
    rstl::reserved_vector<CGuiTextPane*, 5> xa8_textpane_categories;
    rstl::reserved_vector<CGuiModel*, 5> xc0_model_categories;
    rstl::reserved_vector<CGuiTextPane*, 5> xd8_textpane_titles;
    rstl::reserved_vector<CAuiImagePane*, 20> xf0_imagePanes;
    rstl::reserved_vector<CGuiModel*, 5> x144_model_titles;
    rstl::reserved_vector<CGuiModel*, 5> x15c_model_righttitledecos;
    CGuiTextPane* x174_textpane_body = nullptr;
    CGuiTextPane* x178_textpane_title = nullptr;
    CGuiModel* x17c_model_textalpha;
    CGuiWidget* x180_basewidget_yicon = nullptr;
    CGuiTextPane* x184_textpane_yicon = nullptr;
    CGuiTextPane* x188_textpane_ytext = nullptr;
    CGuiSliderGroup* x18c_slidergroup_slider = nullptr;
    CGuiTableGroup* x190_tablegroup_double = nullptr;
    CGuiTableGroup* x194_tablegroup_triple = nullptr;
    union
    {
        struct
        {
            bool x198_24_ : 1;
            bool x198_25_ : 1;
            bool x198_26_ : 1;
            bool x198_27_ : 1;
            bool x198_28_ : 1;
            bool x198_29_ : 1;
        };
        u32 _dummy = 0;
    };
    void InitializeFrameGlue();
    static std::string GetImagePaneName(u32 i);
public:
    CPauseScreenBase(const CStateManager& mgr, const CGuiFrame& frame, const CStringTable& pauseStrg);
};

}
}

#endif // __URDE_CPAUSESCREENBASE_HPP__
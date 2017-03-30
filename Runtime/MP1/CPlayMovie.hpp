#ifndef __URDE_CPLAYMOVIE_HPP__
#define __URDE_CPLAYMOVIE_HPP__

#include "CPlayMovieBase.hpp"
#include "RetroTypes.hpp"

namespace urde
{
namespace MP1
{

class CPlayMovie : public CPlayMovieBase
{
public:
    enum class EWhichMovie
    {
        WinGameBad,
        WinGameGood,
        WinGameBest,
        LoseGame,
        TalonTest,
        AfterCredits,
        SpecialEnding,
        CreditBG
    };
private:
    EWhichMovie x18_which;
    union
    {
        struct
        {
            bool x78_24_ : 1;
            bool x78_25_ : 1;
            bool x78_26_resultsScreen : 1;
            bool x78_27_ : 1;
        };
        u16 _dummy = 0;
    };
    static bool IsResultsScreen(EWhichMovie which);
public:
    CPlayMovie(EWhichMovie which);
};

}
}

#endif // __URDE_CPLAYMOVIE_HPP__

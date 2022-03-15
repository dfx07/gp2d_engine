#include "xintlib.h"

namespace fox
{

    void Z2cutLA(Ap2D xap, Ap2D* outXap, BOOL isCCW)
    {
        *outXap = xap;
        //Z2sortA(*outXap, isCCW);
    }

    FLT Z2disPPV(Vec2D p, Vec2D v, Vec2D pc)
    {
        return(v.x * (pc.x - p.x) + v.y * (pc.y - p.y));
    }
}

#include "xbase.h"


namespace fox
{
    namespace structsp
    {
        namespace operafake
        {
            bool operator>(const Vec2D & a, const Vec2D & b)
            {
                return false;
            }

            bool operator<(const Vec2D & a, const Vec2D & b)
            {
                return false;
            }

            bool operator==(const Vec2D & a, const Vec2D & b)
            {
                return false;
            }
        }
    }
}



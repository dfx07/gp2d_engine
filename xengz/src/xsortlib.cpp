#include "xsortlib.h"
#include "xbase.h"


namespace fox
{

    INT utils::CW(void* _center, const void* _a, const void* _b)
    {
        Vec2D* center = (Vec2D*)_center;
        const Vec2D* a = (const Vec2D*)_a;
        const Vec2D* b = (const Vec2D*)_b;
        if (a->x - center->x >= 0 && b->x - center->x < 0)
            return TRUE;
        if (a->x - center->x < 0 && b->x - center->x >= 0)
            return FALSE;
        if (a->x - center->x == 0 && b->x - center->x == 0)
        {
            if (a->y - center->y >= 0 || b->y - center->y >= 0)
                return a->y > b->y;
            return b->y > a->y;
        }

        // Compute the cross product of vectors (center -> a) x (center -> b)
        FLT det = (a->x - center->x) * (b->y - center->y) - (b->x - center->x) * (a->y - center->y);
        if (det < 0)
            return TRUE;
        if (det > 0)
            return FALSE;

        // Points a and b are on the same line from the center
        // Check which point is closer to the center
        FLT d1 = (a->x - center->x) * (a->x - center->x) + (a->y - center->y) * (a->y - center->y);
        FLT d2 = (b->x - center->x) * (b->x - center->x) + (b->y - center->y) * (b->y - center->y);
        return d1 > d2;
    }

    INT utils::CCW(void* _center, const void* _a, const void* _b)
    {
        Vec2D* center = (Vec2D*)_center;
        const Vec2D* a = (const Vec2D*)_a;
        const Vec2D* b = (const Vec2D*)_b;
        if (a->x - center->x >= 0 && b->x - center->x < 0)
            return FALSE;
        if (a->x - center->x < 0 && b->x - center->x >= 0)
            return TRUE;
        if (a->x - center->x == 0 && b->x - center->x == 0)
        {
            if (a->y - center->y >= 0 || b->y - center->y >= 0)
                return b->y > a->y;
            return  a->y > b->y;
        }

        // Compute the cross product of vectors (center -> a) x (center -> b)
        FLT det = (a->x - center->x) * (b->y - center->y) - (b->x - center->x) * (a->y - center->y);
        if (det < 0)
            return FALSE;
        if (det > 0)
            return TRUE;

        FLT d1 = (a->x - center->x) * (a->x - center->x) + (a->y - center->y) * (a->y - center->y);
        FLT d2 = (b->x - center->x) * (b->x - center->x) + (b->y - center->y) * (b->y - center->y);
        return d1 <= d2;
    }

    void S2sortA(Ap2D& points, BOOL isCCW, Vec2D* pCenter)
    {
        Vec2D center;
        // Không truyền vào điểm center thì tính theo center mặc định
        if (pCenter == NULL)
        {
            FLT sumX = 0, sumY = 0;
            for (INT i = 0; i < points.np; i++)
            {
                sumX += points.At(i).x;
                sumY += points.At(i).y;
            }
            center.x = sumX / points.np;
            center.y = sumY / points.np;
        }
        qsort_s(&points.ap[0], points.np, sizeof(Vec2D), ((isCCW == TRUE) ? utils::CCW : utils::CW), &center);
    }

    void S2sortAX(Ap2D xap, Ap2D* outXap, BOOL isCCW)
    {
        *outXap = xap;
        //Z2sortA(*outXap, isCCW);
    }

}

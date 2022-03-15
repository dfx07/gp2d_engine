#ifndef XSORTLIB_H
#define XSORTLIB_H

#include "xbase.h"

namespace fox
{
    //=============================================================================
    //↓↓↓↓ Hàm hỗ trợ xử lý cho các hàm ở dưới
    namespace utils
    {
        INT CW(void* _center, const void* _a, const void* _b);  // Clockwise
        INT CCW(void* _center, const void* _a, const void* _b); // Counter-clockwise
    };
    //↑↑↑↑ Hàm hỗ trợ xử lý cho các hàm ở dưới
    //=============================================================================

    /*******************************************************************************
    * Sắp xếp các điểm trong mảng Ap2D cùng hoặc ngược chiều kim đồng hồ
    * [Author]: DesertFox - [Date] : 20/11/2020
    # RETURN : VOID
    *******************************************************************************/
    void /*DllExport*/ S2sortA(Ap2D& xap, BOOL isCCW = TRUE, Vec2D* pCenter = NULL);

    /*******************************************************************************
    * Sắp xếp các điểm trong mảng Ap2D cùng hoặc ngược chiều kim đồng hồ
    * [Author]: DesertFox - [Date] : 20/11/2020
    # RETURN : VOID  [Trả về Ap2D mới trong outXap]
    *******************************************************************************/
    void /*DllExport*/ S2sortAX(Ap2D xap, Ap2D* outXap, BOOL isCCW = TRUE);
}

#endif //! XSORTLIB_H


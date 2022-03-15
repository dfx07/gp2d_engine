//==============================================================================
// Định nghĩa yếu tố Polygon trong chương trình sử dụng                         
//                                                                              
//==============================================================================
////////////////////////////////////////////////////////////////////////////////
#ifndef EPOLY_ELEM_H
#define EPOLY_ELEM_H

#include "ebase.h"

namespace fox
{
    class Poly: public BaseObj 
    {
    public:
        Ap2D  ap;      // Mảng điểm
    public:
        INT GetType() const{ return typePoly;}

        virtual void CopyAtr(const BaseObj* obj)
        {
            Poly* poly = (Poly*)obj;

            ap = poly->ap;
        };

        CREATE_CLONE(Poly)
    };
}

#endif // !EPOLY_ELEM_H


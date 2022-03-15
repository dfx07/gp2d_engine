//==============================================================================
// Định nghĩa yếu tố Circle trong chương trình sử dụng                          
//                                                                              
//==============================================================================
////////////////////////////////////////////////////////////////////////////////
#ifndef ECIRCLE_ELEM_H
#define ECIRCLE_ELEM_H

#include "ebase.h"

namespace fox
{
    class Circle : public BaseObj 
    {
    public:
        Vec2D pc;       // Tâm điểm
        FLT   radius;   // Bán kính

    public:
        INT GetType() const{ return typeCirc;}

        virtual void CopyAtr(const BaseObj* obj)
        {
            Circle* circ = (Circle*)obj;

            pc     = circ->pc;
            radius = circ->radius;
        };

        CREATE_CLONE(Circle)
    };
}

#endif // !ECIRCLE_ELEM_H

//==============================================================================
// Định nghĩa yếu tố line trong chương trình sử dụng                            
//                                                                              
//==============================================================================
////////////////////////////////////////////////////////////////////////////////
#ifndef ELINE_ELEM_H
#define ELINE_ELEM_H

#include "ebase.h"

namespace fox
{
    class Line : public BaseObj 
    {
    public:
        Vec2D p1;     // Điểm thứ nhất
        Vec2D p2;     // Điểm thứ hai
        INT   w;      // Độ rộng của đường thẳng
    public:
        INT GetType() const{ return typeLine;}

        virtual void CopyAtr(const BaseObj* obj)
        {
            // Trường hợp bằng NULL là tạo mới
            if (!obj)
            {
                p1 = Vec2D(0, 0);
                p2 = Vec2D(0, 0);
                w  = 0;
            }
            // Trường hợp có đối tượng và copy sang
            else
            {
                Line* line = (Line*)obj;

                p1 = line->p1;
                p2 = line->p2;
                w  = line->w;
            }
        };

        CREATE_CLONE(Line)
    };
}

#endif // !ELINE_ELEM_H
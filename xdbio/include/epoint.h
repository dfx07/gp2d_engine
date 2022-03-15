//==============================================================================
// Định nghĩa yếu tố point trong chương trình sử dụng                           
//                                                                              
//==============================================================================
////////////////////////////////////////////////////////////////////////////////
#ifndef EPOINT_ELEM_H
#define EPOINT_ELEM_H

#include "ebase.h"

namespace fox
{
    class Point : public BaseObj 
    {
    public:
        FLT x;      // Tọa độ X 
        FLT y;      // Tọa độ Y
        FLT w;      // Độ to của điểm
    public:
        Point()
        {
            this->CopyAtr(NULL);
        }

        INT GetType() const{ return typePoint;}

        virtual void CopyAtr(const BaseObj* obj)
        {
            // Trường hợp bằng NULL là tạo mới
            if (!obj)
            {
                x = 0;
                y = 0;
                w = 10;
            }
            // Trường hợp có đối tượng và copy sang
            else
            {
                Point* p = (Point*)obj;

                x = p->x;
                y = p->y;
                w = p->w;
            }
        };

        CREATE_CLONE(Point)
    };
}

#endif // !EPOINT_ELEM_H


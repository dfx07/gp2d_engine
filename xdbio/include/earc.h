//==============================================================================
// Định nghĩa yếu tố ARC trong chương trình sử dụng                             
//                                                                              
//==============================================================================
////////////////////////////////////////////////////////////////////////////////
#ifndef EARC_ELEM_H
#define EARC_ELEM_H

#include "ebase.h"

namespace fox
{
    class Arc: public BaseObj 
    {
    public:
        Vec2D pc    ;   // Tâm                         
        FLT   radius;   // Bán kính cung tròn          
        FLT   thinkn;   // Độ dày cung tròn            
        FLT   rstart;   // Góc bắt đầu [so với trục Ox]
        FLT   rend  ;   // Góc kết thúc[so với trục OX]

    public:
        INT GetType() const { return typeArc;}

        virtual void CopyAtr(const BaseObj* obj)
        {
            Arc* arc = (Arc*)obj;

            pc     = arc->pc    ;
            radius = arc->radius;
            thinkn = arc->thinkn;
            rstart = arc->rstart;
            rend   = arc->rend  ;
        };

        CREATE_CLONE(Arc)
    };
}

#endif // !EARC_ELEM_H
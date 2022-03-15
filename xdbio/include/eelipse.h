//==============================================================================
// Định nghĩa yếu tố Elipse trong chương trình sử dụng                          
//                                                                              
//==============================================================================
////////////////////////////////////////////////////////////////////////////////
#ifndef EELIPSE_ELEM_H
#define EELIPSE_ELEM_H

#include "ebase.h"

namespace fox
{
    class Elip: public BaseObj 
    {
    public:
        Vec2D pc    ;   // Tâm                        
        FLT   xradius;  // Bán kính trục nhỏ           
        FLT   yradius;  // Bán kích trục lớn           
        FLT   thinkn;   // Độ dày                      
        FLT   rstart;   // Góc bắt đầu [so với trục Ox]
        FLT   rend  ;   // Góc kết thúc[so với trục Ox]
    public:
        INT GetType() const{ return typeElip;}

        virtual void CopyAtr(const BaseObj* obj)
        {
            Elip* elip = (Elip*)obj;

            pc      = elip->pc     ;
            xradius = elip->xradius;
            yradius = elip->yradius;
            thinkn  = elip->thinkn ;
            rstart  = elip->rstart ;
            rend    = elip->rend   ;
        };

        CREATE_CLONE(Elip)
    };
}

#endif // !EELIPSE_ELEM_H

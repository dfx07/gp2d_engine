#include "x2dlib.h"

namespace fox
{

    /***************************************************************************
    * Set vector về vector (0 ,0)                                               
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport void V2zero(Vec2D & a)
    {
        a.x = 0;
        a.y = 0;
    }

    /***************************************************************************
    * Set vector về vector (Nan ,Nan)                                           
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport void V2nan(Vec2D & a)
    {
        a.x = NAN;
        a.y = NAN;
    }

    /***************************************************************************
    * Set vector về vector (Nan ,Nan)                                           
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport BOOL V2isnan(const Vec2D& a)
    {
        return (fabs(a.x - NAN) < EPSILON && fabs(a.y - NAN) < EPSILON);
    }

    /***************************************************************************
    * Trừ hai vector [2D]                                                       
    * [Author] : DesertFox - [Date] : 02/03/2020                                
    ***************************************************************************/
    DllExport Vec2D V2sub(const Vec2D& a, const Vec2D& b)
    {
        Vec2D rs;
        rs.x = a.x - b.x;
        rs.y = a.y - b.y;
        return rs;
    }

    /***************************************************************************
    * Đảo chiều của vector [Cùng phương ngược chiều]                            
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2reverse(const Vec2D & vec)
    {
        Vec2D vrec;
        vrec.x = - vec.x;
        vrec.y = - vec.y;
        return vrec;
    }

    /***************************************************************************
    * Đảo chiều của vector [Cùng phương ngược chiều]                            
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport void V2reversex(Vec2D & vec)
    {
        vec.x *= -1;
        vec.y *= -1;
    }

    /***************************************************************************
    * Cộng hai vector [2D]                                                      
    * [Author] : DesertFox - [Date] : 02/03/2020                                
    ***************************************************************************/
    DllExport Vec2D V2add(const Vec2D& a, const Vec2D& b)
    {
        Vec2D rs;
        rs.x = a.x + b.x;
        rs.y = a.y + b.y;
        return rs;
    };

    /***************************************************************************
    * Lấy trung điểm của hai vector [2D]                                        
    * [Author] : DesertFox - [Date] : 02/03/2020                                
    ***************************************************************************/
    DllExport Vec2D V2mid(const Vec2D& a, const Vec2D& b)
    {
        Vec2D rs;
        rs.x = (a.x + b.x) * 0.5;
        rs.y = (a.y + b.y) * 0.5;
        return rs;
    }

    /***************************************************************************
    * Nhân vector với một lượng [2D]                                            
    * [Author] : DesertFox - [Date] : 02/03/2020                                
    ***************************************************************************/
    DllExport Vec2D V2mul(const Vec2D& v, const FLT& factor)
    {
        Vec2D vec ;
        vec.x = v.x * factor;
        vec.y = v.y * factor;
        return vec;
    }

    /***************************************************************************
    * Chia vector một lượng (factor != 0) [2D]                                  
    * [Author] : DesertFox - [Date] : 02/03/2020                                
    ***************************************************************************/
    DllExport Vec2D V2div(const Vec2D& a, FLT factor)
    {
        Vec2D rs;
        if (utils::IsEqual(factor, 0.0))
        {
            assert(0);
            return a;
        }

        rs.x = (a.x) / factor;
        rs.y = (a.y) / factor;
        return rs;
    }

    /***************************************************************************
    * Độ lớn của một vector                                                     
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2mag(const Vec2D& a)
    {
        return sqrt(a.x * a.x + a.y * a.y);
    }

    /***************************************************************************
    * Tìm vector đơn vị của một vector                                          
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2uint(const Vec2D& a)
    {
        FLT mag = V2mag(a);
        if (mag <= 0)
        {
            return Vec2D(0, 0);
        }
        return Vec2D(a.x / mag, a.y / mag);
    }

    /***************************************************************************
    * Tích vô hướng của hai vector                                              
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2dot(const Vec2D& v1, const Vec2D& v2)
    {
        return (v1.x * v2.x + v1.y * v2.y);
    }

    /***************************************************************************
    * Tích vô hướng của hai vector từ các thành phần                            
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2dot(const FLT& x1, const FLT&y1, const FLT& x2, const FLT& y2)
    {
        return (x1 * x2 + y1 * y2);
    }

    /***************************************************************************
    * Quay vector một góc với trục Ox                                           
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2rot(const Vec2D& vec, FLT angleR)
    {
        Vec2D r_vec;
        r_vec.x = cos(angleR) * vec.x - sin(angleR) * vec.y;
        r_vec.y = sin(angleR) * vec.x + cos(angleR) * vec.y;
        return r_vec;
    }

    /***************************************************************************
    * Tích có hướng của hai vector                                              
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2crs(const Vec2D& v1, const Vec2D& v2)
    {
        return (v1.x * v2.y - v1.y * v2.x);
    }

    /***************************************************************************
    * Tích có hướng của hai vector từ các thành phần                            
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2crs(const FLT& x1, const FLT&y1, const FLT& x2, const FLT& y2)
    {
        return (x1 * y2 - y1 * x2);
    }

    /***************************************************************************
    * Di chuyển điểm theo vector đơn vị và độ lớn                               
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2movpnd(Vec2D p, Vec2D& n, FLT& d)
    {
        Vec2D res;
        res.x = p.x + n.x * d;
        res.y = p.y + n.y * d;
        return res;
    }

    /***************************************************************************
    * Góc giữa hai vector                                                       
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2ang2v(const Vec2D& v1, const Vec2D& v2)
    {
        FLT dot = v1.x*v2.x + v1.y*v2.y; // # dot product between v1 ,v2
        FLT det = v1.x*v2.y - v1.y*v2.x; // # determinant
        FLT rad = atan2(det, dot);       // # atan2(y, x) or atan2(sin, cos)
        return(rad);
    }

    /***************************************************************************
    * Tính góc giữa vector và trục Ox                                           
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2angOx(const Vec2D& v)
    {
        // Vec2D(1.0, 0.0) chính là vector đơn vị trục Ox
         FLT rad = V2ang2v(A_OX, v);
        //if (rad > PI) rad -= (FLT)PIW;
        return (rad);
    }

    /***************************************************************************
    * Quay một điểm quanh nguồn với trục có sẵn mặc định trục Ox                
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2rot2(const Vec2D& point   ,    // Tọa độ điểm quay [input]
                           const Vec2D& origin  ,    // Góc tọa độ quay  [input]
                           const FLT&   angR    ,    // Góc quay (radian)[input]
                           const Vec2D& ox      )    // Trục ox          [input]
    {
        Vec2D disPoint; Vec2D oy;

        FLT cosA = (FLT)cos(PIH);
        FLT sinA = (FLT)sin(PIH);

        oy.x = ox.x * cosA - ox.y * sinA;
        oy.y = ox.x * sinA + ox.y * cosA;

        if (utils::IsEqual(oy.x, 0.0)) oy.x = 0;
        if (utils::IsEqual(oy.x, 0.0)) oy.y = 0;

        disPoint.x = cos(angR) * (origin.x - point.x) - 
                     sin(angR) * (origin.y - point.y) + origin.x;
        disPoint.y = sin(angR) * (origin.x - point.x) + 
                     cos(angR) * (origin.y - point.y) + origin.y;
        return oy;
    }

    /****************************************************************************
    * Tìm điểm đối xứng với điểm qua điểm                                        
    * [Author]: DesertFox - [Date] : 09/11/2020                                  
    ****************************************************************************/
    DllExport Vec2D V2reflp(const Vec2D& point, const Vec2D& mid)
    {
        Vec2D vDis = V2sub(mid, point);
        Vec2D pRef = V2add(mid, vDis);
        return pRef;
    }

    /****************************************************************************
    * Tìm điểm đối xứng với điểm qua đoạn thẳng được cho bởi 2 điểm              
    * [Author]: DesertFox - [Date] : 09/11/2020                                  
    ****************************************************************************/
    DllExport Vec2D V2refll(const Vec2D& point, const Vec2D& a, const Vec2D& b)
    {
        Vec2D vRef;
        FLT m, c, d , del = (b.x - a.x);;

        // Trường hợp song song với trục Oy;  Phương trình x = a;
        if (utils::IsEqual(del, 0.0))
        {
            return Vec2D(-point.x+ 2*a.x , point.y) ;
        }
        else
        {
            m = (b.y - a.y) / (b.x - a.x);
            c = (b.x*a.y - a.x*b.y) / (b.x - a.x);
        }
        // Trường hợp tổng quát  Phương trình y = ax +b
        d = (point.x + (point.y - c)*m) / (1 + m*m);

        vRef.x = 2*d - point.x;
        vRef.y = 2*d*m - point.y + 2*c;
        return vRef;
    }

    /****************************************************************************
    * Xóa các điểm trung nhau liên tiếp                                          
    * [Author]: DesertFox - [Date] : 09/11/2020                                  
    ****************************************************************************/
    DllExport void V2remove_double_point(Ap2D& xap)
    {
        INT i = 0 ;

        // Trường hợp điểm đầu và điểm cuối trùng nhau
        while (xap.np >1 && utils::IsEqual(xap.Front(), xap.Back()))
        {
            xap.RemoveBack();
        }

        // Trường hợp tổng quát hai điểm trung nhau
        while (i < xap.np-1)
        {
            if (utils::IsEqual(xap[i], xap[i + 1]))
            {
                xap.RemoveAt(i);
            }
            else i++;
        }
    }
}

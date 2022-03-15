/*****************************************************************//**
 * File     : x2dlib.h
 * Brief    : Xử lý thao tác vector 2D cơ bản
 * Update   :
 *           [Create] : 19/05/2020 - DesertFox
 *           [Update] : 09/11/2020 - DesertFox
 * TODO     :                                                         
 * Note     : Với nhưng hàm giống nhau về tên và có tiền tố x thì có 
              nghĩa là nó sẽ thay đổi chính tham số chuyền vào mà không
              trả về giá trị
 *********************************************************************/

#ifndef X2DLIB_H
#define X2DLIB_H

#include "xbase.h"
#include "xcom.h"

using namespace std;

namespace fox
{
    /***************************************************************************
    * Set vector về vector (0 ,0)                                               
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport void V2zero(Vec2D& a);

    /***************************************************************************
    * Set vector về vector (Nan ,Nan)                                           
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport void V2nan(Vec2D& a);

    /***************************************************************************
    * Kiểm tra vector có phải (Nan ,Nan)                                        
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport BOOL V2isnan(const Vec2D& a);

    /***************************************************************************
    * Cộng hai vector                                                           
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2add(const Vec2D& a, const Vec2D& b);

    /***************************************************************************
    * Trừ hai vector                                                            
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2sub(const Vec2D& a, const Vec2D& b);

    /***************************************************************************
    * Nhân vector với một số                                                    
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2mul(const Vec2D& v, const FLT& factor);

    /***************************************************************************
    * Lấy tỉ lệ của vector                                                      
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2div(const Vec2D& a, FLT factor) ;

    /***************************************************************************
    * Tính trung điểm của hai điểm                                              
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2mid(const Vec2D& a, const Vec2D& b) ;

    /***************************************************************************
    * Đảo chiều của vector [Cùng phương ngược chiều]                            
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2reverse(const Vec2D& vec);

    /***************************************************************************
    * Độ lớn của vector                                                         
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2mag(const Vec2D& a);

    /***************************************************************************
    * Tính vector đơn vị                                                        
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2uint(const Vec2D& a);

    /***************************************************************************
    * Tích vô hướng của hai vector                                              
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2dot(const Vec2D& v1, const Vec2D& v2);

    /***************************************************************************
    * Tích vô hướng của hai vector từ các thành phần                            
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2dot(const FLT& x1, const FLT&y1, const FLT& x2, const FLT& y2);

    /***************************************************************************
    * Tích có hướng của hai vector                                              
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2crs(const Vec2D& v1, const Vec2D& v2);

    /***************************************************************************
    * Tích có hướng của hai vector từ các thành phần                            
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2crs(const FLT& x1, const FLT&y1, const FLT& x2, const FLT& y2);

    /***************************************************************************
    * Quay một vector quanh trục Ox                                             
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2rot(const Vec2D& vec, FLT angleR) ;

    /***************************************************************************
    * Đảo chiều của vector [Cùng phương ngược chiều]                            
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport void V2reversex(Vec2D& vec);

    /***************************************************************************
    * Di chuyển điểm theo vector đơn vị và độ lớn                               
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2movpnd(Vec2D  p,       // Tọa độ điểm cần chuyển   [Input]
                             Vec2D& n,       // Vector đơn vị hướng      [Input]
                             FLT&   d);      // Độ lớn di chuyển         [Input]

    /***************************************************************************
    * Góc giữa hai vector                                                       
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2ang2v(const Vec2D& v1, const Vec2D& v2);

    /***************************************************************************
    * Góc giữa một vector và trục Ox                                            
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport FLT V2angOx(const Vec2D& v);

    /***************************************************************************
    * Quay một điểm quanh nguồn với trục có sẵn [Mặc định] trục Ox              
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2rot2(const Vec2D& point   ,     //Tọa độ điểm quay [input]
                           const Vec2D& origin  ,     //Góc tọa độ quay  [input]
                           const FLT&   angR    ,     //Góc quay (radian)[input]
                           const Vec2D& ox= A_OX);    //Trục ox          [input]

    /***************************************************************************
    * Tìm điểm đối xứng với điểm qua điểm                                       
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2reflp(const Vec2D& point, const Vec2D& mid);

    /***************************************************************************
    * Tìm điểm đối xứng với điểm qua đoạn thẳng được cho bởi 2 điểm             
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport Vec2D V2refll(const Vec2D& point, const Vec2D& a, const Vec2D& b);

    /***************************************************************************
    * Xóa các điểm trung nhau liên tiếp                                         
    * [Author]: DesertFox - [Date] : 09/11/2020                                 
    ***************************************************************************/
    DllExport void V2remove_double_point(Ap2D& xap);
}


#endif // !X2DLIB_H

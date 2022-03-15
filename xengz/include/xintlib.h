/****************************************************************************//*
 * File     : xintlib.h
 * Brief    : Xử lý giao nhau cơ bản 2D và 3D
 * Update   :
 *           [Create] : 19/05/2020 - DesertFox
 *           [Update] : 12/11/2020 - DesertFox
 * TODO     :
 ******************************************************************************/

#ifndef XINTLIB_H
#define XINTLIB_H



#include <algorithm>
#include "xcom.h"
#include "x2dlib.h"


using namespace std;

namespace fox
{

    /*******************************************************************************
    * Đường thẳng cắt vùng [Vùng đó phải quay theo chiều CCW]
    # RETURN : VOID  [Trả về Ap2D mới trong outXap]
    * [Author]: DesertFox - [Date] : 20/11/2020
    *******************************************************************************/
    void DllExport Z2cutLA(Ap2D xap, Ap2D* outXap, BOOL isCCW = TRUE);

    /*******************************************************************************
    * Độ dài hình chiếu điểm xuống vector được cho bởi một điểm và vector đơn vị
    * (d là hình chiếu pc xuống (p,v))
    # RETURN : FLT (Độ lớn của đoạn thẳng pd)
    * [Author]: DesertFox - [Date] : 22/11/2020
    *******************************************************************************/
    FLT DllExport Z2disPPV(Vec2D p,           //  Điểm xuất phát              (input)
                           Vec2D v,           //  Vector đơn vị của muốn chiếu(input)
                           Vec2D pc);         //  Điểm cần đo                 (input)
}

#endif // !XINTLIB_H

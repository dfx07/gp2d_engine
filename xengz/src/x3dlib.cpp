#include "x3dlib.h"


namespace fox
{
    /*******************************************************************************
    * Trừ hai vector [3D]
    * [Author] : DesertFox - [Date] : 02/03/2020
    *******************************************************************************/
    Vec3D V3sub(const Vec3D& a, const Vec3D& b)
    {
        Vec3D rs;
        rs.x = a.x - b.x;
        rs.y = a.y - b.y;
        rs.z = a.z - b.z;
        return rs;
    };
    /*******************************************************************************
    * Cộng hai vector [3D]
    * [Author] : DesertFox - [Date] : 02/03/2020
    *******************************************************************************/
    Vec3D V3add(const Vec3D& a, const Vec3D& b)
    {
        Vec3D rs;
        rs.x = a.x + b.x;
        rs.y = a.y + b.y;
        rs.z = a.z + b.z;
        return rs;
    };
    /*******************************************************************************
    * Lấy trung điểm của hai vector [3D]
    * [Author] : DesertFox - [Date] : 02/03/2020
    *******************************************************************************/
    Vec3D V3mid(const Vec3D& a, const Vec3D& b)
    {
        Vec3D rs;
        rs.x = (a.x + b.x) * 0.5;
        rs.y = (a.y + b.y) * 0.5;
        rs.z = (a.z + b.z) * 0.5;
        return rs;
    }
    /*******************************************************************************
    * Nhân vector với một lượng [3D]
    * [Author] : DesertFox - [Date] : 02/03/2020
    *******************************************************************************/
    Vec3D V3mul(const Vec3D& v, const FLT& factor)
    {
        Vec3D vec ;
        vec.x = v.x * factor;
        vec.y = v.y * factor;
        vec.z = v.z * factor;
        return vec;
    }
    /*******************************************************************************
    * Chia vector một lượng (factor != 0) [3D]
    * [Author] : DesertFox - [Date] : 02/03/2020
    *******************************************************************************/
    Vec3D V3div(const Vec3D& a, FLT factor)
    {
        Vec3D rs;
        if (factor == 0)
        {
            assert(0);
            return a;
        }

        rs.x = (a.x) / factor;
        rs.y = (a.y) / factor;
        rs.z = (a.z) / factor;
        return rs;
    }

    /***********************************************************************
    * Độ lớn của một vector [3D]
    * [Author]: DesertFox - [Date] : 09/11/2020
    **********************************************************************/
    FLT V3mag(const Vec3D& a)
    {
        return sqrt(a.x * a.x + a.y * a.y + a.z* a.z);
    }

    /***********************************************************************
    * Tìm vector đơn vị của một vector  [3D]
    * [Author]: DesertFox - [Date] : 09/11/2020
    **********************************************************************/
    Vec3D V3uint(const Vec3D& a)
    {
        FLT mag = V3mag(a);
        if (mag <= 0)
        {
            return Vec3D(0, 0 ,0);
        }
        return Vec3D(a.x / mag, a.y / mag , a.z/mag);
    }
}
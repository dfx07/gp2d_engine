/****************************************************************************//*
* File     : xcom.h
* Brief    : Xử lý các thao thác hỗ trợ liên quan đến cấu trúc engine
* Update   :
*           [Create] : 19/05/2020 - DesertFox
*           [Update] : 12/11/2020 - DesertFox
* TODO     :
******************************************************************************/
#ifndef XCOM_H
#define XCOM_H

#include <iterator>
#include <random>
#include <map>
#include <fstream>
#include "xdef.h"
#include "xbase.h"


//=============================================================================
//↓ SUPPORT out to the program [Console]

namespace fox
{
    namespace utils
    {
#ifdef _DEBUG
        extern DllExport ostream&  operator<<(std::ostream& os, const Vec2D& v       );
        extern DllExport ostream&  operator<<(std::ostream& os, const Vec3D& v       );
        extern DllExport ostream&  operator<<(std::ostream& os, const Line2D& li     );
        extern DllExport ostream&  operator<<(std::ostream& os, const Line3D& li     );
        extern DllExport ostream&  operator<<(std::ostream& os, const StackVec2D& stk);
        extern DllExport ostream&  operator<<(std::ostream& os, const List2Vec2D& lit);

#endif // _DEBUG

        FLT    DllExport           Map(FLT value, FLT smin, FLT smax, FLT dmin, FLT dmax);

        //=============================================================================
        //↓ convert out to the program [Console]

        GLColor DllExport           Col2Standard(Color color);
        GLColor DllExport           Col2Standard(UINT r, UINT g, UINT b);
        void   DllExport            Vec2Ap2D(vector<Vec2D>& ar2D, Ap2D & xap);

        //↑ convert out to the program [Console]
        //=============================================================================


        //=============================================================================
        //↓ compare to the program [Console]
       
        template <typename T>  // So sánh bằng có delta
        inline BOOL DllExport  IsEqual(const T&val1, const T&val2, const T&eps =EPSILON)
        {
            T diff = val2 - val1;
            return ((diff >= -eps) && (diff <= eps));
        }

        inline BOOL DllExport IsEqual(const Vec2D&val1, const Vec2D&val2, const FLT&eps =EPSILON)
        {
            return IsEqual(val1.x , val2.x ,eps ) && IsEqual(val1.y , val2.y , eps);
        }

        inline BOOL DllExport IsEqual(const Vec3D&val1, const Vec3D&val2, const FLT&eps =EPSILON)
        {
            return (IsEqual(val1.x, val2.x, eps) && 
                    IsEqual(val1.y, val2.y, eps) &&
                    IsEqual(val1.z, val2.z, eps));
        }

        template <typename T>  // So sánh không bằng có delta
        inline BOOL DllExport  IsNotEqual(const T&val1, const T&val2, const T&eps =EPSILON)
        {
            T diff = val2 - val1;
            return ((diff < -eps) && (diff > eps));
        }

        inline BOOL DllExport IsNotEqual(const Vec2D&val1, const Vec2D&val2, const FLT&eps =EPSILON)
        {
            return IsNotEqual(val1.x , val2.x ,eps ) && IsNotEqual(val1.y , val2.y , eps);
        }

        inline BOOL DllExport IsNotEqual(const Vec3D&val1, const Vec3D&val2, const FLT&eps =EPSILON)
        {
            return (IsNotEqual(val1.x, val2.x, eps) && 
                    IsNotEqual(val1.y, val2.y, eps) &&
                    IsNotEqual(val1.z, val2.z, eps));
        }

        template<typename T>    // So sánh lớn hơn bằng có delta        (>)
        inline BOOL DllExport IsGreater(const T&valgreater, const T&val, const T&eps = EPSILON)
        {
            T diff = valgreater - val;

            return (diff > eps);
        }

        template<typename T>    // So sánh lớn hơn hoặc bằng có delta   (>=)
        inline BOOL DllExport IsGreaterOrEqual(const T&valgreater, const T&val, const T&eps = EPSILON)
        {
            T diff = valgreater - val;

            return IsEqual(diff , 0.0) || (diff > eps);
        }

        template<typename T>    // So sánh nhỏ hơn có delta             (<)
        inline BOOL DllExport IsSmaller(const T&valsmaller, const T&val, const T&eps = EPSILON)
        {
            T diff = val - valsmaller;

            return (diff > eps);
        }

        template<typename T>    // So sánh nhỏ hơn hoặc bằng có delta   (<=)
        inline BOOL DllExport IsSmallerOrEqual(const T&valsmaller, const T&val, const T&eps = EPSILON)
        {
            T diff = val - valsmaller;

            return IsEqual(diff , 0.0) || (diff > eps);
        }

        // So sánh mức độ ưu tiên giữa hai giá trị => Sử dụng cho các hàm so sánh VD : qsort,...
        // Chú ý : Phù hợp với loại dữ liệu nguyền thủy hoặc Nạp chồng toán tử " < , == , > " nếu là đối tượng
        template<typename T>
        inline INT _cmp(const void *val1, const void *val2)
        {
             const T& value1 = *((const T*)val1);
             const T& value2 = *((const T*)val2);

             if(value1 < value2 )           return -1;    // val1 đứng trước val2
             else if(value1 == value2 )     return  0;    // val1 bằng val2
             else /*if(value1 > value2 )*/  return  1;    // val1 đứng sau value 2
        }

        // So sánh mức độ ưu tiên giữa 2 vị trí   => Sử dụng cho các hàm so sánh VD : qsort,...
        // Sắp sếp x từ nhỏ đến lớn -> y từ lớn đến nhỏ
        inline INT _cmp_vec2d(const void *val1, const void *val2)
        {
            const Vec2D& value1 = *((const Vec2D*)val1);
            const Vec2D& value2 = *((const Vec2D*)val2);

            if     (IsEqual(value1 , value2))      return  0;
            else if(IsGreater(value2.x, value1.x)) return -1;
            else if(IsSmaller(value2.x, value1.x)) return  1;
            else if(IsGreater(value2.y, value1.y)) return -1;
            else                                   return  1;
        }

        //↑ compare  to the program [Console]
        //=============================================================================


        //=============================================================================
        //↓ Check to the program [Console]

        // Lấy format của file hình ảnh, không sợ bị chỉnh sửa thông tin
        ImgType GetImageTypeExtension(const string path);
        //↑ Check to the program [Console]
        //=============================================================================

        //=============================================================================
        //↓ Ramdom to the program [Console]

        //Hàm sinh ngẫu nhiên số theo phân phối đều
        template<typename T = INT>
        inline T RandomUniform(T start, T end)
        {
            std::random_device rd;              //Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd());             //Standard mersenne_twister_engine seeded with rd()
            std::uniform_int_distribution<T> distrib(start, end);
            return distrib(gen);
        }

        //Hàm sinh ngẫu nhiên số theo phân phối đều => đặc biệt double
        template<>
        inline FLT RandomUniform<FLT>(FLT start, FLT end)
        {
            std::random_device rd;              //Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd());             //Standard mersenne_twister_engine seeded with rd()
            std::uniform_real_distribution<FLT> distrib(start, end);
            return distrib(gen);
        }

        //Hàm sinh ngẫu nhiên số theo phân phối đều => đặc biệt float
        template<>
        inline float RandomUniform<float>(float start, float end)
        {
            std::random_device rd;              //Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd());             //Standard mersenne_twister_engine seeded with rd()
            std::uniform_real_distribution<float> distrib(start, end);
            return distrib(gen);
        }

        //Hàm sinh ngẫu nhiên số theo phân phối chuẩn
        template<typename T = INT>
        inline T RandomNormal(T start, T end)
        {
            std::random_device rd;              //Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd());             //Standard mersenne_twister_engine seeded with rd()
            std::normal_distribution<T> distrib(start, end);
            return distrib(gen);
        }

        //↑ Ramdom to the program [Console]
        //=============================================================================
    }

    namespace structsys
    {
        /*******************************************************************************
        * Lấy thông tin màn hình hiển thị chính
        * [Return] : void
        * [Author] : DesertFox - [Date] : 02/03/2020
        *******************************************************************************/
        BOOL DllExport GetMonitorInforEx(MonitorInfo * infor);
    }
}

//↑ SUPPORT out to the program [Console]
//=============================================================================



#endif // !XCOM_H


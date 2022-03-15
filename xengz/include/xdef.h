#ifndef XDEFLIB_H
#define XDEFLIB_H

#include <iostream>

#define _EXPORT

using namespace std;

typedef int             INT    ;
typedef double          FLT    ;
typedef unsigned int    UINT   ;
typedef int             BOOL   ;
typedef string          String ;
typedef wstring         WString;


//=============================================================================
//↓ Preprocessing disable waring
#pragma warning (disable : 4996)
#pragma warning (disable : 4244)
#pragma warning (disable : 4267)
#pragma warning (disable : 4251)
#pragma warning (disable : 4312)
//↑ Preprocessing disable waring
//=============================================================================



//=============================================================================
//↓ Function debug code
#undef assert
#ifdef _DEBUG
#       define concate(s1, s2)   s1 ## s2
#       define frefix_f(s)       concate(L,s)

#       define assert(f)         _ASSERT(f)
#       define assert_m(f, msg)  _ASSERT_EXPR(f , frefix_f(msg))
#else 
#       define assert(f) 
#       define assert_m(f, msg)
#endif
//↑ Function debug code
//=============================================================================


//=============================================================================
//↓ Define export or import function and class

#ifdef _EXPORT 
#define DllExport   __declspec( dllexport )
#else
#define DllImport   __declspec( dllimport )
#endif // _EXPORT 

//↑ Define export or import function and class
//=============================================================================



//=============================================================================
//↓ Keyword Definition

#define      DELS            0.01                    //
#define      CRS_T           0.001                   //

#define      PIH             1.570796326794897       //  PI/2
#define      PI              3.141592653589793       //  PI
#define      PIW             6.283185307179586       // 2PI

#define      TRUE            1                       //
#define      FALSE           0                       //
                                                     //
                                                     //
#define      EPSILON_LOW     0.00001                 //
#define      EPSILON_MED     0.001                   //
#define      EPSILON_HIG     0.01                    //
                                                     //
#undef       NAN                                     //
#define      NAN             DBL_MAX                 //
                                                     //
#define      EPSILON         EPSILON_MED             //


#define      COL_RED         1.0 , 0.0 , 0.0         //
#define      COL_BLUE        0.0 , 0.0 , 1.0         //
#define      COL_GREEN       0.0 , 1.0 , 0.0         //
#define      COL_YELLOW      1.0 , 1.0 , 0.0         //
#define      COL_BLACK       0.0 , 0.0 , 0.0         //
#define      COL_WHITE       1.0 , 1.0 , 1.0         //
#define      COL_OGIRD       0.078, 0.101, 0.078     //

#define      A_OX            {1,0}                   // Vector đơn vị trục Ox
#define      A_OY            {0,1}                   // Vector đơn vị trục Oy


namespace fox
{
    enum Orien
    {
        LEFT_SIDE  = -1,     // Nằm bên trái    
        COLLINEAR  =  0,     // Nằm trên        
        RIGHT_SIDE =  1,     // Nằm bên phải    
    };

    enum Posrel
    {
        INSIDE     = -1,     // Bên trong       
        BOUNDARY   =  0,     // Nằm trên viền   
        OUTSIDE    =  1,     // Bên ngoài       
    };

    enum ImgType
    {
        IMG_INV       ,      // Không xác định  
        IMG_PNG    = 1,      // png             
        IMG_JPG    = 2,      // jpg , jpeg      
        IMG_BMP    = 3,      // bmp             
        IMG_TIF    = 4,      // tif ,tiff       
        IMG_GIF    = 5,      // gif             
        IMG_ICO    = 6,      // ico             
    };
}


//↑ Keyword Definition
//=============================================================================


//=============================================================================
//↓ Function Definition

#define IS_BASE_CLASS(ptr , base_cls)   dynamic_cast<base_cls*>(ptr)


//↑ Function Definition
//=============================================================================


#endif //!XDEFLIB_H

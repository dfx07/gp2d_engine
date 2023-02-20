#include "xrellib.h"

namespace fox
{
    /*******************************************************************************
    # Lấy khoảng cách từ điểm đến một điểm theo một vector                          
    # RETURN : Độ dài thể hiện qua 2 đại lượng [t, d] có thể âm                     
    # @@ :Đại lượng [t, d] có thể âm                                                
    *******************************************************************************/
    void  DllExport V2pvp(const Vec2D& p,  //   Điểm tính                        [IN]
                          const Vec2D& pc, //   Điểm kết thúc                    [IN]
                          const Vec2D& v,  //   Vec chỉ hướng lấy   rect         [IN]
                          FLT& t,          //   Độ dài cạnh đầu của rect        [OUT]
                          FLT& d)          //   Độ dài cạnh còn lại rect        [OUT]
    {
        Vec2D dir_vec;
        dir_vec = V2sub(pc, p);

        t = v.x* dir_vec.x + v.y*dir_vec.y;
        d = v.x* dir_vec.y - v.y*dir_vec.x;
    }

    /*******************************************************************************
    # Lấy vector đơn vị của một góc [Độ lớn vector =1]                              
    # RETURN : Góc sau chuẩn hóa trong khoảng [0 -> 2PI] radian                     
    *******************************************************************************/
    Vec2D DllExport V2uint_angle(const FLT & rAng)
    {
        Vec2D uint;
        uint.x = cos(rAng);
        uint.y = sin(rAng);
        return uint;
    }

    /*******************************************************************************
    # Tiêu chuẩn hóa góc đưa góc về khoảng [0 -> 2PI]                               
    # RETURN : Góc sau chuẩn hóa trong khoảng [0 -> 2PI] radian                     
    *******************************************************************************/
    FLT DllExport V2standardize_angle(const FLT& rAng)
    {
        FLT rOut = rAng;
        V2standardize_anglex(rOut);
        return rOut;
    }

    /*******************************************************************************
    # Tiêu chuẩn hóa góc đưa góc về khoảng [0 -> 2PI]                               
    # RETURN : void (chuẩn hóa luôn tham số đầu vào)                                
    *******************************************************************************/
    void DllExport V2standardize_anglex(FLT& rAng)
    {
        INT iQuoti  = rAng/PIW;

        rAng = rAng - iQuoti * PIW;
        if (rAng < 0)
        {
            rAng = PIW + rAng;
        }
    }

    /*******************************************************************************
    # Vị trí trái phải của 1 điểm (r) với một đoạn thẳng cho bởi 2 điểm  (p1p2)     
    # RETURN  :-1       : Bên trái đường thẳng                                      
    #           0       : Ba điểm thẳng hàng                                        
    #           1       : Bên phải đường thẳng                                      
    #[Author]: DesertFox       - [Date] : 12/11/2020                                
    *******************************************************************************/
    INT DllExport V2ori_point2line(const Vec2D& p1, const Vec2D& p2, const Vec2D& r)
    {
        const FLT orin = (p2.x - p1.x) * (r.y - p1.y) - (r.x - p1.x) * (p2.y - p1.y);

        if (orin > FLT(0.0))      return Orien::LEFT_SIDE;    /*r ở bên trái p1p2 */
        else if (orin < FLT(0.0)) return Orien::RIGHT_SIDE;   /*r ở bên phải p1p2 */
        else                      return Orien::COLLINEAR;    /*rp1p2 thẳng hàng  */
    }

    /*******************************************************************************
    # Vị trí trái phải của 1 điểm (r) với một đoạn thẳng cho bởi 2 điểm gần đúng    
    # RETURN : -1       : Bên trái đường thẳng                                      
    #           0       : Ba điểm thẳng hàng                                        
    #           1       : Bên phải đường thẳng                                      
    #[Author]: DesertFox       - [Date] : 12/11/2020                                
    *******************************************************************************/
    Orien DllExport V2oriex_point2line(const Vec2D& p1, const Vec2D& p2, const Vec2D& r)
    {
        const FLT orin = (p2.x - p1.x) * (r.y - p1.y) - (r.x - p1.x) * (p2.y - p1.y);

        if (utils::IsEqual(orin, 0.0)) return Orien::COLLINEAR;  /*r p1p2 thẳng hàng*/
        else if (orin < FLT(0.0))      return Orien::RIGHT_SIDE; /*r ở bên phải p1p2*/
        else                           return Orien::LEFT_SIDE;  /*r ở bên trái p1p2*/
    }

    /*******************************************************************************
    # Kiểm tra xem một điểm nằm giữa hai điểm  [ĐK: không phải chính giữa]          
    # RETURN : TRUE     : Điểm nằm giữa                                             
    #          FLASE    : Điểm nằm ngoài                                            
    #[Author]: DesertFox       - [Date] : 12/11/2020                                
    *******************************************************************************/
    BOOL DllExport V2betw_point22point(const Vec2D& p, const Vec2D& q, const Vec2D& m)
    {
        if (q.x <= max(p.x, m.x) && q.x >= min(p.x, m.x) &&
            q.y <= max(p.y, m.y) && q.y >= min(p.y, m.y))
        {
            return TRUE;
        }
        return FALSE;
    }

    /*******************************************************************************
    # Lấy điểm max min của hai đoạn thẳng cho bởi 4 điểm phục vụ cho hàm giao       
    # RETURN : min      : Điểm trên cùng                                            
    #          max      : Điểm dưới cùng                                            
    #[Author]: DesertFox       - [Date] : 12/11/2020                                
    *******************************************************************************/
    void  V2minmax_2segment(const Vec2D& p1 ,      // Điểm Start L1          [input]
                            const Vec2D& p2 ,      // Điểm End   L1          [input]
                            const Vec2D& p3 ,      // Điểm Start L2          [input]
                            const Vec2D& p4 ,      // Điểm End   L2          [input]
                            Vec2D* min /*NULL*/,   // Điểm nhỏ nhất         [output]
                            Vec2D* max /*NULL*/)   // Điểm lớn nhất         [output]
    {
        if (min)
        {
            min->x = std::min<FLT>({ p1.x,p2.x,p3.x,p4.x });
            min->y = std::min<FLT>({ p1.y,p2.y,p3.y,p4.y });
        }
        if (max)
        {
            max->x = std::max<FLT>({ p1.x,p2.x,p3.x,p4.x });
            max->y = std::max<FLT>({ p1.y,p2.y,p3.y,p4.y });
        }
    }

    /*******************************************************************************
    # Xác định điểm nằm trong khoảng tọa độ đoạn thẳng                              
    # RETURN : TRUE      : Thuộc vào đoạn thẳng                                     
    #          FALSE     : Không thuộc đoạn thẳng                                   
    #[Author]: DesertFox       - [Date] : 12/11/2020                                
    *******************************************************************************/
    BOOL V2point_on_bound_segment(  const Vec2D& p1,    // Điểm Start L      [input]
                                    const Vec2D& p2,    // Điểm End   L      [input]
                                    Vec2D& a )          // Điểm xét         [output]
    {
        if(utils::IsGreaterOrEqual(a.x,std::min<FLT>(p1.x, p2.x)) &&
           utils::IsSmallerOrEqual(a.x,std::max<FLT>(p1.x, p2.x)) &&
           utils::IsGreaterOrEqual(a.y,std::min<FLT>(p1.y, p2.y)) &&
           utils::IsSmallerOrEqual(a.y,std::max<FLT>(p1.y, p2.y)) )
        {
            return TRUE;
        }
        return FALSE;
    }

    /*******************************************************************************
    # Kiểm tra một điểm thuộc đoạn thẳng                                            
    # RETURN : TRUE      : Thuộc vào đoạn thẳng                                     
    #          FALSE     : Không thuộc đoạn thẳng                                   
    #[Author]: DesertFox       - [Date] : 12/11/2020                                
    *******************************************************************************/
    BOOL V2point_on_segment(const Vec2D& pt1,          // Điểm Start L       [input]
                            const Vec2D& pt2,          // Điểm End   L       [input]
                                  Vec2D& pt )          // Điểm xét          [output]
    {
        Vec2D p1a = V2sub(pt, pt1); // Vector p1a ;
        Vec2D p2a = V2sub(pt, pt2); // Vector p2a ;

        FLT crs = V2crs(p1a, p2a);

        // 3 collinear point if cross product isqual 0
        if (utils::IsEqual(crs, 0.0))
        {
            FLT dist_p1p  = V2mag(p1a);
            FLT dist_p2p  = V2mag(p2a);
            FLT dist_p1p2 = V2mag(V2sub(pt1, pt2));

            if (dist_p1p <= dist_p1p2 && dist_p2p <= dist_p1p2)
            {
                return TRUE;
            }
        }
        return FALSE;
    }

    /*******************************************************************************
    # Kiểm tra và lấy giao điểm giữa hai đường thẳng cho bởi 2 điểm                 
    # RETURN : TRUE      : Giao nhau                                                
    #          FLASE     : Không giao nhau                                          
    #[Author]: DesertFox       - [Date] : 12/11/2020                                
    *******************************************************************************/
    BOOL V2intersect_2line(const Vec2D& p1,           // Điểm Start L1       [input]
                           const Vec2D& p2,           // Điểm End   L1       [input]
                           const Vec2D& p3,           // Điểm Start L2       [input]
                           const Vec2D& p4 ,          // Điểm End   L2       [input]
                           Vec2D* pOutInter/*=NULL*/) // Giao điểm          [output]
    {
        // Phương trình đường thẳng AB: ax + by = c
        FLT a = p2.y - p1.y;
        FLT b = p1.x - p2.x;
        FLT c = a*(p1.x) + b*(p1.y);

        // Phương trình đường thẳng CD : a1x + b1y = c1
        FLT a1 = p4.y - p3.y;
        FLT b1 = p3.x - p4.x;
        FLT c1 = a1*(p3.x) + b1*(p3.y);

        FLT det = a*b1 - b*a1;

        Vec2D pInter; V2nan(pInter);
        BOOL binter = FALSE;

        // Hai đường thẳng không song song dường như cắt nhau
        if(utils::IsEqual(det , 0.0 , EPSILON_MED) == FALSE)
        {
            pInter.x = (b1 * c - b * c1) / det;
            pInter.y = (a * c1 - a1 * c) / det;
            binter = TRUE;
        }

        if (pOutInter) *pOutInter = pInter;

        return binter;
    }

    /*******************************************************************************
    # Kiểm tra và lấy giao điểm giữa hai đoạn thẳng                                 
    # RETURN : TRUE      : Giao nhau                                                
    #          FLASE     : Không giao nhau                                          
    #[Author]: DesertFox       - [Date] : 12/11/2020                                
    *******************************************************************************/
    BOOL V2intersect_2segment(const Vec2D& p1,           // Điểm Start L1    [input]
                              const Vec2D& p2,           // Điểm End   L1    [input]
                              const Vec2D& p3,           // Điểm Start L2    [input]
                              const Vec2D& p4,           // Điểm End   L2    [input]
                              Vec2D* pOutInter/*=NULL*/) // Giao điểm       [output]
    {
        Vec2D pInter; V2nan(pInter);
        BOOL bInter = FALSE;

        if (V2intersect_2line(p1, p2, p3, p4, &pInter) == TRUE)
        {
            if (V2point_on_segment(p1, p2, pInter) &&
                V2point_on_segment(p3, p4, pInter))
            {
                bInter = TRUE;
            }
        }

        if (pOutInter) *pOutInter = pInter;

        return bInter;
    }

    /*******************************************************************************
    # Vị trí tương đối của điểm với một vùng đóng                                   
    # RETURN : -1       : Nằm trong vùng                                            
    #           0       : Nằm trên đường viền                                       
    #           1       : Nằm ngoài vùng                                            
    # [Author]: DesertFox       - [Date] : 12/11/2020                               
    *******************************************************************************/
    Posrel V2rel_point2poly(const Vec2D& p, const Ap2D& xap)
    {
        if (xap.np < 3)  return Posrel::OUTSIDE;
        //  Tìm x max trong tất cả các điểm xap
        FLT apMaxX = xap[0].x;   INT count = 0;
        for (INT i = 0; i < xap.np; i++)
        {
            if (xap.ap[i].x >= apMaxX)
            {
                apMaxX = xap.ap[i].x;
            }
        }
        Vec2D pExtra(apMaxX + 1, p.y);

        // Điếm số giao điểm của đường thẳng đi qua p cắt area @@
        for (INT i = 0; i < xap.np; i++)
        {
            INT next = (i + 1) % xap.np;
            if (V2intersect_2line(xap.ap[i], xap.ap[next], p, pExtra))
            {
                if (V2oriex_point2line(xap.ap[i], xap.ap[next], p) == COLLINEAR
                    && V2betw_point22point(xap.ap[i], xap.ap[next], p))
                {
                    return Posrel::BOUNDARY;
                }
                count++;
            }
        }
        // Số giao điểm là lẻ thì ở bên trong và ngược lại
        return (count % 2 ==1)? Posrel::INSIDE : Posrel::OUTSIDE;
    }

    /*******************************************************************************
    # Kiểm tra mảng điểm có phải và polygon lồi không                               
    # Tư tưởng chính là kiểm tra 3 điểm liên tiếp nếu orintation thay đổi thì nó là 
    # RETURN : TRUE      Lồi                                                        
    #          FALSE     Lõm                                                        
    # [Author]: DesertFox       - [Date] : 12/11/2020                               
    *******************************************************************************/
    BOOL V2convex_poly(const Ap2D & xap)
    {
        if (xap.np < 3) return FALSE;

        // Khởi tạo hướng phụ thuộc vào vị trí của 3 điểm đầu 
        Orien oricheck = V2oriex_point2line(xap[0] ,xap[1] , xap[2]);

        INT x , y , next ;      // Thứ tự lần lượt là điểm 1, điểm 2, điểm 3
        for (INT i = 1; i < xap.np -1; i++)
        {
            x = i ; y = i+1;    // Tính vị trí 3 điểm liên tiếp
            next = (i+2) % xap.np;

            Orien ori = V2oriex_point2line(xap[x] ,xap[y] , xap[next]);

            if (ori != Orien::COLLINEAR)
            {
                if (ori != oricheck)
                {
                    return FALSE;
                }
            }
        }
        return TRUE;
    }

    /*******************************************************************************
    # Loại bỏ các điểm thẳng hàng liên tiếp                                         
    # RETURN : void                                                                 
    #          tọa độ điểm sẽ được cập nhật trực tiếp vào tham số                   
    # [Author]: DesertFox       - [Date] : 12/11/2020                               
    *******************************************************************************/
    void V2remove_consecutive_collinear( Ap2D & xap)
    {
        if(xap.np < 3 ) return;
        Ap2D temp;  INT prev = 0;
        for (INT i = 1; i < xap.np -1; i++)
        {
            if (V2oriex_point2line(xap[prev], xap[i], xap[i + 1])!= Orien::COLLINEAR)
            {
                temp.Add(xap[prev]);
                prev = i;
            }
        }
        if (V2oriex_point2line(xap[prev], xap[xap.np - 1], xap[0]) != Orien::COLLINEAR)
        {
            temp.Add(xap[xap.np - 1]);
        }

        xap.Swap(temp);
    }


    /*******************************************************************************
    # Tính toán trọng tâm của polygon                                               
    # RETURN : Tọa độ trong tâm của polygon                                         
    # Link : https://math.stackexchange.com/questions/90463                         
    # [Author]: DesertFox       - [Date] : 12/11/2020                               
    *******************************************************************************/
    Vec2D V2cal_centroid_poly(const Ap2D & xap)
    {
        if(xap.np < 3 ) return Vec2D(0 , 0);

        Vec2D centroid(0.0 ,0.0) ;
        FLT asum      = 0.0      ;   // Tổng diện tích polygon
        FLT asum_uint = 0.0      ;   // Diện tích từng đơn vị
        INT j         = xap.np -1;   // Một giải pháp không sử dụng số dư

        FLT x = 0.0 , y= 0.0;
        for (INT i = 0; i < xap.np; i++)
        {
            asum_uint = ((xap[j].x *xap[i].y) - (xap[j].y * xap[j].x));

            asum += asum_uint;

            x += ((xap[j].x *xap[i].x)* asum_uint);
            y += ((xap[j].y *xap[i].y)* asum_uint);
        }

        if (utils::IsNotEqual(asum, 0.0))
        {
            centroid.x =  x/(3.0 * asum);
            centroid.y =  y/(3.0 * asum);
        }
        return centroid;
    }

    /*******************************************************************************
    # Lấy điểm nhỏ nhất và lớn nhất bao toàn bộ  polygon                            
    # RETURN : void , tọa độ chuyền vào là điểm min ,max                            
    #[Author]: DesertFox       - [Date] : 12/11/2020                                
    *******************************************************************************/
    void DllExport V2minmax_boudary_poly(const Ap2D& xap, // Danh sách điểm [input ]
                                         Vec2D& pointmin, // Điểm nhỏ nhất  [output]
                                         Vec2D& pointmax) // Diểm lớn nhất  [output]
    {
        if(xap.np <=0 ) return;

        // Khởi tạo bằng điểm đầu tiên
        pointmax = pointmin = xap[0];

        for (INT i = 1; i < xap.np; i++)
        {
            if(xap[i].x < pointmin.x) pointmin.x = xap[i].x;
            if(xap[i].y < pointmin.y) pointmin.y = xap[i].y;

            if(xap[i].x > pointmax.x) pointmax.x = xap[i].x;
            if(xap[i].y > pointmax.y) pointmax.y = xap[i].y;
        }
    }

    /*******************************************************************************
    # Tìm vùng bao to nhất của mảng điểm                                            
    # RETURN : Đầu ra sẽ là vùng bao với chiều quay ngược chiều kim đồng hồ (CCW)   
    # Link : https://en.wikipedia.org/wiki/Graham_scan#                             
    # [Author]: DesertFox       - [Date] : 12/11/2020                               
    *******************************************************************************/
    Ap2D DllExport V2get_boundary_poly(const Ap2D& xap)
    {
        using namespace structsp;

        Ap2D boOut; 
        // 1. Tìm điểm min trong danh sách các điểm                 
        INT indMin = V2get_minpoint_poly(xap, NULL);
        if(indMin <= -1) return boOut;

        // 2. Sắp xếp theo tứ tự góc từ các điểm còn lại đến điểm min
        CompareEx<FLT,const Vec2D* >* arcmp = new CompareEx<FLT,const Vec2D* >[xap.np];
        for (INT i = 0; i < xap.np; i++)
        {
            //↓ N.V.Thuong [Comment out] Sai thuật toán
            //if (i != indMin)
            //{
                arcmp[i].m_cp   = V2angOx(V2sub(xap[i], xap[indMin]));
                arcmp[i].m_data = &xap[i];
            //}
            //↑ N.V.Thuong [Comment out] Sai thuật toán
        }
        structsp::fox_qsort<FLT, const Vec2D* >(arcmp, xap.np);

        boOut.Add(xap[indMin]);     // giá trị đầu luôn là điểm min;
        // 3. Thực hiện thuật toán  Graham scan
        for (INT i = 0; i < xap.np; i++)
        {
            if (arcmp[i].m_data != &xap[indMin]) // Không push điểm min
            {
                if (boOut.np > 1)
                {
                    Orien ori=  V2oriex_point2line(boOut[boOut.np-2], boOut[boOut.np-1], *arcmp[i].m_data);

                    if (ori == Orien::COLLINEAR || ori == Orien::RIGHT_SIDE)
                    {
                        boOut.RemoveBack();
                    }
                }
                boOut.Add(*((const Vec2D*)arcmp[i].m_data));
            }
        }
        delete[] arcmp;

        return boOut;
    }

    /*******************************************************************************
    # Tìm điểm thuộc polygon có giá trì x và y nhỏ nhất                             
    # RETURN : Tọa độ điểm có giá trị x và y nhỏ nhất                               
    # [Author]: DesertFox       - [Date] : 12/11/2020                                
    *******************************************************************************/
    INT DllExport V2get_minpoint_poly(const Ap2D& xap, Vec2D* pmin/* = NULL*/)
    {
        if (xap.np <= 0)
            return -1;

        // Khởi tạo giá trị vô định cho
        Vec2D ptmin;
        V2nan(ptmin);

        // Khởi tạo ban đầu   tại vị trí 0,0
        INT index = -1;

        // Khởi tạo bằng điểm đầu tiên tại vị trí 0
        index = 0 ; ptmin = xap[0];
        for (INT i = 1; i < xap.np; i++)
        {
            if (xap[i].x < ptmin.x || xap[i].y < ptmin.y)
            {
                ptmin = xap[i];
                index = i;
                continue;
            }
        }

        if (pmin)  *pmin = ptmin;

        return index;
    }

    /*******************************************************************************
    # Sắp xếp mảng điểm theo phong cách nhất định                                   
    # RETURN : Danh sách các điểm nối thành vùng bao                                
    # [Author]: DesertFox       - [Date] : 12/11/2020                                
    *******************************************************************************/
    void DllExport V2sort_points(Ap2D& xap,                // Mảng điếm sử dụng Ap2D
                                 INT(*cmp)(const void*, const void*)/*= _cmp_vec2d*/)
    {
        if(xap.np <= 1 ) return ;
        // Trong trường hợp không có hàm truyền vào ta sẽ sử dụng hàm cố đinh 
        qsort(&xap.ap[0] ,xap.np,sizeof(Vec2D), cmp);
    }

    /*******************************************************************************
    # Kiểm tra một mảng điểm có điểm nào thuộc trong tam giác không                 
    # RETURN : TRUE  : Có                                                           
    #          FALSE : Không                                                        
    # [Author]: DesertFox       - [Date] : 12/11/2020                               
    *******************************************************************************/
    BOOL DllExport V2check_points_in_tri(const Ap2D& xap,        //Tọa độ mảng điểm 
                                         const Vec2D& p1,        //Tọa độ điểm 1    
                                         const Vec2D& p2,        //Tọa độ điểm 2    
                                         const Vec2D& p3)        //Tọa độ điểm 3    
    {
        // Điểm nằm trong sẽ có cùng hướng với các cạnh
        Orien orp12 , orp23, orp31;
        for (INT i = 0; i < xap.np; i++)
        {
            orp12 = V2oriex_point2line(p1 , p2 , xap[i]);
            orp23 = V2oriex_point2line(p2 , p3 , xap[i]);
            orp31 = V2oriex_point2line(p3 , p1 , xap[i]);

            if (orp12 == orp23 && orp23 == orp31)
            {
                return TRUE;
            }
        }
        return FALSE;
    }

    /*******************************************************************************
    # Kiểm tra một tam giác trong mảng điểm có điểm nào trong mảng điểm nằm trong   
    # Chú ý : in1 , in2 ,in3 phải nằm trong khoảng 0< in1, in2, in3 <xap.np         
    # RETURN : TRUE  : Có                                                           
    #          FALSE : Không                                                        
    # [Author]: DesertFox       - [Date] : 12/11/2020                               
    *******************************************************************************/
    BOOL DllExport V2check_points_in_tri(const Ap2D& xap,     //Tọa độ mảng điểm    
                                         const INT&  in1,     //Chỉ số tọa độ điểm 1
                                         const INT&  in2,     //Chỉ số tọa độ điểm 2
                                         const INT&  in3)     //Chỉ số tọa độ điểm 3
    {
        // Điểm nằm trong sẽ có cùng hướng với các cạnh
        Orien orp12 , orp23, orp31;
        for (INT i = 0; i < xap.np; i++)
        {
            // Không tính các điểm thuộc vào tam giác check
            if(i == in1 || i == in2 || i == in3)  continue;
            orp12 = V2oriex_point2line(xap[in1], xap[in2], xap[i]);
            orp23 = V2oriex_point2line(xap[in2], xap[in3], xap[i]);
            orp31 = V2oriex_point2line(xap[in3], xap[in1], xap[i]);

            if (orp12 == orp23 && orp23 == orp31)
            {
                return TRUE;
            }
        }
        return FALSE;
    }


    /*******************************************************************************
    # Kiểm tra một mảng điểm có điểm nào thuộc trong tam giác không                 
    # RETURN : -1  : Nằm trong tam giác                                             
    #           0  : Nằm trên đường viền                                            
    #           1  : Nằm ngoài tam giác                                             
    *******************************************************************************/
    Posrel DllExport V2rel_point_in_tri(const Vec2D& p1,          //Tọa độ điểm 1   
                                        const Vec2D& p2,          //Tọa độ điểm 2   
                                        const Vec2D& p3,          //Tọa độ điểm 3   
                                        const Vec2D& p )          //Điểm xét        
    {
        Orien orp12 , orp23, orp31;  // Vị trí của điểm với các cạnh

        FLT snap = 5;       // Khoảng cách nhỏ lớn nhất có thể bắt đoạn thẳng

        if (V2check_point_in_segment(p1, p2, p, snap)) return Posrel::BOUNDARY;
        orp12 = V2oriex_point2line(p1, p2, p);

        if (V2check_point_in_segment(p2, p3, p, snap)) return Posrel::BOUNDARY;
        orp23 = V2oriex_point2line(p2, p3, p);

        if (V2check_point_in_segment(p3, p1, p, snap)) return Posrel::BOUNDARY;
        orp31 = V2oriex_point2line(p3, p1, p);

        // Điểm nằm trong sẽ có cùng hướng với các cạnh
        if (orp12 == orp23 && orp23 == orp31)
        {
            return Posrel::INSIDE;
        }
        return Posrel::OUTSIDE;
    }

    /*******************************************************************************
    # Kiểm tra một điểm có nằm trên đường thẳng dựa vào khoảng cách                 
    # RETURN : TRUE  : Có                                                           
    #          FALSE : Không                                                        
    *******************************************************************************/
    BOOL DllExport V2check_point_in_segment(const Vec2D& p1,       //Điểm start L   
                                            const Vec2D& p2,       //Điểm end   L   
                                            const Vec2D& p ,       //Điểm xét       
                                            const FLT& snap/*0.0*/)//Độ nhạy        
    {
        // Tính khoảng ngắn nhất từ điểm đó đến đoạn thẳng có sử dụng độ nhạy

        FLT dismin = V2dismin_point2segment(p1, p2, p);

        if (utils::IsSmallerOrEqual(dismin, snap))
        {
            return TRUE;
        }

        return FALSE;
    }

    /*******************************************************************************
    # Quan hệ điểm và đoạn thẳng                                                    
    # RETURN : TRUE  : Có                                                           
    #          FALSE : Không                                                        
    *******************************************************************************/
    BOOL DllExport V2rel_point_in_segment(const Vec2D& p1,       //Điểm start L     
                                          const Vec2D& p2,       //Điểm end   L     
                                          const Vec2D& p )       //Điểm xét         
    {
        // @@ đang sử dụng cross product nhưng không chắc
        Vec2D p1p2 = V2sub(p2, p1);
        Vec2D p2p  = V2sub(p2, p);
        FLT dismin = V2crs(p1p2  , p2p);
        FLT snap = 5000.0;

        //Trường hợp 1: Nó nằm trên đường thẳng của hai điểm
        if (utils::IsSmallerOrEqual(fabs(dismin), snap))
        {
            //Trường hợp 1.1: Nằm trong đoạn hoặc đầu mút
            if (V2check_point_in_rectangle(p1, p2, p))
            {
                if (utils::IsEqual(p1, p))     return 1;// Điểm này gần p1      
                else if (utils::IsEqual(p2, p))return 2;// Điểm này gần p2      
                else return 3;                          // Nằm giữa thông thường
            }
            //Trường hợp 1.2: Nằm ngoài đoạn thẳng
            else
            {
                return 0;
            }
        }
        //Trường hợp 2: Không thuộc vào đường thẳng tạo bởi hai điểm
        else 
        {
            return -1; // Nằm ngoài
        }
    }

    /*******************************************************************************
    # Chia polygon thành triangle                                                   
    # RETURN : Mảng các tọa độ của tam giác                                         
    #          Tọa độ xap mảng điểm phải ngược chiều kim đồng hồ  (CCW)             
    #https://gamedev.net/tutorials/programming/graphics/polygon-triangulation-r3334/
    # [Author]: DesertFox       - [Date] : 12/11/2020                               
    *******************************************************************************/
    Ap2D DllExport V2split_poly2tri(const Ap2D & xap)
    {
        // Chú ý : Tọa độ mảng điểm là ngược chiều kim đồng hồ (CCW)
        Ap2D list_trig; Ap2D xapTemp;
        xapTemp = xap;  // Copy toàn bộ dữ liệu sang
        if (xap.np <= 3) list_trig = xap;

        while (xapTemp.np > 0)
        {
            //PS: Phòng trường hợp nó vào vòng lặp vô hạn nên ta sẽ có chặn trên
            INT old_size = xapTemp.np;
            for (INT i = 0; i < xapTemp.np ; i++)
            {
                // Đoạn này có thể tối ưu làm cho nó không sử dụng lấy phần dư
                INT cur = i; INT pre = ((i-1) <  0)? (xapTemp.np-1):(i-1);
                INT nex = ((i+1) >= xapTemp.np) ? 0:(i+1);

                Orien a =V2oriex_point2line(xapTemp[pre],xapTemp[cur], xapTemp[nex]) ;
                BOOL a1 = V2check_points_in_tri(xapTemp, pre, cur, nex);

                Orien orien = V2oriex_point2line(xapTemp[pre], xapTemp[cur], xapTemp[nex]);
                if ((orien == Orien::LEFT_SIDE || orien == Orien::COLLINEAR)
                    && V2check_points_in_tri(xapTemp, pre, cur, nex) == FALSE)
                {
                    list_trig.Add(xapTemp[pre], xapTemp[cur], xapTemp[nex]);
                    xapTemp.RemoveAt(cur);
                }
            }
            if(xapTemp.np == old_size) break;
        }
        return list_trig;
    }

    /*******************************************************************************
    # Tìm giao điểm của nhiều đường thẳng                                           
    # RETURN : Tọa độ mảng giao điểm và cặp giao điểm                               
    #                                                                               
    # Link: https://cp-algorithms.com/geometry/intersecting_segments.html           
    # [Author]: DesertFox       - [Date] : 12/11/2020                               
    *******************************************************************************/
    Ap2D DllExport V2intersect_nlines(const Ap2D & xap) 
    {
        // Ap2D là mảng điểm mỗi cặp là 1 đường thẳng  [01][12][34]...
        using namespace structsp;
        Ap2D points_inter;

        // Không có điểm hoặc số điểm là lẻ
        if (xap.np == 0 || xap.np % 2 != 0) return Ap2D();

        //1. Sắp sếp các đỉnh theo thứ tự tăng dần x và tăng dần y
        CompareEx<Vec2D,FLOAT>* arcmp = new CompareEx<Vec2D,FLOAT >[xap.np];
        for (INT i = 0; i < xap.np; i+=2)
        {
            arcmp[i].m_cp   = xap[i];
            arcmp[i].m_data = i +0.5;

            arcmp[i+1].m_cp   = xap[i+1];
            arcmp[i+1].m_data = i +0.5;
        }
        fox_qsort<Vec2D, FLOAT>(arcmp, xap.np, utils::_cmp_vec2d);

        vector<FLOAT> list_check_inter; Vec2D inter;
        //2. Thực hiện thuật toán 
        for (INT i = 0; i < xap.np ;i++ )
        {
            bool isTail = false;
            for (auto it = list_check_inter.begin() ; it != list_check_inter.end(); )
            {
                // Tìm thấy điểm kết thúc của đường thẳng => remove đoạn thẳng ra ngoài
                if (arcmp[i].m_data == *it)
                {
                    // Tìm các điểm giao trong list đường thẳng có thẻ giao
                    INT _size = list_check_inter.size();
                    for (INT x =0; x < _size  ; x++)
                    {
                        INT istart1 = (INT)(list_check_inter[x] - 0.5);
                        INT iend1   = (INT)(list_check_inter[x] + 0.5);
                        INT istart2 = (INT)(*it - 0.5);
                        INT iend2   = (INT)(*it + 0.5);
                        if (list_check_inter[x] != *it)
                        {
                            BOOL isInter = V2intersect_2segment(xap[istart1], xap[iend1], xap[istart2], xap[iend2], &inter);
                            if (isInter)
                            {
                                points_inter.Add(inter);
                            }
                        }
                    }
                    it = list_check_inter.erase(it);
                    isTail = true;
                    break;
                }
                else it++;
            }
            if (!isTail)
            {
                list_check_inter.push_back(arcmp[i].m_data);
            }
        }
        delete[] arcmp;

        return points_inter;
    }

    /*******************************************************************************
    # Kiểm tra xem một điểm có thuộc miền vuông góc với đoạn thẳng cho bởi 2 điểm   
    # RETURN : TRUE  : Thuộc miền                                                   
    #          FALSE : Không thuộc miền                                           OK
    *******************************************************************************/
    BOOL DllExport V2check_point_in_perp_domain( const Vec2D& p1, // Điểm đầu       
                                                 const Vec2D& p2, // Điểm cuối      
                                                 const Vec2D& p ) // Điểm xét       
    {
        Vec2D p1p2 = V2sub(p2, p1);      // Vector p1p2
        Vec2D p1p  = V2sub(p , p1);      // Vector p1p
        Vec2D p2p  = V2sub(p , p2);      // Vector p2p

                                         // Dot product của 2 vector :  p1p2_p2p; p1p2_p1p;
        FLT p1p2_p2p = V2dot(p1p2, p2p);
        FLT p1p2_p1p = V2dot(p1p2, p1p);

        // Trường hợp không thuộc miền vuông góc của đoạn thẳng
        if (utils::IsGreater(p1p2_p2p, 0.0) || utils::IsSmaller(p1p2_p1p, 0.0))
        {
            return FALSE;
        }
        return TRUE;
    }

    /*******************************************************************************
    # Kiểm tra xem một điểm có thuộc vùng bao được cho bởi hai điểm min, max        
    # RETURN : TRUE  : Thuộc rectangle                                              
    #          FALSE : Không thuộc rectangle                                      OK
    *******************************************************************************/
    BOOL DllExport V2check_point_in_rectangle(const Vec2D& pr1,  // Điểm rect 1    
                                              const Vec2D& pr2,  // Điểm rect 2    
                                              const Vec2D& p)    // Điểm xét       
    {
        if (p.x >= min(pr1.x, pr2.x) && p.x <= max(pr1.x, pr2.x) &&
            p.y >= min(pr1.y, pr2.y) && p.y <= max(pr1.y, pr2.y))
        {
            return TRUE;
        }
        return FALSE;
    }

    /*******************************************************************************
    # Tìm điểm chiếu vuông góc xuống đường thẳng cho bởi 2 điểm                     
    # RETURN : Tọa độ điểm vuông góc xuống                                          
    # [Author]: DesertFox       - [Date] : 12/11/2020                             OK
    *******************************************************************************/
    Vec2D DllExport V2perpendicular_point2line(const Vec2D& p1,// Điểm đầu đt  L    
                                               const Vec2D& p2,// Điểm cuối đt L    
                                               const Vec2D& p )// Điểm xét          
    {
        Vec2D per ; // Đối với đường thẳng thì luôn có điểm chiếu vuông góc xuống 
        Vec2D p1p2 = V2sub(p2, p1);      // Vector p1p2
        Vec2D p1p  = V2sub(p , p1);      // Vector p1p
        Vec2D p2p  = V2sub(p , p2);      // Vector p2p

        FLT mag = p1p2.x* p1p2.x + p1p2.y* p1p2.y;

        // Trường hợp tổng quát điểm giao đường thẳng
        if (!utils::IsEqual(mag, 0.0))
        {
            FLT det = V2dot(p1p, p1p2);

            FLT t = det / mag;
            per.x = p1.x + t*(p2.x - p1.x);
            per.y = p1.y + t*(p2.y - p1.y);
        }
        else
        {
            // Trường hợp này hai điểm đoạn thẳng trùng nhau  bằng p1 hoặc p2
            per = p1;
        }
        return per;
    }

    /*******************************************************************************
    # Tìm điểm chiếu vuông góc xuống đoạn thẳng cho bởi 2 điểm                      
    # RETURN : Tọa độ điểm vuông góc xuống                                          
    # Link : https://stackoverflow.com/questions/10301001/                          
    # [Author]: DesertFox       - [Date] : 12/11/2020                             OK
    *******************************************************************************/
    BOOL DllExport V2perpendicular_point2segment(const Vec2D& p1,   // Điểm đầu     
                                                 const Vec2D& p2,   // Điểm cuối    
                                                 const Vec2D& p ,   // Điểm xét     
                                                       Vec2D* pout) // Điểm chiếu   
    {
        Vec2D per;  BOOL ret = FALSE;    // Điểm vuông góc, giá trị trả về

        // Trường hợp không có vuông góc, vượt quá đầu mút
        if (!V2check_point_in_perp_domain(p1, p2, p))
        {
            V2nan(per);
        }
        else
        {   // Trường hợp này lấy vuông góc xuống đoạn thẳng
            if (pout == NULL) return TRUE;

            Vec2D p1p2 = V2sub(p2, p1);      // Vector p1p2
            Vec2D p1p  = V2sub(p , p1);      // Vector p1p

            FLT mag = p1p2.x* p1p2.x + p1p2.y * p1p2.y, det = V2dot(p1p, p1p2);

            if (!utils::IsEqual(mag, 0.0))
            {
                FLT t = det / mag;
                per.x = p1.x + t*(p2.x - p1.x);
                per.y = p1.y + t*(p2.y - p1.y);
            }
            // Trường hợp này hai điểm đoạn thẳng trùng nhau
            else per = p1;
            ret = TRUE;
        }
        if (pout != NULL) { *pout = per; } // Điểm vuông góc trả về
        return ret;
    }

    /*******************************************************************************
    # Tìm khoảng cách ngắn nhất từ một điểm đến đoạn thẳng                          
    # RETURN : Khoảng cách nhỏ nhất [Luôn dương]                                  OK
    *******************************************************************************/
    FLT DllExport V2dismin_point2segment( const Vec2D& p1,          // Điểm đầu  [i]
                                          const Vec2D& p2,          // Điểm cuối [i]
                                          const Vec2D& p)           // Điểm xét  [i]
    {
        FLT dis = NAN;  //Khoảng cách từ điểm p đến đoạn thẳng p1p2

        Vec2D p1p2 = V2sub(p2, p1);
        Vec2D p1p  = V2sub(p, p1);
        Vec2D p2p  = V2sub(p, p2);

        FLT dot_p1p2_p2p = V2dot(p1p2, p2p);
        FLT dot_p1p2_p1p = V2dot(p1p2, p1p);

        // Điểm p gần điểm p2 => Khoảng cách là p2p
        if (dot_p1p2_p2p > 0)
        {
            dis = V2mag(p2p);
        }
        // Điểm p gần điểm p1 => Khoảng cách là p1p
        else if (dot_p1p2_p1p < 0)
        {
            dis = V2mag(p1p);
        }
        // Đơn giản chỉ là đường vuông góc từ p xuống p1p2
        else
        {
            FLT mod = V2mag(p1p2);
            dis = abs(V2crs(p1p2, p1p)) / mod;
        }
        return dis;
    }

    /*******************************************************************************
    # Tìm điểm đối xứng của điểm qua đường thẳng cho bởi 2 điểm                     
    # RETURN : Tọa độ điểm đối xứng qua đường thẳng                                 
    # Link : https://stackoverflow.com/questions/3306838                            
    # [Author]: DesertFox       - [Date] : 12/11/2020                             OK
    *******************************************************************************/
    Vec2D V2refect_point2line(const Vec2D& p1,           // Điểm đầu đoạn thẳng     
                              const Vec2D& p2,           // Điểm cuối đoạn thẳng    
                              const Vec2D& p )           // Điểm cần lấy đối xứng   
    {
        // Định nghĩa đường thẳng đi qua p1, p2 là : y = mx + c
        Vec2D ref; FLT denom = (p2.x - p1.x), numer = (p2.y - p1.y);

        // Trường hợp đường thẳng song song với trục Oy 
        if (utils::IsEqual(denom , 0.0))
        {
            ref.x = (p1.x - p.x) + p1.x;
            ref.y = p.y;
        }
        // Trường hợp đường thẳng song song với trục Ox
        else if (utils::IsEqual(numer,0.0))
        {
            ref.x = p.x;
            ref.y = (p1.y - p.y) + p1.y;
        }
        // Trường hợp đối xứng thông thường
        else
        {
            FLT m = numer / denom;
            FLT c = (p2.x*p1.y - p1.x*p2.y) / denom;
            FLT d = (p.x + (p.y - c)*m) / (1 + m*m);

            ref.x = 2 * d - p.x;
            ref.y = 2 * d*m - p.y + 2*c;
        }
        return ref;
    }

    /*******************************************************************************
    # Tìm điểm đối xứng của điểm qua đoạn thẳng cho bởi 2 điểm                      
    # RETURN : TRUE  : Tồn tại điểm đối xứng                                        
    #          FALSE : Không tại điểm đối xứng                                      
    #          pout  : Tọa độ điểm trả về nếu tồn tại                             OK
    *******************************************************************************/
    BOOL DllExport V2refect_point2segment(const Vec2D& p1,   // Điểm đầu đt L    [i]
                                          const Vec2D& p2,   // Điểm cuối đt L   [i]
                                          const Vec2D& p ,   // Điểm lấy         [i]
                                          Vec2D* pout )      // Điểm đối xứng    [O]
    {
        // Định nghĩa đường thẳng đi qua p1, p2 là : y = mx + c
        Vec2D ref; BOOL ret =FALSE; // Điểm đối xứng + giá trị trả về

        // Trường hợp không có điểm đối xứng qua đoạn thẳng
        if (!V2check_point_in_perp_domain(p1 , p2 ,p))
        {
            V2nan(ref);
        }
        // Trường hợp tồn tại điểm đối xứng qua đoạn thẳng
        else
        {
            FLT denom = (p2.x - p1.x), numer = (p2.y - p1.y);
            // Trường hợp đoạn thẳng song song với trục Oy 
            if (utils::IsEqual(denom , 0.0))
            {
                ref.x = (p1.x - p.x) + p1.x;
                ref.y = p.y;
            }
            // Trường hợp đoạn thẳng song song với trục Ox
            else if (utils::IsEqual(numer,0.0))
            {
                ref.x = p.x;
                ref.y = (p1.y - p.y) + p1.y;
            }
            // Trường hợp đối xứng thông thường
            else
            {
                FLT m = numer / denom;
                FLT c = (p2.x*p1.y - p1.x*p2.y) / denom;
                FLT d = (p.x + (p.y - c)*m) / (1 + m*m);

                ref.x = 2 * d - p.x;
                ref.y = 2 * d*m - p.y + 2*c;
            }
            ret = TRUE;
        }
        if (pout) { *pout = ref; }  // Điểm đối xứng trả về 
        return ret;
    }

    /*******************************************************************************
    # Tìm điểm đối xứng của điểm qua điểm                                           
    # RETURN : Tọa độ điểm đối xứng qua điểm                                        
    # [Author]: DesertFox       - [Date] : 12/11/2020                             OK
    *******************************************************************************/
    Vec2D V2refect_point2point(const Vec2D& p1,           // Điểm đầu lấy đối xứng  
                               const Vec2D& p )           // Điểm cần đối xứng      
    {
        // Tìm độ dài từ điểm cần lấy đến điểm trung tâm 
        // Di chuyển điểm ở giữa với một độ lớn bằng p1p và vector đơn vị tương ứng
        Vec2D ref; Vec2D dir_vect = V2sub(p, p1);
        Vec2D unit  = V2uint(dir_vect);
        FLT   mag   = V2mag(dir_vect) ;

        ref = V2movpnd(p, unit, mag );
        return ref;
    }

    /*******************************************************************************
    # Tìm polygon sau khi đoạn thẳng cắt polygon                                    
    # RETURN : Mảng các polygon được đường thẳng cắt ra                             
    # [Author]: DesertFox       - [Date] : 12/11/2020                               
    *******************************************************************************/
    vector<Ap2D> V2cut_line2poly(const Vec2D p1,  // Điểm đầu                       
                                 const Vec2D p2,  // Điểm thứ 2 đoạn thẳng          
                                 const Ap2D& xap) // Điểm polygon                   
    {
        vector<Ap2D> vec_poly_split;
        BOOL  bInter;  Vec2D pInter;
        vector<std::pair<Vec2D, pair<INT, INT>>> vInter;
        for (INT i = 0; i< xap.np; i++)
        {
            INT x= i, y= (i + 1) % xap.np;
            BOOL bLoop = FALSE;
            bInter = V2intersect_2segment(xap[x], xap[y], p1, p2, &pInter);
            if (bInter)
            {
                for (INT ii = 0; ii < vInter.size(); ii++)
                {
                    if (utils::IsEqual(pInter, vInter[ii].first))
                    {
                        vInter[ii].first = pInter;
                        vInter[ii].second = make_pair(x ,y);
                        bLoop = TRUE;
                        break;
                    }
                }
                if (bLoop == FALSE)
                {
                    vInter.push_back({ pInter, {x,y} });
                }
            }
        }
        // Sắp xếp các đỉnh giao theo một thứ tự nào đó. ???

        BOOL* arMark = new BOOL[xap.np];
        for (INT i = 0; i < xap.np; i++)
        {
            arMark[i] = FALSE;
        }
        
        for (INT i = 0; i < xap.np; i++)
        {
            if (arMark[i] == FALSE)
            {
                Ap2D poly_split;
                INT index = i; INT count =0;

                while (count < xap.np)  //PS: Phòng trường hợp nó vào vòng lặp vô hạn nên ta sẽ có chặn trên
                {
                    INT x = index; INT y = (index + 1)% xap.np;

                    Orien or_pfirst = poly_split.np == 0 ? Orien::COLLINEAR : V2oriex_point2line(p1, p2, poly_split[0]);
                    Orien or_pstart = V2oriex_point2line(p1, p2, xap[x]);

                    // Câu lệnh dưới tương đương = or_pfirst và or_pstart = Orien::COLLINEAR
                    if (or_pfirst * or_pstart == Orien::COLLINEAR || (or_pstart == or_pfirst))
                    {
                        poly_split.Add(xap[x]);
                        arMark[x] = TRUE;
                    }
                    BOOL check = FALSE;
                    // Đẩy các điểm giao cắt vào polygon
                    for (INT ii = 0; ii < vInter.size(); ii++)
                    {
                        if (x == vInter[ii].second.first && y == vInter[ii].second.second)
                        {
                            or_pfirst = poly_split.np == 0 ? Orien::COLLINEAR : V2oriex_point2line(p1, p2, poly_split[0]);
                            Orien or_pend   = V2oriex_point2line(p1, p2, xap[y]);

                            poly_split.Add(vInter[ii].first);

                            if (or_pend == Orien::COLLINEAR || (or_pend == or_pfirst))
                            {
                                poly_split.Add(xap[y]);
                                arMark[y] = TRUE;
                                index = y;
                            }

                            // Tìm điểm giao gần nhất theo chiều ngược chiều kim đồng hồ (CCW)
                            FLT fDisMin = -1; INT iIndexMin = ii;
                            for (INT in = 0; in < vInter.size(); in++)
                            {
                                FLT dis = V2mag(V2sub(vInter[in].first, vInter[ii].first));
                                Orien ori_min = V2oriex_point2line(xap[x], xap[y], vInter[in].first);
                                if (in != ii && (ori_min == Orien::LEFT_SIDE &&  ( fDisMin ==-1 ||dis <= fDisMin)))
                                {
                                    iIndexMin = in;
                                    fDisMin = dis;
                                }
                            }

                            poly_split.Add(vInter[iIndexMin].first);

                            INT st = vInter[iIndexMin].second.first;
                            INT ed = vInter[iIndexMin].second.second;
                            if (V2oriex_point2line(p1, p2, xap[st]) == or_pfirst)
                            {
                                poly_split.Add(xap[st]);
                                arMark[st] = TRUE;
                                index = st;
                            }

                            if (V2oriex_point2line(p1, p2, xap[ed]) == or_pfirst)
                            {
                                poly_split.Add(xap[ed]);
                                arMark[ed] = TRUE;
                                index = ed;
                                check = TRUE;
                            }
                            break;
                        }
                    }
                    if(check == FALSE) index = y;
                    count++;
                    if(i == index ) break;
                }
                vec_poly_split.push_back(poly_split);
            }
        }
        delete arMark;
        for (INT i = 0; i < vec_poly_split.size(); i++)
        {
            V2remove_double_point(vec_poly_split[i]);
        }
        return vec_poly_split;
    }
    // Trường hợp đặc biệt là các điểm đầu mút
    //if (utils::IsGreater(p1p2_p2p , 0.0))
    //{
    //    
    //}
    //else if (utils::IsSmaller(p1p2_p1p, 0.0))
    //{
    //    per = p1;
    //}
}
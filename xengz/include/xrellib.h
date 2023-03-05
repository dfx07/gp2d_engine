#ifndef XRELLIB_H
#define XRELLIB_H


#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "xcom.h"
#include "x2dlib.h"

using namespace std;

namespace fox
{
    /*******************************************************************************
    # Lấy khoảng cách từ điểm đến một điểm theo một vector                          
    # [ R ] : Độ dài thể hiện qua 2 đại lượng [t, d] có thể âm                      
    # [/!\] : Đại lượng [t, d] có thể âm                                            
    *******************************************************************************/
    void  DllExport V2pvp(const Vec2D& p,    //Điểm tính                        [IN]
                          const Vec2D& pc,   //Điểm kết thúc                    [IN]
                          const Vec2D& v,    //Vec chỉ hướng lấy   rect         [IN]
                          FLT& t,            //Độ dài cạnh đầu của rect        [OUT]
                          FLT& d);           //Độ dài cạnh còn lại rect        [OUT]

    /*******************************************************************************
    # Lấy vector đơn vị của một góc [Độ lớn vector =1]                              
    # RETURN : Góc sau chuẩn hóa trong khoảng [0 -> 2PI] radian                     
    *******************************************************************************/
    Vec2D DllExport V2uint_angle(const FLT& rAng);

    /*******************************************************************************
    # Tiêu chuẩn hóa góc đưa góc về khoảng [0 -> 2PI]                               
    # RETURN : Góc sau chuẩn hóa trong khoảng [0 -> 2PI] radian                     
    *******************************************************************************/
    FLT DllExport V2standardize_angle(const FLT& rAng);

    /*******************************************************************************
    # Tiêu chuẩn hóa góc đưa góc về khoảng [0 -> 2PI]                               
    # RETURN : void (chuẩn hóa luôn tham số đầu vào)                                
    *******************************************************************************/
    void DllExport V2standardize_anglex(FLT& rAng);

    /*******************************************************************************
    # Vị trí trái phải của 1 điểm (r) với một đoạn thẳng cho bởi 2 điểm  (p1p2)     
    # RETURN : -1       : Bên trái đường thẳng                                      
    #           0       : Ba điểm thẳng hàng                                        
    #           1       : Bên phải đường thẳng                                      
    *******************************************************************************/
    INT DllExport V2ori_point2line(const Vec2D& p1, const Vec2D& p2, const Vec2D& r);


    /*******************************************************************************
    # Vị trí trái phải của 1 điểm (r) với một đoạn thẳng cho bởi 2 điểm gần đúng    
    # RETURN : -1       : Bên trái đường thẳng                                      
    #           0       : Ba điểm thẳng hàng                                        
    #           1       : Bên phải đường thẳng                                      
    *******************************************************************************/
    Orien DllExport V2oriex_point2line(const Vec2D& p1, const Vec2D& p2, const Vec2D& r);


    /*******************************************************************************
    # Kiểm tra xem một điểm nằm giữa hai điểm  [ĐK: không phải chính giữa]          
    # RETURN : TRUE     : Điểm nằm giữa                                             
    #          FLASE    : Điểm nằm ngoài                                            
    *******************************************************************************/
    BOOL DllExport V2betw_point22point(const Vec2D& p, const Vec2D& q, const Vec2D& m);


    /*******************************************************************************
    # Lấy điểm max min của hai đoạn thẳng cho bởi 4 điểm phục vụ cho hàm giao       
    # RETURN : min      : Điểm trên cùng                                            
    #          max      : Điểm dưới cùng                                            
    *******************************************************************************/
    void DllExport V2minmax_2segment(const Vec2D& p1 ,  // Điểm Start L1     [input]
                                     const Vec2D& p2 ,  // Điểm End   L1     [input]
                                     const Vec2D& p3 ,  // Điểm Start L2     [input]
                                     const Vec2D& p4 ,  // Điểm End   L2     [input]
                                     Vec2D* min = NULL, // Điểm nhỏ nhất    [output]
                                     Vec2D* max = NULL);// Điểm lớn nhất    [output]


    /*******************************************************************************
    # Xác định điểm nằm trong khoảng tọa độ đoạn thẳng                              
    # RETURN : TRUE      : Thuộc vào đoạn thẳng                                     
    #          FALSE     : Không thuộc đoạn thẳng                                   
    *******************************************************************************/
    BOOL DllExport V2point_on_bound_segment(const Vec2D& p1, // Điểm Start L [input]
                                            const Vec2D& p2, // Điểm End   L [input]
                                                  Vec2D& a );// Điểm xét    [output]


    /*******************************************************************************
    # Kiểm tra một điểm thuộc đoạn thẳng                                            
    # RETURN : TRUE      : Thuộc vào đoạn thẳng                                     
    #          FALSE     : Không thuộc đoạn thẳng                                   
    *******************************************************************************/
    BOOL DllExport V2point_on_segment(const Vec2D& pt1,  // Điểm Start L     [input]
                                      const Vec2D& pt2,  // Điểm End   L     [input]
                                            Vec2D& pt ); // Điểm xét        [output]

    /*******************************************************************************
    # Kiểm tra một điểm thuộc 1 đường thẳng cho bởi 2 điểm                          
    # RETURN : TRUE      : Thuộc vào đường thẳng                                    
    #          FALSE     : Không thuộc đường thẳng                                  
    *******************************************************************************/
    BOOL DllExport V2point_on_line(const Vec2D& pt1,    // Điểm Start L      [input]
                                   const Vec2D& pt2,    // Điểm End   L      [input]
                                         Vec2D& pt );   // Điểm xét         [output]

    /*******************************************************************************
    # Kiểm tra một điểm thuộc 1 đường thẳng cho 1 điểm và 1 vector đơn vị           
    # RETURN : TRUE      : Thuộc vào đường thẳng                                    
    #          FALSE     : Không thuộc đường thẳng                                  
    *******************************************************************************/
    BOOL DllExport V2point_on_line2(const Vec2D& p,    // Điểm Start L       [input]
                                    const Vec2D& v,    // Vector đơn vị      [input]
                                          Vec2D& pc ); // Điểm xét          [output]

    /*******************************************************************************
    # Kiểm tra một điểm thuộc một tia                                               
    # RETURN : TRUE      : Thuộc vào tia                                            
    #          FALSE     : Không thuộc tia                                          
    *******************************************************************************/
    BOOL DllExport V2point_on_ray(const Vec2D& pt,       // Điểm bắt đầu tia [input]
                                  const Vec2D& v,        // vector đơn vị tia[input]
                                        Vec2D& pc );     // Điểm xét        [output]

    /*******************************************************************************
    # Kiểm tra một điểm thuộc một tia                                               
    # RETURN : TRUE      : Thuộc vào tia                                            
    #          FALSE     : Không thuộc tia                                          
    *******************************************************************************/
    BOOL DllExport V2point_on_ray(const Vec2D& pt,       // Điểm bắt đầu tia [input]
                                  const Vec2D& v,        // vector đơn vị tia[input]
                                        Vec2D& pc );     // Điểm xét        [output]


    /*******************************************************************************
    # Kiểm tra và lấy giao điểm giữa hai đường thẳng cho bởi 2 điểm                 
    # RETURN : TRUE      : Giao nhau                                                
    #          FLASE     : Không giao nhau                                          
    *******************************************************************************/
    BOOL DllExport V2intersect_2line(const Vec2D& p1,   // Điểm Start L1     [input]
                                     const Vec2D& p2,   // Điểm End   L1     [input]
                                     const Vec2D& p3,   // Điểm Start L2     [input]
                                     const Vec2D& p4 ,  // Điểm End   L2     [input]
                                     Vec2D* pOutInter= NULL);// Giao điểm   [output]

    /*******************************************************************************
    # Kiểm tra và lấy giao điểm giữa hai đoạn thẳng                                 
    # RETURN : TRUE      : Giao nhau                                                
    #          FLASE     : Không giao nhau                                          
    *******************************************************************************/
    BOOL DllExport V2intersect_2segment(const Vec2D& p1,   // Điểm Start L1  [input]
                                        const Vec2D& p2,   // Điểm End   L1  [input]
                                        const Vec2D& p3,   // Điểm Start L2  [input]
                                        const Vec2D& p4 ,  // Điểm End   L2  [input]
                                        Vec2D* pOutInter= NULL);//Giao điểm [output]


    /*******************************************************************************
    # Vị trí tương đối của điểm với một vùng đóng                                   
    # RETURN : -1       : Nằm trong vùng                                            
    #           0       : Nằm trên đường viền                                       
    #           1       : Nằm ngoài vùng                                            
    *******************************************************************************/
    Posrel DllExport V2rel_point2poly(const Vec2D& p, const Ap2D& xap);


    /*******************************************************************************
    # Kiểm tra mảng điểm có phải và polygon lồi không                               
    # Tư tưởng chính là kiểm tra 3 điểm liên tiếp nếu orintation thay đổi thì nó là 
    # RETURN : TRUE      Lồi                                                        
    #          FALSE     Lõm                                                        
    *******************************************************************************/
    BOOL DllExport V2convex_poly(const Ap2D& xap);


    /*******************************************************************************
    # Loại bỏ các điểm thẳng hàng liên tiếp                                         
    # RETURN : void                                                                 
    #          tọa độ điểm sẽ được cập nhật trực tiếp vào tham số                   
    *******************************************************************************/
    void DllExport V2remove_consecutive_collinear( Ap2D& xap);

    /*******************************************************************************
    # Tính toán trọng tâm của polygon                                               
    # RETURN : Tọa độ trong tâm của polygon                                         
    #                                                                               
    *******************************************************************************/
    Vec2D DllExport V2cal_centroid_poly(const Ap2D& xap);

    /*******************************************************************************
    # Lấy điểm nhỏ nhất và lớn nhất bao toàn bộ  polygon                            
    # RETURN : void , tọa độ chuyền vào là điểm min ,max                            
    #                                                                               
    *******************************************************************************/
    void DllExport V2minmax_boudary_poly(const Ap2D& xap , // Điểm polygon          
                                         Vec2D &pointmin , // Điểm trái trên        
                                         Vec2D &pointmax); // Điểm phải dưới        

    /*******************************************************************************
    # Tìm vùng bao to nhất của mảng điểm                                            
    # RETURN : Đầu ra sẽ là vùng bao với chiều quay ngược chiều kim đồng hồ (CCW)   
    #                                                                               
    *******************************************************************************/
    Ap2D DllExport V2get_boundary_poly(const Ap2D& xap );

    /*******************************************************************************
    # Tìm điểm thuộc polygon có giá trì x và y nhỏ nhất                             
    # RETURN : Tọa độ điểm có giá trị x và y nhỏ nhất                               
    #                                                                               
    *******************************************************************************/
    INT DllExport V2get_minpoint_poly(const Ap2D& xap, Vec2D *pmin= NULL);

    /*******************************************************************************
    # Sắp xếp mảng điểm theo phong cách nhất định                                   
    # RETURN : Danh sách các điểm nối thành vùng bao                                
    #                                                                               
    *******************************************************************************/
    void DllExport V2sort_points(Ap2D& xap ,               // Mảng điếm sử dụng Ap2D
                                INT (*cmp)(const void*,const void*) = utils::_cmp_vec2d);

    /*******************************************************************************
    # Kiểm tra một mảng điểm có điểm nào thuộc trong tam giác không                 
    # RETURN : TRUE  : Có                                                           
    #          FALSE : Không                                                        
    *******************************************************************************/
    BOOL DllExport V2check_points_in_tri(const Ap2D& xap,        //Tọa độ mảng điểm
                                         const Vec2D& p1,        //Tọa độ điểm 1    
                                         const Vec2D& p2,        //Tọa độ điểm 2    
                                         const Vec2D& p3);       //Tọa độ điểm 3    

    /*******************************************************************************
    # Kiểm tra một tam giác trong mảng điểm có điểm nào trong mảng điểm nằm trong   
    # Chú ý : in1 , in2 ,in3 phải nằm trong khoảng 0< in1, in2, in3 <xap.np         
    # RETURN : TRUE  : Có                                                           
    #          FALSE : Không                                                        
    *******************************************************************************/
    BOOL DllExport V2check_points_in_tri(const Ap2D& xap,     //Tọa độ mảng điểm   
                                         const INT&  in1,     //Chỉ số tọa độ điểm 1
                                         const INT&  in2,     //Chỉ số tọa độ điểm 2
                                         const INT&  in3);    //Chỉ số tọa độ điểm 3

    /*******************************************************************************
    # Kiểm tra một mảng điểm có điểm nào thuộc trong tam giác không                 
    # RETURN : -1  : Nằm trong tam giác                                             
    #           0  : Nằm trên đường viền                                            
    #           1  : Nằm ngoài tam giác                                             
    *******************************************************************************/
    Posrel DllExport V2rel_point_in_tri(const Vec2D& p1,          //Tọa độ điểm 1   
                                        const Vec2D& p2,          //Tọa độ điểm 2   
                                        const Vec2D& p3,          //Tọa độ điểm 3   
                                        const Vec2D& p );         //Điểm xét        

    /*******************************************************************************
    # Kiểm tra một điểm có nằm trên đường thẳng dựa vào khoảng cách                 
    # RETURN : TRUE  : Có                                                           
    #          FALSE : Không                                                        
    *******************************************************************************/
    BOOL DllExport V2check_point_in_segment(const Vec2D& p1,       //Điểm start L   
                                            const Vec2D& p2,       //Điểm end   L   
                                            const Vec2D& p ,       //Điểm xét       
                                            const FLT& snap = 0.0);//Độ nhạy        

    /*******************************************************************************
    # Quan hệ điểm và đoạn thẳng                                                    
    # RETURN : TRUE  : Có                                                           
    #          FALSE : Không                                                        
    *******************************************************************************/
    INT DllExport V2rel_point_in_segment(const Vec2D& p1,       //Điểm start L      
                                         const Vec2D& p2,       //Điểm end   L      
                                         const Vec2D& p );      //Điểm xét          

    /*******************************************************************************
    # Chia polygon thành triangle                                                   
    # RETURN : Mảng các tọa độ của tam giác                                         
    #          Tọa độ xap mảng điểm phải ngược chiều kim đồng hồ  (CCW)             
    *******************************************************************************/
    Ap2D DllExport V2split_poly2tri(const Ap2D& xap);

    /*******************************************************************************
    # Tìm giao điểm của nhiều đường thẳng                                           
    # RETURN : Tọa độ giao điểm và cặp giao điểm                                    
    #                                                                               
    *******************************************************************************/
    Ap2D DllExport V2intersect_nlines(const Ap2D& xap);

    /*******************************************************************************
    # Kiểm tra xem một điểm có thuộc miền vuông góc với đoạn thẳng cho bởi 2 điểm   
    # RETURN : TRUE  : Thuộc miền                                                   
    #          FALSE : Không thuộc miền                                             
    *******************************************************************************/
    BOOL DllExport V2check_point_in_perp_domain( const Vec2D& p1, // Điểm đầu       
                                                 const Vec2D& p2, // Điểm cuối      
                                                 const Vec2D& p );// Điểm xét       

    /*******************************************************************************
    # Kiểm tra xem một điểm có thuộc vùng bao được cho bởi hai điểm min, max        
    # RETURN : TRUE  : Thuộc rectangle                                              
    #          FALSE : Không thuộc rectangle                                        
    *******************************************************************************/
    BOOL DllExport V2check_point_in_rectangle( const Vec2D& pr1,  // Điểm rect 1    
                                               const Vec2D& pr2,  // Điểm rect 2    
                                               const Vec2D& p );  // Điểm xét       

    /*******************************************************************************
    # Tìm điểm chiếu vuông góc xuống đường thẳng cho bởi 2 điểm                     
    # RETURN : Tọa độ điểm vuông góc xuống                                          
    #                                                                               
    *******************************************************************************/
    Vec2D DllExport V2perpendicular_point2line(const Vec2D& p1, // Điểm đầu         
                                               const Vec2D& p2, // Điểm cuối        
                                               const Vec2D& p );// Điểm chiếu       

    /*******************************************************************************
    # Tìm điểm chiếu vuông góc xuống đoạn thẳng cho bởi 2 điểm                      
    # RETURN : TRUE  : Nếu có hình chiếu                                            
    #          FALES : Không có hình chiếu                                          
    #          pout  : Điểm hình chiếu nếu có                                       
    *******************************************************************************/
    BOOL DllExport V2perpendicular_point2segment(const Vec2D& p1,   // Điểm đầu  [i]
                                                 const Vec2D& p2,   // Điểm cuối [i]
                                                 const Vec2D& p ,   // Điểm xét  [i]
                                                 Vec2D* pout= NULL);// Điểm chiếu[O]

    /*******************************************************************************
    # Tìm khoảng cách ngắn nhất từ một điểm đến đoạn thẳng                          
    # RETURN : Khoảng cách nhỏ nhất [Luôn dương]
    *******************************************************************************/
    FLT DllExport V2dismin_point2segment( const Vec2D& p1,          // Điểm đầu  [i]
                                          const Vec2D& p2,          // Điểm cuối [i]
                                          const Vec2D& p);          // Điểm xét  [i]

    /*******************************************************************************
    # Tìm điểm đối xứng của điểm qua đường thẳng cho bởi 2 điểm                     
    # RETURN : Tọa độ điểm đối xứng qua đường thẳng                                 
    #                                                                               
    *******************************************************************************/
    Vec2D DllExport V2refect_point2line(const Vec2D& p1, // Điểm đầu đoạn thẳng     
                                        const Vec2D& p2, // Điểm cuối đoạn thẳng    
                                        const Vec2D& p );// Điểm cần lấy đối xứng   

    /*******************************************************************************
    # Tìm điểm đối xứng của điểm qua đoạn thẳng cho bởi 2 điểm                      
    # RETURN : TRUE  : Tồn tại điểm đối xứng                                        
    #          FALSE : Không tại điểm đối xứng                                      
    #          pout  : Tọa độ điểm trả về nếu tồn tại                               
    *******************************************************************************/
    BOOL DllExport V2refect_point2segment(const Vec2D& p1,   // Điểm đầu đt L    [i]
                                          const Vec2D& p2,   // Điểm cuối đt L   [i]
                                          const Vec2D& p ,   // Điểm lấy         [i]
                                          Vec2D* pout= NULL);// Điểm đối xứng    [O]

    /*******************************************************************************
    # Tìm điểm đối xứng của điểm qua điểm                                           
    # RETURN : Tọa độ điểm đối xứng qua điểm                                        
    #                                                                               
    *******************************************************************************/
    Vec2D DllExport V2refect_point2point(const Vec2D& p1, // Điểm đầu lấy đối xứng  
                                         const Vec2D& p );// Điểm cần đối xứng      

    /*******************************************************************************
    # Tìm polygon sau khi đoạn thẳng cắt polygon                                    
    # RETURN : Mảng các polygon được đường thẳng cắt ra                             
    #                                                                               
    *******************************************************************************/
    vector<Ap2D> DllExport V2cut_line2poly(const Vec2D p1,   // Điểm đầu            
                                           const Vec2D p2,   // Điểm 2 đoạn thẳng   
                                           const Ap2D& xap );// Điểm polygon        
}
#endif // !XRELLIB_H


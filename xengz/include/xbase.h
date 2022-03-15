#ifndef XBASE_H
#define XBASE_H

#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <windows.h>
#include <winuser.h>

#include "xdef.h"

using namespace std;


namespace fox
{
    /****************************************************************************
    * NAMESPACE : structbase
    * Định nghĩa các loại dữ liệu trong : 2D, 3D.
    * ↓↓↓↓ [Author]: DesertFox    -[Date] :11/01/2021
    ***************************************************************************/
    namespace structbase
    {
        //=============================================================================
        //↓↓↓↓ V2D
        template <typename T>
        struct /*DllExport*/ V2D
        {
            T x;
            T y;

            V2D() : x(0), y(0)
            {
            };
            V2D(T x, T y) : x(x), y(y)
            {
            };
        };

        //=============================================================================
        //↓↓↓↓ V3D
        template <typename T>
        struct /*DllExport*/ V3D
        {
            T x;
            T y;
            T z;

            V3D() : x(0), y(0), z(0)
            {
            };
            V3D(T x, T y, T z) : x(x), y(y), z(z)
            {
            };
        };

        //=============================================================================
        //↓↓↓↓ LINE
        template <typename T>
        struct /*DllExport*/ LINE2D
        {
            V2D<T> p1;
            V2D<T> p2;

            LINE2D() : p1(0, 0), p2(0, 0)
            {
            };
            LINE2D(V2D<T> p1, V2D<T> p2) :p1(p1), p2(p2)
            {
            };
        };

        template <typename T>
        struct /*DllExport*/ LINE3D
        {
            V3D<T> p1;
            V3D<T> p2;

            LINE3D() : p1(0, 0, 0), p2(0, 0, 0) {}
            LINE3D(V3D<T> p1, V3D<T> p2) :p1(p1), p2(p2)
            {
            }
        };

        //=============================================================================
        //↓↓↓↓ COLOR 
        template <typename T>
        struct /*DllExport*/ COLORRGB
        {
            T r;
            T g;
            T b;
            T a;

            COLORRGB() : r(0), g(0), b(0), a(1)
            {
            };
            COLORRGB(T r, T g, T b, T a = 1) : r(r), g(g), b(b), a(a)
            {
            };
        };
    };

    typedef /*DllExport*/ structbase::V2D<FLT>         Vec2D  ;
    typedef /*DllExport*/ structbase::V2D<FLT>         Point2D;
    typedef /*DllExport*/ structbase::V2D<INT>         Loc2D  ;
    typedef /*DllExport*/ structbase::V2D<UINT>        Size2D ;
    typedef /*DllExport*/ structbase::V3D<FLT>         Vec3D  ;
    typedef /*DllExport*/ structbase::LINE2D<FLT>      Line2D ;
    typedef /*DllExport*/ structbase::LINE3D<FLT>      Line3D ;

    typedef /*DllExport*/ structbase::COLORRGB<UINT>   Color  ;
    typedef /*DllExport*/ structbase::COLORRGB<FLT>    GLColor;

    //===========================================================================
    //↓↓↓↓ Function cho class bên dưới

    BOOL DllExport operator==(const Vec2D& v1, const Vec2D& v2);

    //↑↑↑↑ Function cho class bên dưới
    //===========================================================================

    /****************************************************************************
    * NAMESPACE : structbase
    * Cấu trúc phần tử của các dữ liệu thông dụng: StackNode, ListNode,List2Node
    * ↓↓↓↓ [Author]: DesertFox    -[Date] :11/01/2021
    ***************************************************************************/
    namespace structbase
    {
        //=============================================================================
        //↓↓↓↓ STACK
        template <typename T>
        struct  StackNode
        {
            T m_data;
            StackNode* m_pNext;

            StackNode()
            {
                m_pNext = NULL;
            }
            StackNode(const T& obj)
            {
                m_pNext = NULL;
                m_data = obj;
            }
            StackNode* GetNext()
            {
                return m_pNext;
            }
            T* GetData()
            {
                return &m_data;
            }
        };

        //=============================================================================
        //↓↓↓↓ LIST1
        template <typename T>
        struct ListNode
        {
            T m_Data;
            ListNode* m_pNext;

            ListNode() : m_pNext(NULL) {}

            ListNode(const T& obj)
            {
                m_Data = obj;
            }
        };

        //=============================================================================
        //↓↓↓↓ LIST2
        template <typename T>
        struct List2Node
        {
            T m_data;
            List2Node* m_pNext;
            List2Node* m_pPrev;

            List2Node()
            {
                m_pNext = NULL;
                m_pPrev = NULL;
            }
            List2Node(const T& obj) : m_pNext(NULL), m_pPrev(NULL)
            {
                m_pNext = NULL;
                m_pPrev = NULL;
                m_data = obj;
            }
            List2Node* GetNext()
            {
                return m_pNext;
            }
            List2Node* GetPrev()
            {
                return m_pPrev;
            }
            T* GetData()
            {
                return &m_data;
            }
        };
    }

    /****************************************************************************
    * NAMESPACE : structgl
    * Cấu dữ liệu cơ bản sử dụng cho việc vẽ 2D và 3D : RectView
    * ↓↓↓↓ [Author]: DesertFox    -[Date] :17/01/2021
    ***************************************************************************/
    namespace structgl
    {
        class DllExport RectView
        {
        public:
            INT  m_iLeft   ;     //Tọa độ trái tọa độ view
            INT  m_iTop    ;     //Tọa độ trên tọa độ view
            UINT m_uiWidth ;     //Chiền rộng view
            UINT m_uiHeight;     //Chiều cao  view

        public:
            RectView() : m_iLeft(0) , m_iTop(0), m_uiHeight(0), m_uiWidth(0)
            {
            }
            RectView(INT left , INT right, UINT width, UINT height)
            {
                m_iLeft    = left  ;
                m_iTop     = right ;
                m_uiWidth  = width ;
                m_uiHeight = height;
            }
            void Set(INT left, INT right, UINT width, UINT height)
            {
                m_iLeft    = left  ;
                m_iTop     = right ;
                m_uiWidth  = width ;
                m_uiHeight = height;
            }
        };
    };

    /****************************************************************************
    * NAMESPACE : structsys
    * Cấu dữ liệu cơ bản chứa thông tin hệ thống
    * ↓↓↓↓ [Author]: DesertFox    -[Date] :17/01/2021
    ****************************************************************************/
    namespace structsys
    {
        struct DllExport MonitorInfo
        {
            INT           DISFREQ;      // Tần số làm mới màn hình 
            UINT          WIDTH  ;      // Chiều rộng màn hình
            UINT          HEIGHT ;      // Chiều cao màn hình
            INT           VERSION;      // Phiên bản driver màn hinh
            String        NAME   ;      // Tên thiết bị
        };
    }

    /****************************************************************************
    * NAMESPACE : structsp
    * Cấu dữ liệu cơ bản chứa hỗ trợ
    * ↓↓↓↓ [Author]: DesertFox    -[Date] :17/01/2021
    *****************************************************************************/
    namespace structsp
    {
        // Hàm này sử dụng cho so sanh bên dưới 
        // @@ Biết là nó không an toàn với luồng nhưng hiện tại chưa biết cách nào
        static int (*s_fcmp)(const void *, const void *) =NULL;

        // Hỗ trợ cho so sánh mở rộng 
        template<typename T ,class Tval>
        struct DllExport CompareEx
        {
            T       m_cp  ;                             
            Tval    m_data;                             

            //↑ Chú ý : Hàm gán của cấu trúc dữ liệu này .Nếu không
            //sử dụng hàm so sánh s_fcmp  thì nó sẽ sử dụng toán tử [< , == , >] mặc định của đối tượng
        };

        //🡓 Hàm giả operator cho việc tạo hàm sử dụng template
        namespace operafake
        {
            bool operator > (const Vec2D& a, const Vec2D& b);
            bool operator < (const Vec2D& a, const Vec2D& b);
            bool operator ==(const Vec2D& a, const Vec2D& b);
        }
        //🡑 Hàm giả operator cho việc tạo hàm sử dụng template

        // Hàm thực hiện sắp xếp dữ liệu sử dụng Quicksort 
        // Nếu không truyền vào cmp_fun nó sẽ sử dụng hàm so sánh mặc định;
        // Hàm cmp_fun cần trả về 3 giá trị :                             ;
        //                                 |  -1 nếu val1 đứng trước val2 ;
        //                                 |   0 nếu val1 bằng val2       ;
        //                                 |   1 nếu val1 đứng sau val2   ;
        template<typename T ,class Tval>
        void fox_qsort(CompareEx<T, Tval>* arr, size_t nsize, int (*cmp_fun)(const void* , const void*) = NULL)
        {
            s_fcmp = NULL;
            if (cmp_fun == NULL)
            {
                qsort(arr, nsize, sizeof(CompareEx<T, Tval>), _cmpsp_base<T, Tval>);
            }
            else
            {
                s_fcmp = cmp_fun;
                qsort(arr, nsize, sizeof(CompareEx<T, Tval>), _cmpsp_ext<T, Tval>);
            }
        }

        // Hàm so sanh giá trị của struct CompareEx mặc định với các loại dữ liệu mặc định
        // hoặc là các class đã operator  overloading [ <, == , > ]
        template<typename T, class Tval>
        inline int _cmpsp_base(const void* val1, const void* val2)
        {
            using namespace operafake;

           const auto& value1 = *((const CompareEx<T, Tval>*)val1);
           const auto& value2 = *((const CompareEx<T, Tval>*)val2);

           if(value1.m_cp < value2.m_cp )   return -1; // val1 đứng trước val2;
           if(value1.m_cp == value2.m_cp)   return  0; // val1 bằng val2      ;
           if(value1.m_cp > value2.m_cp )   return  1; // val1 đứng sau val2  ;
           return 1;
        }

        // Hàm so sanh giá trị của struct CompareEx mở rộng với tự định nghĩa hàm so sánh
        // của thành phần  m_cp hàm trả về int ={-1, 0 ,1}
        template<typename T, class Tval>
        inline int _cmpsp_ext(const void* val1, const void* val2)
        {
            //const CompareEx<T, Tval>& value1 = *((const CompareEx<T, Tval>*)val1);
            //const CompareEx<T, Tval>& value2 = *((const CompareEx<T, Tval>*)val2);
            if(s_fcmp == NULL) return -1;
            return  s_fcmp(val1, val2);
        }
    }


    /****************************************************************************
    * NAMESPACE : exstructbase
    * Cấu trúc dữ liệu thông dụng : Array, Stack, List, List2
    * ↓↓↓↓ [Author]: DesertFox    -[Date] :11/01/2021
    *****************************************************************************/
    namespace foxstruct
    {
        using namespace structbase;

        template <class T>
        class DllExport ArX
        {
        public:
            INT         np;
            vector<T>   ap;

        public:
            ArX() : np(0) {};
            ArX(INT np) : np(np) { ap.reserve(np); };
            ArX(const T& xap);
            /*******************************************************************************
            * Thêm một phần tử vào mảng Ap2D [Dùng trong đệ quy]
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void Add(T p);

            /*******************************************************************************
            * Thêm nhiều phần tử vào mảng Ap2D
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            template<typename... Types>
            void Add(T p, Types... vars);

            /*******************************************************************************
            * brief____: Xóa toàn bộ phần tử Vec2D trong Ap2D
            * return__ : void
            * [Author]: DesertFox - [Date] : 08/12/2020
            *******************************************************************************/
            void Clear();

            /*******************************************************************************
            * brief____: Hoán đổi dữ liệu của hai mảng Vec2D
            * return__ : void
            * [Author]: DesertFox - [Date] : 08/12/2020
            *******************************************************************************/
            void Swap(ArX<T>& xap);

            /*******************************************************************************
            * brief____: Sao chép dữ liệu từ mảng khác
            * return__ : void
            * [Author]: DesertFox - [Date] : 08/12/2020
            *******************************************************************************/
            void Copy(const ArX<T>& xap);

            /*******************************************************************************
            * brief____: Hoán đổi dữ liệu của hai mảng Vec2D
            * return__ : void
            * [Author]: DesertFox - [Date] : 08/12/2020
            *******************************************************************************/
            void Reverse();

            /*******************************************************************************
            * brief____: Lấy phần từ thứ i trong mảng [Lấy giá trị copy]
            * return__ : Giá trị T
            * [Author]: DesertFox - [Date] : 08/12/2020
            *******************************************************************************/
            T At(INT i)                 const;

            /*******************************************************************************
            * brief____: Lấy phần từ thứ i trong mảng [Lấy tham chiếu]
            * ---------  giá trị i luôn dương
            * return__ : Giá trị T
            * [Author]: DesertFox - [Date] : 08/12/2020
            *******************************************************************************/
            T& operator[] (INT i);

            const T& operator[] (INT i) const;

            ArX& operator= (const T& xap);

            /*******************************************************************************
            * Xóa phần tử thứ i trong mảng                                  
            * [Author]: DesertFox - [Date] : 08/12/2020                     
            # RETURN :  void                                                
            *******************************************************************************/
            void RemoveAt(INT i);

            /*******************************************************************************
            * brief____: Xóa phần tử cuối cùng của mảng                     
            * return__ : void                                               
            * [Author]: DesertFox - [Date] : 08/12/2020                     
            *******************************************************************************/
            void RemoveBack()                 ;

            /*******************************************************************************
            * brief____: Xóa phần tử đầu tiên của mảng                      
            * return__ : void                                               
            * [Author]: DesertFox - [Date] : 08/12/2020                     
            *******************************************************************************/
            void RemoveFront()                 ;

            /*******************************************************************************
            * brief____: Lấy ra phần tử đâu tiên                            
            * return__ : void                                               
            * [Author]: DesertFox - [Date] : 08/12/2020                     
            *******************************************************************************/
            T& Front()                         ;

            /*******************************************************************************
            * brief____: Lấy ra phần tử cuối cùng                           
            * return__ : void                                               
            * [Author]: DesertFox - [Date] : 08/12/2020                     
            *******************************************************************************/
            T& Back()                          ;

            /*******************************************************************************
            * brief____: Kiểm tra xem mảng rỗng                             
            * return__ : void                                               
            * [Author]: DesertFox - [Date] : 08/12/2020                     
            *******************************************************************************/
            const BOOL Empty()            const;
        };


        template <class T>
        class /*DllExport*/ Stack
        {
        public:
            INT                m_iCount;
            StackNode<T>*      m_pTop;

        public:
            Stack() : m_iCount(0), m_pTop(NULL) {}
            ~Stack() { this->Clear(); }
            void Empty() const { return (m_pTop == NULL); }
            INT  GetSize() { return m_iCount; };
            StackNode<T>* GetHead() const { return m_pTop; };
            /*******************************************************************************
            * Xóa toàn bộ đối tượng trong stack
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void Clear();

            /*******************************************************************************
            * Hoán đổi dữ liệu của hai stack
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void Swap(Stack<T>& stk);

            /*******************************************************************************
            * Đẩy dữ liệu vào trong stack
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void Push(const T& obj);

            /*******************************************************************************
            * Pop dữ liệu đầu khỏi stack
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void Pop();
        };

        template <class T>
        class /*DllExport*/ List2
        {
        public:
            INT           m_iCount;
            List2Node<T>* m_pFirst;
            List2Node<T>* m_pLast;
        public:
            List2() : m_iCount(0), m_pFirst(NULL), m_pLast(NULL) {}
            ~List2() { this->Clear(); }
            /*******************************************************************************
            * Hoán đổi dữ liệu của hai danh sách liên kết đôi
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void Swap(List2& lst);

            /*******************************************************************************
            * Lấy ra phần tử đầu tiên
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  Pointer  List2Node<T>
            *******************************************************************************/
            List2Node<T>* GetHead() const;

            /*******************************************************************************
            * Lấy ra phần tử cuối cùng
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  Pointer  List2Node<T>
            *******************************************************************************/
            List2Node<T>* GetTail() const;

            /*******************************************************************************
            * Xóa toàn bộ đối tượng trong danh sách
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void Clear();

            /*******************************************************************************
            * Thêm đối tượng vào danh sách
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void Add(const T& obj);

            /*******************************************************************************
            * Xóa đối tượng đầu tiên của danh sách
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void PopFront();

            /*******************************************************************************
            * Xóa đối tượng ở sau cùng của danh sách
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void PopBack();

            /*******************************************************************************
            * Xóa một đối tượng khỏi danh sách liên kết trùng con trỏ đối tượng
            * Không thể sử dụng con trỏ obj sau khi xóa
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void RemoveAt(const T* obj);

            /*******************************************************************************
            * Xóa một đối tượng khỏi danh sách liên kết trùng dữ liệu
            * [Author]: DesertFox - [Date] : 08/12/2020
            # RETURN :  void
            *******************************************************************************/
            void RemoveAt(const T& obj);
        };

        //==============================================================================
        // Class XFilterable                                                            
        //==============================================================================
        class XFilterable
        {
        public:
            //Kiểm tra xem node có được chấp nhận hay không     : Mặc định là TRUE
            /*DllExport*/ virtual BOOL IsFilter(XFilterable* filter) { return TRUE; };

            // Kiểm tra xem con của node có cần duyệt hay không : Mặc định là TRUE
            /*DllExport*/ virtual BOOL IsFilterChidren(XFilterable* filter) { return TRUE; };
        };

        //==============================================================================
        // Class Tree                                                                   
        //==============================================================================
        // Mỗi một tree sẽ có một filter tương ứng kế thừ từ XFilterable. Trong XFiltera
        // kế thừa hai hàm IsFilter và IsFilterChidren là hai chức năng lọc node trong tree
        template<class T>
        class Tree : public XFilterable
        {
        protected:
            INT             m_ID;               // Định danh                
            INT             m_iParentID;        // ID cha                   
        protected:
            INT             m_iDeep;            // Độ sâu của cây           
            string          m_strName;          // Tên của nhánh            
            vector<T*>      m_DataList;         // Danh sách dữ liệu chứa   
            vector<INT>     m_ChildrenIDList;   // Danh sách con của nó     
        public:
            Tree()
            {
                m_ID        = -1;
                m_iParentID = -1;
                m_strName = "None";
            }
            Tree(String name)
            {
                m_ID        = -1;
                m_iParentID = -1;
                m_strName   = name;
            }
            virtual ~Tree()
            {
                cout << "Free Tree :" << m_ID << endl;
                for (int i = 0; i < m_DataList.size();i++)
                {
                    delete m_DataList[i];
                }
                m_DataList.clear();
            }
            void ShowData()
            {
                cout << " [ ";
                for (int i = 0; i < m_DataList.size();i++)
                {
                    cout << m_DataList[i]->GetStrType();
                    cout << ",";
                }
                cout << "] ";
            }
        public:
            void AddChildren(Tree<T>* nodeChildren)
            {
                assert(nodeChildren);

                if (nodeChildren->m_ID != -1)
                {
                    m_ChildrenIDList.push_back(nodeChildren->m_ID);

                    // Tăng độ sâu của cây lên một và set parent cho node
                    nodeChildren->m_iDeep = this->m_iDeep + 1;
                    nodeChildren->m_iParentID = this->m_ID;
                }
            }
            vector<INT>* GetChildrenList()
            {
                return &m_ChildrenIDList;
            }

            // Thêm một phần tử vào trong dữ liệu node
            void AddData(T* obj)
            {
                m_DataList.push_back(obj);
            }

            // Xóa một phần tử trong dữ liệu node
            void DeleteData(T* obj)
            {
                for (int i = 0; i < m_DataList.size(); i++)
                {
                    if (obj == m_DataList[i])
                    {
                        // Chỉ xóa phần tử đầu tiên nó gặp
                        m_DataList.erase(m_DataList.begin() +i);
                        break;
                    }
                }
            }

            // Xóa toàn bộ phần tử trong dữ liệu node
            void ClearData()
            {
                for (int i = 0; i < m_DataList.size();i++)
                {
                    delete m_DataList[i];
                }
                m_DataList.clear();
            }
        };

        //==============================================================================
        // Class Hash                                                                   
        //==============================================================================
        template<class T>
        class TreeHash
        {
        protected:
            vector<T*>         m_TreeData;
            vector<INT>        m_RetainID;
            INT                m_MaxID   ;
        public:
            TreeHash()
            {
                m_MaxID = 0;
            }
            virtual ~TreeHash()
            {
                cout << "Free TreeHash " << endl;
                INT nSize = m_TreeData.size();
                for (INT i = 0; i < nSize; i++)
                {
                    delete m_TreeData[i];
                }
                m_TreeData.clear();
                m_RetainID.clear();
            }

        public:  // DEBUG
            void ShowTreeHash()
            {
                cout << "ListID";
                for (INT i = 0; i < m_MaxID; i++)
                {
                    if (m_TreeData[i] == NULL)
                    {
                        cout << "<- NULL";
                    }
                    else
                    {
                        cout << "<-" << m_TreeData[i]->m_ID;
                        m_TreeData[i]->ShowData();
                    }
                }
                cout << endl;
            }
            void ShowRetain()
            {
                cout << "ListRetain";
                for (INT i = 0; i < m_RetainID.size(); i++)
                {
                    cout << "<-" << m_RetainID[i];
                }
                cout << endl;
            }
            /*******************************************************************************
            # Tìm kiếm chỉ số của một phần tử trong hash                                    
            # Trả về : chỉ số trong hash                                                    
            *******************************************************************************/
            INT Find(T* elem)
            {
                for (int i = 0; i < m_MaxID; i++)
                {
                    if (m_TreeData[i] == elem)
                    {
                        return i;
                    }
                }
                return -1;
            }

            /*******************************************************************************
            # Lấy phần tử với chỉ số đã cho                                                 
            # Trả về : Con trỏ thành phần nếu tìm thấy                                      
            *******************************************************************************/
            T* Get(INT index)
            {
                if (index <0 || index >= m_MaxID)
                {
                    assert(0);
                    return NULL;
                }
                return m_TreeData[index];
            }

            /*******************************************************************************
            # Bỏ một phần tử khỏi Hash sử dụng địa chỉ                                      
            # Trả về : Con trỏ đến phần tử đã được loại bỏ                                  
            *******************************************************************************/
            T* Remove(INT index)
            {
                if (index < 0 || index >= m_MaxID)
                {
                    assert(0);
                }
                T* pNodeTemp = NULL;
                m_RetainID.push_back(index);
                pNodeTemp = m_TreeData[index];
                m_TreeData[index] = NULL;

                return pNodeTemp;
            }

            /*******************************************************************************
            # Xóa một phần tử khỏi Hash sử dụng định danh                                   
            # Trả về : void                                                                 
            # Chú ý  : Nó sẽ gọi hàm xóa của các elem trong Hash                            
            *******************************************************************************/
            void Delete(INT index)
            {
                if (index < 0 || index >= m_MaxID)
                {
                    assert(0);
                }
                m_RetainID.push_back(index);
                delete m_TreeData[index];
                m_TreeData[index] = NULL;
            }
        protected:

            /*******************************************************************************
            # Thêm một phần tử mới vào Hash                                                 
            # RETURN : TRUE  :Thêm thành công                                               
            #          FALSE :Không thể thêm                                                
            *******************************************************************************/
            INT Add(T* node)
            {
                if (node == NULL)
                {
                    assert(0);
                    return -1;
                }
                INT index = -1;
                // Trường hợp ID còn và sẽ được cấp phát lại theo thứ tự
                if (!m_RetainID.empty())
                {
                    index = m_RetainID.front();
                    m_TreeData[index] = node;
                    //node->m_ID     = id;
                    m_RetainID.erase(m_RetainID.begin());
                }
                // Trường hợp cấp phát id mới và tăng ID max lên
                else
                {
                    index = m_MaxID;
                    m_TreeData.push_back(node);
                    m_MaxID++;
                }
                return index;
            }
        };

        //==============================================================================
        //↓↓↓↓ Class list2

        template<class T>
        inline List2Node<T>* List2<T>::GetHead() const
        {
            return m_pFirst;
        }

        template<class T>
        inline List2Node<T>* List2<T>::GetTail() const
        {
            return m_pLast;
        }

        template<class T>
        inline void List2<T>::Swap(List2& lst)
        {
            swap(m_iCount, lst.m_iCount);
            swap(m_pFirst, lst.m_pFirst);
            swap(m_pLast , lst.m_pLast);
        }

        template<class T>
        inline void List2<T>::Clear()
        {
            List2Node<T>* node = m_pFirst;
            while (node != NULL)
            {
                List2Node<T>* nodeDel = node;
                node = node->m_pNext;
                delete nodeDel;
            }
            m_iCount = 0;
            m_pLast = m_pFirst = NULL;
        }

        template<class T>
        inline void List2<T>::Add(const T& obj)
        {
            List2Node<T>* node = new List2Node<T>(obj);

            if (m_pFirst == NULL)
            {
                m_pFirst = node;
                m_pLast = node;
            }
            else
            {
                m_pLast->m_pNext = node;
                node->m_pPrev = m_pLast;
                m_pLast = node;
            }
            m_iCount++;
        }

        template<class T>
        inline void List2<T>::PopFront()
        {
            if (m_pFirst != NULL)
            {
                List2Node<T>* nodeDel = m_pFirst;
                if (m_pFirst->m_pNext == NULL)
                {
                    if (m_pFirst == m_pLast)
                    {
                        m_pLast = NULL;
                    }
                    m_pFirst = NULL;
                }
                else
                {
                    m_pFirst = m_pFirst->m_pNext;
                    m_pFirst->m_pPrev = NULL;
                }
                delete nodeDel;
                m_iCount--;
            }
        }

        template<class T>
        inline void List2<T>::PopBack()
        {
            if (m_pLast != NULL)
            {
                List2Node<T>* nodeDel = m_pLast;
                if (m_pLast->m_pPrev == NULL)
                {
                    if (m_pFirst == m_pLast)
                    {
                        m_pFirst = NULL;
                    }
                    m_pLast = NULL;
                }
                else
                {
                    m_pLast = m_pLast->m_pPrev;
                    m_pLast->m_pNext = NULL;
                }
                delete nodeDel;
                m_iCount--;
            }
        }

        template<class T>
        inline void List2<T>::RemoveAt(const T* obj)
        {
            List2Node<T>* nodeNext = m_pFirst;
            while (nodeNext != NULL)
            {
                if (nodeNext->m_data == obj)
                {
                    List2Node<T>* nodeDel = nodeNext;
                    if (nodeDel == m_pFirst)             // Node đầu tiên 
                    {
                        m_pFirst = nodeDel->m_pNext;     // Chỉ có một Node
                        if (m_pFirst == NULL)  m_pLast = NULL;
                        else
                        {
                            nodeDel->m_pNext->m_pPrev = NULL;
                        }
                        nodeNext = nodeDel->m_pNext;
                    }
                    else if (nodeDel->m_pNext == NULL)   // Node cuối cùng 
                    {
                        m_pLast = nodeDel->m_pPrev;
                        m_pLast->m_pNext = NULL;
                        nodeNext = NULL;
                    }
                    else                                 // Node ở giữa
                    {
                        nodeDel->m_pPrev->m_pNext = nodeDel->m_pNext;
                        nodeDel->m_pNext->m_pPrev = nodeDel->m_pPrev;
                        nodeNext = nodeDel->m_pNext;
                    }
                    delete nodeDel; m_iCount--;
                }
                else
                {
                    nodeNext = nodeNext->m_pNext;
                }
            }
        }

        template<class T>
        inline void List2<T>::RemoveAt(const T& obj)
        {
            List2Node<T>* nodeNext = m_pFirst;
            while (nodeNext != NULL)
            {
                if (nodeNext->m_data == obj)
                {
                    List2Node<T>* nodeDel = nodeNext;
                    if (nodeDel == m_pFirst)             // Node đầu tiên 
                    {
                        m_pFirst = nodeDel->m_pNext;     // Chỉ có một Node
                        if (m_pFirst == NULL)  m_pLast = NULL;
                        else
                        {
                            nodeDel->m_pNext->m_pPrev = NULL;
                        }
                        nodeNext = nodeDel->m_pNext;
                    }
                    else if (nodeDel->m_pNext == NULL)  // Node cuối cùng 
                    {
                        m_pLast = nodeDel->m_pPrev;
                        m_pLast->m_pNext = NULL;
                        nodeNext = NULL;
                    }
                    else                                // Node ở giữa
                    {
                        nodeDel->m_pPrev->m_pNext = nodeDel->m_pNext;
                        nodeDel->m_pNext->m_pPrev = nodeDel->m_pPrev;
                        nodeNext = nodeDel->m_pNext;
                    }
                    delete nodeDel; m_iCount--;
                }
                else
                {
                    nodeNext = nodeNext->m_pNext;
                }
            }
        }
        //↑↑↑↑ Class list2
        //=============================================================================

        //=============================================================================
        //↓↓↓↓ Class stack
        template<class T>
        inline void Stack<T>::Clear()
        {
            StackNode<T>* node = m_pTop;
            while (node != NULL)
            {
                StackNode<T>* nodeDel = node;
                node = node->GetNext();
                delete nodeDel;
            }
            m_pTop = NULL;
            m_iCount = 0;
        }
        template<class T>
        inline void Stack<T>::Swap(Stack<T>& stk)
        {
            swap(stk.m_iCount, this->m_iCount);
            swap(this->m_pTop, stk.m_pTop);
        }
        template<class T>
        inline void Stack<T>::Push(const T& obj)
        {
            StackNode<T>* node = new StackNode<T>(obj);
            if (m_iCount == 0 || m_pTop == NULL)
            {
                node->m_pNext = NULL;
                m_pTop = node;
            }
            else
            {
                node->m_pNext = m_pTop;
                m_pTop = node;
            }
            m_iCount++;
        }
        template<class T>
        inline void Stack<T>::Pop()
        {
            if (m_iCount > 0 && m_pTop != NULL)
            {
                StackNode<T>* nodeDel = m_pTop;
                m_pTop = m_pTop->m_pNext;
                m_iCount = (m_iCount <= 0) ? 0 : m_iCount - 1;
                delete nodeDel;
            }
            else
            {
                this->Clear();
            }
        }
        //↑↑↑↑ Class stack
        //=============================================================================


        //=============================================================================
        //↓↓↓↓ Class ArX
        template<class T>
        inline ArX<T>::ArX(const T& xap)
        {
            this->np = xap.np;
            std::copy(xap.ap.begin(), xap.ap.end(), std::back_inserter(ap));
        }

        // Hàm tường minh có một dữ liệu đầu vào
        template<class T>
        inline void ArX<T>::Add(T p)
        {
            ap.push_back(p);
            this->np++;
        }

        // Hàm thêm sử dụng cho nhiều tham số đầu vào
        template<class T> template<typename... Types>
        inline void ArX<T>::Add(T p, Types... vars)
        {
            ap.push_back(p);
            this->np++;
            this->Add(vars...);
        }

        template<class T>
        inline void ArX<T>::Clear()
        {
            this->np = 0;
            ap.clear();
        }
        template<class T>
        inline void ArX<T>::Swap(ArX<T>& xap)
        {
            std::swap(xap.np, np);
            this->ap.swap(xap.ap);
        }
        template<class T>
        inline void ArX<T>::Copy(const ArX<T>& xap)
        {
            this->np = xap.np;
            std::copy(xap.ap.begin(), xap.ap.end(), std::back_inserter(ap));
        }
        template<class T>
        inline void ArX<T>::Reverse()
        {
            std::reverse(ap.begin(), ap.end());
        }
        template<class T>
        inline T ArX<T>::At(INT i) const
        {
            assert(i>0 && i< np);
            return ap.at(i);
        }
        template<class T>
        inline T& ArX<T>::operator[](INT i)
        {
            assert(i< np);
            return ap[i];
        }

        template<class T>
        inline const T& ArX<T>::operator[](INT i) const
        {
            assert(i < np);
            return ap[i];
        }

        template<class T>
        inline ArX<T>& ArX<T>::operator=(const T& xap)
        {
            this->np = xap.np;
            std::copy(xap.ap.begin(), xap.ap.end(), std::back_inserter(ap));
            return *this;
        }
        template<class T>
        inline void ArX<T>::RemoveAt(INT i)
        {
            assert(i < np);
            ap.erase(ap.begin() + i);
            np--;
        }
        template<class T>
        inline void ArX<T>::RemoveBack()
        {
            if (!ap.empty())
            {
                ap.pop_back();
                np = (np >0 )? np-1: 0;
            }
        }
        template<class T>
        inline void ArX<T>::RemoveFront()
        {
            if (!ap.empty())
            {
                ap.erase(ap.begin());
                np = (np >0 )? np-1: 0;
            }
        }

        template<class T>
        inline T& ArX<T>::Front() 
        {
            return ap.front();
        }
        template<class T>
        inline T& ArX<T>::Back()
        {
            return ap.back();
        }
        template<class T>
        inline const BOOL ArX<T>::Empty() const
        {
            return np == 0 ? TRUE : FALSE;
        }
    };

    typedef foxstruct::Stack<Vec2D>  StackVec2D;
    typedef foxstruct::List2<Vec2D>  List2Vec2D;

    typedef foxstruct::ArX<Vec2D>    Ap2D;
    typedef foxstruct::ArX<Line2D>   Al2D;
    typedef foxstruct::ArX<Vec2D>    Ap3D;

}

#endif //!XBASE_H

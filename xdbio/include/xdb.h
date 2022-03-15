//==============================================================================
// Định nghĩa các cơ sở dữ liệu sử dụng cho ứng dụng                            
//                                                                              
//==============================================================================
////////////////////////////////////////////////////////////////////////////////
#ifndef XDB_H
#define XDB_H

#include "elem.h"
#include <string>
#include <iostream>


#define NONE_QUERY -98989898  // DbQuery query tất cả

namespace fox
{
    using namespace foxstruct;

    class NodeObj;
    class NodeObjManager;
    typedef vector<INT>* POSITION;

    enum
    {
        NodeNone = -9999,
        NodeType = -8080,
        NodeTab  = -7070,
        NodeTrunk= -6060,
        NodeRoot = -1010,
    };

    // Nhưng node không chứa dữ liệu sẽ có [Type < 0]
    enum
    {
        TRUNK_OBJ  = -1,
        TRUNK_INFO = -2,
        TAB_OBJ    = -4,
    };

    // Định nghĩa các finder node 
    enum
    {
        // Sử dụng cho trường hợp lấy ra nhiều thứ
        TRUNK_ALL = -12345677,  // Lấy hết tất cả các trunk 
        TAB_ALL   = -12345678,  // Lấy hết tất cả các tab
        TYPE_ALL  = -12345679,  // Lấy hết tất cả các type
    };

    //==============================================================================
    // Class NodePropertis                                                          
    // Chứa thông tin của node                                                      
    //==============================================================================
    ////////////////////////////////////////////////////////////////////////////////
    class NodePropertis
    {
    protected:
        String  m_strProName;
        INT     m_iDataType ;  // Loại dữ liệu trên node này là loại nào? Phục vụ cho tìm kiếm
        INT     m_iTab      ;
        INT     m_iNodeType ;  // Node này thuộc loại nào? Phục vụ cho tìm kiếm

    protected:
        //virtual BOOL FilterChildren(NodePropertis* pNodeFiter) { return FALSE; }
        //virtual BOOL FilterType(NodePropertis* pNodeFiter) { return FALSE; }

    public:
        NodePropertis()
        {
            m_iTab       = -1;
            m_iDataType  = -1;
            m_iNodeType  = NodeNone;
            m_strProName = "";
        }
    };

    //==============================================================================
    // Class NodeFilter                                                             
    // chứa thông tin mà nó lọc trong tree NodeObj                                  
    //==============================================================================
    class NodeFilter : public XFilterable
    {
    public:
        INT     m_iTab ;
        INT     m_iType;
        INT     m_iTrunk;
    public:
        void SetActivateTab(INT itab)
        {
            m_iTab = itab;
        }
        void SetActivateType(INT itype)
        {
            m_iType = itype;
        }
        void SetActivateTrunk(INT itrunk)
        {
            m_iTrunk = itrunk;
        }
    public:
        DllExport virtual BOOL IsFilter(XFilterable* filter);

        DllExport virtual BOOL IsFilterChidren(XFilterable* filter);
    };

    //==============================================================================
    // Class TreeObjNode                                                            
    // chứa đối tượng trong cây dữ liệu                                             
    //==============================================================================
    class NodeObj : public Tree<BaseObj>, public NodePropertis
    {
    private:

    public:
        NodeObj() : Tree(), NodePropertis()
        {

        }
        NodeObj(String name): Tree(name), NodePropertis()
        {

        }
    public:

        virtual BOOL IsFilterChildren(XFilterable* pNodeFiter)
        {
            return pNodeFiter->IsFilterChidren(this);
        }

        virtual BOOL IsFilter(XFilterable* pNodeFiter)
        {
            return pNodeFiter->IsFilter(this);
        }
    public:

        // @@ Chưa đúng lắm 
        INT GetNodeType()
        {
            return m_iDataType;
        }

        //==============================================================================
        // Tìm kiếm node theo type đã cho theo tìm kiếm chiều rộng (BFS)                
        // Trả về : Node có type trùng đầu tiên                                         
        //==============================================================================
        DllExport NodeObj* FindBNodeType(XFilterable* pFilter, NodeObjManager* pMana);

        //==============================================================================
        // Tìm kiếm node theo type đã cho theo tìm kiếm chiều sâu (DFS)                 
        // Trả về : Node có type trùng đầu tiên                                         
        //==============================================================================
        DllExport NodeObj* FindDNodeType(XFilterable* pFilter, NodeObjManager* pMana);

        //==============================================================================
        // Tìm kiếm toàn bộ node có type trùng với type đã cho                          
        // Trả về : Danh sách các node phù hợp                                          
        //==============================================================================
        DllExport void FindAllNodeType(XFilterable* pFilter, NodeObjManager* pMana, vector<NodeObj*>* outNode);

        //==============================================================================
        // Xóa dữ liệu trong chứa trong node                                            
        // Trả về : void                                                                
        //==============================================================================
        DllExport void RemoveChildren(NodeObjManager* pMana);

        //==============================================================================
        //↓↓↓ DEBUG TEST
#ifdef DEBUG
        // Hiển thị cây chế độ DEBUG
        DllExport void PrintTree(NodeObjManager * pMana);
#endif
        //↑↑↑ DEBUG TEST
        //==============================================================================

        friend class NodeObjManager;
        friend class DbQuery;
        friend class NodeFilter;
    };

    //==============================================================================
    // Class NodeObjManager                                                         
    // chứa đối tượng trong cây dữ liệu                                             
    //==============================================================================
    class NodeObjManager : public TreeHash<NodeObj>
    {
    private:
        NodeObj* CreateObjNode(String nodeName)
        {
            NodeObj* pNewNode = new NodeObj(nodeName);
            pNewNode->m_iNodeType = NodeNone;

            INT index = this->Add(pNewNode);
            if (index > -1)
            {
                pNewNode->m_ID = index;
                return pNewNode;
            }
            else {
                assert(0);
                delete pNewNode;
                return NULL;
            }
        }
    public:
        // Tạo node root chỉ có đầu tiên
        NodeObj* CreateNodeRoot()
        {
            NodeObj* pNodeRoot = CreateObjNode("ROOT");
            if (pNodeRoot)
            {
                pNodeRoot->m_iNodeType = NodeRoot;
                pNodeRoot->m_iDeep = 1;
            }
            return pNodeRoot;
        }

        // Tạo node trunk đầu tiên có độ sâu bằng 1
        NodeObj* CreateNodeTrunk(String nodeName, INT iDataType)
        {
            NodeObj* pNodeRoot = CreateObjNode(nodeName);
            if (pNodeRoot)
            {
                pNodeRoot->m_iNodeType = NodeTrunk;
                pNodeRoot->m_iDataType = iDataType;
            }
            return pNodeRoot;
        }

        // Tạo node tab đầu tiên có độ sâu bằng 2
        NodeObj* CreateNodeTab(String nodeName,INT iTab, INT iDataType)
        {
            NodeObj* pNewNode = CreateObjNode(nodeName);
            if (pNewNode)
            {
                pNewNode->m_iNodeType = NodeTab;
                pNewNode->m_iDataType = iDataType;
                pNewNode->m_iTab      = iTab;
            }
            return pNewNode;
        }

        // Tạo node type chứa dữ liệu được thêm vào sau node root
        NodeObj* CreateNodeType(String nodeName, INT iDataType)
        {
            NodeObj* pNodeType = CreateObjNode(nodeName);
            if (pNodeType)
            {
                pNodeType->m_iNodeType = NodeType;
                pNodeType->m_iDataType = iDataType;
            }
            return pNodeType;
        }
    };

    struct PlanInfo
    {
        INT m_nTab; // Số tab 
    };

    //==============================================================================
    // Class DataBase                                                               
    // Chứa toàn bộ thông tin của chương trình sử dụng cho nhiều mục đích           
    //==============================================================================
    class DataBase
    {
    public:
        NodeObj*        m_NodeRoot; //Node root của toàn bộ cây                          

        NodeObj*        m_NodeObj ; //Node trunk chứa toàn bộ đối tượng                  
        NodeObj*        m_NodeInfo; //Node trunk chứa dữ liệu chứa thông tin chung bản vẽ

        NodeObjManager* m_NodeManager;

        PlanInfo        m_Plan;     // Thông tin của ứng dụng : gồm tab 

    private:

        // Tạo nốt gốc Root chứa: bao gồm : OBJ , INFOR
        void CreateRoot()
        {
            m_NodeRoot = m_NodeManager->CreateNodeRoot();
        }

        // Tạo ra các node Trunk chứa thông tin 
        void CreateDBObj()
        {
            m_NodeObj = m_NodeManager->CreateNodeTrunk("OBJ_DB", TRUNK_OBJ);

            if (m_NodeObj != NULL)
            {
                m_NodeRoot->AddChildren(m_NodeObj);

                // Tạo node tab : tab 
                for (int itab = 0; itab < m_Plan.m_nTab; itab++)
                {
                    NodeObj* m_pNodeTab = m_NodeManager->CreateNodeTab(String("Tab_")+std::to_string(itab), itab, TAB_OBJ);

                    m_NodeObj->AddChildren(m_pNodeTab);

                    // Tạo node type: là các yếu tố
                    for (INT i = 0; i < typeMax; i++)
                    {
                        NodeObj* pNodeType = m_NodeManager->CreateNodeType(GetTypeString(i), i);
                        m_pNodeTab->AddChildren(pNodeType);
                    }
                }
            }
        }

        void CreateDBInfo()
        {
            m_NodeInfo = m_NodeManager->CreateNodeTrunk("INFO_DB", TRUNK_INFO);

            if (m_NodeInfo != NULL)
            {
                m_NodeRoot->AddChildren(m_NodeInfo);

                for (INT itab = 0; itab < m_Plan.m_nTab; itab++)
                {
                    NodeObj* pNodeTab = m_NodeManager->CreateNodeTab(String("Tab_")+std::to_string(itab), itab, TAB_OBJ);
                    m_NodeInfo->AddChildren(pNodeTab);
                }
            }
        }

        void InitDataBase()
        {
            m_Plan.m_nTab = 3;
            CreateRoot();
            {
                CreateDBObj();
                CreateDBInfo();
            }
        }
    public:
        DataBase()
        {
            m_NodeManager = new NodeObjManager();
            InitDataBase();
        }
        ~DataBase() 
        {
            delete m_NodeManager;
        }
    public:

        BOOL AddObj(BaseObj* obj)
        {
            NodeFilter filter;
            filter.SetActivateTrunk(TRUNK_OBJ);
            filter.SetActivateTab(obj->m_iTab);
            filter.SetActivateType(obj->GetType());

            NodeObj* pNodeFound = m_NodeRoot->FindDNodeType(&filter, m_NodeManager);
            if(!pNodeFound)
            {
                assert_m(0,"pNodeFound can not found !");
                return FALSE;
            }
            pNodeFound->AddData(obj);
            return TRUE;
        }

        BOOL DeleteObj(BaseObj* obj)
        {
            NodeFilter filter;
            filter.SetActivateTrunk(TRUNK_OBJ);
            filter.SetActivateTab(obj->m_iTab);
            filter.SetActivateType(obj->GetType());


            NodeObj* pNodeFound = m_NodeRoot->FindDNodeType(&filter, m_NodeManager);
            if(!pNodeFound)
            {
                assert_m(0,"pNodeFound can not found !");
                return FALSE;
            }
            pNodeFound->DeleteData(obj);

            return TRUE;
        }

        void RemoveRoot()
        {
            m_NodeRoot->RemoveChildren(m_NodeManager);
        }

//==============================================================================
//↓↓↓ DEBUG TEST
#ifdef DEBUG
        // Hiển thị cây chế độ DEBUG
        DllExport void PrintRoot();
#endif
//↑↑↑ DEBUG TEST
//==============================================================================
    };


    //==============================================================================
    // Class RQuery                                                                 
    // Mục đích chứa thông tin trả về từ DbQuery                                    
    //==============================================================================
    class RQuery
    {
    public:
        vector<BaseObj*> m_QrListObj;
        BOOL             m_bPri [typeMax];

    private:
        // Hàm so sánh hai con trỏ của loại cơ sở
        // Hàm so sánh các kết quả đối tượng theo thứ tự : Tabs ->[Thấp đến cao  ] [0]
        //                                                  Pri ->[Thứ tự ưu tiên] [1]
        //                                                  Init->[Khởi tạo trước] [2]
        static int Compare_sort(const void * obj1, const void* obj2)
        {
            BaseObj* pObj1 = *((BaseObj**)obj1);
            BaseObj* pObj2 = *((BaseObj**)obj2);

            //↓ Hàm này có thể thay trung cho tất cả 
            //for (int i = 0; i < 3; i++)
            //{
            //    if (pObj1->m_cSort[0] < pObj2->m_cSort[0])
            //    {
            //        return -1;
            //    }
            //    else if (pObj1->m_cSort[0] > pObj2->m_cSort[0])
            //    {
            //        return 1;
            //    }
            //}
            //return 0;
            //↑ Hàm này có thể thay trung cho tất cả 

            // Sắp xếp Tabs ->[Thấp đến cao]
            if (pObj1->m_cSort[0] < pObj2->m_cSort[0])
            {
                return -1;
            }
            else if (pObj1->m_cSort[0] > pObj2->m_cSort[0])
            {
                return 1;
            }

            // Sắp xếp Pri ->[Thứ tự ưu tiên]
            if (pObj1->m_cSort[1] < pObj2->m_cSort[1])
            {
                return -1;
            }
            else if (pObj1->m_cSort[1] > pObj2->m_cSort[1])
            {
                return 1;
            }

            // Sắp xếp Init->[Khởi tạo trước]
            if (pObj1->m_cSort[2] < pObj2->m_cSort[2])
            {
                return -1;
            }
            else if (pObj1->m_cSort[2] > pObj2->m_cSort[2])
            {
                return 1;
            }

            return 0;
        }
    public:
        INT GetSize()
        {
            return m_QrListObj.size();
        }
        BaseObj* Get(INT i)
        {
            if (i >= 0 && i < m_QrListObj.size())
            {
                return m_QrListObj[i];
            }
            return NULL;
        }

        void Add(BaseObj* obj)
        {
            m_QrListObj.push_back(obj);
        }
        
        // Nó sử dụng cho việc sắp xếp khi query ra
        void SetDefaultPriority()
        {
            int iPri = 0;
            m_bPri[typePoly ] = iPri++;
            m_bPri[typeElip ] = iPri++;
            m_bPri[typeArc  ] = iPri++;
            m_bPri[typeCirc ] = iPri++;
            m_bPri[typeLine ] = iPri++;
            m_bPri[typePoint] = iPri++;
        }

        // Sắp xếp các đối tượng đầu ra theo một thứ tự mong muốn 
        // Hiện tại chỉ sort theo type thôi + Cái này tham khảo trong wih
        // @@ Đang phân vân nếu cây có thêm điều kiện sort nữa thì làm sao để tổng quát nó

        void Sort()
        {
            int num = 0;
            // Tránh phải tạo biến tạm
            for (int i = 0; i < m_QrListObj.size(); i++)
            {
                // Điều kiện thêm tab thứ mấy
                m_QrListObj[i]->m_cSort[0] = m_QrListObj[i]->m_iTab;

                // Sắp xếp theo priority
                m_QrListObj[i]->m_cSort[1] = m_bPri[m_QrListObj[i]->GetType()];

                // Thằng nào vào trước thì query ra trước thì lấy trước
                m_QrListObj[i]->m_cSort[2] = num;

                num++;
            }

            // Tiến hành sắp xếp
            qsort(&m_QrListObj[0], num, sizeof(BaseObj*), Compare_sort);
        }
    };

    //==============================================================================
    // Class DbQuery                                                                
    // Mục đích thực hiện truy vấn giống Tsql                                       
    //==============================================================================
    class DbQuery
    {
    private:
        DataBase* m_pCurDataBase;
        RQuery*   m_pQrResult;

        INT       m_iTrunkQr;
        INT       m_iTabQr  ;

    private:
        BOOL      m_bFlag[typeMax] = {FALSE}; // Thiết lập tất cả đối tượng là không được query ra


    private:

        // Trong trường hợp đối tượng trong data cần lọc thêm
        BOOL IsObjFilter(BaseObj* obj)
        {
            return TRUE;
        }

        BOOL IsFilter(NodeObj* node)
        {
            // Chỉ lọc các node là dạng type mọi node khác đều không lọc
            switch (node->m_iNodeType)
            {
                case NodeType:
                {
                    if (m_bFlag[node->m_iDataType] == TRUE)
                    {
                        return TRUE;
                    }
                    break;
                }
            }
            return FALSE;
        }

        BOOL IsFilterChildren(NodeObj* node)
        {
            // Chỉ có 3 tầng được duyệt ở đây thuộc 3 dạng : ROOT , TRUNK , TAB
            // Riêng node Type : Sẽ được xử lý ở hàm Filter
            switch (node->m_iNodeType)
            {
                case NodeRoot:
                {
                    return TRUE;
                    break;
                }
                case NodeTrunk:
                {
                    if (node->m_iDataType == m_iTrunkQr || m_iTrunkQr == TRUNK_ALL)
                    {
                        return TRUE;
                    }
                    break;
                }
                case NodeTab:
                {
                    if (node->m_iTab == m_iTabQr || m_iTabQr == TAB_ALL)
                    {
                        return TRUE;
                    }
                    break;
                }
                default:
                    break;
            }
            return FALSE;
        }

        // Hàm này tương tự tìm kiếm all bên database
        void Query(NodeObj* node, NodeObjManager* mana)
        {
            if (IsFilter(node))
            {
                for (int i = 0; i < node->m_DataList.size(); i++)
                {
                    if (IsObjFilter(node->m_DataList[i]))
                    {
                        m_pQrResult->Add(node->m_DataList[i]);
                    }
                }
            }

            // Tránh phải query ra các node không cần thiết
            if (IsFilterChildren(node))
            {
                for (int i = 0; i < node->m_ChildrenIDList.size(); i++)
                {
                    NodeObj* pNodeChildren = mana->Get(node->m_ChildrenIDList[i]);

                    this->Query(pNodeChildren, mana);
                }
            }
        }

        //↓2021.05.26 N.V.Thuong Cái này muốn giữ lại để để sử dụng sau 
        //template<T>
        //void Query(Tree<T>*node, TreeHash<T>* mana )
        //{
        //    if (IsFilter(node))
        //    {
        //        for (int i = 0; i < node->m_DataList.size(); i++)
        //        {
        //            m_pQrResult->Add(node->m_DataList[0]);
        //        }
        //    }
        //    for (int i = 0; i < node->m_ChildrenIDList.size(); i++)
        //    {
        //        Tree<T>* pNodeChildren = mana->Get(i);
        //        this->Query(pNodeChildren, mana);
        //    }
        //}
        //↑2021.05.26 N.V.Thuong Cái này muốn giữ lại để để sử dụng sau 
    public:
        DbQuery()
        {
            m_pQrResult   = new RQuery();
            m_iTrunkQr    = TRUNK_ALL;
            m_iTabQr      = TAB_ALL;

            m_pQrResult->SetDefaultPriority();
            this->SetFilterOff();
        }

        DbQuery(DataBase* database)
        {
            m_pQrResult   = new RQuery();
            m_iTrunkQr    = TRUNK_OBJ   ;
            m_iTabQr      = TAB_ALL     ;

            m_pQrResult->SetDefaultPriority();
            this->SetFilterOff();

            m_pCurDataBase = database;
        }
        ~DbQuery()
        {
            delete m_pQrResult;
        }

    // Thiết lập tham số trước khi tiến hành query
    public: 

        void SetDataBase(DataBase* database)
        {
            m_pCurDataBase = database;
        }

        void SetTabOn(INT itab)
        {
            m_iTabQr = itab;
        }

        void SetRootOn(INT itrunk)
        {
            m_iTrunkQr = itrunk;
        }

        void SetFilterOff(/*Toàn bộ*/)
        {
            for (int i = 0; i < typeMax; i++)
            {
                m_bFlag[i] = FALSE;
            }
        }

        void SetFilterOn(/*Toàn bộ*/)
        {
            for (int i = 0; i < typeMax; i++)
            {
                m_bFlag[i] = TRUE;
            }
        }

        // Thiết lập các loại đối tượng dữ liệu sẽ được lấy ra
        void SetFilterOn(const INT& itype)
        {
            assert(itype >= 0 && itype < typeMax);
            m_bFlag[itype] = TRUE;
        }

        // Thiết lập các loại đối tượng dữ liệu sẽ được lấy ra cho hàm sử dụng nhiều tham số 
        template<typename...ARGS>
        void SetFilterOn(const INT& iType, const ARGS&...restTypes)
        {
            m_bFlag[iType] = TRUE;
            SetFilterOn(restTypes...);
        }

        // Thiết lập các loại đối tượng dữ liệu sẽ không được lấy ra
        void SetFilterOff(const INT& itype)
        {
            assert(itype >= 0 && itype < typeMax);
            m_bFlag[itype] = FALSE;
        }

        // Thiết lập các loại đối tượng dữ liệu sẽ không được lấy ra cho hàm sử dụng nhiều tham số 
        template<typename...ARGS>
        void SetFilterOff(const INT& iType, const ARGS&...restTypes)
        {
            m_bFlag[iType] = FALSE;
            SetFilterOff(restTypes...);
        }
    // Hàm chức năng query hoặc chức năng phụ trợ
    public:

        RQuery* Execute()
        {
            // Search information on root information
            if (m_iTrunkQr == TRUNK_OBJ)
            {
                this->Query(m_pCurDataBase->m_NodeObj , m_pCurDataBase->m_NodeManager);
            }
            // Search information on root object
            else if (m_iTrunkQr == TRUNK_INFO)
            {
                this->Query(m_pCurDataBase->m_NodeInfo , m_pCurDataBase->m_NodeManager);
            }

            // List of searchable objects
            return m_pQrResult;
        }
        
    };
}


#endif // !XDB_H




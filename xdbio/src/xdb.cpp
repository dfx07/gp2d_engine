#include "xdb.h"
#include <queue>

namespace fox
{
    //==============================================================================
    // Tìm kiếm node theo type đã cho theo tìm kiếm chiều rộng (BFS)                
    // Trả về : Node có type trùng đầu tiên                                         
    //==============================================================================
    NodeObj* NodeObj::FindBNodeType(XFilterable* pFilter, NodeObjManager* pMana)
    {
        NodeObj* pNodeFound = NULL;
        std::queue<NodeObj* > QueueNode;

        QueueNode.push(this); // Khởi tạo với node hiện tại

        while (!QueueNode.empty())
        {
            NodeObj* pNodeTemp = QueueNode.front();
            if (pNodeTemp->IsFilter(pFilter))
            {
                pNodeFound = pNodeTemp;
                break;
            }
            for (int i = 0; i < pNodeTemp->m_ChildrenIDList.size();i++)
            {
                NodeObj* pNodeChil = pMana->Get(pNodeTemp->m_ChildrenIDList[i]);
                QueueNode.push(pNodeChil);
            }

            // Xóa đi node đã duyệt lâu đời nhất
            QueueNode.pop();
        }
        return pNodeFound;
    }

    //==============================================================================
    // Tìm kiếm node theo type đã cho theo tìm kiếm chiều sâu (DFS)                 
    // Trả về : Node có type trùng đầu tiên                                         
    //==============================================================================
    NodeObj* NodeObj::FindDNodeType(XFilterable* pFilter, NodeObjManager* pMana)
    {
        if (this->IsFilter(pFilter))
        {
            return this;
        }

        if (this->IsFilterChildren(pFilter))
        {
            for (int i = 0; i < m_ChildrenIDList.size();i++)
            {
                NodeObj* pNodeChil = pMana->Get(m_ChildrenIDList[i]);
                NodeObj* pNodeFound = pNodeChil->FindDNodeType(pFilter, pMana);
                if (pNodeFound != NULL)
                {
                    return pNodeFound;
                }
            }
        }

        return NULL;
    }

    //==============================================================================
    // Tìm kiếm toàn bộ node có type trùng với type đã cho                          
    // Trả về : Danh sách các node phù hợp                                          
    //==============================================================================
    void NodeObj::FindAllNodeType(XFilterable* pFilter, NodeObjManager* pMana, vector<NodeObj*>* outNode)
    {
        if (this->IsFilter(pFilter))
        {
            outNode->push_back(this);
        }

        for (int i = 0; i < m_ChildrenIDList.size();i++)
        {
            NodeObj* pNodeChil = pMana->Get(m_ChildrenIDList[i]);
            pNodeChil->FindAllNodeType(pFilter, pMana, outNode);
        }
    }
    void NodeObj::RemoveChildren(NodeObjManager * pMana)
    {
        // Xóa dữ liệu của các node con của nó 
        for (int i = 0; i < m_ChildrenIDList.size();i++)
        {
            NodeObj* pChildren = pMana->Get(m_ChildrenIDList[i]);
            if (pChildren)
            {
                pChildren->RemoveChildren(pMana);
                pMana->Delete(pChildren->m_ID);
            }
        }
        m_ChildrenIDList.clear();
    }
#ifdef DEBUG
    void NodeObj::PrintTree(NodeObjManager * pMana)
    {
        std::cout << m_strName;
        cout << "(" << this->m_DataList.size() << ")";
        if (this->m_ChildrenIDList.size() > 0)
        { 
            cout << "-> [";
            for (int i = 0; i < this->m_ChildrenIDList.size(); i++)
            {
                NodeObj* pChildren = pMana->Get(m_ChildrenIDList[i]);
                pChildren->PrintTree(pMana);
                cout << ",";
            }
            cout << "]";
        }
    }
#endif

#ifdef DEBUG
    void DataBase::PrintRoot()
    {
        m_NodeRoot->PrintTree(m_NodeManager);
        cout << endl;
    }
#endif

    BOOL NodeFilter::IsFilterChidren(XFilterable * filter)
    {
        NodeObj* pNodeObj = (NodeObj*)filter;
        switch (pNodeObj->m_iNodeType)
        {
            case NodeRoot:   // Node Root 
            {
                return TRUE;
                break;
            }
            case NodeTrunk:  // Node Trunk
            {
                if (pNodeObj->m_iDataType == m_iTrunk || m_iTrunk == TRUNK_ALL)
                {
                    return TRUE;
                }
                break;
            }
            case NodeTab:    // Node Tab
            {
                // Trường hợp trùng hoặc lấy hết 
                if (pNodeObj->m_iTab == m_iTab || m_iTab == TAB_ALL)
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

    BOOL NodeFilter::IsFilter(XFilterable * filter)
    {
        NodeObj* pNodeObj = (NodeObj*)filter;

        switch (pNodeObj->m_iNodeType)
        {
            case NodeType:  // Node Type
            {
                if (pNodeObj->m_iDataType == m_iType || m_iType == TYPE_ALL)
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
}


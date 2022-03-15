//==============================================================================
// Định nghĩa các loại và lớp cơ bản yếu tố được sử dụng                        
//                                                                              
//==============================================================================
////////////////////////////////////////////////////////////////////////////////

#ifndef EBASE_ELEM_H
#define EBASE_ELEM_H

#define CREATE_CLONE(class_name)            \
virtual class_name* Clone()                 \
{                                           \
    class_name* pNewObj = new class_name(); \
    pNewObj->CopyAtr(this);                 \
    return pNewObj;                         \
}                                           \


#include "xdef.h"
#include "xbase.h"

namespace fox
{
    enum 
    {
        typeNone  =-1,       // Đối tượng không xác định
        typePoint = 0,       // Đối tượng điểm          
        typeLine  = 1,       // Đối tượng đoạn thẳng    
        typeCirc  = 2,       // Đối tượng hình tròn     
        typeArc   = 3,       // Đối tượng cung tròn     
        typePoly  = 4,       // Đối tượng hình polygon  
        typeElip  = 5,       // Đối tượng ellipse       
        typeMax    ,         // Đếm                     
    };

    DllExport String GetTypeString(int iType);
}

namespace fox
{
    class BaseObj
    {
    private:
        UINT     m_id;
        UINT     m_idParent;

    private:
        BaseObj* m_pBaseObj; // Đối tượng cơ sở mà nó trỏ đến
        INT      m_cSort[4]; // Điều kiện sắp xếp
    public:
        INT      m_iTab    ; // Tab của đối tượng

    public:
        BaseObj() { m_id = 0; m_idParent = 0; }
        virtual ~BaseObj() {}
        virtual  INT GetType() const{ return typeNone; }

    public:
        virtual void CopyAtr(const BaseObj* cp)
        {
            this->m_idParent = cp->m_idParent;
        };

        BaseObj* GetBaseObj() { return m_pBaseObj; }

    public:
        virtual BaseObj& operator=(const BaseObj& base)
        {
            if (this != &base)
            {
                assert(GetType() == base.GetType());
                this->m_id       = base.m_id;
                this->m_idParent = base.m_idParent;
                this->m_pBaseObj = base.m_pBaseObj;
                this->CopyAtr(&base);
            }
            return *this;
        }

        CREATE_CLONE(BaseObj)

        friend class RQuery;
        friend class DataBase;
    };
}

#endif //!EBASE_ELEM_H
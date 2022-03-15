#include "xcom.h"

namespace fox
{
    namespace utils
    {
        ostream& operator<<(std::ostream& os, const Vec2D& v)
        {
            os << "(" << v.x << "," << v.y << ")";
            return os;
        }

        ostream& operator<<(std::ostream& os, const Vec3D& v)
        {
            os << "(" << v.x << "," << v.y << v.z << ")";
            return os;
        }

        ostream& operator<<(std::ostream& os, const Line2D& li)
        {
            os << "[P1" << li.p1 << ",P2" << li.p2 << "]";
            return os;
        }

        ostream& operator<<(std::ostream& os, const Line3D& li)
        {
            os << "[P1" << li.p1 << ",P2" << li.p2 << "]";
            return os;
        }

        ostream& operator<<(std::ostream& os, const StackVec2D& stk)
        {
            os << "Stack {";
            auto head = stk.GetHead();
            while (head != NULL)
            {
                os << *(head->GetData()) << ",";

                head = head->GetNext();
            }
            os << "}";
            return os;
        }

        ostream&  operator<<(std::ostream& os, const List2Vec2D& lit)
        {
            os << "List2 {";
            auto head = lit.GetHead();
            while (head != NULL)
            {
                os << *(head->GetData()) << ",";

                head = head->GetNext();
            }
            os << "}";
            return os;
        }

        FLT Map(FLT value, FLT smin, FLT smax, FLT dmin, FLT dmax)
        {
            if (value <= smin) return dmin;
            if (value >= smax) return dmax;

            FLT      a1 = value - smin;
            FLT      b2 = dmax  - dmin;
            FLT      b1 = smax  - smin;
            return dmin + (a1 * b2) / b1;
        }

        GLColor Col2Standard(Color color)
        {
            GLColor rC;
            rC.r = (color.r / 256);
            rC.g = (color.g / 256);
            rC.b = (color.b / 256);
            if (rC.r > 1.0) rC.r = 1.0f;
            if (rC.g > 1.0) rC.g = 1.0f;
            if (rC.b > 1.0) rC.b = 1.0f;
            return rC;
        }

        GLColor Col2Standard(UINT r, UINT g, UINT b)
        {
            GLColor rC;
            rC.r = (FLT)r / 256;
            rC.g = (FLT)g / 256;
            rC.b = (FLT)b / 256;
            if (rC.r > 1.0) rC.r = 1.0f;
            if (rC.g > 1.0) rC.g = 1.0f;
            if (rC.b > 1.0) rC.b = 1.0f;
            return rC;
        }

        void Vec2Ap2D(vector<Vec2D>& ar2D, Ap2D & xap)
        {
             xap.np = ar2D.size();
             std::copy(ar2D.begin(),ar2D.end(), std::back_inserter(xap.ap));
        }

        ImgType GetImageTypeExtension(const string path)
        {
            // Chỉ khởi tạo lần đầu tiên vào hàm  mapping > Thêm loại vào đây
            static const map<const char* , ImgType> smTypeMap =
            {
                {"\x89\x50\x4E\x47\x0D\x0A\x1A\x0A" , IMG_PNG},  // 89 50 4E 47 0D 0A 1A 0A hoặc FF D8 FF
                {"\xFF\xD8\xFF"                     , IMG_JPG},  // FF D8 FF               
                {"\x42\x4D"                         , IMG_BMP},  // 42 4D                  
                {"\x49\x49\x2A\x00"                 , IMG_TIF},  // 49 49 2A 00            
                {"\x47\x49\x46\x38"                 , IMG_GIF},  // 47 49 46 38            
                {"\x00\x00\x01\x00"                 , IMG_ICO},  // 47 49 46 38            
            };
            // Chú ý : Một vài loại sẽ kiểm tra dự thêm vào offset

            const int buff_size = 512;                           // header buffer size
            char data_header[buff_size] = {'\x00'};              // header buffer  khởi tạo '\0'
            ifstream img_file(path , std::ios::binary);          // Không có ios::binary nó sẽ dừng vì có 0A

            if (!img_file.is_open())
            {
                cout << "Could not open the file !" << endl;
                return   ImgType::IMG_INV;
            }

            int count_size = 0; char byte;
            while (img_file.get(byte) && count_size < buff_size)
            {
                data_header[count_size] = byte;
                count_size++;
            }
            img_file.close();

            // Kiểm tra trong danh sách mapping
            for (auto it = smTypeMap.begin(); it != smTypeMap.end(); it++)
            {
                if (count_size < strlen(it->first))  continue;
                if (strncmp(it->first, data_header, strlen(it->first))== 0)
                {
                    return it->second;
                }
            }
            return ImgType::IMG_INV;
        }
    }

    namespace structsys
    {
        BOOL GetMonitorInforEx(MonitorInfo * infor)
        {
            if (!infor)
            {
                assert(0);
                return FALSE;
            }
            DEVMODE devmode;
            devmode.dmSize = sizeof(DEVMODE);

            BOOL bResult = EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devmode);

            if (bResult)
            {
                infor->WIDTH      = devmode.dmPelsWidth       ;
                infor->HEIGHT     = devmode.dmPelsHeight      ;
                infor->DISFREQ    = devmode.dmDisplayFrequency;
                infor->VERSION    = devmode.dmDriverVersion   ;
                infor->NAME       = string((const char*)&(devmode.dmDeviceName[0]), CCHDEVICENAME);
            }
            return bResult;
        }
    }
}



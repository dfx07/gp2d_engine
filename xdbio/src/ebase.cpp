#include "ebase.h"

namespace  fox
{
    String GetTypeString(int iType)
    {
        switch (iType)
        {
            case typePoint: return "typePoint"; break;
            case typeLine:  return "typeLine";  break;
            case typeCirc:  return "typeCirc";  break;
            case typeArc:   return "typeArc";   break;
            case typePoly:  return "typePoly";  break;
            case typeElip:  return "typeElip";  break;
            default:
                assert(0);
                break;
        }
        return "";
    }
}

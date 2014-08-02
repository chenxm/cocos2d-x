#include "platform/CCCommon.h"
#include "CCStdC.h"
//#include <QMessageBox>

NS_CC_BEGIN

#define MAX_LEN         (cocos2d::kMaxLogLen + 1)

void MessageBox(const char * pszMsg, const char * pszTitle)
{
//    QMessageBox::warning(NULL, pszTitle, pszMsg, QMessageBox::Ok, QMessageBox::NoButton);
    CCLOGERROR(pszMsg);
}

void LuaLog(const char *pszMsg)
{
    CC_UNUSED_PARAM(pszMsg);
//    int bufflen = MultiByteToWideChar(CP_UTF8, 0, pszMsg, -1, NULL, 0);
//    WCHAR* widebuff = new WCHAR[bufflen + 1];
//    memset(widebuff, 0, sizeof(WCHAR) * (bufflen + 1));
//    MultiByteToWideChar(CP_UTF8, 0, pszMsg, -1, widebuff, bufflen);

//    OutputDebugStringW(widebuff);
//    OutputDebugStringA("\n");

//	bufflen = WideCharToMultiByte(CP_ACP, 0, widebuff, -1, NULL, 0, NULL, NULL);
//	char* buff = new char[bufflen + 1];
//	memset(buff, 0, sizeof(char) * (bufflen + 1));
//	WideCharToMultiByte(CP_ACP, 0, widebuff, -1, buff, bufflen, NULL, NULL);
//	puts(buff);

//	delete[] widebuff;
//	delete[] buff;
}

NS_CC_END


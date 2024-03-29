#ifndef MINIDUMPER_H
#define MINIDUMPER_H

#include <windows.h>

class CMiniDumper
{
public:

    CMiniDumper(bool bPromptUserForMiniDump = true);
    ~CMiniDumper(void);
    void setPath(const wchar_t* path);

private:

    static LONG WINAPI unhandledExceptionHandler(struct _EXCEPTION_POINTERS *pExceptionInfo);
	void disableSetUnhandledExceptionFilter();
	static void __cdecl myInvalidParameterHandler(const wchar_t* expression,
											const wchar_t* function, 
											const wchar_t* file, 
											unsigned int line, 
											uintptr_t pReserved);
	static void __cdecl myPurecallHandler(void);
    void setMiniDumpFileName(void);
    bool getImpersonationToken(HANDLE* phToken);
    BOOL enablePrivilege(LPCTSTR pszPriv, HANDLE hToken, TOKEN_PRIVILEGES* ptpOld);
    BOOL restorePrivilege(HANDLE hToken, TOKEN_PRIVILEGES* ptpOld);
    LONG writeMiniDump(_EXCEPTION_POINTERS *pExceptionInfo );

    _EXCEPTION_POINTERS *m_pExceptionInfo;
    TCHAR m_szMiniDumpPath[MAX_PATH];
    TCHAR m_szSettingPath[MAX_PATH];
    TCHAR m_szAppPath[MAX_PATH];
    TCHAR m_szAppBaseName[MAX_PATH];
    bool m_bPromptUserForMiniDump;

    static CMiniDumper* s_pMiniDumper;
    static LPCRITICAL_SECTION s_pCriticalSection;
};

#endif // MINIDUMPER_H

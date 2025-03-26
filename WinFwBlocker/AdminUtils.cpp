#include "pch.h"
#include "AdminUtils.h"

bool AdminUtils::IsRunAsAdmin()
{
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;

    // ���䲢��ʼ��SID
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid(
        &NtAuthority,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &adminGroup)) {
        return false;
    }

    // ������Ƴ�Ա�ʸ�
    if (!CheckTokenMembership(NULL, adminGroup, &isAdmin)) {
        isAdmin = FALSE;
    }

    FreeSid(adminGroup);
    return isAdmin == TRUE;
}

void AdminUtils::ElevateNow()
{
    WCHAR szPath[MAX_PATH];
    if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath))) {
        // ʹ��ShellExecute�Թ���ԱȨ����������
        SHELLEXECUTEINFO sei = { sizeof(sei) };
        sei.lpVerb = L"runas";
        sei.lpFile = szPath;
        sei.hwnd = NULL;
        sei.nShow = SW_NORMAL;

        if (!ShellExecuteEx(&sei)) {
            DWORD dwError = GetLastError();
            if (dwError == ERROR_CANCELLED) {
                printf("�û��ܾ���UAC��������\n");
            }
        }
        exit(0); // �˳���ǰʵ��
    }
}

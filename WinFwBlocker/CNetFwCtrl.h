#pragma once

#include "pch.h"
class CNetFwCtrl
{
public:
	CNetFwCtrl();
	~CNetFwCtrl();

	bool GetRule(const std::wstring& ruleName, INetFwRule** ppRule);
	void PrintRuleInfo(const std::wstring& ruleName);
	const wchar_t* GetProtocolText(LONG protocol);
    // �޸Ĺ���Զ�̵�ַ
	bool SetRuleRemoteAddresses(const std::wstring& ruleName, const std::wstring& remoteAddrs);
	// ��ȡ����Զ�̵�ַ
	std::wstring GetRuleRemoteAddress(const std::wstring& ruleName);
    // ����Զ�̵�ַ�ַ���Ϊ�����ĵ�ַ�б�
	std::vector<std::wstring> ParseRemoteAddresses(const std::wstring& remoteAddrs);
private:
	INetFwPolicy2* m_pPolicy = NULL;
};


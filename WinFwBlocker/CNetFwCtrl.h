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
    // 修改规则远程地址
	bool SetRuleRemoteAddresses(const std::wstring& ruleName, const std::wstring& remoteAddrs);
	// 获取规则远程地址
	std::wstring GetRuleRemoteAddress(const std::wstring& ruleName);
    // 解析远程地址字符串为单独的地址列表
	std::vector<std::wstring> ParseRemoteAddresses(const std::wstring& remoteAddrs);
private:
	INetFwPolicy2* m_pPolicy = NULL;
};


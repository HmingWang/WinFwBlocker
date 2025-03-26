#include "pch.h"
#include "CNetFwCtrl.h"

CNetFwCtrl::CNetFwCtrl()
{
    HRESULT hr = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
        throw std::runtime_error("COM initialization failed");

    hr = CoCreateInstance(
        __uuidof(NetFwPolicy2),
        NULL,
        CLSCTX_INPROC_SERVER,
        __uuidof(INetFwPolicy2),
        (void**)&m_pPolicy);

    if (FAILED(hr))
    {
        CoUninitialize();
        throw std::runtime_error("Failed to create firewall policy instance");
    }
}

CNetFwCtrl::~CNetFwCtrl()
{
    if (m_pPolicy)
        m_pPolicy->Release();
    CoUninitialize();
}

bool CNetFwCtrl::GetRule(const std::wstring& ruleName, INetFwRule** ppRule)
{
    INetFwRules* pRules = NULL;
    HRESULT hr = m_pPolicy->get_Rules(&pRules);
    if (FAILED(hr))
        return false;

    hr = pRules->Item(_bstr_t(ruleName.c_str()), ppRule);
    pRules->Release();

    return SUCCEEDED(hr);
}

void CNetFwCtrl::PrintRuleInfo(const std::wstring& ruleName)
{
    INetFwRule* pRule = NULL;
    if (!GetRule(ruleName, &pRule))
    {
        printf("Rule '%ws' not found\n", ruleName.c_str());
        return;
    }

    BSTR name, desc, app, localPorts, remoteAddrs;
    LONG protocol;
    NET_FW_ACTION action;
    NET_FW_RULE_DIRECTION direction;
    VARIANT_BOOL enabled;

    pRule->get_Name(&name);
    pRule->get_Description(&desc);
    pRule->get_ApplicationName(&app);
    pRule->get_LocalPorts(&localPorts);
    pRule->get_RemoteAddresses(&remoteAddrs);
    pRule->get_Protocol(&protocol);
    pRule->get_Action(&action);
    pRule->get_Direction(&direction);
    pRule->get_Enabled(&enabled);

    printf("\n[Rule: %ws]\n", name);
    printf("  Description: %ws\n", desc ? desc : L"");
    printf("  Application: %ws\n", app ? app : L"");
    printf("  Local Ports: %ws\n", localPorts ? localPorts : L"");
    printf("  Remote Addresses: %ws\n", remoteAddrs ? remoteAddrs : L"");
    printf("  Protocol: %ws\n", GetProtocolText(protocol));
    printf("  Action: %s\n", action == NET_FW_ACTION_ALLOW ? "Allow" : "Block");
    printf("  Direction: %s\n", direction == NET_FW_RULE_DIR_IN ? "Inbound" : "Outbound");
    printf("  Enabled: %s\n", enabled == VARIANT_TRUE ? "Yes" : "No");

    SysFreeString(name);
    SysFreeString(desc);
    SysFreeString(app);
    SysFreeString(localPorts);
    SysFreeString(remoteAddrs);
    // SysFreeString(protocol);
    pRule->Release();
}

const wchar_t* CNetFwCtrl::GetProtocolText(LONG protocol)
{
    switch (protocol)
    {
    case NET_FW_IP_PROTOCOL_TCP:
        return L"TCP";
    case NET_FW_IP_PROTOCOL_UDP:
        return L"UDP";
    case NET_FW_IP_PROTOCOL_ANY:
        return L"Any";
    default:
        return L"Other";
    }
}

bool CNetFwCtrl::SetRuleRemoteAddresses(const std::wstring& ruleName, const std::wstring& remoteAddrs)
{
    INetFwRule* pRule = NULL;
    if (!GetRule(ruleName, &pRule))
        return false;

    HRESULT hr = pRule->put_RemoteAddresses(_bstr_t(remoteAddrs.c_str()));
    pRule->Release();

    if (SUCCEEDED(hr)) {
        return true;
    }
    else return false;
}

std::wstring CNetFwCtrl::GetRuleRemoteAddress(const std::wstring& ruleName)
{
    INetFwRules* pRules = NULL;
    HRESULT hr = m_pPolicy->get_Rules(&pRules);
    if (FAILED(hr)) return L"";

    INetFwRule* pRule = NULL;
    hr = pRules->Item(_bstr_t(ruleName.c_str()), &pRule);
    pRules->Release();

    if (FAILED(hr)) return L"";

    BSTR bstrRemoteAddrs = NULL;
    pRule->get_RemoteAddresses(&bstrRemoteAddrs);
    pRule->Release();

    std::wstring result = bstrRemoteAddrs ? bstrRemoteAddrs : L"";
    SysFreeString(bstrRemoteAddrs);

    return result;
}

std::vector<std::wstring> CNetFwCtrl::ParseRemoteAddresses(const std::wstring& remoteAddrs)
{
    std::vector<std::wstring> result;

    if (remoteAddrs.empty() || remoteAddrs == L"Any" || remoteAddrs == L"*") {
        result.push_back(L"Any");
        return result;
    }

    // 分割逗号分隔的地址
    std::wistringstream iss(remoteAddrs);
    std::wstring token;

    while (std::getline(iss, token, L',')) {
        // 去除前后空格
        token.erase(token.begin(), std::find_if(token.begin(), token.end(), [](int ch) {
            return !std::iswspace(ch);
            }));
        token.erase(std::find_if(token.rbegin(), token.rend(), [](int ch) {
            return !std::iswspace(ch);
            }).base(), token.end());

        if (!token.empty()) {
            // 检查是否是IP范围 (192.168.1.1-192.168.1.100)
            //size_t dashPos = token.find(L'-');
            //if (dashPos != std::wstring::npos) {
            //    std::wstring startAddr = token.substr(0, dashPos);
            //    std::wstring endAddr = token.substr(dashPos + 1);

            //    // 这里可以添加IP范围解析逻辑
            //    result.push_back(token);
            //}
            //else {
            //    result.push_back(token);
            //}
            // 
            //去除掩码
            size_t dashPos = token.find(L'/');
            if (dashPos != std::wstring::npos) {
                std::wstring startAddr = token.substr(0, dashPos);
                // 这里可以添加IP范围解析逻辑
                result.push_back(startAddr);
            }
        }
    }

    return result;
}

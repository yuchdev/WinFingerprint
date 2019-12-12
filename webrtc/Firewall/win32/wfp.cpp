#include "wfp.h"

WFP::WFP() {
    engine_handle_ = nullptr;
    ZeroMemory(&engine_handle_, sizeof(HANDLE));
    ZeroMemory(&sublayer_guid_, sizeof(GUID));
    sublayer_guid_ = GUID();
    printf_s("WFP()\n");
}

WFP::~WFP() {
    allow_all();
    FwpmEngineClose0(engine_handle_);
    printf_s("~WFP()\n");
}

bool WFP::add_to_exceptions(const std::string &blob_path) {
    bool result = false;
    if (blob_path.empty()) {
        printf_s("Blob path is empty!\n");
        return result;
    }

    if (std::find(exclusion_paths_.begin(), exclusion_paths_.end(), converter_.from_bytes(blob_path.data())) == exclusion_paths_.end()) {
        exclusion_paths_.push_back(converter_.from_bytes(blob_path.data()));
        result = true;
    }
    printf_s("Success add path: '%s'\n", blob_path.data());
    return result;
}

bool WFP::deny_all_except() {
    bool result  = false;
    if (exclusion_paths_.empty()) {
        printf_s("Path's is empty!\n");
        return result;
    }

    uint64_t filter_id = 0;
    DWORD ret_code = ERROR_SUCCESS;

    FWPM_SESSION0           session;
    FWPM_SUBLAYER0          sublayer;

    FWPM_FILTER0            deny_all_filter_v4;
    FWPM_FILTER0            deny_all_filter_v6;

    /// init all WFP struct of zeros
    memset(&session,  0, sizeof (FWPM_SESSION0));
    memset(&sublayer, 0, sizeof (FWPM_SUBLAYER0));

    /// try to Open Firewall Engine
    ret_code = FwpmEngineOpen0(NULL, RPC_C_AUTHN_WINNT, NULL, &session, &engine_handle_);
    ret_code = FwpmSubLayerDeleteByKey0(engine_handle_, &sublayer_guid_);

    RtlZeroMemory(&deny_all_filter_v4,  sizeof (FWPM_FILTER0));
    RtlZeroMemory(&deny_all_filter_v6,  sizeof (FWPM_FILTER0));

    /// block ipv4 traffic
    wchar_t name_v4[] = L"Block ipv4";
    deny_all_filter_v4.layerKey             = FWPM_LAYER_ALE_AUTH_CONNECT_V4;
    deny_all_filter_v4.action.type          = FWP_ACTION_BLOCK;
    deny_all_filter_v4.subLayerKey          = sublayer_guid_;
    deny_all_filter_v4.weight.type          = FWP_UINT8;
    deny_all_filter_v4.weight.uint8         = 0xF;
    deny_all_filter_v4.numFilterConditions  = 0;
    deny_all_filter_v4.displayData.name     = name_v4;

    ret_code = FwpmFilterAdd0(engine_handle_, &deny_all_filter_v4, NULL, &filter_id);
    if (ret_code != ERROR_SUCCESS) {
        printf_s("[%s][%d] EC: '%lu'", __FUNCTION__, __LINE__, ret_code);
        allow_all();
        return result;
    }
    else {
        printf_s("[%s][%d] Success added filter ID: '%lu'", __FUNCTION__, __LINE__, filter_id);
        filter_ids_.push_back(filter_id);
    }

    /// block ipv6 traffic
    wchar_t name_v6[] = L"Block ipv6";
    deny_all_filter_v6.layerKey             = FWPM_LAYER_ALE_AUTH_CONNECT_V6;
    deny_all_filter_v6.action.type          = FWP_ACTION_BLOCK;
    deny_all_filter_v6.subLayerKey          = sublayer_guid_;
    deny_all_filter_v6.weight.type          = FWP_UINT8;
    deny_all_filter_v6.weight.uint8         = 0xF;
    deny_all_filter_v6.numFilterConditions  = 0;
    deny_all_filter_v6.displayData.name     = name_v6;
    ret_code = FwpmFilterAdd0(engine_handle_, &deny_all_filter_v6, NULL, &filter_id);
    if (ret_code != ERROR_SUCCESS) {
        printf_s("[%s][%d] EC: '%lu'", __FUNCTION__, __LINE__, ret_code);
        allow_all();
        return result;
    }
    else {
        printf_s("[%s][%d] Success added filter ID: '%lu'", __FUNCTION__, __LINE__, filter_id);
        filter_ids_.push_back(filter_id);
    }


    /// add exceptions to firewall
    for (auto &item : exclusion_paths_) {

        FWP_BYTE_BLOB* blob = (FWP_BYTE_BLOB*)malloc(sizeof(FWP_BYTE_BLOB));

        if (!blob) {
            allow_all();
            return result;
        }

        DWORD res = FwpmGetAppIdFromFileName0(item.data(), &blob);
        if (res != ERROR_SUCCESS) {
            printf_s("[%s][%d] EC: '%lu'", __FUNCTION__, __LINE__, ret_code);
            allow_all();
            return result;
        }

        exclusion_blobs_.push_back(blob);

        FWPM_FILTER0 blob_filter_v4;
        FWPM_FILTER0 blob_filter_v6;

        RtlZeroMemory(&blob_filter_v4, sizeof (FWPM_FILTER0));
        RtlZeroMemory(&blob_filter_v6, sizeof (FWPM_FILTER0));

        FWPM_FILTER_CONDITION0  blob_condition;

        RtlZeroMemory(&blob_condition, sizeof (FWPM_FILTER_CONDITION0));

        wchar_t allow_v4[] = L"Allow app v4";
        blob_condition.fieldKey                = FWPM_CONDITION_ALE_APP_ID;
        blob_condition.matchType               = FWP_MATCH_EQUAL;
        blob_condition.conditionValue.type     = FWP_BYTE_BLOB_TYPE;
        blob_condition.conditionValue.byteBlob = blob;

        blob_filter_v4.layerKey                = FWPM_LAYER_ALE_AUTH_CONNECT_V4;
        blob_filter_v4.action.type             = FWP_ACTION_PERMIT;
        blob_filter_v4.subLayerKey             = sublayer_guid_;
        blob_filter_v4.weight.type             = FWP_UINT8;
        blob_filter_v4.weight.uint8            = 0xF;
        blob_filter_v4.filterCondition         = &blob_condition;
        blob_filter_v4.numFilterConditions     = 1;
        blob_filter_v4.displayData.name        = allow_v4;

        ret_code = FwpmFilterAdd0(engine_handle_, &blob_filter_v4, NULL, &filter_id);
        if (ret_code != ERROR_SUCCESS) {
            printf_s("[%s][%d] EC: '%lu'", __FUNCTION__, __LINE__, ret_code);
            allow_all();
            return result;
        }
        else {
            printf_s("[%s][%d] Success added filter ID: '%lu'", __FUNCTION__, __LINE__, filter_id);
            filter_ids_.push_back(filter_id);
        }

        wchar_t allow_v6[] = L"Allow app v6";
        blob_filter_v6.layerKey                = FWPM_LAYER_ALE_AUTH_CONNECT_V6;
        blob_filter_v6.action.type             = FWP_ACTION_PERMIT;
        blob_filter_v6.subLayerKey             = sublayer_guid_;
        blob_filter_v6.weight.type             = FWP_UINT8;
        blob_filter_v6.weight.uint8            = 0xF;
        blob_filter_v6.filterCondition         = &blob_condition;
        blob_filter_v6.numFilterConditions     = 1;
        blob_filter_v6.displayData.name        = allow_v6;

        ret_code = FwpmFilterAdd0(engine_handle_, &blob_filter_v6, NULL, &filter_id);
        if (ret_code != ERROR_SUCCESS) {
            printf_s("[%s][%d] EC: '%lu'", __FUNCTION__, __LINE__, ret_code);
            allow_all();
            return result;
        }
        else {
            printf_s("[%s][%d] Success added filter ID: '%lu'", __FUNCTION__, __LINE__, filter_id);
            filter_ids_.push_back(filter_id);
        }
    }

    return true;
}

bool WFP::allow_all() {
    bool result = false;
    if (filter_ids_.empty()) return result;

    printf_s("Remove filters\n");
    for (auto &filter: filter_ids_) {
        FwpmFilterDeleteById0(engine_handle_, filter);
        printf_s("Remove filter_id: '%I64u'\n", filter);
    }

    printf_s("Remove filters done...\n");
    filter_ids_.clear();
    close_all_blobs();
    return true;
}

void WFP::close_all_blobs() {
    if (exclusion_blobs_.empty()) return;

    printf_s("Remove pointers...\n");
    printf_s("Bolbs size: '%u'", exclusion_blobs_.size());
    exclusion_blobs_.clear();
    printf_s("Remove pointers done\n");
}

void WFP::get_error(LPTSTR fname, DWORD ec) {
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    ec = GetLastError();
    FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                ec,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR) &lpMsgBuf,
                0, NULL );

    /// Display the error message and exit the process
    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)fname) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR),  TEXT("%s failed with error %d: %s"),fname, ec, lpMsgBuf);
    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}

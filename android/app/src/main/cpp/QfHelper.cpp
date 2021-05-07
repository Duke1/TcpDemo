//
// Created by Duke
//

#include "QfHelper.h"
#include <arpa/inet.h>
#include <netdb.h>

#include "rapidjson/document.h"
#include "RapJson.h"

using namespace rapidjson;

std::string QfHelper::findIpByDomain(std::string domain) {
    int i = 0;
    struct hostent *host;

    host = gethostbyname(domain.c_str());


    auto *json = new RapJson();

    //official name
    json->AddMember("official_name", host->h_name, json->document->GetAllocator());

    //aliases
    Value aliases(kArrayType);
    Document::AllocatorType &allocator = json->document->GetAllocator();
    for (i = 0; host->h_aliases[i]; i++) {
        aliases.PushBack(StringRef(host->h_aliases[i]), allocator);
    }
    json->AddMember("aliases", aliases, allocator);

    //ips
    Value ips(kArrayType);
    Document::AllocatorType &allocator1 = json->document->GetAllocator();
    for (i = 0; host->h_addr_list[i]; i++) {
        auto ip = inet_ntoa(*((struct in_addr *) host->h_addr_list[i]));
        ips.PushBack(StringRef(ip), allocator1);
    }
    json->AddMember("ips", ips, allocator1);

    std::string result = json->ToString();
    delete json;
    //LOGI("域名信息：%s", result.c_str());
    return result;
}

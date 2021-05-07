//
// Created by Duke
//

#include "RapJson.h"

using namespace rapidjson;

RapJson::RapJson() {
    document = new Document();
    document->SetObject();
}

RapJson::~RapJson() {
    delete document;
}

std::string RapJson::ToString() {

    StringBuffer strBuffer;
    Writer<StringBuffer> writer(strBuffer);
    document->Accept(writer);

    //const char *resultStr = strBuffer.GetString();
    //size_t strSize = strlen(resultStr);

    return std::string(strBuffer.GetString());

}

void RapJson::AddMember(char *name, Value &value, Document::AllocatorType &allocator) {
    document->AddMember(StringRef(name), value, allocator);
}

void RapJson::AddMember(char *name, char *value, Document::AllocatorType &allocator) {
    document->AddMember(StringRef(name), StringRef(value), allocator);
}

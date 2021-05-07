//
// Created by Duke.
//

#ifndef TCPDEMO_RAPJSON_H
#define TCPDEMO_RAPJSON_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/allocators.h"

#include <string>

using namespace rapidjson;

class RapJson {
    public:
        Document *document;

    public:
        RapJson();

        ~RapJson();

        std::string ToString();

        void AddMember(char *name, Value &value, Document::AllocatorType &allocator);

        void AddMember(char *name, char *value, Document::AllocatorType &allocator);
};


#endif //TCPDEMO_RAPJSON_H

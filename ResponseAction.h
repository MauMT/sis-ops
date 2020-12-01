#pragma once

#include <string>

enum class ResponseActionType { AccessAddressQuery,
                                AllocateProcessQuery,
                                DeallocateProcessQuery,
                                CommentQuery,
                                FinishQuery,
                                ExitQuery,
                                Error };

class ResponseAction {
   public:
    ResponseActionType type;

    ResponseAction(ResponseActionType type);
    virtual ~ResponseAction() = 0;
};

class Query : public ResponseAction {
   public:
    Query();
};

class AllocateProcessQuery : public ResponseAction {
   public:
    int process_id;
    int bytes;

    AllocateProcessQuery(int process_id, int bytes);
};

class DeallocateProcessQuery : public ResponseAction {
   public:
    int process_id;

    DeallocateProcessQuery(int process_id);
};

class AccessAddressQuery : public ResponseAction {
   public:
    int process_id;
    int virtual_address;
    bool modify;

    AccessAddressQuery(int process_id, int virtual_address, bool modify);
};

class CommentQuery : public ResponseAction {
   public:
    std::string comment;

    CommentQuery(std::string comment);
    void print();
};

class FinishQuery : public ResponseAction {
   public:
    FinishQuery();
};

class ExitQuery : public ResponseAction {
   public:
    ExitQuery();
};

class Error : public ResponseAction {
   public:
    std::string message;

    Error(std::string message);
    void print();
};
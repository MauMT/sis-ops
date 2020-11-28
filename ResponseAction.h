#include <string>

enum class ResponseActionType { AccessAddressQuery,
                                AllocateProcessQuery,
                                DeallocateProcessQuery,
                                CommentQuery,
                                FinishQuery,
                                ExitQuery,
                                Error };

enum class QueryType { AccessAddressQuery,
                       AllocateProcessQuery,
                       DeallocateProcessQuery,
                       CommentQuery,
                       FinishQuery,
                       ExitQuery };

enum class ErrorType { InvalidID,
                       };

class ResponseAction {
   public:
    ResponseAction(ResponseActionType type);

    ResponseActionType type;
};

class Query : public ResponseAction {
   public:
    Query();
};

class AllocateProcessQuery : public Query {
    int process_id;
    int bytes;

   public:
    AllocateProcessQuery(int process_id, int bytes);
};

class DeallocateProcessQuery : public Query {
    int process_id;

   public:
    DeallocateProcessQuery(int process_id);
};

class AccessAddressQuery : public Query {
    int process_id;
    int virtual_address;
    bool modify;

   public:
    AccessAddressQuery(int process_id, int virtual_address, bool modify);
};

class CommentQuery : public Query {
    std::string comment;

   public:
    CommentQuery(std::string comment);
    void print();
};

class Error : public ResponseAction {
    std::string message;

   public:
    Error(std::string message);
    void print();
};
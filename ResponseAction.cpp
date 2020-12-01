#include "ResponseAction.h"

#include <iostream>
#include <string>

using namespace std;

ResponseAction::ResponseAction(ResponseActionType type) {
    this->type = type;
}

ResponseAction::~ResponseAction() {
}

AccessAddressQuery::AccessAddressQuery(int process_id, int virtual_address, bool modify) : ResponseAction(ResponseActionType::AccessAddressQuery) {
    this->process_id = process_id;
    this->virtual_address = virtual_address;
    this->modify = modify;
}

AllocateProcessQuery::AllocateProcessQuery(int process_id, int bytes) : ResponseAction(ResponseActionType::AllocateProcessQuery) {
    this->process_id = process_id;
    this->bytes = bytes;
}

DeallocateProcessQuery::DeallocateProcessQuery(int process_id) : ResponseAction(ResponseActionType::DeallocateProcessQuery) {
    this->process_id = process_id;
}

CommentQuery::CommentQuery(std::string comment) : ResponseAction(ResponseActionType::CommentQuery) {
    this->comment = comment;
}

void CommentQuery::print() {
    std::cout << "C " << comment << endl << endl;
}

FinishQuery::FinishQuery() : ResponseAction(ResponseActionType::FinishQuery) {

}

ExitQuery::ExitQuery() : ResponseAction(ResponseActionType::ExitQuery) {
    
}

Error::Error(std::string message) : ResponseAction(ResponseActionType::Error) {
    this->message = message;
}

void Error::print() {
    std::cout << "Error: " << message << endl << endl;
}

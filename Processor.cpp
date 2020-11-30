#include "Processor.h"

#include <vector>

#include "Clock.h"

using namespace std;

Processor::Processor() {
    memory = Memory(2048);
    swap_area = SwapArea();
    input_handler = InputHandler(this);
    swapper = new FIFOSwapper(&memory, &swap_area);
    swap_in_count = 0;
    swap_out_count = 0;
    clock = 0;
}

Processor::~Processor() {
    delete swapper;
}

template <class T>
T castResponse(ResponseAction* action) {
    return *(dynamic_cast<T*>(action))
}

void Processor::exec(string filename) {
    input_handler.loadFile(filename);
    while (input_handler.isReading()) {
        ResponseAction* action = input_handler.readNextLine();
        switch (action->type) {
            case ResponseActionType::AllocateProcessQuery: {
                AllocateProcessQuery query = castResponse<AllocateProcessQuery>(action);
                allocateProcess(query);
            } break;
            case ResponseActionType::AccessAddressQuery: {
                AccessAddressQuery query = castResponse<AccessAddressQuery>(action);
                accessAddress(query);
            } break;
            case ResponseActionType::DeallocateProcessQuery: {
                DeallocateProcessQuery query = castResponse<DeallocateProcessQuery>(action);
                deallocateProcess(query);
            } break;
            case ResponseActionType::CommentQuery: {
                CommentQuery comment = castResponse<CommentQuery>(action);
                comment.print();
            } break;
            case ResponseActionType::FinishQuery:
                reinitialize();
                break;
            case ResponseActionType::ExitQuery:
                exit();
                break;
            case ResponseActionType::Error: {
                Error error = castResponse<Error>(action);
                error.print();
            } break;
            default:
                break;
        }

        delete action;
    }
}

void Processor::accessAddress(AccessAddressQuery query) {
}

void Processor::allocateProcess(AllocateProcessQuery query) {
    Process new_process = Process(query.bytes, query.bytes, clock);

    auto pages = new_process.getPages();
    for (auto& page : pages) {
        if (memory.getFreeFrames() <= 0) {
            swapper->swapOut();
            clock += 1 * 1000;
        }
        int frame_number = memory.getFreeFrameIndex();
        memory.setPageToFrame(frame_number, &page);
        clock += 1 * 1000;
    }
}

void Processor::deallocateProcess(DeallocateProcessQuery query) {
}

void Processor::reinitialize() {
}

void Processor::exit() {
}

void Processor::printStats() {
}
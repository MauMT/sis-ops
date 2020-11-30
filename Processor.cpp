#include "Processor.h"
#include "Clock.h"

#include <vector>

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

void Processor::accessAddress(AccessAddressQuery query) {
}

void Processor::allocateProcess(AllocateProcessQuery query) {
    Process new_process = Process(query.bytes, query.bytes, clock);

    auto pages = new_process.getPages();
    for (auto &page : pages) {
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
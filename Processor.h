#include <map>

#include "InputHandler.h"
#include "Memory.h"
#include "Process.h"
#include "Swapper.h"

// TODO: documentar
class Processor {
    std::map<int, Process> processes;
    Memory memory;
    Swapper swapper;
    int clock;
    int swap_in_count;
    int swap_out_count;
    InputHandler input_handler;

   public:
    Processor();
    void accessAddress(AccessAddressQuery query);
    void allocateProcess(AllocateProcessQuery query);
    void deallocateProcess(DeallocateProcessQuery query);
    void reinitialize();
    void exit();
    void printStats();
};
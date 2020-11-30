#include <map>

#include "InputHandler.h"
#include "Memory.h"
#include "Process.h"
#include "Swapper.h"
#include "SwapArea.h"

// TODO: documentar
class Processor {
    std::map<int, Process> processes;
    Memory memory;
    SwapArea swap_area;
    Swapper *swapper;
    int swap_in_count;
    int swap_out_count;
    InputHandler input_handler;

   public:
    Processor();
    ~Processor();
    void accessAddress(AccessAddressQuery query);
    void allocateProcess(AllocateProcessQuery query);
    void deallocateProcess(DeallocateProcessQuery query);
    void reinitialize();
    void exit();
    void printStats();
};
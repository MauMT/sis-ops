using namespace std;
#include <map>
#include "Process.h"
#include "Memory.h"
#include "Swapper.h"
#include "InputHandler.h"

class Processor{
    map<int, Process> processes;
    Memory memory;
    Swapper swapper;
    int clock;
    int swap_in_count;
    int swap_out_count;
    InputHandler inputHandler;

    

};
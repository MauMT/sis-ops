#include "Memory.h"
#include "SwapArea.h"

class Swapper {
   protected:
    Memory* memory;
    SwapArea* swap_area;

   public:
    Swapper(Memory* nemory, SwapArea* swap_area);
    virtual void swap(Page* page);
};

class FIFOSwapper : public Swapper {
   public:
    FIFOSwapper(Memory* nemory, SwapArea* swap_area);
    void swap(Page* page);
};

class LRUSwapper : public Swapper {
   public:
    LRUSwapper(Memory* nemory, SwapArea* swap_area);
    void swap(Page* page);
};
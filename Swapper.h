#pragma once

#include "Memory.h"
#include "SwapArea.h"

class Swapper {
   protected:
    Memory* memory;
    SwapArea* swap_area;

   public:
    Swapper(Memory* memory, SwapArea* swap_area);
    /**
     * Saca una página del swap area y la inserta en la memoria real. Asume que ya 
     * hay frames libres en la memoria real para insertar la página.
     * 
     * @param page la página que va a salir del swap area.
     */
    void swapIn(Page* page);
    /**
     * Inserta una página de la memoria real en el swap area de acuerdo a la 
     * política de la instancia.
     * 
     * @return apuntador a la página que entró en el swap area.
     */
    virtual Page* swapOut() = 0;
};

class FIFOSwapper : public Swapper {
   public:
    FIFOSwapper(Memory* memory, SwapArea* swap_area);
    /**
     * Inserta una página de la memoria real en el swap area de acuerdo a la 
     * política First In First Out.
     * 
     * @return apuntador a la página que entró en el swap area.
     */
    Page* swapOut();
};

class LRUSwapper : public Swapper {
   public:
    LRUSwapper(Memory* memory, SwapArea* swap_area);
    /**
     * Inserta una página de la memoria real en el swap area de acuerdo a la 
     * política Least Recently Used.
     * 
     * @return apuntador a la página que entró en el swap area.
     */
    Page* swapOut();
};
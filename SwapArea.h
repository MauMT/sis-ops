#pragma once

#include <vector>

#include "Page.h"

/**
 * Modela el area de swapeo. Provee una interfaz para insertar y remover paginas de esta area.
 */ 
class SwapArea {
    std::vector<Page *> pages;

   public:
    SwapArea();

    /**
     * @return referencia al vector de páginas del swap area.
     */
    std::vector<Page *> &getPages();

    /**
     * Inserta una pagina al swap area.
     * 
     * @param page apuntador a la pagina a insertar.
     */
    void insertPage(Page *page);

    /**
     * Encuentra la pagina de un proceso donde se encuentra su direccion virtual
     * virtual_address.
     * 
     * @param process_id Id del proceso a buscar.
     * @param virtual_address direccion virtual a buscar.
     * @return apuntador a la pagina encontrada. nullptr si no se encontro.
     */
    Page *findPage(int process_id, int virtual_address);

    /**
     * Elimina la pagina en el Swap Area de un proceso.
     * 
     * @param page apuntador del proceso a eliminar
     */
    void removePage(Page *page);
};
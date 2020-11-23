#include <vector>

#include "Page.h"
class SwapArea {
    std::vector<Page *> pages;

   public:
    SwapArea();

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
    Page *findPage(int process_id, int virtual_addreess);
};
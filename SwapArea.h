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
    Page *findPage(int process_id, int virtual_address);

    /**
     * Elimina la pagina en el Swap Area de un proceso.
     * 
     * @param page apuntador del proceso a eliminar
     */
    void removePage(Page *page);
};

SwapArea::SwapArea() {
    pages = std::vector<Page *>(0);
}

void SwapArea::insertPage(Page *page) {
    // Este if checa si el Swap Area esta lleno.
    if (pages.size() >= 256) {
        // No agrega el apuntador de la pagina.
        // Deberia mostrar algun tipo de error.
        return;
    }

    // No esta lleno, inserta la nueva pagina.
    pages.push_back(page);
}

Page *SwapArea::findPage(int process_id, int virtual_address) {
    // Recorre el vector que contiene las paginas.
    for (Page *page : pages) {
        // Encuentra y regresa la pagina si el process_id coincide y si el virtual address esta en el rango correcto.
        if (page->getProcessId() == process_id && virtual_address >= page->getVirtualAddressStart() && virtual_address < page->getVirtualAddressStart() + 16) {
            return page;
        }
    }

    // Regresa nullptr si no encuentra la pagina correcta.
    return nullptr;
}

void SwapArea::removePage(Page *page) {
    // Busca la pagina `page` y le asigna el apuntador resultado a la variable temp.
    Page *temp = findPage(page->getProcessId(), page->getVirtualAddressStart());

    // Itera el vector de paginas y borra la page del vector.
    for (int i = 0; i < pages.size(); i++) {
        if (pages[i] == temp) {
            pages.erase(pages.begin() + i);
        }
    }
}

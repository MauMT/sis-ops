#include "Page.h"

class Frame {
    bool free;
    Page *page;

   public:
    Frame();

    /**
     * 
     * @return apuntador a la pagina del frame.
     */
    Page *getPage();

    /**
     * 
     * @return el Id del proceso que aloja el frame.
     */
    int getProcessId();

    /**
     * 
     * @return si el frame esta libre (no tiene asignado un proceso).
     */
    bool isFree();

    /**
     * Asigna la pagina de un proceso al frame
     * 
     * @param page pagina del proceso
     */
    void setPage(Page *page);

    /**
     * Libera el frame de la pagina;
     * 
     *
     */
    void setFree(bool free = true);
};

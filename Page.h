// TODO: documentar
class Page {
    static const int page_size = 16;
    int in_memory;
    int real_address_start;
    int virtual_address_start;
    int swap_address;
    int process_id;
    int last_use;

   public:
    Page(int process_id, int page_number);  // virtual_address_start se calcula con page_number

    bool isInMemory();
    int getLastUse();
    int getProcessId();
    int getVirtualAddressStart();
    int getRealAddressStart();

    /**
     * Regresa si la pagina contiene la direccion virtual virtual_address del
     * proceso
     * 
     * @param virtual_address direccion virtual a buscar.
     * @return si la direccion virtual esta en la pagina.
     */
    bool holdsVirtualAddress(int virtual_address);
};
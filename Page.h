// TODO: documentar
class Page {
    static const int page_size = 16;
    bool in_memory;
    int frame_number; //era real_address_start
    int page_number; // era virtual_address_start
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
    void setProcessId(int);

    /**
     * Regresa si la pagina contiene la direccion virtual virtual_address del
     * proceso
     * 
     * @param virtual_address direccion virtual a buscar.
     * @return si la direccion virtual esta en la pagina.
     */
    bool holdsVirtualAddress(int virtual_address);
};

Page::Page(int process_id, int page_number){
    this->process_id=process_id;
    this->page_number=page_number;
}

bool Page::isInMemory(){
    return in_memory;
}

bool Page::holdsVirtualAddress(int virtual_address){
    
    return true; // ¿cómo se prueba eso?
}

int Page::getLastUse(){
    return last_use;
}

int Page::getProcessId(){
    return process_id;
}

void Page::setProcessId(int process_id){
    this->process_id=process_id;
}

int Page::getVirtualAddressStart(){
    return page_number;
}

int Page::getRealAddressStart(){
    return frame_number;
}
class Frame {
    bool free;
    int process_id;

   public:
    Frame();

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
     * Asigna un proceso con id process_id al frame.
     * 
     * @param process_id
     */
    void setProcessId(int process_id);
};
#include <vector>

#include "Frame.h"

class Memory {
    int size;
    int free_frames;
    std::vector<Frame> frames;

   public:
    Memory(int size);

    /**
     * Regresa una referencia a los frames de la memoria.
     * 
     * @return referencia al contenedor de frames.
     */
    std::vector<Frame>& getFrames();

    /**
     * Asigna un proceso a un frame.
     * 
     * @param process_id numero del frame a modificar.
     * @param frame_number numero del frame a modificar.
     * @return copia del frame.
     */
    void setFrameProcess(int process_id, int frame_number);

    /**
     * Libera el frame numero frame_number.
     * 
     * @param frame_number numero del frame a liberar.
     */
    void freeFrame(int frame_number);

    /**
     * Regresa el numero de frames libres en memoria.
     * 
     * @return el numero de frames.
     */
    int getFreeFrames();

};

#include <map>
#include <string>

#include "InputHandler.h"
#include "Memory.h"
#include "Process.h"
#include "SwapArea.h"
#include "Swapper.h"

// TODO: documentar
/**
 * Modelo para el procesador.
 * 
 * Ejecuta un archivo de texto con una serie de comandos para manipular procesos.
 */
class Processor {
    std::map<int, Process> processes;
    Memory memory;
    SwapArea swap_area;
    Swapper *swapper;
    int swap_in_count;
    int swap_out_count;
    InputHandler input_handler;

   public:
    Processor();
    ~Processor();

    /**
     * Ejecuta los comandos de un archivo de texto
     * 
     * @param filename ruta del archivo a ejecutar
     */
    void exec(std::string filename);

    /**
     * Accesa a una dirección de memoria virtual de un proceso.
     * 
     * @param query Objeto con la información del process_id, dirección de memoria virtual y 
     *              una bandera para indicar si el proceso se va a accessar.
     */
    void accessAddress(AccessAddressQuery query);

    /**
     * Carga un nuevo proceso en memoria.
     * 
     * @param query Objeto con la información del nuevo proceso (id y número de bytes).
     */
    void allocateProcess(AllocateProcessQuery query);

    /**
     * Libera las páginas de un proceso de la memoria real y el swap area.
     * 
     * @param query Objeto con el id del proceso a liberar.
     */
    void deallocateProcess(DeallocateProcessQuery query);

    /**
     * Reinicia el estado del procesador al inicial.
     */
    void reinitialize();

    /**
     * Termina la ejecución de la lectura de comandos.
     */
    void exit();

    /**
     * Imprime las estadísticas en el estado actual del procesador.
     */
    void printStats();
};
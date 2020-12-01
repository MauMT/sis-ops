#pragma once

#include <fstream>

#include "ResponseAction.h"
class Processor;  // Include circular

/**
 * Maneja la entrada para el procesador. Incluye la carga y lectura de un archivo de texto, además 
 * de la interpretación de los comandos a objetos (ResponseAction) que pueden ser usados por el procesador.
 */
class InputHandler {
    Processor *processor;

   public:
    InputHandler(Processor *processor = nullptr);
    ~InputHandler();

    /**
     * Interpreta una línea de texto como un comando válido (ResponseAction).
     * 
     * @param line linea a interpretar.
     * @return ResponseAction correspondiente al string.
     */
    ResponseAction *parse(std::string line);

    /**
     *Borra todos los espacios vacíos antes de alguno de los caracteres de los comandos 
     * 
     *@param string por modificar  
     */
    friend void lTrim(std::string &s);

    /**
     * Elimina los espacios vacíos y el primer caracter del comando, deja a los valores enteros listos para ser leídos
     * 
     * @param string por modificar
     */
    friend void firstCharDel(std::string &s);
   
    /**
     * Borra todos los espacios vacíos después del último caracter alfanumérico de un comando
     * 
     * @param string por modificar
     */
    friend void rTrim(std::string &s);
};

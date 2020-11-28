#include <string>
#include <sstream>

#include "ResponseAction.h"
class Processor; // Include circular

// Tal vez incluir logica para leer el archivo de texto
class InputHandler {
    Processor* processor;  // Se necesita para validar el input

   public:
    InputHandler(Processor* processor);
    ResponseAction parse(std::string line);
    std::string removeSpaces(std::string s1);
};

std::string InputHandler::removeSpaces(std::string s1){
  std::stringstream ss;
  std::string aux;
  ss<<s1;
  s1="";
  while (getline(ss,aux,' ')) {
    s1=s1+aux;
  } 
   return s1;
}

ResponseAction InputHandler::parse(std::string line){
    std::string console_line = removeSpaces(line);

   
}
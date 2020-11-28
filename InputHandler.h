#include <string>
#include <sstream>
#include <iostream>

#include "ResponseAction.h"
class Processor; // Include circular

// Tal vez incluir logica para leer el archivo de texto
class InputHandler {
    Processor* processor;  // Se necesita para validar el input

   public:
    InputHandler(Processor* processor);
    ResponseAction parse(std::string line);
    friend void lTrim(std::string &s);
    friend void firstCharDel(std::string &s);
    friend void rTrim(std::string &s):
};

void lTrim(std::string &s){
  auto pos = s.find_first_not_of(' ');
  if(s.size()>1)
    s=s.substr(pos);
}

void rTrim(std::string &s){
  auto pos = s.find_last_not_of(' ');
  //lTrim(s);
  if(s.size()>1)
    s=s.substr(0,pos+1);
}

void firstCharDel(std::string &s){
  if(s.size()>1)
    s=s.substr(1);
  lTrim(s);
}

ResponseAction InputHandler::parse(std::string line){
    std::stringstream ss;
    lTrim(line);
    char commandSymbol=line[0];
    firstCharDel(line);
   
    int input_process_id;
    int input_n; //Se trata de una solicitud de “n” bytes para cargar un proceso a la memoria. 
    int input_direccion_virtual;
    bool input_m; //Si “m” es 0, la dirección correspondiente sólo se lee; si es 1, también se modifica
    
    switch(commandSymbol)
    {
        case 'p': case 'P':
            ss<<line;
            ss>>input_n>>input_process_id;
            if(ss.fail())
            {
                return ResponseActionType::Error;
            }
            return ResponseActionType::AllocateProcessQuery;
            break;
        case 'a': case 'A':
            ss<<line;
            ss>>input_direccion_virtual>>input_process_id>>input_m;
            if(ss.fail())
            {
                return ResponseActionType::Error;
            }
            return ResponseActionType::AccessAddressQuery;
            break;
        case 'l': case 'L':
            ss<<line;
            ss>>input_process_id;
            if(ss.fail())
            {
                return ResponseActionType::Error;
            }
            return ResponseActionType::DeallocateProcessQuery;
            break;
        
        case 'c': case 'C':
            std::cout<<"C\n"<<line<<std::endl;
            return ResponseActionType::CommentQuery; 
            break;
        
        case 'f': case 'F':
            return ResponseActionType::FinishQuery;
        
        case 'e': case 'E':
            return ResponseActionType::ExitQuery; 
            break;
        
        default:
            return ResponseActionType::Error;
            break;
    }
   return ResponseActionType::Error; //qué regresar?🤔
}
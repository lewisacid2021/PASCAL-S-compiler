
#include <iostream>
#include <unordered_map>
#include <vector>

#include "symbolTable.h"

#ifndef PASCC_PSTDLIB_H
#define PASCC_PSTDLIB_H


/**
 * @brief standard library for pascal-s
 */
class PLib {
 public:
  PLib();
  ~PLib(){};

  bool Call(std::string lib_name);
  bool UnCall(std::string lib_name);

  void Preserve(SymbolTable* st);

  void Generationvisitor(FILE* dst);

 private:
  bool CheckMathLib();
  struct Lib {
    std::string _def;
    bool _called;
  };
  std::unordered_map<std::string, Lib> math_map;
};


#endif 

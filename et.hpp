#ifndef et_hpp
#define et_hpp

#include<cstdlib>
#include<string>
#include<iostream>
#include"stack.hpp"

class et{
private:
	struct etNode{
		std::string key;
		etNode *right;
    etNode *left;
    etNode *parent;
	};

  size_t count;
	etNode *tree;

bool ver_alpha_str(std::string s); //Adaptacion de isalpha para strings
bool ver_dig_str(std::string s); //Adaptacion de isnum para strings

etNode * copy(etNode *tree); //Crea una copia distinta al arbol de expresion de referencia
void clear(etNode * &tree); //Elimina todos los elementos del arbol del expresion
void concatenate(etNode *tree, std::ostream &out) const;
void display(etNode *tree, std::ostream &out) const; //Imprime el contenido del arbol en la terminal

void derivar(etNode *tree, std::string variable); //Funcion de derivacion por casos recursivos
void simplificar(etNode *tree); //Funcion de para simplificar operaciones entre constantes
void simplificar_rec(etNode *tree); //Funcion recursiva para simplificarsobre un arbol

public:
	et(); //Constructor por defecto
	et(std::string s); //Constructor sobre funcion en notacion preorden
  et(const et &rhs); //Constructor copia
	~et(); //Destructor

  bool empty(void) const; //Revisa si hay elementos en el arbol
  void clear(void); //Version publica de clear
  void display(std::ostream &out = std::cout) const; //Version publica de display

	void derivar(std::string variable = "x"); //Version publica de derivar
	void simplificar(); //Version publica de simplificar
};

#include "et.cpp"
#endif

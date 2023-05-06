#ifdef et_hpp

/**
Input: String
Verifica si todos los caracteres del string son alfabeticas
*/
bool et::ver_alpha_str(std::string s){
  for (unsigned i = 0; i<s.size(); i++){
    if(not(isalpha(s[i]))){
      return false;
    }
  }
  return true;
}

/**
Input: String
Verifica si todos los caracteres del string son numericos
*/
bool et::ver_dig_str(std::string s){
  for (unsigned i = 0; i<s.size(); i++){
    if(not(isdigit(s[i]))){
      return false;
    }
  }
  return true;
}
/**
Input: Nodo de arbol de expresion
Crea una copia nueva del nodo de arbol de expresion junto a sus nodos hijos
*/
et::etNode * et::copy(etNode *tree){
  if (tree != nullptr){
    etNode * aux = new etNode;
    aux->key = tree->key;
    aux->left = copy(tree->left);
    aux->right = copy(tree->right);
    return aux;
  } else return nullptr;
}

/**
Input: Nodo de arbol de expresion
Destruye el nodo y los nodos hijos
*/
void et::clear(etNode * &tree){
  if (tree != nullptr){
    clear(tree->left);
    clear(tree->right);
    delete tree;
    count--;
  }
  tree = nullptr;
}

/**
Input: Nodo de arbol de expresion y stream de salida
Concatena losementos del arbol en un string siguiendo el formato; nodo izquierdo, nodo padre, nodo derecho. Si encuentra un operador crea parentesis para indicar orden de operacion
*/
void et::concatenate(etNode *tree, std::ostream &out) const{
  if (tree != nullptr){
    bool bin = (tree->key == "+" or tree->key == "-" or tree->key == "/"
    or tree->key == "*" or tree->key=="^");
    if(bin) std::cout <<"(";
    concatenate(tree->left, out);
    std::cout << tree->key;
    concatenate(tree->right, out);
    if(bin) std::cout<<")";
  }
}

/**
Input: Nodo de arbol de expresion y stream de salida
Imprime los elementos del arbol segun el resultado de concatenate
*/
void et::display(etNode *tree, std::ostream &out) const{
  concatenate(tree, out);
  std::cout << std::endl;
}

et::et(){
  count = 0;
  tree = nullptr;
}

/**
Input: String en notacion preorden
Crea un nodo para cada elemento del string, guarda los nodos creados en un stack. Si encuentra un operador une los nodos previos necesarios como hijos del nodo de la operacion
Funcion basada en algoritmo de conversion presentado en Logica para ciencias de la computacion
*/
et::et(std::string s){
  count = s.size();
  Stack<etNode*> aux1;
  for (unsigned i = 0; i<s.size(); i++){
    if (isalpha(s[i])){
      etNode *aux2 = new etNode;
      aux2->key = s[i];
      aux2->left = aux2->right = nullptr;
      aux1.push(aux2);
    } else if (isdigit(s[i])){
      std::string aux_str = "";
      aux_str += s[i];
      while (i+1<s.size() and isdigit(s[i+1])){
        i++;
        aux_str += s[i];
      }
      etNode *aux2 = new etNode;
      i++;
      aux2->key = aux_str;
      aux2->left = aux2->right = nullptr;
      aux1.push(aux2);
    } else if(s[i] == '+' or s[i] == '-' or s[i] == '/' or s[i] == '*' or s[i]=='^'){
      etNode *aux2 = new etNode;
      aux2->key = s[i];
      aux2->right = aux1.pop();
      aux2->left = aux1.pop();
      aux1.push(aux2);
    }
  }
  tree = aux1.pop();
}

et::et(const et &rhs){
  count = rhs.count;
  tree = copy(rhs.tree);
}

et::~et(){
  clear();
  tree = nullptr;
}

bool et::empty(void) const{
  return (count == 0);
}

void et::clear(void){
  clear(tree);
}

void et::display(std::ostream &out) const{
  display(tree, out);
}

/**
Input: Nodo desde el cual se aplica la derivacion  y string de la vriable sobre la cual derivar
Verifica los casos de derivacion para saber como implementar la derivacion aplicando recursividad donde sea necesaria.
Procesa unicamente sumas, restas, multiplicacion, division y algunos casos de exponentes. Para exponentes solo procesa casos de exponentes constantes o que tengan "e" como la base
*/
void et::derivar(etNode *tree, std::string variable){
  if (tree == nullptr){
    return;

  } else if ((ver_alpha_str(tree->key) and tree->key != variable) or ver_dig_str(tree->key) ){
    tree->key = "0";
    return;

  } else if (tree->key == variable){
    tree->key = "1";
    return;

  } else if (tree->key == "+" or tree->key == "-"){
    if ((ver_alpha_str(tree->left->key) and tree->left->key != variable) or ver_dig_str(tree->left->key)){
      tree->left->key = "0";
    } else {
      derivar(tree->left, variable);
    }
    if ((ver_alpha_str(tree->right->key) and tree->right->key != variable) or ver_dig_str(tree->right->key)){
      tree->right->key = "0";
    } else {
      derivar(tree->right, variable);
    }

  } else if (tree->key == "*"){
    bool left_const = ((ver_alpha_str(tree->left->key) and tree->left->key != variable) or ver_dig_str(tree->left->key));
    bool right_const = ((ver_alpha_str(tree->right->key) and tree->right->key != variable) or ver_dig_str(tree->right->key));
    if (left_const and right_const){
      tree->key = "0";
      clear(tree->right);
      clear(tree->left);
      return;
    } else if (left_const){
      if (tree->right->key == variable){
          tree->key = tree->left->key;
          clear(tree->right);
          clear(tree->left);
      } else {
        derivar(tree->right, variable);
      }
    } else if (right_const){
      if (tree->left->key == variable){
          tree->key = tree->right->key;
          clear(tree->right);
          clear(tree->left);
      } else {
        derivar(tree->left, variable);
      }
    } else {
      etNode * copia_izquierda = copy(tree->left);
      etNode * copia_derecha = copy(tree->right);
      etNode * mult = new etNode;
      etNode * mult2 = new etNode;
      tree->key = "+";
      derivar(tree->left, variable);
      derivar(tree->right, variable);
      mult->key = "*";
      mult->left = tree->left;
      mult->right = copia_derecha;
      tree->left = mult;
      mult2->key = "*";
      mult2->left = copia_izquierda;
      mult2->right = tree->right;
      tree->right = mult2;
    }

  } else if (tree->key == "/"){
    bool left_const = ((ver_alpha_str(tree->left->key) and tree->left->key != variable) or ver_dig_str(tree->left->key));
    bool right_const = ((ver_alpha_str(tree->right->key) and tree->right->key != variable) or ver_dig_str(tree->right->key));
    if (left_const and right_const) {
      tree->key = "0";
      clear(tree->right);
      clear(tree->left);
    } else if (right_const) {
      if (tree->left->key == variable){
        tree->left->key = "1";
      } else {
        derivar(tree->left, variable);
      }
    } else {
      etNode * potencia = new etNode;
      etNode * dos = new etNode;
      etNode * copia_derecha = copy(tree->right);
      etNode * copia_derecha2 = copy(tree->right);
      potencia->key = "^";
      potencia->left = tree->right;
      potencia->right = dos;
      dos->key = "2";
      dos->left = dos->right = nullptr;
      tree->right = potencia;
      etNode * copia_izquierda = copy(tree->left);
      etNode * resta = new etNode;
      etNode * mult = new etNode;
      etNode * mult2 = new etNode;
      derivar(tree->left, variable);
      derivar(copia_derecha2, variable);
      resta->key = "-";
      resta->left = mult;
      resta->right = mult2;
      mult->key = "*";
      mult->left = tree->left;
      mult->right = copia_derecha;
      mult2->key = "*";
      mult2->left = copia_izquierda;
      mult2->right = copia_derecha2;
      tree->left = resta;
    }
  } else if (tree->key == "^"){
    bool left_const = ((ver_alpha_str(tree->left->key) and tree->left->key != variable) or ver_dig_str(tree->left->key));
    bool right_const = ((ver_alpha_str(tree->right->key) and tree->right->key != variable) or ver_dig_str(tree->right->key));
    if (left_const and right_const) {
      tree->key = "0";
      clear(tree->right);
      clear(tree->left);
      return;
    } else if (right_const) {
      if (tree->left->key == variable){
        if (tree->right->key == "2"){
          tree->key="*";
        } else {
          etNode * potencia = new etNode;
          etNode * resta = new etNode;
          etNode * uno = new etNode;
          etNode * copia_derecha = copy(tree->right);
          tree->key = "*";
          potencia->key = "^";
          potencia->left = tree->left;
          potencia->right = resta;
          resta->key = "-";
          resta->left = tree->right;
          resta->right = uno;
          uno->key = "1";
          uno->left = uno->right = nullptr;
          tree->left = copia_derecha;
          tree->right = potencia;
        }
      } else {
        if (tree->right->key == "2"){
          tree->key = "*";
          etNode * aux = copy(tree->left);
          etNode * mult = new etNode;
          derivar(aux, variable);
          mult->key = "*";
          mult->left = tree->left;
          mult->right = aux;
          tree->left = tree->right;
          tree->right = mult;
        } else {
          etNode * potencia = new etNode;
          etNode * resta = new etNode;
          etNode * uno = new etNode;
          etNode * copia_derecha = copy(tree->right);
          etNode * mult = new etNode;
          etNode * der = copy(tree->left);
          tree->key = "*";
          potencia->key = "^";
          potencia->left = tree->left;
          potencia->right = resta;
          resta->key = "-";
          resta->left = tree->right;
          resta->right = uno;
          uno->key = "1";
          uno->left = uno->right = nullptr;
          mult->key = "*";
          mult->left = copia_derecha;
          mult->right = potencia;
          derivar(der, variable);
          tree->left = mult;
          tree->right = der;
        }
      }
    } else if (tree->left->key == "e") {
      etNode * potencia = new etNode;
      etNode * der = copy(tree->right);
      potencia->key = "^";
      potencia->left = tree->left;
      potencia->right = tree->right;
      derivar(der, variable);
      tree->key = "*";
      tree->left = der;
      tree->right = potencia;
    } else {
      std:: cout<< "Se necesita logaritmo, no se procesan logaritmos" << std::endl;
    	exit(1);
    }
  }
}

void et::derivar(std::string variable){
  derivar(tree,variable);
}

/**
Input: Nodo a simplificar
Busca nodos de operaciones cuyos ambos operandos sean constantes numericas y los une, a excepcion de la division o exponentes
*/
void et::simplificar(etNode *tree){
  if(tree->key == "+"){
    if (ver_dig_str(tree->left->key) and ver_dig_str(tree->right->key)){
      tree->key = std::to_string(stoi(tree->left->key)+ stoi(tree->right->key));
      clear(tree->left);
      clear(tree->right);
    }
  } else if (tree->key == "-"){
    if (ver_dig_str(tree->left->key) and ver_dig_str(tree->right->key)){
      tree->key = std::to_string(stoi(tree->left->key) - stoi(tree->right->key));
      clear(tree->left);
      clear(tree->right);
    }
  } else if(tree->key == "*") {
    if (ver_dig_str(tree->left->key) and ver_dig_str(tree->right->key)){
      tree->key = std::to_string(stoi(tree->left->key) * stoi(tree->right->key));
      clear(tree->right);
      clear(tree->left);
    } else if (tree->left->key == "1"){
      tree->key = tree->right->key;
      clear(tree->left);
      etNode *aux = tree->right;
      tree->left = tree->right->left;
      tree->right = tree->right->right;
      delete aux;
    } else if (tree->right->key == "1"){
      tree->key = tree->left->key;
      clear(tree->right);
      etNode *aux = tree->left;
      tree->right = tree->left->right;
      tree->left = tree->left->left;
      delete aux;
    } else if (tree->left->key == "0" or tree->right->key == "0"){
      tree->key = "0";
      clear(tree->left);
      clear(tree->right);
    }
  }
}

/**
Input: Nodo desde el cual se aplica simplificacion
Aplica la simplificacion recursiva a cada rama del arbol y finalmente usa funcion "simplificar" sobre el nodo para asegurar que si se necesitan reducciones adicionales, se hagan
Se separa de funcion simplificar para identificar funcionalidad con mayor facilidad
*/
void et::simplificar_rec(etNode *tree){
  if(tree != nullptr){
    simplificar_rec(tree->left);
    simplificar_rec(tree->right);
    simplificar(tree);
  }
}

void et::simplificar(){
  simplificar_rec(tree);
}
#endif

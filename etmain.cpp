#include<iostream>
#include<string>
#include "et.hpp"
#include "stack.hpp"
using namespace std;

string preorden(string s);

int main(){
  /**
  Strings de muestra;
    Se imprime string en terminal
    Se cambia notacion del string a preorden
    Se imprime string en terminal
    Se crea el arbol de expresion
    Se imprime arbol en terminal
  */
  //string  formula = "ab+dc/-";
  // string  formula = "(33+22)-(55/44)+a";
  // string formula = "x";
  // string formula = "x+22";
  // string formula = "a*22";
  // string formula = "22*x";
  // string formula = "x*22";
  // string formula = "a*(x+22)";
  // string formula = "(x+a)*22";
  // string formula = "(x+a)*(x-b)";
  // string formula = "22/b";
  // string formula = "x/a";
  // string formula = "a/x";
  // string formula = "(x+22)/x";
  // string formula = "22^b";
  // string formula = "x^2";
  // string formula = "x^a";
  // string formula = "(x+a)^22";
  // string formula = "(x+22)^a";
  // string formula = "e^(24*x)";
  string formula = "e^(24*(x^2))";
  cout << formula << endl;
  string pre = preorden(formula);
  cout << pre << endl;
  et form(pre);
  form.display();
  form.derivar();
  form.display();
  form.simplificar();
  form.display();
  return 0;
}

/**
Input: String de funcion en notacion infija
Cambia la notacion de infija a prefija
*/
string preorden(string s){
  Stack<char> aux;
  string output;
  for (unsigned i=0; i < s.size(); i++){
    if (isalpha(s[i])){
      output += s[i];
    } else if (isdigit(s[i])) {
      output += s[i];
      while(i+1<s.size() and isdigit(s[i+1])){
        i++;
        output += s[i];
      }
      output += '#';
    } else if (s[i] == '+' or s[i] == '-' or s[i] == '/' or s[i] == '*' or s[i]== '^'){
      if (!aux.empty()) if(aux.peek()!='(') output += aux.pop();
      aux.push(s[i]);
    } else if (s[i] == '('){
      aux.push(s[i]);
    } else if (s[i] == ')'){
      output+= aux.pop();
      aux.pop();
    }
  }
  while (!aux.empty()){
    output+=aux.pop();
  }
  return output;
}

#include "abb.h"
#include <string>
#include <iostream>
#include <list>
#include <math.h>


ABB::ABB () {
	raiz = NULL;
	tamanho = 0;
}

ABB::~ABB () {}

void ABB::inserir(int x) {
	Node* novo = new Node;
	
	novo->elemento = x;
	novo->altura = 1;;
	novo->num_fies = 0;
	novo->fiEs = NULL;
	novo->fiDi = NULL;

	if (inserir(raiz,novo) != 0){
		tamanho++;
	}
	
}



int ABB::inserir(Node* &aux, Node* x) {
	//se raiz é nula, é onde deve ser inserido	

	if (aux == NULL) {
		aux = x;
		return 1;
	}

	else {
		//se elemento inserido for igual a raiz, deve ser ignorado. 0 = falha na inserir
		if (x->elemento == aux->elemento) {
			x = NULL;
			return 0;
		}
		
		//se for elemento inserido for maior  
		if (x->elemento > aux->elemento) {
			if (inserir(aux->fiDi, x) != 0) {
				Node* x = aux->fiDi;
				Node* y = aux->fiEs;
				int a,b;

				if (x == NULL) 
					a = 0;
					else 
						a = x->altura;

				if (y == NULL) 
					b = 0;
					else 
						b = y->altura;
				

				if (a >= b)
					aux->altura = a + 1;					
					else 
						aux->altura = b + 1;
			}

			else {
				return 0;
			}			
		}

		else if (x->elemento < aux->elemento) {
			if (inserir(aux->fiEs, x) != 0) {
				Node* x = aux->fiDi;
				Node* y = aux->fiEs;
				int a,b;

				if (x == NULL) 
					a = 0;
					else 
						a = x->altura;

				if (y == NULL) 
					b = 0;
					else 
						b = y->altura;
				

				if (a >= b)
					aux->altura = a + 1;					
					else 
						aux->altura = b + 1;
			}

			else {
				return 0;
			}		

				aux->num_fies++;
		}
		
	}

	return 1;
}


int ABB::busca(Node* &pt, Node* &raiz, int x) {	
	if (raiz == NULL) {
		return 0;
	}

	else {
		if (x == raiz->elemento) {
			pt = raiz;
			return 1;
		}

		else 
			if (x > raiz->elemento) {
				if (raiz->fiDi == NULL) {
					pt = raiz;
					return 3;
				}
				else {
					return busca(pt, raiz->fiDi, x);
				}
			}

		else
			if (x < raiz->elemento) {
				if (raiz->fiEs == NULL) {
					pt = raiz;
					return 2;
				}
				else {
					return busca(pt, raiz->fiEs, x);
				}
			}
	}
}


void ABB::remocao(int x) {
	Node* prev = nullptr;
	Node* aux = raiz;
	Node* aux2 = nullptr;
	Node* aux3 = nullptr;

	while (aux != NULL) {

		if(x > aux->elemento) {
			prev = aux;
			aux = aux->fiDi;
		}

		else if(x < aux->elemento) {
			prev = aux;
			aux = aux->fiEs;
		}


		else if(aux->elemento == x) {
			if (aux->fiEs == NULL && aux->fiDi == NULL) {				
				if (prev == nullptr) {
					raiz = NULL;
					aux = NULL;
				}
				else if (aux->elemento > prev->elemento) {
					prev->fiDi = NULL;
					aux = NULL;
				}
				else if (aux->elemento < prev->elemento) {
					prev->fiEs = NULL;
					prev->num_fies--;
					aux = NULL;
				}

				if (prev != nullptr)
					prev->altura = 1;
			}

			else if (aux->fiEs == NULL && aux->fiDi != NULL) {
				if (prev == nullptr) {
					raiz = aux->fiDi;
					aux = NULL;
				}
				else if (aux->elemento > prev->elemento) {
					prev->fiDi = aux->fiDi;
					aux = NULL;
				}
				else if (aux->elemento < prev->elemento) {
					prev->fiEs = aux->fiDi;
					prev->num_fies--;
					aux = NULL;
				}

				if (prev->fiDi != nullptr && prev->fiEs != nullptr) {
					if (prev->fiDi->altura >= prev->fiEs->altura) {
						prev->altura = prev->fiDi->altura + 1;
					}
					else {
						prev->altura = prev->fiEs->altura + 1;
					}
				}

				else if (prev->fiDi == nullptr) {
					prev->altura = prev->fiEs->altura + 1;
				}

				else if (prev->fiEs == nullptr) {
					prev->altura = prev->fiDi->altura + 1;
				}

			}

			else if (aux->fiEs != NULL && aux->fiDi == NULL) {
				if (prev == nullptr) {
					raiz = aux->fiEs;
					aux = NULL;
				}
				else if (aux->elemento > prev->elemento) {
					prev->fiDi = aux->fiEs;
					aux = NULL;
				}
				else if (aux->elemento < prev->elemento) {
					prev->fiEs = aux->fiEs;
					prev->num_fies--;
					aux = NULL;
				}

				if (prev->fiDi != nullptr && prev->fiEs != nullptr) {
					if (prev->fiDi->altura >= prev->fiEs->altura) {
						prev->altura = prev->fiDi->altura + 1;
					}
					else {
						prev->altura = prev->fiEs->altura + 1;
					}
				}

				else if (prev->fiDi == nullptr) {
					prev->altura = prev->fiEs->altura + 1;
				}

				else if (prev->fiEs == nullptr) {
					prev->altura = prev->fiDi->altura + 1;
				}
			}

			else if (aux->fiEs != NULL && aux->fiDi != NULL) {
				aux2 = aux->fiEs;
				aux3 = aux;
				while (aux2->fiDi != NULL) {
					aux3 = aux2;
					aux2 = aux2->fiDi;
				}
				
				aux3->fiDi = nullptr;
				aux3->altura--;
				aux2->fiDi = aux->fiDi;
				aux2->fiEs = aux->fiEs;
				aux2->num_fies = aux->num_fies - 1;

				if (aux->fiDi->altura >= aux->fiEs->altura) {
					aux2->altura = aux->fiDi->altura + 1;
				}
				else {
					aux2->altura = aux->fiEs->altura + 1;
				}

				if (prev == nullptr) {
					raiz = aux2;
					aux = NULL;
				}
				else if (aux->elemento > prev->elemento) {
					prev->fiDi = aux->fiEs;
					aux = NULL;
				}
				else if (aux->elemento < prev->elemento) {
					prev->fiEs = aux->fiEs;
					prev->num_fies--;
					aux = NULL;
				}		

			}
			tamanho--;
		}

	}
}



std::string ABB::toString() {
	std::list <Node*> l_aux;
	std::string arvore;
    
    if (raiz != NULL) {
   		l_aux.push_back(raiz);
    }

	while(!l_aux.empty()) {

		Node* x = l_aux.front();
		if(x->fiEs != NULL) {
			l_aux.push_back(x->fiEs);
		}

		if(x->fiDi != NULL) {
			l_aux.push_back(x->fiDi);
		}



		//std::cout << "El: " << x->elemento << " Alt: " << x->altura << " NumEsq: " << x->num_fies << std::endl;


		std::string s = std::to_string(x->elemento) + "_";
		arvore += s;
		l_aux.pop_front();
	}
	return arvore;
}

int ABB::enesimoElemento(int n) {
	Node* aux = raiz;
	int x;

	while (aux != nullptr) {
		x = aux->num_fies;

		//std::cout << n << ".." << x << std::endl;

		if (n <= x) {
			aux = aux->fiEs;
		}

		else if (n == x+1) {
			return aux->elemento;
		}

		else if(n > x+1) {
			n = n - x - 1;
			aux = aux->fiDi;
			
		}
	}
}

int ABB::posicao(int n) {
	Node* aux = raiz;
	int i = aux->num_fies + 1;

	while (aux != nullptr) {
		if (n == aux->elemento) {
			return i; 
		}

		else if (n > aux->elemento) {
			aux = aux->fiDi;
			if (aux != nullptr)
				i = i + aux->num_fies + 1;
		}

		else if (n < aux->elemento) {
			i = i - (aux->num_fies + 1);
			aux = aux->fiEs;
			if (aux != nullptr)	
				i = i + aux->num_fies + 1;
		}
	}
}

bool ABB::ehCheia() {
	if (raiz != nullptr) {
		if (tamanho == pow(2, raiz->altura) - 1) {
			return true;
		}
	}

	else 
		return false;
}

int ABB::mediana() {
	if (tamanho%2 == 1) {
		return enesimoElemento((tamanho + 1)/2);
	}

	else 
		return enesimoElemento(tamanho/2);

}

bool ABB::ehCompleta(Node* &aux) {
	if (aux->fiEs == nullptr && aux->fiDi != nullptr) {
		if (aux->altura > 2) {
			return false;
		}

		else 
			return ehCompleta(aux->fiDi);
		
	}

	else if (aux->fiEs != nullptr && aux->fiDi == nullptr) {
		if (aux->altura > 2) {
			return false;
		}

		else 
			return ehCompleta(aux->fiEs);
	}

	else if (aux->fiEs == nullptr && aux->fiDi == nullptr) {
		return true;
	}

	else if (aux->fiEs != nullptr && aux->fiDi != nullptr) {
		if (abs(aux->fiEs->altura - aux->fiDi->altura) > 1) {
			return false;
		}

		else {
			if (ehCompleta(aux->fiEs) == false || ehCompleta(aux->fiDi) == false) {
				return false;
			}
			else 
				return true;
		}
	}
}

bool ABB::ehCompleta() {
	if (ehCheia()) {
		return true;
	}

	else {
		return ehCompleta(raiz);
	}
}
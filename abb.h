#ifndef _ABB_H_
#define _ABB_H_

#include <string>

class ABB {
	protected:  
		struct Node
		{
			Node* fiEs;
			Node* fiDi;
			int altura;
			int num_fies;
			int elemento;
		};

		int tamanho;
		int num_folhas;
		Node* raiz;
		int inserir(Node* &aux1, Node* x);
		bool ehCompleta(Node* &aux);

	public:
		ABB();
		~ABB();
		//funcoes basicas
			void inserir(int x);
			int busca(Node* &pt, Node* &raiz, int x);
			void remocao(int x);
		
		//funcoes requisitadas
			int enesimoElemento(int n);
			int posicao(int n);
			bool ehCheia();
			int mediana();
			bool ehCompleta();		
			std::string toString();

};

#endif

#include <iostream>
#include "abb.h"
#include <string>
#include <fstream>




void iniciarABB(std::string c, ABB &arv){
    int x;

    std::string aux;
    while (!c.empty()){
        if(c.front() == ' ') {
        	x = std::stoi (aux, nullptr, 10);
        	aux.clear();
        	arv.inserir(x);
        	c.erase(0,1);
        }
        else{
            aux = aux + c.front();
            c.erase(0,1);
        }
    }

    if (!aux.empty()) {
    	x = std::stoi (aux, nullptr, 10);
        aux.clear();
        arv.inserir(x);
    }
}


void ler_comando(std::string c, ABB &arv) {
	std::string aux;
	int x;
	while (!c.empty()){
		if(c.front() == ' ') {
        	c.erase(0,1);
        	break;
        }
        else{
            aux = aux + c.front();
            c.erase(0,1);
        }
    }

    if (!c.empty()) {
    	x = std::stoi (c, nullptr, 10);
    }

    if (aux == "ENESIMO") {
    	std::cout << "O elemento na " << x << "ª posicao eh o: " << arv.enesimoElemento(x) << std::endl;
    }

    else if (aux == "POSICAO") {
    	std::cout << "O elemento " << x << " esta na " << arv.posicao(x) << "ª posicao" << std::endl;
    }


    else if (aux == "MEDIANA") {
    	std::cout << "A mediana da ABB eh o elemento: " << arv.mediana() << std::endl;
    }

    else if (aux == "CHEIA") {
    	if (arv.ehCheia()) {
    		std::cout << "A ABB eh cheia!" << std::endl;
    	}
    	
    	else
    		std::cout << "A ABB Nao eh cheia! " << std::endl;
    }

    else if (aux == "COMPLETA") {
    	if (arv.ehCompleta()) {
			std::cout << "A ABB eh completa!" << std::endl;
    	}

    	else 
    		std::cout << "A ABB nao eh completa!" << std::endl;
    }

    else if (aux == "IMPRIMA") {
    	std::cout << "Imprimindo ABB por nivel: " << arv.toString() << std::endl;
    }

    else if (aux == "REMOVA") {
    	std::cout << "Removendo o elemento: " << x << " ..." << std::endl;
    	arv.remocao(x);
    }

}

int main () {

	ABB arv;

    std::string line;

    std::ifstream myfile ("arquivo_de_entrada_ABB.txt");

    //inserindo os elementos da arvore

    //system("clear");


    if (myfile.is_open()) {
        while (getline (myfile,line)) {
            iniciarABB(line, arv);
        }

        myfile.close();
    }

    else 
    	std::cout << "Unable to open file" << std::endl;

     /*
     std::cout << arv.toString() << std::endl;
     if (arv.ehCheia()) {
     	 std::cout << "eh cheia" << std::endl;
     }
     */


    //entrada de comandos pelo arquivo
    myfile.open("arquivo_de_comando.txt");

    if (myfile.is_open())
    {
        while (getline (myfile,line))
        {
            ler_comando(line, arv);
        }

        myfile.close();
    }
    else
		std::cout << "Unable to open file" << std::endl;
     

    return 0;
}

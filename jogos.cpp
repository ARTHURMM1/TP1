#include "Jogos.hpp"

char JogosDeTabuleiro::get_casa(int linha, int coluna) const{
    if ((linha <= this->getLinhas()) && (coluna <= this->getColunas()))
    {
        return Tabuleiro[linha][coluna];
    }
}

int JogosDeTabuleiro::imprimir_vetor() const {
    for (int i = 0; i < this->getLinhas(); i++)
    {
        std::cout << "|"; 
        for (int j = 0; j < this->getColunas(); j++)
        {

        }
    }
}

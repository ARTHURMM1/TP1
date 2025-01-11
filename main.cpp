#include "jogos.hpp"

int main()
{
    std::cout << VERDE;
    std::cout << VERDE;
    std::cout << VERDE;
    Reversi* tabelao = new Reversi();
    tabelao->imprimir_vetor();
    tabelao->setLinhasColunas(5,5);
    tabelao->imprimir_vetor();
}
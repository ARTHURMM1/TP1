#include "Jogos.hpp"


JogosDeTabuleiro::JogosDeTabuleiro(int linhas, int colunas) : linhas_(linhas), colunas_(colunas){
        //Caso o vetor seja inicializado com sem parametros, entao ele sera iniciado com tamanho zero
        //Caso ele for aumentado, essas novas "casas" serao prenchidas com ' '.
    Tabuleiro_.resize(linhas, std::vector<int>(colunas, 0));
}

int JogosDeTabuleiro::getLinhas() const { return this->linhas_; };
int JogosDeTabuleiro::getColunas() const { return colunas_; };
std::vector<std::vector<int>> JogosDeTabuleiro::get_tabuleiro() const { return Tabuleiro_; };
char JogosDeTabuleiro::get_casa(int linha, int coluna) const{
    if ((linha <= linhas_) && (coluna <= colunas_))
    {
        return Tabuleiro[linha][coluna];
    }
    return 'F';
}

void JogosDeTabuleiro::setLinhasColunas(int linha, int coluna) { linhas_ = linha; colunas_ = coluna; };

int JogosDeTabuleiro::imprimir_vetor() const {
    int casa;
    for (int i = 0; i < this->getLinhas(); i++)
    {
        std::cout << FUNDO_VERDE << "|" << RESETAR; 
        for (int j = 0; j < this->getColunas(); j++)
        {
            casa = this->get_casa(i, j);
            if(casa == 0)
            {
                std::cout << FUNDO_VERDE << " " << RESETAR;
            }
            else if (casa == 1)
            {
                std::cout << "X";
            }
            else
            {
                std::cout << FUNDO_BRANCO << "O" << RESETAR;
            }
            std::cout << FUNDO_VERDE << "|" << RESETAR;
        }
        std::cout << std::endl;
    }
    return 0;
}


Reversi::Reversi(int linhas, int colunas) : JogosDeTabuleiro(linhas, colunas) {
    JogadasValidas_.resize(linhas, std::vector<bool>(colunas, false));
}

    
std::vector<std::vector<bool>> Reversi::atualizar_jogadas_validas(int jogador) const {
    int preta, branca;
    std::vector<std::vector<int>> Tabuleiro = this->get_tabuleiro();
    std::vector<std::vector<bool>> JogadasValidas = JogadasValidas_;
    if (jogador == 1) {
        preta = 1;
        branca = 2;
    }
    else{
        preta = 2;
        branca = 1;
    }
    //verificar casas invalidas por nao terem a cor oposta em volta.
    for (int i = 0; i < getLinhas()

    
}
int Reversi::ler_jogada(int linha, int coluna, int jogador) {

}
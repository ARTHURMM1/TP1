#ifndef jogos_hpp
#define Jogos_hpp
#include <iostream>
#include <vector>
#include "cores.hpp"

class JogosDeTabuleiro{
    public:
        JogosDeTabuleiro(int linhas = 0, int colunas = 0);
        //virtual ~JogosDeTabuleiro();
        int getLinhas() const;
        int getColunas() const;
        std::vector<std::vector<int>> get_tabuleiro() const;
        char get_casa(int linha, int coluna) const;
        void setLinhasColunas(int linha, int coluna);
        int imprimir_vetor() const;
        

        /*virtual int ler_jogada(int linha, int coluna) = 0;
        virtual bool verificar_jogada(int linha, int coluna) const = 0;
        virtual bool testar_condicao_de_vitoria() const = 0;*/
    
    private:
        int linhas_, colunas_;
        std::vector<std::vector<int>> Tabuleiro_;
};

class Reversi : public JogosDeTabuleiro{
    public:
        //Quando nao passar nem um parametro o tamanho do board sera padrao para reversi (8x8)
        Reversi(int linhas = 8, int colunas = 8);
        int ler_jogada(int linha, int coluna, int jogador) override;
        //bool verificar_jogada(int linha, int coluna, int jogador) override;
        std::vector<std::vector<bool>> atualizar_jogadas_validas(int jogador) const;
        //bool testar_condicao_de_vitoria() const override;
    private:
        std::vector<std::vector<bool>> JogadasValidas_;
};

/*class Lig4 : public JogosDeTabuleiro{
    public:
        Lig4(int linhas = 6, int colunas = 7);
        int ler_jogada(int linha, int coluna) override;
        bool verificar_jogada(int linha, int coluna) const override;
        bool testar_condicao_de_vitoria() const override;
    private:
};

class JogoDaVelha : public JogosDeTabuleiro{
    public:
        JogoDaVelha(int linhas = 3, int colunas = 3);
        int ler_jogada(int linha, int coluna) override;
        bool verificar_jogada(int linha, int coluna) const override;
        bool testar_condicao_de_vitoria() const override;
        private:
};
*/
#endif

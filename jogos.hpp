#ifndef jogos_hpp
#define Jogos_hpp
#include <iostream>
#include <vector>

class JogosDeTabuleiro{
    public:
        JogosDeTabuleiro(int linhas = 0, int colunas = 0) : _linhas(linhas), _colunas(colunas){
            //Caso o vetor seja inicializado com sem parametros, entao ele sera iniciado com tamanho zero
            //Caso ele for aumentado, essas novas "casas" serao prenchidas com ' '.
            Tabuleiro.resize(linhas, std::vector<char>(colunas, ' '));
        }

        virtual ~JogosDeTabuleiro() = default;
        int getLinhas() const { return _linhas; };
        int getColunas() const { return _colunas; };
        char get_casa(int linha, int coluna) const;
        int setLinhasColunas(int linhas, int colunas) { _linhas = linhas; _colunas = colunas; }
        int imprimir_vetor() const;
        virtual int ler_jogada(int linha, int coluna) = 0;
        virtual bool verificar_jogada(int linha, int coluna) const = 0;
        virtual bool testar_condicao_de_vitoria() const = 0;
    private:
        int _linhas, _colunas;
        std::vector<std::vector<char>> Tabuleiro;
};

class Reversi : public JogosDeTabuleiro{
    public:
    //Quando nao passar nem um parametro o tamanho do board sera padrao para reversi (8x8)
    Reversi(int linhas = 8, int colunas = 8) : JogosDeTabuleiro(linhas, colunas){}
    int ler_jogada(int linha, int coluna) override;
    bool verificar_jogada(int linha, int coluna) const override;
    bool testar_condicao_de_vitoria() const override;
    private:
};

class Lig4 : public JogosDeTabuleiro{
    public:
    Lig4(int linhas = 6, int colunas = 7) : JogosDeTabuleiro(linhas, colunas){}
    int ler_jogada(int linha, int coluna) override;
    bool verificar_jogada(int linha, int coluna) const override;
    bool testar_condicao_de_vitoria() const override;
    private:
};

class JogoDaVelha : public JogosDeTabuleiro{
    public:
    JogoDaVelha(int linhas = 3, int colunas = 3) : JogosDeTabuleiro(linhas, colunas){}
    int ler_jogada(int linha, int coluna) override;
    bool verificar_jogada(int linha, int coluna) const override;
    bool testar_condicao_de_vitoria() const override;
    private:
};
#endif

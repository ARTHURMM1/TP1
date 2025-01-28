#ifndef BOTPLAYER_HPP
#define BOTPLAYER_HPP
#include <vector>
#include <utility>
#include "jogos.hpp"

// Classe base abstrata para representar bots em jogos de tabuleiro
class BotPlayer {
public:
    virtual ~BotPlayer() = default;

    // Método abstrato para calcular a próxima jogada do bot
    virtual std::pair<int, int> calcularProximaJogada(
        const JogosDeTabuleiro& jogo, 
        int jogadorAtual
    ) = 0;

protected:
    BotPlayer() = default;
    BotPlayer(const BotPlayer&) = delete;
    BotPlayer& operator=(const BotPlayer&) = delete;
};

// Classe para implementar o bot do jogo Reversi
class ReversiBot : public BotPlayer {
public:
    std::pair<int, int> calcularProximaJogada(
        const JogosDeTabuleiro& jogo, 
        int jogadorAtual
    ) override;

private:
    int _minimax(Reversi& jogo, int profundidade, bool maximizando, int jogadorAtual);
    int _avaliarTabuleiro(const Reversi& jogo, int jogadorAtual);
};

// Classe para implementar o bot do jogo Lig 4
class Lig4Bot : public BotPlayer {
public:
    std::pair<int, int> calcularProximaJogada(
        const JogosDeTabuleiro& jogoBase, 
        int jogadorAtual
    ) override;

private:
    int _minimax(Lig4& jogo, bool maximizando, int jogadorAtual);
};

// Classe para implementar o bot do jogo da velha
class JogoDaVelhaBot : public BotPlayer {
public:
    std::pair<int, int> calcularProximaJogada(
        const JogosDeTabuleiro& jogoBase, 
        int jogadorAtual
    ) override;

private:
    void minimax(const JogoDaVelha& jogo, int& melhorLinha, int& melhorColuna, int jogador);
    int _minimax(JogoDaVelha& jogo, int profundidade, bool maximizando, int jogador);
};

#endif

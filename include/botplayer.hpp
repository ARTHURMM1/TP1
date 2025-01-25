#ifndef BOTPLAYER_HPP
#define BOTPLAYER_HPP
#include <vector>
#include <utility>

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
    // Proibindo cópia e atribuição acidental
    BotPlayer() = default;
    BotPlayer(const BotPlayer&) = delete;
    BotPlayer& operator=(const BotPlayer&) = delete;
};

// Classe para implementar o bot do jogo Reversi
class ReversiBot : public BotPlayer {
public:
    // Sobrescreve o método da classe base
    std::pair<int, int> calcularProximaJogada(
        const JogosDeTabuleiro& jogo, 
        int jogadorAtual
    ) override;
};

// Classe para implementar o bot do jogo Lig 4
class Lig4Bot : public BotPlayer {
public:
    // Sobrescreve o método da classe base
    std::pair<int, int> calcularProximaJogada(
        const JogosDeTabuleiro& jogo, 
        int jogadorAtual
    ) override;
};

// Classe para implementar o bot do jogo da velha
class JogoDaVelhaBot : public BotPlayer {
public:
    // Sobrescreve o método da classe base
    std::pair<int, int> calcularProximaJogada(
        const JogosDeTabuleiro& jogo, 
        int jogadorAtual
    ) override;
};

#endif 

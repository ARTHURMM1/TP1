#include "botplayer.hpp"
#include "jogos.hpp"

//JOGO DA VELHA
class BotPlayer {
public:
    void minimax(const JogoDaVelha& jogo, int& melhorLinha, int& melhorColuna, int jogador);

private:
    int _minimax(JogoDaVelha& jogo, int profundidade, bool maximizando, int jogador);
};

void BotPlayer::minimax(const JogoDaVelha& jogo, int& melhorLinha, int& melhorColuna, int jogador) {
    int melhorPontuacao = INT_MIN;
    
    for (int i = 0; i < jogo.getLinhas(); i++) {
        for (int j = 0; j < jogo.getColunas(); j++) {
            if (jogo.get_casa(i, j) == 0) { // Se a casa está vazia
                JogoDaVelha copia = jogo;
                copia.ler_jogada(i, j, jogador);

                int pontuacao = _minimax(copia, 0, false, jogador);
                if (pontuacao > melhorPontuacao) {
                    melhorPontuacao = pontuacao;
                    melhorLinha = i;
                    melhorColuna = j;
                }
            }
        }
    }
}

int BotPlayer::_minimax(JogoDaVelha& jogo, int profundidade, bool maximizando, int jogador) {
    if (jogo.testar_condicao_de_vitoria()) {
        return maximizando ? -1 : 1; // Vitória do oponente ou do bot
    }
    
    // Verifica empate
    bool temEspacosVazios = false;
    for (int i = 0; i < jogo.getLinhas(); i++) {
        for (int j = 0; j < jogo.getColunas(); j++) {
            if (jogo.get_casa(i, j) == 0) {
                temEspacosVazios = true;
                break;
            }
        }
    }
    if (!temEspacosVazios) return 0; // Empate

    int melhorPontuacao = maximizando ? INT_MIN : INT_MAX;
    int outroJogador = (jogador == 1) ? 2 : 1;

    for (int i = 0; i < jogo.getLinhas(); i++) {
        for (int j = 0; j < jogo.getColunas(); j++) {
            if (jogo.get_casa(i, j) == 0) { // Se a casa está vazia
                JogoDaVelha copia = jogo;
                copia.ler_jogada(i, j, maximizando ? jogador : outroJogador);

                int pontuacao = _minimax(copia, profundidade + 1, !maximizando, jogador);
                if (maximizando) {
                    melhorPontuacao = std::max(melhorPontuacao, pontuacao);
                } else {
                    melhorPontuacao = std::min(melhorPontuacao, pontuacao);
                }
            }
        }
    }
    return melhorPontuacao;
}

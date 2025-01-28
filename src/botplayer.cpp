#include "botplayer.hpp"
#include <climits>
#include <algorithm>

// --- Implementação do Jogo da Velha Bot ---

void JogoDaVelhaBot::minimax(const JogoDaVelha& jogo, int& melhorLinha, int& melhorColuna, int jogador) {
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

int JogoDaVelhaBot::_minimax(JogoDaVelha& jogo, int profundidade, bool maximizando, int jogador) {
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

std::pair<int, int> JogoDaVelhaBot::calcularProximaJogada(const JogosDeTabuleiro& jogoBase, int jogadorAtual) {
    const JogoDaVelha& jogo = static_cast<const JogoDaVelha&>(jogoBase); 
    int melhorLinha = -1, melhorColuna = -1;
    minimax(jogo, melhorLinha, melhorColuna, jogadorAtual);
    return {melhorLinha, melhorColuna};
}

// --- Implementação do Lig 4 Bot ---

std::pair<int, int> Lig4Bot::calcularProximaJogada(const JogosDeTabuleiro& jogoBase, int jogadorAtual) {
    const Lig4& jogo = static_cast<const Lig4&>(jogoBase); 
    int melhorColuna = -1;
    int melhorPontuacao = INT_MIN;

    for (int coluna = 0; coluna < jogo.getColunas(); ++coluna) {
        if (jogo.verificar_jogada(0, coluna, 0)) {
            Lig4 copia = jogo;
            copia.ler_jogada(0, coluna, jogadorAtual);

            int pontuacao = _minimax(copia, false, jogadorAtual);

            if (pontuacao > melhorPontuacao) {
                melhorPontuacao = pontuacao;
                melhorColuna = coluna;
            }
        }
    }

    return {melhorColuna, -1};
}

int Lig4Bot::_minimax(Lig4& jogo, bool maximizando, int jogadorAtual) {
    if (jogo.testar_condicao_de_vitoria()) {
        return maximizando ? -100 : 100;
    }

    bool movimentosPossiveis = false;
    for (int coluna = 0; coluna < jogo.getColunas(); ++coluna) {
        if (jogo.verificar_jogada(0, coluna, 0)) {
            movimentosPossiveis = true;
            break;
        }
    }
    if (!movimentosPossiveis) return 0; // Empate

    int outroJogador = (jogadorAtual == 1) ? 2 : 1;
    int melhorPontuacao = maximizando ? INT_MIN : INT_MAX;

    for (int coluna = 0; coluna < jogo.getColunas(); ++coluna) {
        if (jogo.verificar_jogada(0, coluna, 0)) {
            Lig4 copia = jogo;
            copia.ler_jogada(0, coluna, maximizando ? jogadorAtual : outroJogador);

            int pontuacao = _minimax(copia, !maximizando, jogadorAtual);

            if (maximizando) {
                melhorPontuacao = std::max(melhorPontuacao, pontuacao);
            } else {
                melhorPontuacao = std::min(melhorPontuacao, pontuacao);
            }
        }
    }

    return melhorPontuacao;
}

// --- Implementação Atualizada do Reversi Bot ---

int ReversiBot::_minimax(Reversi& jogo, int profundidade, bool maximizando, int jogadorAtual) {
    if (jogo.testar_condicao_de_vitoria() || profundidade >= 4) { 
        return _avaliarTabuleiro(jogo, jogadorAtual);
    }

    int melhorPontuacao = maximizando ? INT_MIN : INT_MAX;
    int jogador = maximizando ? jogadorAtual : (jogadorAtual == 1 ? 2 : 1);

    // Iterar sobre todas as jogadas válidas
    for (int linha = 0; linha < jogo.getLinhas(); linha++) {
        for (int coluna = 0; coluna < jogo.getColunas(); coluna++) {
            if (jogo.verificar_jogada(linha, coluna, jogador)) {
                jogo.ler_jogada(linha, coluna, jogador);

                // Chamada recursiva para Minimax
                int pontuacao = _minimax(jogo, profundidade + 1, !maximizando, jogadorAtual);

                // jogo.desfazer_jogada(linha, coluna);

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

// Método para avaliar o tabuleiro
int ReversiBot::_avaliarTabuleiro(const Reversi& jogo, int jogadorAtual) {
    int oponente = (jogadorAtual == 1) ? 2 : 1;
    int pontuacao = 0;

    int mobilidadeJogador = 0;
    int mobilidadeOponente = 0;

    for (int linha = 0; linha < jogo.getLinhas(); linha++) {
        for (int coluna = 0; coluna < jogo.getColunas(); coluna++) {
            if (jogo.verificar_jogada(linha, coluna, jogadorAtual)) mobilidadeJogador++;
            if (jogo.verificar_jogada(linha, coluna, oponente)) mobilidadeOponente++;
        }
    }
    pontuacao += (mobilidadeJogador - mobilidadeOponente) * 2;

    // Controle de cantos e bordas
    for (int linha = 0; linha < jogo.getLinhas(); linha++) {
        for (int coluna = 0; coluna < jogo.getColunas(); coluna++) {
            int casa = jogo.get_casa(linha, coluna);
            if (casa == jogadorAtual) {
                if ((linha == 0 || linha == jogo.getLinhas() - 1) &&
                    (coluna == 0 || coluna == jogo.getColunas() - 1)) {
                    pontuacao += 20; // Cantos valem mais
                } else if (linha == 0 || linha == jogo.getLinhas() - 1 ||
                           coluna == 0 || coluna == jogo.getColunas() - 1) {
                    pontuacao += 5; // Bordas valem menos que cantos
                } else {
                    pontuacao += 1; // Centros têm valor padrão
                }
            } else if (casa == oponente) {
                if ((linha == 0 || linha == jogo.getLinhas() - 1) &&
                    (coluna == 0 || coluna == jogo.getColunas() - 1)) {
                    pontuacao -= 20; // Penaliza cantos ocupados pelo oponente
                } else if (linha == 0 || linha == jogo.getLinhas() - 1 ||
                           coluna == 0 || coluna == jogo.getColunas() - 1) {
                    pontuacao -= 5; // Penaliza bordas ocupadas pelo oponente
                } else {
                    pontuacao -= 1; // Penaliza centros ocupados pelo oponente
                }
            }
        }
    }

    return pontuacao;
}

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

//JOGO LIG 4
std::pair<int, int> Lig4Bot::calcularProximaJogada(const JogosDeTabuleiro& jogoBase, int jogadorAtual) {
    Lig4 jogo = static_cast<const Lig4&>(jogoBase); 
    int melhorColuna = -1;
    int melhorPontuacao = INT_MIN;

    // Itera pelas colunas disponíveis
    for (int coluna = 0; coluna < jogo.getColunas(); ++coluna) {
        if (jogo.verificar_jogada(coluna)) {
            Lig4 copia = jogo;
            copia.ler_jogadas(coluna, jogadorAtual);
            
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

    // Verifica empate
    bool movimentosPossiveis = false;
    for (int coluna = 0; coluna < jogo.getColunas(); ++coluna) {
        if (jogo.verificar_jogada(coluna)) {
            movimentosPossiveis = true;
            break;
        }
    }
    if (!movimentosPossiveis) return 0; // Empate

    int outroJogador = (jogadorAtual == 1) ? 2 : 1;
    int melhorPontuacao = maximizando ? INT_MIN : INT_MAX;

    for (int coluna = 0; coluna < jogo.getColunas(); ++coluna) {
        if (jogo.verificar_jogada(coluna)) {
            Lig4 copia = jogo;
            copia.ler_jogadas(coluna, maximizando ? jogadorAtual : outroJogador);

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

//REVERSI
std::pair<int, int> ReversiBot::calcularProximaJogada(const JogosDeTabuleiro& jogoBase, int jogadorAtual) {
    Reversi jogo = static_cast<const Reversi&>(jogoBase); // Converte para Reversi
    int melhorPontuacao = INT_MIN;
    int melhorLinha = -1, melhorColuna = -1;

    // Percorre todas as casas possíveis
    for (int linha = 0; linha < jogo.getLinhas(); linha++) {
        for (int coluna = 0; coluna < jogo.getColunas(); coluna++) {
            if (jogo.verificar_jogada(linha, coluna, jogadorAtual)) {
                // Simula a jogada
                Reversi copia = jogo;
                copia.ler_jogada(linha, coluna, jogadorAtual);

                // Avalia a jogada usando Minimax
                int pontuacao = _minimax(copia, 0, false, jogadorAtual);

                if (pontuacao > melhorPontuacao) {
                    melhorPontuacao = pontuacao;
                    melhorLinha = linha;
                    melhorColuna = coluna;
                }
            }
        }
    }

    return {melhorLinha, melhorColuna};
}

int ReversiBot::_minimax(Reversi& jogo, int profundidade, bool maximizando, int jogadorAtual) {
    // Verifica condição de vitória ou profundidade máxima
    if (jogo.testar_condicao_de_vitoria() || profundidade == 5) {
        return _avaliarTabuleiro(jogo, jogadorAtual);
    }

    int melhorPontuacao = maximizando ? INT_MIN : INT_MAX;
    int outroJogador = (jogadorAtual == 1) ? 2 : 1;

    for (int linha = 0; linha < jogo.getLinhas(); linha++) {
        for (int coluna = 0; coluna < jogo.getColunas(); coluna++) {
            if (jogo.verificar_jogada(linha, coluna, maximizando ? jogadorAtual : outroJogador)) {
                Reversi copia = jogo;
                copia.ler_jogada(linha, coluna, maximizando ? jogadorAtual : outroJogador);

                int pontuacao = _minimax(copia, profundidade + 1, !maximizando, jogadorAtual);

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

int ReversiBot::_avaliarTabuleiro(const Reversi& jogo, int jogadorAtual) {
    int oponente = (jogadorAtual == 1) ? 2 : 1;
    int pontuacao = 0;

    // Heurística: valoriza bordas e cantos
    for (int linha = 0; linha < jogo.getLinhas(); linha++) {
        for (int coluna = 0; coluna < jogo.getColunas(); coluna++) {
            int casa = jogo.get_casa(linha, coluna);
            if (casa == jogadorAtual) {
                pontuacao += (linha == 0 || linha == jogo.getLinhas() - 1 || coluna == 0 || coluna == jogo.getColunas() - 1) ? 3 : 1;
            } else if (casa == oponente) {
                pontuacao -= (linha == 0 || linha == jogo.getLinhas() - 1 || coluna == 0 || coluna == jogo.getColunas() - 1) ? 3 : 1;
            }
        }
    }

    return pontuacao;
}

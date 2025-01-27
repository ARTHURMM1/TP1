#include <iostream>
#include <stdlib.h>
#include <string>
#include "cadastro.hpp"
#include "jogos.hpp"
#include "partida.hpp"
#include <algorithm>

int main () {
    // Inicializa o vetor de cadastro, carregando as informações do .txt
    Cadastro jogadores;
    jogadores.import("cadastro.txt");
    
    // Inicializa a partida
    Partida partida;

    // Vetor de comandos
    std::vector<std::string> commands = {
        "CJ",    // 0: Cadastrar Jogador
        "RJ",    // 1: Remover Jogador
        "LJ",    // 2: Listar Jogadores
        "EP",    // 3: Executar Partida
        "FS"     // 4: Finalizar Sistema
    };

    while (true) {
        std::string inputComando;
        std::cin >> inputComando;

        // Procura o índice do comando
        auto it = std::find(commands.begin(), commands.end(), inputComando);
        
        if (it == commands.end()) {
            std::cout << "comando inválido" << std::endl;
            continue;
        }

        int indexComando = std::distance(commands.begin(), it);

        switch(indexComando) {
            case 0: { // Cadastrar Jogador
                std::string nome, apelido;
                std::cin >> nome >> apelido;
                
                Jogador novoJogador(nome, apelido);
                
                if (jogadores.check(novoJogador)) {
                    std::cout << "ERRO: jogador repetido" << std::endl;
                } else {
                    jogadores.adicionarJogador(novoJogador);
                    jogadores.save("cadastro.txt");
                }
                break;
            }
            case 1: { // Remover Jogador
                std::string apelido;
                std::cin >> apelido;
                
                Jogador jogadorRemover("", apelido);
                jogadores.removeJogador(jogadorRemover);
                jogadores.save("cadastro.txt");
                break;
            }
            case 2: { // Listar Jogadores
                std::string ordem;
                std::cin >> ordem;
                
                // Implementar ordenação por Nome (N) ou Apelido (A)
                jogadores.mostrarJogadores();
                break;
            }
            case 3: { // Executar Partida
                int tipoJogo;
                int num_jogadores;
                std::string nomeJogador1, nomeJogador2;
                std::cout << "Insira o número de jogadores (1 ou 2)" << std::endl;
                if (num_jogadores == 1)
                {
                    
                }
                std::cin >> tipoJogo >> nomeJogador1 >> nomeJogador2;
                
                Jogador* jogador1 = nullptr;
                Jogador* jogador2 = nullptr;
                
                // Procura jogadore
                
                for (const auto& j : jogadores.getJogadores()) {
                    if (j->getNome() == nomeJogador1 || j->getApelido() == nomeJogador1) {
                        jogador1 = j.get();
                    }
                    if (j->getNome() == nomeJogador2 || j->getApelido() == nomeJogador2) {
                        jogador2 = j.get();
                    }
                }
                
                if (!jogador1 || !jogador2) {
                    std::cout << "ERRO: jogador inexistente" << std::endl;
                } else {
                    if (partida.iniciarPartida(jogador1, jogador2, tipoJogo)) {
                        // Loop de jogo
                        int jogadorAtual = 1;
                        while (!partida.verificarFimDeJogo()) {
                            std::cout << "Turno do Jogador " << jogadorAtual << std::endl;
                            partida.imprimirTabuleiro();
                            
                            int linha, coluna;
                            std::cin >> linha >> coluna;
                            
                            if (!partida.realizarJogada(jogadorAtual, linha, coluna)) {
                                continue;  // Jogada inválida, tenta novamente
                            }
                            
                            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
                        }
                    }
                }
                break;
            }
            case 4: // Finalizar Sistema
                jogadores.save("cadastro.txt");
                return 0;
            default:
                std::cout << "erro inesperado" << std::endl;
                return 1;
        }
    }

    return 0;
}

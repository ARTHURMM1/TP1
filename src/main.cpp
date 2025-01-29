/**
 * @file main.cpp
 * @brief Sistema de gerenciamento de jogadores e jogos com funcionalidade de cadastro, remoção, busca e partidas.
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include "cadastro.hpp"
#include "jogos.hpp"
#include "partida.hpp"
#include <algorithm>

/**
 * @brief Exibe o menu de comandos do sistema.
 */
void mostrarMenu() {
    std::cout << NEGRITO << DIVIDER << RESETAR;
    std::cout << AMARELO << "=== Menu de Comandos ===" << RESETAR << std::endl;
    std::cout << "CJ - Cadastrar novo jogador" << std::endl;
    std::cout << "RJ - Remover jogador" << std::endl;
    std::cout << "LJ - Listar jogadores" << std::endl;
    std::cout << "PJ - Procurar jogador" << std::endl;
    std::cout << "NP - Nova partida" << std::endl;
    std::cout << "F  - Finalizar programa" << std::endl;
    std::cout << "H  - Ajuda (mostra este menu)" << std::endl;
    std::cout << DIVIDER << RESETAR << std::endl;
}



/**
 * @brief Cadastra um novo jogador no sistema.
 * @param jogadores Referência ao objeto Cadastro para gerenciar jogadores.
 */
void cadastrarJogador(Cadastro& jogadores) {
    std::string nome, apelido;
    std::cout << "Digite o nome do jogador: ";
    std::cin.ignore();
    std::getline(std::cin, nome);
    std::cout << "Digite o apelido do jogador: ";
    std::getline(std::cin, apelido);

    Jogador novoJogador(nome, apelido);

    if (!jogadores.check(novoJogador)) {
        jogadores.adicionarJogador(novoJogador);
        jogadores.save("cadastro.txt");
    } else {
        std::cout << "ERRO: Jogador já cadastrado!" << std::endl;
    }
}

/**
 * @brief Remove um jogador do sistema.
 * @param jogadores Referência ao objeto Cadastro para gerenciar jogadores.
 */
void removerJogador(Cadastro& jogadores) {
    std::string apelido;
    std::cout << "Digite o apelido do jogador a ser removido: ";
    std::cin.ignore();
    std::getline(std::cin, apelido);

    Jogador alvo("", apelido);
    jogadores.removeJogador(alvo);
    jogadores.save("cadastro.txt");
}

/**
 * @brief Procura por um jogador no sistema.
 * @param jogadores Referência ao objeto Cadastro para gerenciar jogadores.
 */
void procurarJogador(const Cadastro& jogadores) {
    std::string apelido;
    std::cout << "Digite o apelido do jogador: ";
    std::cin.ignore();
    std::getline(std::cin, apelido);

    Jogador alvo("", apelido);
    if (jogadores.check(alvo)) {
        std::cout << "Jogador encontrado!" << std::endl;
    } else {
        std::cout << "Jogador não encontrado." << std::endl;
    }
}

/**
 * @brief Inicia uma nova partida entre dois jogadores ou contra um bot.
 * @param jogadores Referência ao objeto Cadastro para gerenciar jogadores.
 */
void iniciarNovaPartida(Cadastro& jogadores) {
    std::string apelido1, apelido2;
    int tipoJogo;
    bool vsBot = false;

    std::cout << NEGRITO << DIVIDER << RESETAR;
    std::cout << AMARELO << "=== Tipos de Jogo ===" << RESETAR << std::endl;
    std::cout << "1 - Jogo da Velha" << std::endl;
    std::cout << "2 - Lig4" << std::endl;
    std::cout << "3 - Reversi" << std::endl;
    std::cout << DIVIDER << std::endl;

    std::cout << "Escolha o tipo de jogo: ";
    std::cin >> tipoJogo;

    if (tipoJogo < 1 || tipoJogo > 3) {
        std::cout << VERMELHO << "Tipo de jogo inválido!" << RESETAR << std::endl;
        return;
    }

    std::cout << "Jogar contra BOT? (1-Sim, 0-Não): ";
    std::cin >> vsBot;

    // Verifica se a entrada não é 1 nem 0, e continua pedindo até que seja válida
    if (vsBot != 1 && vsBot != 0) {
        std::cout << VERMELHO << "Entrada inválida! " << RESETAR << std::endl;
        return;
    }
    std::cout << DIVIDER << std::endl;
    std::cout << "Digite o apelido do Jogador 1: ";
    std::cin.ignore();
    std::getline(std::cin, apelido1);

    Jogador jogador1("", apelido1);
    if (!jogadores.check(jogador1)) {
        std::cout << VERMELHO << "Jogador 1 não encontrado!" << RESETAR << std::endl;
        return;
    }

    for (const auto& jogador : jogadores.get_jogadores()) {
        if (jogador->getApelido() == apelido1) {
            if (!vsBot) {
                std::cout << "Digite o apelido do Jogador 2: ";
                std::getline(std::cin, apelido2);
                Jogador jogador_teste("", apelido2);
                if (!jogadores.check(jogador_teste)) {
                    std::cout << VERMELHO << "Jogador 2 não encontrado!" << RESETAR << std::endl;
                    return;
                }
                for (const auto& jogador2 : jogadores.get_jogadores()) {
                    if (jogador2->getApelido() == apelido2) {
                        Partida partida(tipoJogo, jogador.get(), jogador2.get());
                        partida.iniciarPartida();
                        break;
                    }
                }
            } else {
                if (jogador->getApelido() == apelido1) {
                    Partida partida(tipoJogo, jogador.get());
                    partida.iniciarPartida();
                }
            }
        }
}

// Após a partida, salva as atualizações do cadastro
jogadores.save("cadastro.txt");
std::cout << NEGRITO << DIVIDER << RESETAR << std::endl;
}


/**
 * @brief Função principal do programa.
 * @return Retorna 0 em caso de execução bem-sucedida.
 */
int main() {
    Cadastro jogadores;
    jogadores.import("cadastro.txt");

    std::vector<std::string> commands = {"CJ", "RJ", "LJ", "PJ", "NP", "F", "H"};
    std::string inputComando;

    std::cout << "Bem-vindo ao Sistema de Jogos!" << std::endl;
    mostrarMenu();

 while (true) {
    std::cout << "\nDigite um comando: ";
    std::cin >> inputComando;

    // Converte o comando para maiúsculas
    std::transform(inputComando.begin(), inputComando.end(), inputComando.begin(), ::toupper);

    auto it = std::find(commands.begin(), commands.end(), inputComando);

    if (it == commands.end()) {
        std::cout << "Comando inválido! Digite 'H' para ver os comandos disponíveis." << std::endl;
        continue;
    }

    int indexComando = std::distance(commands.begin(), it);

    switch(indexComando) {
        case 0: // CJ
            cadastrarJogador(jogadores);
            break;
        case 1: // RJ
            removerJogador(jogadores);
            break;
        case 2: // LJ
            jogadores.mostrarJogadores();
            break;
        case 3: // PJ
            procurarJogador(jogadores);
            break;
        case 4: // NP
            iniciarNovaPartida(jogadores);
            std::cout << "teste1";  // Verifique se esta mensagem é realmente necessária
            std::cin.ignore();  // Limpa o buffer de entrada
            break;
        case 5: // F
            std::cout << "Programa finalizado." << std::endl;
            return 0;
        case 6: // H
            mostrarMenu();
            break;
        default:
            std::cout << "Erro inesperado!" << std::endl;
            return 1;
    }
}

}

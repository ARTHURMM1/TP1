/**
 * @file teste.cpp 
 * @brief Arquivo de testes que abriga toda a implementação de testes que julgamos necessários.
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cadastro.hpp"
#include "jogos.hpp"
#include "partida.hpp"
#include <stdexcept>
#include <sstream>

TEST_CASE("Teste de serialização e desserialização do Jogador") {
    Jogador jogador("João Silva", "joaosilva", 10, 5, 8, 3, 7, 2);

    SUBCASE("Serialização") {
        std::string serializado = jogador.serializar();
        CHECK(serializado == "João Silva,joaosilva,10,5,8,3,7,2");
    }

    SUBCASE("Desserialização") {
        std::string linha = "Maria Oliveira,mariaoliveira,15,6,9,4,12,3";
        Jogador jogadorDesserializado = Jogador::deserializar(linha);

        CHECK(jogadorDesserializado.getNome() == "Maria Oliveira");
        CHECK(jogadorDesserializado.getApelido() == "mariaoliveira");
        CHECK(jogadorDesserializado.getVitorias(jogadorDesserializado.getVelha()) == 15);
        CHECK(jogadorDesserializado.getDerrotas(jogadorDesserializado.getVelha()) == 6);
        CHECK(jogadorDesserializado.getVitorias(jogadorDesserializado.getLig4()) == 9);
        CHECK(jogadorDesserializado.getDerrotas(jogadorDesserializado.getLig4()) == 4);
        CHECK(jogadorDesserializado.getVitorias(jogadorDesserializado.getReversi()) == 12);
        CHECK(jogadorDesserializado.getDerrotas(jogadorDesserializado.getReversi()) == 3);
    }

    SUBCASE("Desserialização com formato inválido") {
        std::string linhaInvalida = "João Silva,joaosilva,10,5,8,3,7"; // Faltando um campo
        CHECK_THROWS_AS(Jogador::deserializar(linhaInvalida), std::invalid_argument);
    }

    SUBCASE("Desserialização com valores negativos") {
        std::string linhaNegativa = "João Silva,joaosilva,-10,5,8,3,7,2";
        CHECK_THROWS_AS(Jogador::deserializar(linhaNegativa), std::invalid_argument);
    }
}

TEST_CASE("Teste de adição e remoção de jogadores no Cadastro") {
    Cadastro cadastro;
    Jogador jogador1("João Silva", "joaosilva", 10, 5, 8, 3, 7, 2);
    Jogador jogador2("Maria Oliveira", "mariaoliveira", 15, 6, 9, 4, 12, 3);

    SUBCASE("Adicionar jogador") {
        cadastro.adicionarJogador(jogador1);
        CHECK(cadastro.check(jogador1) == true);
    }

    SUBCASE("Adicionar jogador duplicado") {
        cadastro.adicionarJogador(jogador1);
        CHECK_THROWS_AS(cadastro.adicionarJogador(jogador1), std::invalid_argument);
    }

    SUBCASE("Remover jogador") {
        cadastro.adicionarJogador(jogador1);
        cadastro.adicionarJogador(jogador2);
        cadastro.removeJogador(jogador1);
        CHECK(cadastro.check(jogador1) == false);
        CHECK(cadastro.check(jogador2) == true);
    }

    SUBCASE("Remover jogador não cadastrado") {
        CHECK_THROWS_AS(cadastro.removeJogador(jogador1), std::invalid_argument);
    }
}

TEST_CASE("Teste de importação e salvamento de jogadores") {
    Cadastro cadastro;
    std::string caminhoArquivo = "test_jogadores.txt";

    SUBCASE("Importar jogadores de arquivo") {
        std::ofstream arquivo(caminhoArquivo);
        arquivo << "João Silva,joaosilva,10,5,8,3,7,2\n";
        arquivo << "Maria Oliveira,mariaoliveira,15,6,9,4,12,3\n";
        arquivo.close();

        cadastro.import(caminhoArquivo);
        CHECK(cadastro.check(Jogador("João Silva", "joaosilva", 10, 5, 8, 3, 7, 2)) == true);
        CHECK(cadastro.check(Jogador("Maria Oliveira", "mariaoliveira", 15, 6, 9, 4, 12, 3)) == true);
    }

    SUBCASE("Salvar jogadores em arquivo") {
        cadastro.adicionarJogador(Jogador("João Silva", "joaosilva", 10, 5, 8, 3, 7, 2));
        cadastro.adicionarJogador(Jogador("Maria Oliveira", "mariaoliveira", 15, 6, 9, 4, 12, 3));
        cadastro.save(caminhoArquivo);

        std::ifstream arquivo(caminhoArquivo);
        std::string linha;
        std::getline(arquivo, linha);
        CHECK(linha == "João Silva,joaosilva,10,5,8,3,7,2");
        std::getline(arquivo, linha);
        CHECK(linha == "Maria Oliveira,mariaoliveira,15,6,9,4,12,3");
        arquivo.close();
    }
}

TEST_CASE("Teste de exibição de jogadores") {
    Cadastro cadastro;
    Jogador jogador1("João Silva", "joaosilva", 10, 5, 8, 3, 7, 2);
    Jogador jogador2("Maria Oliveira", "mariaoliveira", 15, 6, 9, 4, 12, 3);

    cadastro.adicionarJogador(jogador1);
    cadastro.adicionarJogador(jogador2);

    SUBCASE("Mostrar jogadores") {
        // Redirecionar a saída padrão para um stringstream para verificar a saída
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        cadastro.mostrarJogadores();

        std::cout.rdbuf(old); // Restaurar a saída padrão

        std::string output = buffer.str();
        CHECK(output.find("João Silva joaosilva") != std::string::npos);
        CHECK(output.find("Maria Oliveira mariaoliveira") != std::string::npos);
    }
}

TEST_CASE("Testando a classe Reversi") {
    Reversi reversi(8, 8);

    SUBCASE("Testando configuração inicial do tabuleiro") {
        CHECK(reversi.get_casa(3, 3) == 2);
        CHECK(reversi.get_casa(3, 4) == 1);
        CHECK(reversi.get_casa(4, 3) == 1);
        CHECK(reversi.get_casa(4, 4) == 2);
    }

    SUBCASE("Testando verificar_jogada") {
        CHECK(reversi.verificar_jogada(2, 3, 1) == true);
        CHECK(reversi.verificar_jogada(3, 2, 1) == true);
        CHECK(reversi.verificar_jogada(5, 4, 1) == false);
    }

    SUBCASE("Testando ler_jogada") {
        CHECK(reversi.ler_jogada(2, 3, 1) > 0);
        CHECK(reversi.get_casa(2, 3) == 1);
    }

    SUBCASE("Testando testar_condicao_de_vitoria") {
        CHECK(reversi.testar_condicao_de_vitoria() == false);
    }

    SUBCASE("Testando calcular_pontuacao") {
        auto pontuacao = reversi.calcular_pontuacao();
        CHECK(pontuacao.first == 2); // Jogador 1 (X)
        CHECK(pontuacao.second == 2); // Jogador 2 (O)
    }
}

TEST_CASE("Testando a classe JogoDaVelha") {
    JogoDaVelha jogo(3, 3);

    SUBCASE("Testando verificar_jogada") {
        CHECK(jogo.verificar_jogada(0, 0, 1) == true);
        jogo.ler_jogada(0, 0, 1);
        CHECK(jogo.verificar_jogada(0, 0, 2) == false);
    }

    SUBCASE("Testando ler_jogada") {
        CHECK(jogo.ler_jogada(0, 0, 1) == 1);
        CHECK(jogo.get_casa(0, 0) == 1);
    }

    SUBCASE("Testando determinar_vencedor") {
        jogo.ler_jogada(0, 0, 1);
        jogo.ler_jogada(1, 1, 1);
        jogo.ler_jogada(2, 2, 1);
        CHECK(jogo.determinar_vencedor() == 1);
    }

    SUBCASE("Testando testar_condicao_de_vitoria") {
        jogo.ler_jogada(0, 0, 1);
        jogo.ler_jogada(1, 1, 1);
        jogo.ler_jogada(2, 2, 1);
        CHECK(jogo.testar_condicao_de_vitoria() == true);
    }
}

TEST_CASE("Testando a classe Lig4") {
    Lig4 lig4(6, 7);

    SUBCASE("Testando verificar_jogada") {
        CHECK(lig4.verificar_jogada(0, 0, 1) == true);
        for (int i = 0; i < 6; ++i) {
            lig4.ler_jogada(i, 0, 1);
        }
        CHECK(lig4.verificar_jogada(0, 0, 1) == false);
    }

    SUBCASE("Testando ler_jogada") {
        CHECK(lig4.ler_jogada(0, 0, 1) == 1);
        CHECK(lig4.get_casa(5, 0) == 1);
    }

    SUBCASE("Testando testar_condicao_de_vitoria") {
        lig4.ler_jogada(5, 0, 1);
        lig4.ler_jogada(5, 1, 1);
        lig4.ler_jogada(5, 2, 1);
        lig4.ler_jogada(5, 3, 1);
        CHECK(lig4.testar_condicao_de_vitoria() == true);
    }
}



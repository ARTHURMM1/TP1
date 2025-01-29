
Projeto Final - Jogos de Tabuleiro

Este projeto foi desenvolvido como trabalho final da disciplina PDS II (2º Semestre de 2024) na Universidade Federal de Minas Gerais. O objetivo foi implementar um sistema de jogos de tabuleiro, utilizando os conceitos de Programação Orientada a Objetos (POO).

-Descrição do Projeto-
O sistema possui três módulos principais:

1. Hierarquia de Classes para Jogos
   Uma classe abstrata Jogos foi desenvolvida para representar jogos de tabuleiro de forma geral. A partir dela, foram implementados três jogos específicos:
   - Jogo da Velha
   - Lig4 
   - Reversi 
A classe foi construída de forma reciclável e podem ser adicionados outros jogos com suas respectivas implementações.

   Cada classe herda da base e especializa métodos para lidar com jogadas, validações, condições de vitória, e impressão do tabuleiro.

2. Cadastro de Jogadores
   Um sistema para gerenciar jogadores, com as seguintes funcionalidades:
   - Cadastro e remoção de jogadores.
   - Armazenamento e atualização de estatísticas (vitórias e derrotas) para cada jogo.
   - Salvamento e leitura de dados a partir de um arquivo de texto para persistência.

3. Execução de Partidas
   - O sistema permite iniciar partidas entre dois jogadores para qualquer jogo implementado.
   - Durante as partidas, é possível validar jogadas, atualizar o estado do tabuleiro e verificar condições de vitória.
   - Estatísticas dos jogadores são atualizadas ao término da partida.

-Funcionalidades-
Comandos Disponíveis
Os comandos suportados pelo sistema são os seguintes:

1. Cadastrar Jogador
   CJ <Apelido> <Nome>
   Mensagens esperadas:
   - Jogador cadastrado com sucesso.
   - ERRO: dados incorretos.
   - ERRO: jogador repetido.

2. Remover Jogador
   RJ <Apelido>
   Mensagens esperadas:
   - Jogador removido com sucesso.
   - ERRO: jogador inexistente.

3. Listar Jogadores
   LJ [A|N]
   Lista jogadores ordenados por Apelido (A) ou Nome (N).
   Exemplo de saída:
   <Apelido> <Nome>
   REVERSI - V: <#vitorias> D: <#derrotas>
   LIG4 - V: <#vitorias> D: <#derrotas>
   VELHA - V: <#vitorias> D: <#derrotas>

4. Executar Partida
   EP <Jogo: (R|L|V)> <Apelido Jogador 1> <Apelido Jogador 2>
   Mensagens esperadas:
   - ERRO: dados incorretos.
   - ERRO: jogador inexistente.

5. Finalizar Sistema
   F

Entrada de Jogadas
Durante uma partida, o sistema solicita jogadas no formato apropriado para cada jogo. Mensagens de erro são exibidas caso a jogada seja inválida ou esteja no formato incorreto.

Estrutura do Projeto
A estrutura de diretórios do projeto segue a seguinte organização:

ProjetoFinal/
├── bin/           # Arquivos executáveis gerados
├── include/       # Arquivos de cabeçalho (.hpp)
├── obj/           # Arquivos objeto (.o)
├── src/           # Código-fonte (.cpp)
├── tests/         # Arquivos de teste unitário
├── .gitignore     # Arquivos e pastas ignorados pelo Git
├── Makefile       # Automação da compilação
├── README.md      # Descrição do projeto

-Como Executar-
Compilação
Utilize o Makefile para compilar o projeto através do comando:
make

Os executáveis serão gerados na pasta bin/.

Execução
Para executar o programa principal, utilize o comando:
./bin/main

Testes
Os testes unitários foram implementados com a biblioteca doctest. Para executar os testes, utilize o comando:
make test

Documentação
A documentação do código foi gerada utilizando o Doxygen. Para acessá-la, basta abrir o PDF "documentação.pdf".

Dificuldades Encontradas
- Construir classes abstratas recicláveis para alterações futuras.
- Implementar o algoritmo minimax no Bot.
- Trabalhar com o Git e GitHub (perdemos a conta de quantas vezes deletamos e clonamos porque não sabíamos como resolver algum merge ou quando o pull não funcionava). 

Funcionalidades Extras
- Implementação de uma IA simples para jogar contra um dos jogadores (algoritmo Minimax).
- Suporte a personalização de tamanho do tabuleiro em Lig4.
- Uso de cores e estilos no terminal para melhorar a interface visual.

Autores
Este projeto foi desenvolvido em grupo como parte do trabalho final da disciplina PDS II.
Nota: Para mais informações sobre o desenvolvimento, consulte os comentários no código e a documentação gerada pelo Doxygen.

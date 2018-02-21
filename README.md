# Iart
Este é o repositório do trabalho da disciplina de iart (feup).
O objetivo é conceber uma algoritmo minimax (alpha beta) que permita jogar [Whirlwind] (https://boardgamegeek.com/boardgame/159022/whirlwind).

##Jogo
É um jogo de tabuleiro em que o objetivo é:
- para as peças pretas, atravessar verticalmente com uma linha de peças o tabuleiro
- para as peças brancas, atravessar horizontalmente com uma linha de peças o tabuleiro
O primeiro a conseguir o objetivo ganha.
Primeiro começam as peças pretas e depois as brancas e assim sucessivamente.
Em cada jogada podem ser jogadas uma ou duas peças (não se pode assar a jogada).
Devido ao facto de já haverem peças pré-posicionadas, o jogo não pode resultar em empate.

Optou-se por fazer várias implementações do algoritmo minimax (ainda sem alpha beta) em várias linguagens para testar a robustez de cada uma para o problema proposto.

##Java
Java é uma linguagens simples e orientada para objetos. Foi a primeira escolha. No entanto, a execução do algoritmo apenas era capaz de processar 2 niveis de profundidade num tempo de razoável (menos de 5 segundos). Pensou-se assim que seria mais eficiente fazer o algoritmo num paradigma de programação em lógica.

##Prolog
O pensava-se o prolog seria mais eficinte que java porque a linguagem suporta muito bem litas (o tabuleiro pode ser representado por uma lista) e tem outras optimizaçoes (?threads?) para precorrer-las de forma rápida. No entanto, com a implementação do minimax, a execução do algoritmo apenas era capaz de processar 1 nivel de profundidade num tempo de razoável (menos de 5 segundos). Pensamos que isto se deve ao facto de se procorrer muitas vezes as litas, que por vezes parecem ser desnecessárias quando comparado a linguagens como java.

##C
Assim pensamos ser mais fácil fazer o trabalho em linguagem c visto podermos fazer uma melhor gestão de memória que em java.

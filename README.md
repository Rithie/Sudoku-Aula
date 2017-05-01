# Sudoku-Aula

![Sudoku](https://media.giphy.com/media/l4FGDOfMgfhZX8Szu/giphy.gif)

### Clone o repositório:

git clone https://github.com/Rithie/Sudoku-Aula.git

### para compilar no terminal:

```sh
g++  sodoku.cpp -o sodoku
```

```sh
./sodoku
```

## Como funciona o Algoritimo: 

Encontrar a linha, e coluna de uma posição vazia
se estiver vazia, retornar true
Para digitos de 1 a 9

 1 - Se não houver colisões para o numero na row ou col atribur o numero a linha e coluna e recursivamente tentar preencher o restante da matriz.

 2 -  Se a recursão obtiver sucesso retornar true
 	Else,remove o numero e tenta outro
 3 - Se todos os digitios tiverem sido tentados e falharem, retornar falso
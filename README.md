# Parsing Tree C++ - Avaliador de Expressões

## Descrição

Este projeto implementa um avaliador de expressões matemáticas e booleanas em C++ usando uma árvore de parsing baseada em gramática livre de contexto. O programa é capaz de processar expressões que incluem:

- **Operações aritméticas**: adição (+), subtração (-), multiplicação (*), divisão (/)
- **Operações booleanas**: AND (&&), OR (||)
- **Operações de comparação**: igual (==), diferente (!=), menor (<), maior (>), menor ou igual (<=), maior ou igual (>=)
- **Operações unárias**: negação aritmética (-)
- **Parênteses**: para controle de precedência
- **Literais**: números inteiros e valores booleanos (true/false)

## Estrutura do Projeto

```
ParseTree/
├── main.cpp           # Programa principal
├── parser.h           # Definições do parser
├── parse.cpp          # Implementação do parser
├── expressions.h      # Definições das classes de expressões
├── expressions.cpp    # Implementação das classes de expressões
├── input              # Arquivo de entrada com casos de teste
└── output/
    └── main.exe       # Executável compilado
```

## Arquitetura

### Classes Principais

1. **Parser**: Responsável pela análise léxica e sintática
   - Tokenização da entrada
   - Verificação de parênteses balanceados
   - Construção da árvore de parsing seguindo a precedência de operadores

2. **Expression**: Classe base abstrata para todas as expressões
   - `evaluateInt()`: Avalia expressões que retornam inteiros
   - `evaluateBool()`: Avalia expressões que retornam booleanos

3. **Hierarquia de Expressões**:
   - **Literal**: Valores constantes (int/bool)
   - **BinaryExpression**: Operações com dois operandos
     - `AddExp`: Adição e subtração
     - `MulExp`: Multiplicação e divisão
     - `RelExp`: Operações relacionais
     - `EqExp`: Operações de igualdade
     - `AndExp`: Operação AND lógica
     - `OrExp`: Operação OR lógica
   - **UnaryExpression**: Operações unárias (negação)
   - **ParenthesesExpression**: Expressões entre parênteses

4. **Operator**: Encapsula operadores como strings

### Precedência de Operadores

O parser segue a seguinte hierarquia de precedência (do menor para o maior):

1. `||` (OR lógico)
2. `&&` (AND lógico)
3. `==`, `!=` (igualdade/desigualdade)
4. `<`, `>`, `<=`, `>=` (comparação)
5. `+`, `-` (adição/subtração)
6. `*`, `/` (multiplicação/divisão)
7. `-` (negação unária)
8. `()` (parênteses)

## Funcionalidades

### Entrada
- Primeira linha: número de expressões a serem avaliadas
- Linhas seguintes: uma expressão por linha

### Saída
- Para cada expressão válida: resultado da avaliação
- Para expressões inválidas: "error"

### Tratamento de Erros
- Parênteses desbalanceados
- Divisão por zero
- Operações incompatíveis entre tipos
- Tokens inválidos
- Sintaxe incorreta

## Exemplos de Uso

```
Entrada:
7
1
2 + 3 * 2
( 2 - - -3 ) * 2
3 / 2
true || false == false
( true || false ) == false
true + 3

Saída:
1
8
10
1
true
false
error
```

## Compilação

```bash
# Compilar o projeto
g++ -std=c++11 -o ParseTree/output/main.exe ParseTree/main.cpp ParseTree/parse.cpp ParseTree/expressions.cpp

# Executar com arquivo de entrada
./ParseTree/output/main.exe < ParseTree/input
```

## Requisitos

- Compilador C++ com suporte a C++11 ou superior
- Sistema operacional: Windows/Linux/macOS

## Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

## Autor

Eduardo - 2025

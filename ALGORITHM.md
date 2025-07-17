# Algoritmo de Parsing - Documentação Técnica

## Visão Geral

O parser implementa um analisador descendente recursivo (Recursive Descent Parser) para processar expressões matemáticas e booleanas. O algoritmo segue a gramática livre de contexto definida pela precedência de operadores.

## Gramática Formal

```
expression    → or_expression
or_expression → and_expression ('||' and_expression)*
and_expression → eq_expression ('&&' eq_expression)*
eq_expression → rel_expression (('==' | '!=') rel_expression)*
rel_expression → add_expression (('<' | '>' | '<=' | '>=') add_expression)*
add_expression → mul_expression (('+' | '-') mul_expression)*
mul_expression → unary_expression (('*' | '/') unary_expression)*
unary_expression → ('-')? primary_expression
primary_expression → NUMBER | BOOLEAN | '(' expression ')'
```

## Fluxo de Execução

### 1. Análise Léxica (Tokenização)

A função `tokenizer()` é responsável por:
- Separar a entrada em tokens individuais
- Identificar números, operadores e palavras-chave
- Tratar operadores compostos (==, !=, <=, >=, &&, ||)
- Ignorar espaços em branco

### 2. Análise Sintática

O parser utiliza uma abordagem descendente recursiva onde:
- Cada regra da gramática corresponde a uma função
- A precedência é respeitada pela ordem das chamadas
- Cada função constrói um nó da árvore de parsing

### 3. Construção da Árvore de Parsing

A árvore é construída usando o padrão Composite:
- `Expression`: Interface base para todos os nós
- `BinaryExpression`: Nós com dois operandos
- `UnaryExpression`: Nós com um operando
- `Literal`: Nós folha (valores constantes)

### 4. Avaliação

A avaliação é feita através do padrão Visitor:
- `evaluateInt()`: Para expressões aritméticas
- `evaluateBool()`: Para expressões booleanas
- Tratamento de tipos dinâmico com exceções

## Precedência de Operadores

| Prioridade | Operador | Associatividade | Descrição |
|------------|----------|----------------|-----------|
| 1 (menor) | `\|\|` | Esquerda | OR lógico |
| 2 | `&&` | Esquerda | AND lógico |
| 3 | `==`, `!=` | Esquerda | Igualdade |
| 4 | `<`, `>`, `<=`, `>=` | Esquerda | Comparação |
| 5 | `+`, `-` | Esquerda | Adição/Subtração |
| 6 | `*`, `/` | Esquerda | Multiplicação/Divisão |
| 7 | `-` (unário) | Direita | Negação |
| 8 (maior) | `()` | - | Parênteses |

## Tratamento de Erros

### Tipos de Erro

1. **Erro Léxico**: Tokens inválidos
2. **Erro Sintático**: Sequência de tokens inválida
3. **Erro Semântico**: Operações incompatíveis entre tipos
4. **Erro de Execução**: Divisão por zero, overflow

### Estratégia de Recuperação

- Validação de parênteses antes do parsing
- Exceções para interromper o parsing em caso de erro
- Mensagem genérica "error" para todos os tipos de erro

## Complexidade

- **Tempo**: O(n) onde n é o número de tokens
- **Espaço**: O(d) onde d é a profundidade da árvore

## Limitações do Algoritmo

1. **Não suporta ambiguidade**: Gramática não ambígua
2. **Associatividade fixa**: Todos os operadores binários são associativos à esquerda
3. **Precedência fixa**: Não é possível alterar a precedência em tempo de execução
4. **Tipos limitados**: Apenas inteiros e booleanos

## Possíveis Melhorias

1. **Suporte a ponto flutuante**: Adicionar literais decimais
2. **Variáveis**: Implementar tabela de símbolos
3. **Funções**: Adicionar chamadas de função
4. **Melhor tratamento de erros**: Mensagens específicas e posição do erro
5. **Otimizações**: Constant folding, dead code elimination

## Exemplo de Execução

Para a expressão `2 + 3 * 4`:

1. **Tokenização**: [2, +, 3, *, 4]
2. **Parsing**: 
   - `parse_exp()` → `or_exp()` → `and_exp()` → `eq_exp()` → `rel_exp()` → `add_exp()`
   - `add_exp()` cria `AddExp(2, +, MulExp(3, *, 4))`
3. **Avaliação**: `2 + (3 * 4)` = `2 + 12` = `14`

## Referencias

- Aho, Alfred V., et al. "Compilers: Principles, Techniques, and Tools" (Dragon Book)
- Grune, Dick, et al. "Modern Compiler Design"
- Crafting Interpreters by Robert Nystrom

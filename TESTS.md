# Casos de Teste para o Avaliador de Expressões

## Casos de Teste Básicos

### Aritméticos
- `1` → `1`
- `2 + 3` → `5`
- `10 - 4` → `6`
- `3 * 4` → `12`
- `8 / 2` → `4`

### Precedência
- `2 + 3 * 4` → `14` (não `20`)
- `(2 + 3) * 4` → `20`
- `2 * 3 + 4` → `10`
- `2 + 3 * 4 - 1` → `13`

### Negação Unária
- `-5` → `-5`
- `--5` → `5`
- `---5` → `-5`
- `2 + -3` → `-1`
- `(2 - --3) * 2` → `10`

### Divisão
- `10 / 2` → `5`
- `7 / 2` → `3` (divisão inteira)
- `10 / 0` → `error`

### Booleanos
- `true` → `true`
- `false` → `false`
- `true && false` → `false`
- `true || false` → `true`

### Comparações
- `5 > 3` → `true`
- `2 < 1` → `false`
- `5 >= 5` → `true`
- `3 <= 2` → `false`
- `4 == 4` → `true`
- `3 != 3` → `false`

### Expressões Complexas
- `true || false && true` → `true`
- `(true || false) && true` → `true`
- `5 > 3 && 2 < 4` → `true`
- `true || false == false` → `true`
- `(true || false) == false` → `false`

### Casos de Erro
- `true + 3` → `error`
- `5 && true` → `error`
- `((2 + 3)` → `error` (parênteses desbalanceados)
- `2 + + 3` → `error`
- `2 3` → `error`

## Estrutura do Arquivo de Entrada

```
número_de_casos
expressão_1
expressão_2
...
expressão_n
```

Exemplo:
```
3
2 + 3
true && false
5 > 3
```

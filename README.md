<div align="center">
  <h3 align="center">TBO2</h3>
</div>

## Sobre

TBO2 foi o segundo trabalho desenvolvido ao longo da disciplina de Técnicas de Busca e Ordenação, ministrada pelo professor Giovanni.

## Começando

### Pré-requisitos

- Linux (sem suporte pro windows, sra. microsoft)
- [GNU Compiler Collection](https://gcc.gnu.org/)

### Instalando

1. Clone o repositório

   ```sh
   git clone https://github.com/srjheam/ufes-tbo2.git
   ```

2. Dirija-se ao seu diretório

   ```sh
   cd ufes-tbo2/
   ```

3. Compile o código-fonte

   ```sh
   make
   ```

#### Flags

- RED_PILL

1. Compile com

   ```sh
   make CFLAGS='-DRED_PILL'
   ```

E liberte-se da matrix.

## Usando

Intruções de uso para o giovanni.

### Giovanni

giovanni.

```sh
./trab2 <nome_arquivo_entrada> <nome_arquivo_saida>
```

Onde,

- `nome_arquivo_entrada` - é o nome do arquivo de entrada.
- `nome_arquivo_saida` - é o nome do arquivo de saída.

## Contribuindo

Este projeto está configurado e integrado com o Visual Studio Code.

### Valgrind

Há uma regra no [Makefile](./Makefile) para lançar rapidamente o Valgrind. O resultado será salvo em [valgrind-out.txt](./valgrind-out.txt).

```sh
make valgrind VALARGS=<args>
```

Onde,

- `args` - são os argumentos para passar ao programa. Opcional.

## Suporte

Esse programa não funciona em ambientes não-POSIX e pode até mesmo não funcionar em sistemas não-Linux.

Isso se deve ao fato de usar APIs que são extensões do POSIX e não fazem parte do padrão C.

## Licença

Licenciado sob [Unlicense](./LICENSE).

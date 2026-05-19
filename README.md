# Jogo

- [Diagrama Jogo Modelo](https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/TopicosTrab/DiagramaJogoModelo.jpg)
- [Modelo Especificação para Trabalho](https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/TopicosTrab/Modelo_Especificacao_para_Trabalho_TecnicasProgramacao.pdf)

# Dependências
- SFML
- g++
- make

## Linux
Instalar o SFML no linux, em uma distribuição debian:
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

## Windows
- Instale o [MSYS2](https://www.msys2.org/)
- Abra o terminal do MSYS2
```bash
pacman -Syu
```
- Instale o g++ e o make
```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-sfml
```
- Adicione o gcc e o SFML ao path do Windows `C:\msys64\ucrt64\bin`

## Como rodar
```bash
make run
```

ou

1. Compilar o projeto
```bash
make
```

2. Executar
```bash
./bin/jogo
```
# Jogo

## TODO
- [ ] Implementar tempoExplosao na MinaExtraterrestre
- [ ] Usar nivel de maldade nos inimigos
- [ ] Fazer demonio lançar projétil
- [ ] Singletons: Jogo, Gerenciador_Colisoes, Gerenciador_Grafico
- [ ] Usar: observer, mediator, iterator... https://refactoring.guru/design-patterns
- [ ] Cores UML: amarelinho, verde e vermelho. Tabelas também

- [Diagrama Jogo Modelo](https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/TopicosTrab/DiagramaJogoModelo.jpg)
- [Modelo Especificação para Trabalho](https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/TopicosTrab/Modelo_Especificacao_para_Trabalho_TecnicasProgramacao.pdf)

# Dependências
- SFML 2.5.1
- GCC 7.3.0
- make

## Linux (RECOMENDADO)
- Instale as principais dependências do projeto, utilizando o apt:
```bash
sudo apt-get update
sudo apt-get install build-essential libsfml-dev
```

- Verifique se o g++ está instalado
```bash
g++ --version
```

## Windows
- Baixe o [SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/)
- Extraia a pasta para `C:\` para que o diretório seja `C:\SFML-2.5.1`. Esse diretório deverá conter uma pasta chamada `bin`
- Na mesma página do SFML 2.5.1, baixe o **MinGW Build 7.3.0**
- Extraia para `C:\` para que o diretório seja `C:\mingw64`. Esse diretório deverá conter uma pasta chamada `bin`
- Adicione ao PATH:
    - C:\mingw64\bin
    - C:\SFML-2.5.1\bin

- Abra um terminal no windows e verifique se o g++ foi instalado:
```bash
g++ --version
```
Se tudo foi feito corretamente, deve aparecer algo similar a isso:
```
g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 7.3.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

## Como rodar
Atalho:
- Linux: `make run`
- Windows: `mingw32-make run`

Passo a passo:
1. Compile o projeto
- Linux: `make`
- Windows: `mingw32-make`

2. Execute o binário
- Linux: `./bin/jogo`
- Windows: `.\bin\jogo.exe`
# Jogo

- [Diagrama Jogo Modelo](https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/TopicosTrab/DiagramaJogoModelo.jpg)
- [Modelo Especificação para Trabalho](https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/TopicosTrab/Modelo_Especificacao_para_Trabalho_TecnicasProgramacao.pdf)

# Dependências
- SFML
- g++
- make

## Linux
Instale as principais dependências do projeto, utilizando o apt:
```bash
sudo apt-get update
sudo apt-get install build-essential libsfml-dev
```

Verifique se o g++ está instalado
```bash
g++ --version
```

## Windows
- Instale o [MSYS2](https://www.msys2.org/)
- Mantenha o diretório de instalação padrão `C:\msys64`
- Abra o terminal do MSYS2
- Atualize os pacotes do sistema
```bash
pacman -Syu
```
- Instale o g++, o make e o SFML:
```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-sfml mingw-w64-ucrt-x86_64-make
```
- Adicione o gcc e o SFML ao path do Windows: `C:\msys64\ucrt64\bin`

Verifique se o g++ está instalado em um novo terminal do Windows
```bash
g++ --version
```

## Como rodar
```bash
make run
```

ou

1. Compile o projeto
```bash
make
```

2. Execute o binário
- No Linux:
```bash
./bin/jogo
```
- No windows:
```base
.\bin\jogo.exe
```
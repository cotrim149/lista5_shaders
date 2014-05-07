O projeto é executado utilizando o arquivo Makefile em ambiente Linux - Distro = Ubuntu 13.10

Linha de compilação usada:

g++ CG.cpp Mesh.cpp InitShader.cpp main.cpp -w -lSDL -lGL -lGLU -lglut -lGLEW -o exec

g++ = compilador de C++
main.cpp = código fonte principal do projeto.
CG.cpp = Responsável pela inicialização do OpenGL.
Mesh.cpp = Responsável pela Inicialização e processamento da malha, como ampliação, redução e translação. 
InitShader.cpp = Responsável pela inicialização dos shaders
exec = executável de código fonte
Flags de compilação
	-w = identificação de erros que estão fora do padrão
	-lSDL = lincagem entre as bibliotecas SDL e código usado
	-lGL = lincagem entre as bibliotecas do OpenGL e código usado
	-lGlU e -lglut = utilização do freeglut
	-LGLEW = lincagem entre as bibliotecas de glew e o código usado
	-o = flag para saida de arquivo compilador
	
Para conforto foi utlizado o Makefile, o qual pode ser compilado usando o comando : 
	make

Arquivos usados para compilação

bun_zipper.off
	Arquivo usado para guardar valores em float - pontos do desenho - e em inteiros  - cores e indices da face de cada ponto.
	Cada linha representa um ponto e uma cor usada por este ponto.

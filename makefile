all:
	make vm-linux vm-windows compiler-linux compiler-windows

linux:
	make vm-linux compiler-linux

vm-linux:
	gcc -o bin/codex -Wall -O2 src/vm/*.c

compiler-linux:
	cd src/compiler/; bison -d -o Parser.cpp Parser.y; flex -o Lexer.cpp Lexer.l; cd ../../; g++ -o bin/codexc src/compiler/*.cpp src/compiler/syntax/*.cpp 

vm-windows:
	i586-mingw32msvc-cc -o bin/codex.exe -Wall -O2 src/vm/*.c

compiler-windows:
	cd src/compiler/; bison -d -o Parser.cpp Parser.y; flex -o Lexer.cpp Lexer.l; cd ../../; i586-mingw32msvc-c++ -o bin/codexc.exe src/compiler/*.cpp src/compiler/syntax/*.cpp

clean:
	rm src/compiler/Parser.hpp src/compiler/Parser.cpp src/compiler/Lexer.cpp


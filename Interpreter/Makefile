CXX      := g++
CXXFLAGS := -ggdb -std=c++17
CPPFLAGS := -MMD

COMPILE  := $(CXX) $(CXXFLAGS) $(CPPFLAGS)

SRCS     := SyntaxTreePrinterDriver.cpp SyntaxTreeGenerator.cpp SyntaxTreePrinter.cpp Token.cpp Scanner.cpp Parser.cpp RuntimeError.cpp InterpreterFile.cpp Environment.cpp ConflictResolver.cpp Lox.cpp Application.cpp
DEPS     := $(SRCS:.cpp=.d)


Application: Expr.h Stmt.h Lox.o SyntaxTreePrinter.o Token.o Scanner.o Parser.o RuntimeError.o InterpreterFile.o Environment.o ConflictResolver.o Application.o
	@$(COMPILE) Lox.o SyntaxTreePrinter.o Token.o Scanner.o Parser.o RuntimeError.o InterpreterFile.o Environment.o ConflictResolver.o Application.o -o $@


SyntaxTreePrinter: Expr.h Stmt.h SyntaxTreePrinterDriver.o
	@$(COMPILE) SyntaxTreePrinterDriver.o -o $@


SyntaxTreeGenerator: SyntaxTreeGenerator.o
	@$(COMPILE) $< -o $@


Expr.h Stmt.h: SyntaxTreeGenerator
	@./SyntaxTreeGenerator .


.PHONY: clean
clean:
	rm -f *.d *.o SyntaxTreePrinter SyntaxTreeGenerator Application

-include $(DEPS)

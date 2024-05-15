#include "Lox.h"
#include "FunctionFile.cpp"
#include "ClassFile.cpp"
#include "InstanceFile.cpp"

std::string readFile(std::string_view path) {
  std::ifstream file{path.data(), std::ios::in | std::ios::binary | std::ios::ate};
  if (!file) {
    std::cerr << "Failed to open file " << path << ": " << std::strerror(errno) << "\n";
    std::exit(74);
  }
  std::string contents;
  contents.resize(file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(contents.data(), contents.size());
  return contents;
}
Interpreter interpreter{};
void run(std::string_view source) {
  Scanner scanner {source};
  std::vector<Token> tokens = scanner.scanTokens();
  Parser parser{tokens};
  std::vector<std::shared_ptr<Stmt>> statements = parser.parse();
  if (hadError) return;
  Resolver resolver{interpreter};
  resolver.resolve(statements);
  if (hadError) return;
  interpreter.interpret(statements);
}
void runFile(std::string_view path) {
  std::string contents = readFile(path);
  run(contents);
  if (hadError) std::exit(65);
  if (hadRuntimeError) std::exit(70);
}
void runPrompt() {
  for (;;) {
    std::cout << "> ";
    std::string line;
    if (!std::getline(std::cin, line)) break;
    run(line);
    hadError = false;
  }
}

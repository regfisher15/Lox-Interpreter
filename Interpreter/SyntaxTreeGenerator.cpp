#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

std::vector<std::string_view> split(std::string_view str, std::string_view delim) {
  std::vector<std::string_view> out;
  std::string_view::size_type start = 0;
  std::string_view::size_type end   = str.find(delim);
  while (end != std::string_view::npos) {
    out.push_back(str.substr(start, end - start));
    start = end + delim.length();
    end   = str.find(delim, start);
  }
  out.push_back(str.substr(start, end - start));
  return out;
}
std::string_view trim(std::string_view str) {
  auto isspace = [] (auto c) { return std::isspace(c); };
  auto start = std::find_if_not(str.begin(), str.end(), isspace);
  auto end = std::find_if_not(str.rbegin(), str.rend(), isspace).base();
  return {start, std::string_view::size_type(end - start)};
}
std::string toLowerCase(std::string_view str) {
  std::string out;
  for (char c : str) {
    out.push_back(std::tolower(c));
  }
  return out;
}
std::string fix_pointer(std::string_view field) {
  std::ostringstream out;
  std::string_view type = split(field, " ")[0];
  std::string_view name = split(field, " ")[1];
  bool close_bracket = false;
  if (type.substr(0, 12) == "std::vector<") {
    out << "std::vector<";
    type = type.substr(12, type.length() - 13);
    close_bracket = true;
  }
  if (type.back() == '*') {
    type.remove_suffix(1);
    out << "std::shared_ptr<" << type << ">";
  } else {
    out << type;
  }
  if (close_bracket) out << ">";
  out << " " << name;
  return out.str();
}
void defineVisitor(std::ofstream& writer, std::string_view baseName, const std::vector<std::string_view>& types) {
  writer << "struct " << baseName << "Visitor {\n";
  for (std::string_view type : types) {
      std::string_view typeName = trim(split(type, ":")[0]);
      writer << "  virtual std::any visit" << typeName << baseName << "(std::shared_ptr<" << typeName << "> " <<
      toLowerCase(baseName) << ") = 0;\n";
  }
  writer << "  virtual ~" << baseName << "Visitor() = default;\n";
  writer << "};\n";
}

void defineType(std::ofstream& writer, std::string_view baseName, std::string_view className, std::string_view fieldList) {
  writer << "struct " << className << ": " << baseName << ", public std::enable_shared_from_this<" << className << "> {\n";
  writer << "  " << className << "(";
  std::vector<std::string_view> fields = split(fieldList, ", ");
  writer << fix_pointer(fields[0]);
  for (int i = 1; i < fields.size(); ++i) {
    writer << ", " << fix_pointer(fields[i]);
  }
  writer << ")\n" << "    : ";
  std::string_view name = split(fields[0], " ")[1];
  writer << name << "{std::move(" << name << ")}";
  for (int i = 1; i < fields.size(); ++i) {
    name = split(fields[i], " ")[1];
    writer << ", " << name << "{std::move(" << name << ")}";
  }
  writer << "\n" << "  {}\n";
  writer << "\n"
            "  std::any accept(" << baseName << "Visitor& visitor)"
                " override {\n"
            "    return visitor.visit" << className << baseName <<
                "(shared_from_this());\n"
            "  }\n";
  writer << "\n";
  for (std::string_view field : fields) {
    writer << "  const " << fix_pointer(field) << ";\n";
  }
  writer << "};\n\n";
}
void defineAst(const std::string& outputDir, const std::string& baseName, const std::vector<std::string_view>& types) {
  std::string path = outputDir + "/" + baseName + ".h";
  std::ofstream writer{path};
  writer << "#pragma once\n"
            "\n"
            "#include <any>\n"
            "#include <memory>\n"
            "#include <utility>  // std::move\n"
            "#include <vector>\n"
            "#include \"Token.h\"\n"
            "\n";
  if (baseName == "Stmt") writer << "#include \"Expr.h\"\n";
  writer << "\n";
  for (std::string_view type : types) {
    std::string_view className = trim(split(type, ": ")[0]);
    writer << "struct " << className << ";\n";
  }
  writer << "\n";
  defineVisitor(writer, baseName, types);
  writer << "\n"
            "struct " << baseName << " {\n"
            "  virtual std::any accept(" << baseName <<
            "Visitor& visitor) = 0;\n"
            "};\n\n";
  for (std::string_view type : types) {
    std::string_view className = trim(split(type, ": ")[0]);
    std::string_view fields = trim(split(type, ": ")[1]);
    defineType(writer, baseName, className, fields);
  }
}
int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: SyntaxTreeGenerator <output directory>\n";
    std::exit(64);
  }
  std::string outputDir = argv[1];
  defineAst(outputDir, "Expr", {
    "Assign   : Token name, Expr* value",
    "Binary   : Expr* left, Token op, Expr* right",
    "Call     : Expr* callee, Token paren,"
              " std::vector<Expr*> arguments",
    "Get      : Expr* object, Token name",
    "Grouping : Expr* expression",
    "Literal  : std::any value",
    "Logical  : Expr* left, Token op, Expr* right",
    "Set      : Expr* object, Token name, Expr* value",
    "Super    : Token keyword, Token method",
    "This     : Token keyword",
    "Unary    : Token op, Expr* right",
    "Variable : Token name"
  });
  defineAst(outputDir, "Stmt", {
    "Block      : std::vector<Stmt*> statements",
    "Class      : Token name, Variable* superclass,"
                " std::vector<Function*> methods",
    "Expression : Expr* expression",
    "Function   : Token name, std::vector<Token> params,"
                " std::vector<Stmt*> body",
    "If         : Expr* condition, Stmt* thenBranch,"
                " Stmt* elseBranch",
    "Print      : Expr* expression",
    "Return     : Token keyword, Expr* value",
    "Var        : Token name, Expr* initializer",
    "While      : Expr* condition, Stmt* body"
  });
}

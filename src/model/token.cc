
#include "../model/token.h"

#include <cmath>
#include <string>

s21::Token::Token(std::string token_name, token_type token_type,
                  priority priority, std::function<double(double, double)> op)
    : token_name_(token_name),
      token_type_(token_type),
      priority_(priority),
      operator_(op) {}

std::string s21::Token::GetName() { return token_name_; }

s21::token_type s21::Token::GetTokenType() { return token_type_; }

s21::priority s21::Token::GetPriority() { return priority_; }

std::function<double(double, double)> s21::Token::GetOperator() {
  return operator_;
}

void s21::CreateTokenMap(std::map<std::string, s21::Token>& temp_map) {
  using namespace std;

  initializer_list<pair<const string, Token>> list = {
      {" ", Token(" ", kNumber, None, nullptr)},
      {"x", Token("x", kNumber, None, nullptr)},
      {"(", Token("(", kOpenBracket, None, nullptr)},
      {")", Token(")", kCloseBracket, None, nullptr)},
      {"+", Token("+", kOperator, Low, op2arg(+))},
      {"-", Token("-", kOperator, Low, op2arg(-))},
      {"*", Token("*", kOperator, Medium, op2arg(*))},
      {"/", Token("/", kOperator, Medium, op2arg(/))},
      {"~", Token("~", kUnaryOperator, Highest, op1arg(-))},
      {"^", Token("^", kOperator, High, f2arg(pow))},
      {"mod", Token("mod", kOperator, Medium, f2arg(fmod))},
      {"cos", Token("cos", kFunction, High, f1arg(cos))},
      {"sin", Token("sin", kFunction, High, f1arg(sin))},
      {"tan", Token("tan", kFunction, High, f1arg(tan))},
      {"acos", Token("acos", kFunction, High, f1arg(acos))},
      {"asin", Token("asin", kFunction, High, f1arg(asin))},
      {"atan", Token("atan", kFunction, High, f1arg(atan))},
      {"sqrt", Token("sqrt", kFunction, High, f1arg(sqrt))},
      {"ln", Token("ln", kFunction, High, f1arg(log))},
      {"log", Token("log", kFunction, High, f1arg(log10))},
  };
  temp_map.insert(list);
}
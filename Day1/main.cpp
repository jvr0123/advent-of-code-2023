#include <array>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string_view>

static const std::set<char> sValidTokens{'1', '2', '3', '4', '5',
                                         '6', '7', '8', '9'};
static const std::array<std::string, 9> sValidTokenStrings{
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
static const std::map<std::string, std::string> sStringLookup{
    {"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"}, {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"}};

// assume inputs are well-formed
int tokenizer(std::string_view source)
{
  auto left{source.cbegin()};
  auto right{source.crbegin()};

  // check if both keys are in the token set
  while (sValidTokens.count(*left) == 0 || sValidTokens.count(*right) == 0)
  {
    if (sValidTokens.count(*left) == 0)
      ++left;
    if (sValidTokens.count(*right) == 0)
      ++right;
  }

  std::string token{*left};
  token += *right;
  // std::cout << token << std::endl;
  return std::stoi(token);
}

std::string checkCollision(std::string_view str)
{
  for (auto token : sValidTokenStrings)
  {
    if (str.find(token) != std::string_view::npos)
    {
      return token;
    }
  }
  return "";
}
// assume inputs are well-formed
int stringTokenizer(std::string_view source)
{
  auto left{source.cbegin()};
  auto right{source.crbegin()};

  std::string leftSoFar{}, rightSoFar{};

  std::string leftResult{}, rightResult{};

  bool leftFound{false}, rightFound{false};

  // check if both keys are in the token set
  while (!leftFound || !rightFound)
  {

    leftSoFar += *left;
    if (checkCollision(leftSoFar) != "")
    {
      leftFound = true;
      leftResult = sStringLookup.at(checkCollision(leftSoFar));
    }
    else if (sValidTokens.count(*left) != 0 && !leftFound)
    {
      leftFound = true;
      leftResult = *left;
    }

    rightSoFar = *right + rightSoFar;
    if (checkCollision(rightSoFar) != "")
    {
      rightFound = true;
      rightResult = sStringLookup.at(checkCollision(rightSoFar));
    }
    else if (sValidTokens.count(*right) != 0 && !rightFound)
    {
      rightFound = true;
      rightResult = *right;
    }
    if (!leftFound)
      ++left;
    if (!rightFound)
      ++right;
  }

  std::string token = leftResult + rightResult;
  return std::stoi(token);
}

int main()
{
  std::fstream input("input");
  if (!input)
  {
    std::cerr << "Failed to open input file.\n";
    return 1;
  }
  std::string line{};
  int count1{}, count2{};

  while (getline(input, line))
  {
    count1 += tokenizer(line);
    count2 += stringTokenizer(line);
  }

  input.close();

  std::cout << std::format("{} : {}", "Part 1:", count1) << std::endl;
  std::cout << std::format("{} : {}", "Part 2:", count2) << std::endl;
}
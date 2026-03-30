#pragma once

#include <string>
#include <vector>

namespace Lexicon
{
namespace Core
{

class Tokenizer
{
public:
  static std::vector<std::string> tokenize(const std::string &text);
};

} // namespace Core
} // namespace Lexicon

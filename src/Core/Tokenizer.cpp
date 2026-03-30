#include "Lexicon/Core/Tokenizer.h"
#include <cctype>

namespace Lexicon
{
namespace Core
{

std::vector<std::string> Tokenizer::tokenize(const std::string &text)
{
  std::vector<std::string> tokens;
  std::string buf;

  for (char c : text)
  {
    if (std::isalnum(static_cast<unsigned char>(c)))
    {
      buf += std::tolower(static_cast<unsigned char>(c));
    }
    else
    {
      if (!buf.empty())
      {
        tokens.push_back(buf);
        buf.clear();
      }
    }
  }

  if (!buf.empty())
  {
    tokens.push_back(buf);
  }

  return tokens;
}

} // namespace Core
} // namespace Lexicon

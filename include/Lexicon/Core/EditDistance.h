#pragma once

#include <string>

namespace Lexicon
{
namespace Core
{

class EditDistance
{
public:
  static size_t calculate(const std::string &s1, const std::string &s2);
};

} // namespace Core
} // namespace Lexicon

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Lexicon
{
namespace Index
{

class KGramIndex
{
public:
  explicit KGramIndex(size_t k = 3);

  void addTerm(const std::string &term);

  std::vector<std::string> getTermsForKGram(const std::string &kgram) const;

  std::vector<std::string> generateKGrams(const std::string &str) const;

private:
  size_t k_;
  std::unordered_map<std::string, std::unordered_set<std::string>> index_;
};

} // namespace Index
} // namespace Lexicon

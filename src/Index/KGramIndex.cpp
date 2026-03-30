#include "Lexicon/Index/KGramIndex.h"

namespace Lexicon
{
namespace Index
{

KGramIndex::KGramIndex(size_t k)
    : k_(k)
{
}

void KGramIndex::addTerm(const std::string &term)
{
  std::vector<std::string> grams = generateKGrams(term);

  for (const auto &g : grams)
  {
    index_[g].insert(term);
  }
}

std::vector<std::string>
KGramIndex::getTermsForKGram(const std::string &kgram) const
{
  auto it = index_.find(kgram);

  if (it != index_.end())
  {
    return std::vector<std::string>(it->second.begin(), it->second.end());
  }

  return {};
}

std::vector<std::string> KGramIndex::generateKGrams(const std::string &str) const
{
  std::vector<std::string> res;
  std::string s = "$" + str + "$";

  if (s.length() < k_)
  {
    res.push_back(s);
    return res;
  }

  for (size_t i = 0; i <= s.length() - k_; ++i)
  {
    res.push_back(s.substr(i, k_));
  }

  return res;
}

} // namespace Index
} // namespace Lexicon

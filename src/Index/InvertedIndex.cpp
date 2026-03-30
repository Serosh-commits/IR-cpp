#include "Lexicon/Index/InvertedIndex.h"
#include "Lexicon/Core/Tokenizer.h"

#include <algorithm>

namespace Lexicon
{
namespace Index
{

void InvertedIndex::addDocument(DocID doc_id, const std::string &text)
{
  docs_[doc_id] = text;

  std::vector<std::string> tokens = Core::Tokenizer::tokenize(text);

  for (uint32_t pos = 0; pos < tokens.size(); ++pos)
  {
    const std::string &term = tokens[pos];
    auto &postings = dict_[term];

    if (postings.empty() || postings.back().doc_id != doc_id)
    {
      postings.push_back({doc_id, {pos}});
    }
    else
    {
      postings.back().positions.push_back(pos);
    }
  }
}

const PostingsList &InvertedIndex::getPostings(const std::string &term) const
{
  auto it = dict_.find(term);

  if (it != dict_.end())
  {
    return it->second;
  }

  return empty_;
}

DocIDList InvertedIndex::docids(const PostingsList &postings)
{
  DocIDList res;
  res.reserve(postings.size());

  for (const auto &p : postings)
  {
    res.push_back(p.doc_id);
  }

  return res;
}

std::string InvertedIndex::getDocumentText(DocID doc_id) const
{
  auto it = docs_.find(doc_id);

  if (it != docs_.end())
  {
    return it->second;
  }

  return "";
}

} // namespace Index
} // namespace Lexicon

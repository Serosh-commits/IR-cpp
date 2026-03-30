#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace Lexicon
{
namespace Index
{

using DocID = uint32_t;
using PositionList = std::vector<uint32_t>;

struct Posting
{
  DocID doc_id;
  PositionList positions;
};

using PostingsList = std::vector<Posting>;
using DocIDList = std::vector<DocID>;

class InvertedIndex
{
public:
  InvertedIndex() = default;

  void addDocument(DocID doc_id, const std::string &text);

  const PostingsList &getPostings(const std::string &term) const;

  static DocIDList docids(const PostingsList &postings);

  std::string getDocumentText(DocID doc_id) const;

  size_t getCorpusSize() const
  {
    return docs_.size();
  }

private:
  std::unordered_map<std::string, PostingsList> dict_;
  std::unordered_map<DocID, std::string> docs_;
  PostingsList empty_;
};

} // namespace Index
} // namespace Lexicon

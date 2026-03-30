#pragma once

#include "Lexicon/Index/InvertedIndex.h"

namespace Lexicon
{
namespace Index
{

class QueryProcessor
{
public:
  static DocIDList intersect(const DocIDList &p1, const DocIDList &p2);

  static DocIDList unionize(const DocIDList &p1, const DocIDList &p2);

  static DocIDList difference(const DocIDList &p1, const DocIDList &p2);

  static DocIDList phrase(const PostingsList &p1, const PostingsList &p2,
                         int dist = 1);
};

} // namespace Index
} // namespace Lexicon

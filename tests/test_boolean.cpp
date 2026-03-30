#include "Lexicon/Index/InvertedIndex.h"
#include "Lexicon/Index/QueryProcessor.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace Lexicon;

static void same(const Index::DocIDList &res, const Index::DocIDList &exp,
                 const std::string &name)
{
  if (res == exp)
  {
    std::cout << "[ok] " << name << "\n";
  }
  else
  {
    std::cout << "[fail] " << name << "\n";
    std::cout << "  exp: ";
    for (auto d : exp)
    {
      std::cout << d << " ";
    }
    std::cout << "\n  got: ";
    for (auto d : res)
    {
      std::cout << d << " ";
    }
    std::cout << "\n";
    assert(false);
  }
}

int main()
{
  Index::InvertedIndex idx;

  idx.addDocument(1, "apple banana cherry");
  idx.addDocument(2, "apple banana");
  idx.addDocument(3, "banana cherry");
  idx.addDocument(4, "cherry dates");

  idx.addDocument(5, "to be or not to be");
  idx.addDocument(6, "whether tis nobler in the mind");

  auto p_apple = idx.getPostings("apple");
  auto p_banana = idx.getPostings("banana");
  auto p_cherry = idx.getPostings("cherry");

  auto ids_apple = Index::InvertedIndex::docids(p_apple);
  auto ids_banana = Index::InvertedIndex::docids(p_banana);
  auto ids_cherry = Index::InvertedIndex::docids(p_cherry);

  same(Index::QueryProcessor::intersect(ids_apple, ids_banana), {1, 2}, "and");
  same(Index::QueryProcessor::unionize(ids_apple, ids_cherry), {1, 2, 3, 4},
       "or");
  same(Index::QueryProcessor::difference(ids_banana, ids_apple), {3}, "not");

  auto p_to = idx.getPostings("to");
  auto p_be = idx.getPostings("be");

  same(Index::QueryProcessor::phrase(p_to, p_be), {5}, "phrase");

  return 0;
}

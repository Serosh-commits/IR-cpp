#include "Lexicon/Core/Tokenizer.h"
#include "Lexicon/Index/InvertedIndex.h"
#include "Lexicon/Index/QueryProcessor.h"
#include <iostream>
#include <string>
#include <vector>

using namespace Lexicon;

static void show(const std::string &q, const Index::DocIDList &res,
                 const Index::InvertedIndex &idx)
{
  std::cout << "Query: " << q << "\n[" << res.size() << " results]\n";

  for (auto id : res)
  {
    std::cout << "  - doc " << id << ": " << idx.getDocumentText(id) << "\n";
  }

  std::cout << "---\n";
}

int main()
{
  Index::InvertedIndex idx;

  idx.addDocument(1, "Antony and Cleopatra");
  idx.addDocument(2, "Julius Caesar play document");
  idx.addDocument(3, "The Tempest play");
  idx.addDocument(4, "Hamlet by Shakespeare");

  idx.addDocument(7, "to be or not to be");
  idx.addDocument(8, "I want to be the best");
  idx.addDocument(9, "To run is not to be");

  auto p1 = idx.getPostings("to");
  auto p2 = idx.getPostings("be");

  auto ids1 = Index::InvertedIndex::docids(p1);
  auto ids2 = Index::InvertedIndex::docids(p2);

  show("to AND be", Index::QueryProcessor::intersect(ids1, ids2), idx);
  show("phrase \"to be\"", Index::QueryProcessor::phrase(p1, p2), idx);

  return 0;
}

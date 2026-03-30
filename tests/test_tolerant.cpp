#include "Lexicon/Core/EditDistance.h"
#include "Lexicon/Index/KGramIndex.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace Lexicon;

void test_edit()
{
  std::cout << "test_edit...\n";
  assert(Core::EditDistance::calculate("kitten", "sitting") == 3);
  assert(Core::EditDistance::calculate("flaw", "lawn") == 2);
  assert(Core::EditDistance::calculate("gumbo", "gambol") == 2);
}

void test_kgram()
{
  std::cout << "test_kgram...\n";
  Index::KGramIndex idx(3);
  idx.addTerm("castle");

  auto gs = idx.generateKGrams("castle");
  assert(gs.size() == 6);
  assert(gs[0] == "$ca");
  assert(gs[5] == "le$");

  auto ts = idx.getTermsForKGram("ast");
  assert(ts.size() == 1);
  assert(ts[0] == "castle");

  idx.addTerm("vast");
  ts = idx.getTermsForKGram("ast");
  assert(ts.size() == 2);
}

int main()
{
  test_edit();
  test_kgram();
  std::cout << "OK\n";
  return 0;
}

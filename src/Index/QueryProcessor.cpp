#include "Lexicon/Index/QueryProcessor.h"
#include <cmath>

namespace Lexicon
{
namespace Index
{

DocIDList QueryProcessor::intersect(const DocIDList &p1, const DocIDList &p2)
{
  DocIDList res;
  auto it1 = p1.begin();
  auto it2 = p2.begin();

  while (it1 != p1.end() && it2 != p2.end())
  {
    if (*it1 == *it2)
    {
      res.push_back(*it1);
      ++it1;
      ++it2;
    }
    else if (*it1 < *it2)
    {
      ++it1;
    }
    else
    {
      ++it2;
    }
  }

  return res;
}

DocIDList QueryProcessor::unionize(const DocIDList &p1, const DocIDList &p2)
{
  DocIDList res;
  auto it1 = p1.begin();
  auto it2 = p2.begin();

  while (it1 != p1.end() && it2 != p2.end())
  {
    if (*it1 == *it2)
    {
      res.push_back(*it1);
      ++it1;
      ++it2;
    }
    else if (*it1 < *it2)
    {
      res.push_back(*it1);
      ++it1;
    }
    else
    {
      res.push_back(*it2);
      ++it2;
    }
  }

  while (it1 != p1.end())
  {
    res.push_back(*it1);
    ++it1;
  }

  while (it2 != p2.end())
  {
    res.push_back(*it2);
    ++it2;
  }

  return res;
}

DocIDList QueryProcessor::difference(const DocIDList &p1, const DocIDList &p2)
{
  DocIDList res;
  auto it1 = p1.begin();
  auto it2 = p2.begin();

  while (it1 != p1.end() && it2 != p2.end())
  {
    if (*it1 == *it2)
    {
      ++it1;
      ++it2;
    }
    else if (*it1 < *it2)
    {
      res.push_back(*it1);
      ++it1;
    }
    else
    {
      ++it2;
    }
  }

  while (it1 != p1.end())
  {
    res.push_back(*it1);
    ++it1;
  }

  return res;
}

DocIDList QueryProcessor::phrase(const PostingsList &p1, const PostingsList &p2,
                                 int dist)
{
  DocIDList res;
  auto it1 = p1.begin();
  auto it2 = p2.begin();

  while (it1 != p1.end() && it2 != p2.end())
  {
    if (it1->doc_id == it2->doc_id)
    {
      auto pos1 = it1->positions.begin();
      auto pos2 = it2->positions.begin();
      bool found = false;

      while (pos1 != it1->positions.end() && pos2 != it2->positions.end())
      {
        if ((int)*pos2 - (int)*pos1 == dist)
        {
          found = true;
          break;
        }
        else if ((int)*pos2 > (int)*pos1 + dist)
        {
          ++pos1;
        }
        else
        {
          ++pos2;
        }
      }

      if (found)
      {
        res.push_back(it1->doc_id);
      }

      ++it1;
      ++it2;
    }
    else if (it1->doc_id < it2->doc_id)
    {
      ++it1;
    }
    else
    {
      ++it2;
    }
  }

  return res;
}

} // namespace Index
} // namespace Lexicon

#include "Lexicon/Core/EditDistance.h"
#include <algorithm>
#include <vector>

namespace Lexicon
{
namespace Core
{

size_t EditDistance::calculate(const std::string &s1, const std::string &s2)
{
  const size_t m = s1.length();
  const size_t n = s2.length();

  std::vector<std::vector<size_t>> d(m + 1, std::vector<size_t>(n + 1));

  for (size_t i = 0; i <= m; ++i)
  {
    d[i][0] = i;
  }

  for (size_t j = 0; j <= n; ++j)
  {
    d[0][j] = j;
  }

  for (size_t i = 1; i <= m; ++i)
  {
    for (size_t j = 1; j <= n; ++j)
    {
      const size_t cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

      d[i][j] = std::min({
          d[i - 1][j] + 1,
          d[i][j - 1] + 1,
          d[i - 1][j - 1] + cost,
      });
    }
  }

  return d[m][n];
}

} // namespace Core
} // namespace Lexicon

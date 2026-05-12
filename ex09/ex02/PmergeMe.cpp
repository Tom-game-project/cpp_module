#include "PmergeMe.hpp"
#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>
#include <deque>

// 配列を直接渡すだけ
// int pend = find_pend_value(my_pairs, 9);
template <typename PairContainer>
int find_pend_value(const PairContainer& pairs, int main_val) {
  for (typename PairContainer::const_iterator it = pairs.begin(); it != pairs.end(); ++it) {
    if (it->first == main_val) return it->second;
  }
  return -1;
}

// Container: 入力データの型 (例: std::vector<int>)
// PairContainer: ペアを格納する型 (例: std::vector<std::pair<int, int> >)
template <typename Container, typename PairContainer>
void build_pairs(const Container& input, PairContainer& pairs, int& straggler) {
  
  typename Container::const_iterator it = input.begin();

  while (it != input.end()) {
    typename Container::const_iterator next_it = it;
    ++next_it;

    if (next_it == input.end()) {
      straggler = *it;
      break;
    }

    if (*it > *next_it) {
      pairs.push_back(std::make_pair(*it, *next_it));
    } else {
      pairs.push_back(std::make_pair(*next_it, *it));
    }

    it = next_it;
    ++it;
  }
}

int jacobster(int i) {
  if (i == 0 || i == 1) {
    return i;
  } else {
    return jacobster(i - 1) + 2 * jacobster(i - 2);
  }
}

template <typename Container>
Container ford_johnson_sort(Container v) 
{
  if (v.size() <= 1) {
    return v;
  }

  std::vector<std::pair<int, int> > pairs;
  int straggler = -1;
  bool has_straggler = (v.size() % 2 != 0);

  build_pairs(v, pairs, straggler);

  Container main_chain;
  for (size_t i = 0; i < pairs.size(); ++i) {
    main_chain.push_back(pairs[i].first);
  }

  Container sorted_main = ford_johnson_sort(main_chain);

  Container pend;
  for (size_t i = 0; i < sorted_main.size(); ++i) {
    int partner = find_pend_value(pairs, sorted_main[i]);
    pend.push_back(partner);
  }

  Container paired_main = sorted_main;

  if (!pend.empty()) {
    sorted_main.insert(sorted_main.begin(), pend[0]);
  }

  int prev_jacob = 1;
  int k = 3;

  while (prev_jacob < static_cast<int>(pend.size())) {
    int curr_jacob = jacobster(k);
    
    int max_idx = std::min(curr_jacob, static_cast<int>(pend.size())) - 1;

    for (int i = max_idx; prev_jacob <= i; --i) {
      int target = pend[static_cast<std::size_t>(i)];
      int partner_val = paired_main[static_cast<std::size_t>(i)];

      typename Container::iterator partner_it = std::find(sorted_main.begin(), sorted_main.end(), partner_val);

      typename Container::iterator insert_pos = std::lower_bound(sorted_main.begin(), partner_it, target);

      sorted_main.insert(insert_pos, target);
    }
    
    prev_jacob = curr_jacob;
    k++;
  }

  if (has_straggler) {
    typename Container::iterator pos = std::lower_bound(sorted_main.begin(), sorted_main.end(), straggler);
    sorted_main.insert(pos, straggler);
  }

  return sorted_main;
}

template std::vector<int> ford_johnson_sort<std::vector<int> >(std::vector<int>);
template std::deque<int> ford_johnson_sort<std::deque<int> >(std::deque<int>);

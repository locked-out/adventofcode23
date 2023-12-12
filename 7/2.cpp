#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

#define HAND_SIZE 5
#define N_VALUES 13

typedef struct hand {
  int most_common;
  int second_most;
  int hand[HAND_SIZE];
} hand_t;

bool operator < (const hand &a, const hand &b) {
  if (a.most_common != b.most_common) return a.most_common < b.most_common;
  if (a.second_most != b.second_most) return a.second_most < b.second_most;
  for (int i = 0; i < HAND_SIZE; i++) {
    if (a.hand[i] != b.hand[i]) return a.hand[i] < b.hand[i];
  }

  return false;
}

int get_card_value(const char c) {
  switch (c) {
    case 'J':
      return 0;
    case 'T':
      return 9;
    case 'Q':
      return 10;
    case 'K':
      return 11;
    case 'A':
      return 12;
    default:
      return c - '1';
  }
}

hand_t read_hand(const std::string &s) {
  hand_t hand;

  std::vector<int> card_frequencies(N_VALUES);
  int jokers = 0;

  for (int i = 0; i < HAND_SIZE; i++) {
    int value = get_card_value(s[i]);
    if (value == 0) {
      // Joker card
      jokers++;
    } else {
      card_frequencies[value]++;
    }
    hand.hand[i] = value;
  }

  std::sort(card_frequencies.begin(), card_frequencies.end(), std::greater<>());
  
  hand.most_common = card_frequencies[0] + jokers;
  hand.second_most = card_frequencies[1];

  return hand;
}

int main (int argc, char *argv[]) {
  std::string hand_string;
  int bid;

  std::vector<std::pair<hand_t, int>> hands;

  while (std::cin >> hand_string) {
    hand_t hand = read_hand(hand_string);
    std::cin >> bid;

    hands.push_back(std::make_pair(hand, bid));
  }

  std::sort(hands.begin(), hands.end());

  int ans = 0;

  int rank = 1;
  for (auto [_, bid] : hands) {
    ans += rank * bid;
    rank++;
  }
  
  std::cout << ans << '\n';

  return 0;
}


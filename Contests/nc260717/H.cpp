#include <array>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {

constexpr int TYPES = 3;
constexpr int HAND_COUNT = 10;
constexpr int STATE_COUNT = HAND_COUNT * HAND_COUNT;
constexpr int LIMIT = 1000;
constexpr int AVERAGE_WINDOW = 100;

using Hand = std::array<int, TYPES>;
using Values = std::array<long double, STATE_COUNT>;

int card_id(char card) {
    if (card == 'R') {
        return 0;
    }
    if (card == 'S') {
        return 1;
    }
    return 2;
}

int score(int alice, int bob) {
    if (alice == bob) {
        return 1;
    }
    return (alice + 1) % TYPES == bob ? 3 : 0;
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::array<Hand, HAND_COUNT> hands{};
    int hand_id[4][4][4];
    for (auto &plane : hand_id) {
        for (auto &row : plane) {
            for (int &value : row) {
                value = -1;
            }
        }
    }

    int hand_count = 0;
    for (int rock = 0; rock <= 3; ++rock) {
        for (int scissors = 0; rock + scissors <= 3; ++scissors) {
            const int paper = 3 - rock - scissors;
            hands[hand_count] = {rock, scissors, paper};
            hand_id[rock][scissors][paper] = hand_count++;
        }
    }

    int next_hand[HAND_COUNT][TYPES][TYPES]{};
    for (int h = 0; h < HAND_COUNT; ++h) {
        for (int played = 0; played < TYPES; ++played) {
            if (hands[h][played] == 0) {
                continue;
            }
            for (int drawn = 0; drawn < TYPES; ++drawn) {
                Hand next = hands[h];
                --next[played];
                ++next[drawn];
                next_hand[h][played][drawn] =
                    hand_id[next[0]][next[1]][next[2]];
            }
        }
    }

    std::vector<Values> dp(LIMIT + 1);
    dp[0].fill(0);

    for (int round = 1; round <= LIMIT; ++round) {
        const Values &previous = dp[round - 1];
        Values &current = dp[round];

        for (int alice_hand = 0; alice_hand < HAND_COUNT; ++alice_hand) {
            for (int bob_hand = 0; bob_hand < HAND_COUNT; ++bob_hand) {
                long double best = -std::numeric_limits<long double>::infinity();

                for (int alice_card = 0; alice_card < TYPES; ++alice_card) {
                    if (hands[alice_hand][alice_card] == 0) {
                        continue;
                    }

                    long double worst =
                        std::numeric_limits<long double>::infinity();
                    for (int bob_card = 0; bob_card < TYPES; ++bob_card) {
                        if (hands[bob_hand][bob_card] == 0) {
                            continue;
                        }

                        long double expected_future = 0;
                        for (int alice_draw = 0; alice_draw < TYPES; ++alice_draw) {
                            const int next_alice =
                                next_hand[alice_hand][alice_card][alice_draw];
                            for (int bob_draw = 0; bob_draw < TYPES; ++bob_draw) {
                                const int next_bob =
                                    next_hand[bob_hand][bob_card][bob_draw];
                                expected_future +=
                                    previous[next_alice * HAND_COUNT + next_bob];
                            }
                        }

                        const long double value =
                            score(alice_card, bob_card) + expected_future / 9;
                        if (value < worst) {
                            worst = value;
                        }
                    }

                    if (worst > best) {
                        best = worst;
                    }
                }

                current[alice_hand * HAND_COUNT + bob_hand] = best;
            }
        }
    }

    long double average_score = 0;
    for (int state = 0; state < STATE_COUNT; ++state) {
        average_score +=
            (dp[LIMIT][state] - dp[LIMIT - AVERAGE_WINDOW][state]) /
            AVERAGE_WINDOW;
    }
    average_score /= STATE_COUNT;

    int test_count;
    std::cin >> test_count;
    std::cout << std::fixed << std::setprecision(12);

    while (test_count--) {
        long long k;
        std::string alice_cards, bob_cards;
        std::cin >> k >> alice_cards >> bob_cards;

        Hand alice{};
        Hand bob{};
        for (char card : alice_cards) {
            ++alice[card_id(card)];
        }
        for (char card : bob_cards) {
            ++bob[card_id(card)];
        }

        const int alice_index = hand_id[alice[0]][alice[1]][alice[2]];
        const int bob_index = hand_id[bob[0]][bob[1]][bob[2]];
        const int state = alice_index * HAND_COUNT + bob_index;

        long double answer;
        if (k <= LIMIT) {
            answer = dp[static_cast<int>(k)][state];
        } else {
            answer = dp[LIMIT][state] + (k - LIMIT) * average_score;
        }
        std::cout << answer << '\n';
    }

    return 0;
}

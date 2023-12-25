#include "ip_filter.hpp"

#include <gtest/gtest.h>

TEST(Google_test, test_version) {
	EXPECT_GT(version(), 0);
}

TEST(Google_test, test_sort) {
  std::vector<std::vector<int>> case_1 =     {{1, 2, 3, 0},
                                              {1, 2, 3, 4}};
  std::vector<std::vector<int>> case_1_exp = {{1, 2, 3, 4},
                                              {1, 2, 3, 0}};
  std::vector<std::vector<int>> case_2 =     {{1, 2, 3, 4},
                                              {10, 25, 3, 4}};
  std::vector<std::vector<int>> case_2_exp = {{10, 25, 3, 4},
                                              {1, 2, 3, 4}};
  reverse_lexicographically_sort(case_1);
  EXPECT_EQ(case_1, case_1_exp);

  reverse_lexicographically_sort(case_2);
  EXPECT_EQ(case_2, case_2_exp);
}

TEST(Google_test, test_filter_1) {
  std::vector<std::vector<int>> case_1 =     {{1, 2, 3, 4},
                                              {10, 2, 3, 4},
                                              {100, 2, 3, 4}};
  std::vector<std::vector<int>> case_1_exp = {{1, 2, 3, 4}};

  auto case_1_res = filter(case_1, 1);
  EXPECT_EQ(case_1_res, case_1_exp);
}

TEST(Google_test, test_filter_2) {
  std::vector<std::vector<int>> case_1 =     {{1, 2, 3, 4},
                                              {10, 2, 3, 4},
                                              {100, 2, 3, 4}};
  std::vector<std::vector<int>> case_1_exp = {{10, 2, 3, 4}};

  auto case_1_res = filter(case_1, 10, 2, 3);
  EXPECT_EQ(case_1_res, case_1_exp);
}

TEST(Google_test, test_filter_any) {
  std::vector<std::vector<int>> case_1 =     {{1, 2, 3, 4},
                                              {10, 2, 3, 4},
                                              {100, 2, 3, 4}};
  std::vector<std::vector<int>> case_1_exp = {{100, 2, 3, 4}};

  auto case_1_res = filter_any(case_1, 100);
  EXPECT_EQ(case_1_res, case_1_exp);
}
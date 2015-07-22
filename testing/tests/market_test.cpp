#include "gtest/gtest.h"
#include "market.h"

// Tests the market state.
TEST(Market, DefaultState) {
  Ruleset * r = new Ruleset(Ruleset::DEFAULT);
  Market s={std::shared_ptr<Ruleset>(r)};

  // check state is Ruleset::DEFAULT.market_state
  //
  // <TechnicalDetails>
  //
  // </TechnicalDetails>
  EXPECT_EQ(Ruleset::DEFAULT.market_state, s._state);

  // Проверить, что состояние меняется в соотв. с таблицей вероятностей
  //
  // <TechnicalDetails>
  //
  // </TechnicalDetails>
  int states[6]={};
#define NUM_TESTS 10000
  for (int i=0;i<NUM_TESTS;++i) {
    s._state=0;
    s.changeState();
    states[s._state]++;
  }
  EXPECT_GE(NUM_TESTS*r->market_state_matrix[0][0], states[0])<<"States are="<<states[0]<<","<<states[1]<<","<<states[2]<<","<<states[3]<<","<<states[4]<<","<<states[5];
}
/*
const char kHelloString[] = "Hello, world!";

// Tests the c'tor that accepts a C string.
TEST(MyString, ConstructorFromCString) {
  const MyString s(kHelloString);
  EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));
  EXPECT_EQ(sizeof(kHelloString)/sizeof(kHelloString[0]) - 1,
            s.Length());
}

// Tests the copy c'tor.
TEST(MyString, CopyConstructor) {
  const MyString s1(kHelloString);
  const MyString s2 = s1;
  EXPECT_EQ(0, strcmp(s2.c_string(), kHelloString));
}

// Tests the Set method.
TEST(MyString, Set) {
  MyString s;

  s.Set(kHelloString);
  EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));

  // Set should work when the input pointer is the same as the one
  // already in the MyString object.
  s.Set(s.c_string());
  EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));

  // Can we set the MyString to NULL?
  s.Set(NULL);
  EXPECT_STREQ(NULL, s.c_string());
}
*/

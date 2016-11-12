
#include "gtest/gtest.h"
#include "Observer.hpp"

#include <sstream>
#include <iostream>

std::stringstream cout;

class Listener : public IObserver
{
  std::string m_n;
public:
  Listener(std::string n) : m_n(n) {}
  void SendMessage(MessageHandler const & msg) override
  {
    cout << "Listener " << m_n << "; ";
    msg();
  }

  std::size_t hash() const override
  {
    return std::hash<std::string>()(m_n);
  }
  bool operator==(IObserver const & b) override
  {
    if (hash() == b.hash()) return true;
    return false;
  }
};


TEST(Observer_test, listener)
{
  Listener l1("One");
  Listener l2("two");
  Listener l3("One");

  EXPECT_EQ(l1 == l2, false);
  EXPECT_EQ(l1 == l3, true);
}

TEST(Observer_test, disp)
{
  auto l1 = std::make_shared<Listener>("One");
  auto l2 = std::make_shared<Listener>("two");
  Dispatcher disp;

  disp.Subscribe(l1);
  disp.Subscribe(l1);
  disp.Subscribe(l2);

  disp.SendMessage([]() {cout << "wowowowow ";});

  disp.Unsubscribe(l1);
  disp.Unsubscribe(l2);
  disp.Unsubscribe(l2);

  EXPECT_EQ(cout.str(), "Listener One; wowowowow Listener two; wowowowow ");
}

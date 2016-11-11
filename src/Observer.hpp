#pragma once

#include <functional>
#include <list>
#include <algorithm>
#include <memory>
#include <string>

using MessageHandler = std::function<void()>;

class IObserver // Subscriber
{
public:
  virtual ~IObserver() {}
  virtual void SendMessage(MessageHandler const &) = 0;
  virtual bool operator==(IObserver const &) = 0;
  virtual std::size_t hash() const = 0;
};

using ObserverPtr = std::shared_ptr<IObserver>;

class Dispatcher
{
public:
  void Subscribe(ObserverPtr const & newSubscriber)
  {
    auto it = std::find(m_subscriberList.begin(), m_subscriberList.end(), newSubscriber);
    if (it == m_subscriberList.end())
      m_subscriberList.push_back(newSubscriber);
  }

  void Unsubscribe(ObserverPtr const & subscriber)
  {
    auto it = std::find(m_subscriberList.begin(), m_subscriberList.end(), subscriber);
    if (it != m_subscriberList.end())
      m_subscriberList.erase(it);
  }

  void SendMessage(MessageHandler const & msg)
  {
    for (auto const & i : m_subscriberList)
      i->SendMessage(msg);
  }
protected:
  // вот я думаю, или использовать std::vector<std::reference_wrapper<IObserver>> 
  std::list<ObserverPtr> m_subscriberList;
};
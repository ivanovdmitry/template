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
  virtual void SendMessage(MessageHandler) = 0;
  virtual bool operator==(IObserver &) = 0;
  virtual std::size_t hash() = 0;
};

using ObserverPtr = std::shared_ptr<IObserver>;

class Dispatcher
{
public:
  void Subscribe(ObserverPtr const & newSubscriber)
  {
    for (auto it = std::begin(m_subscriberList); it != std::end(m_subscriberList); ++it)
    {
      if (*it == newSubscriber)
        return;
    }
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
    for (auto const i : m_subscriberList)
      i->SendMessage(msg);
  }
protected:
  // вот я думаю, или использовать std::vector<std::reference_wrapper<IObserver>> 
  std::list<ObserverPtr> m_subscriberList;
};
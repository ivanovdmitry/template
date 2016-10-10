#pragma once

class IGameObject 
{
public:
  virtual ~IGameObject() = default;
  virtual void UpDate() = 0;
};
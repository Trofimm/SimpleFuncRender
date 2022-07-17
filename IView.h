#pragma once

class IViewport // Interface for viewport
{
public:
  virtual ~IViewport() = default;

  virtual void Draw() = 0;
};
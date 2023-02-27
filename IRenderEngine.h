#pragma once


class IRenderEngine // Interface for rendering engines
{
public:
  virtual ~IRenderEngine() = default;

  virtual void Render() = 0;
};
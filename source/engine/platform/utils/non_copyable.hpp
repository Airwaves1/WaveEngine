#pragma once

namespace Wave
{

class NonCopyable
{
  public:
     NonCopyable() = default;

  private:
    NonCopyable(const NonCopyable &)            = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;
};
} // namespace Wave
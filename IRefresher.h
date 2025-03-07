#pragma once
#include <chrono>
#include <thread>
#include <time.h>

class IRefresher
{
  public:
    virtual ~IRefresher() = default;
    virtual void refresh() = 0;
};

class TimeRefresher : public IRefresher
{
  private:
    float _refreshRate = 1000;

  public:
    TimeRefresher(float refreshRate)
    {
        _refreshRate = refreshRate;
    }
    void refresh() {
        // wait before next cycle. cycle repeats every 1/refreshRate seconds or one refreshRate amount at a second
        std::this_thread::sleep_for(std::chrono::milliseconds(int(1000 / _refreshRate)));
    }
};

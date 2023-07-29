

#include <cstdlib>
#include <iostream>
#include <mutex>

#include <gtest/gtest.h>

#include "event_system_async.hpp"

namespace {
// NOLINTNEXTLINE
static std::unordered_map<std::string, int> called{};
}  // namespace

// NOLINTNEXTLINE
static std::mutex mutex;

namespace {
void addCall(const std::string& call) {
  std::unique_lock lock{mutex};
  if (called.find(call) == called.end()) {
    called[call] = 1;
  } else {
    called[call] += 1;
  }
}
}  // namespace

struct TestEvent {
  int  integer;
  char character;
};

TEST(AsyncEvents, Test) {
  pllama::EventSystem_Async<TestEvent> sut{4};

  sut.on<TestEvent>([](const TestEvent& event) {
    EXPECT_EQ(event.integer, 1);
    EXPECT_EQ(event.character, 'c');
    addCall("handler1");
  });

  sut.on<TestEvent>([](const TestEvent& event) {
    EXPECT_EQ(event.integer, 1);
    EXPECT_EQ(event.character, 'c');
    addCall("handler2");
  });

  sut.on<TestEvent>([](const TestEvent& event) {
    EXPECT_EQ(event.integer, 1);
    EXPECT_EQ(event.character, 'c');
    addCall("handler3");
  });

  sut.on<TestEvent>([](const TestEvent& event) {
    EXPECT_EQ(event.integer, 1);
    EXPECT_EQ(event.character, 'c');
    addCall("handler4");
  });

  sut.emit<TestEvent>({1, 'c'});

  sleep(1);

  EXPECT_EQ(called["handler1"], 1);
  EXPECT_EQ(called["handler2"], 1);
  EXPECT_EQ(called["handler3"], 1);
  EXPECT_EQ(called["handler4"], 1);

  sut.wait_shutdown();
}
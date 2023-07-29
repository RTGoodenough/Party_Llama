
#include <gtest/gtest.h>
#include <unordered_map>

#include "event_system_immediate.hpp"

namespace {
// NOLINTNEXTLINE
static std::unordered_map<std::string, int> called{};
}  // namespace

namespace {
void addCall(const std::string& call) {
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

struct AnotherEvent {
  std::string str;
};

struct ThirdEvent {
  bool boolean;
};

TEST(ImmediateEvents, CallbacksFire) {
  called.clear();
  pllama::EventSystem_Immediate<TestEvent> sut;

  auto test1 = [](const TestEvent& event) {
    EXPECT_EQ(event.integer, 1);
    EXPECT_EQ(event.character, 'c');
    addCall("lambda");
  };

  sut.on<TestEvent>(test1);

  sut.emit(TestEvent{1, 'c'});

  EXPECT_EQ(called["lambda"], 1);
}

void testFunc(const TestEvent& event) {
  EXPECT_EQ(event.integer, 1);
  EXPECT_EQ(event.character, 'c');
  called["function"] = 1;
}

TEST(ImmediateEvents, DifferentCallbackTypes) {
  called.clear();

  pllama::EventSystem_Immediate<TestEvent> sut;

  auto lambda = [](const TestEvent& event) {
    EXPECT_EQ(event.integer, 1);
    EXPECT_EQ(event.character, 'c');
    addCall("lambda");
  };

  //NOLINTNEXTLINE
  int  capture = 5;
  auto captureLambda = [capture](const TestEvent& event) {
    EXPECT_EQ(event.integer, 1);
    EXPECT_EQ(capture, 5);
    EXPECT_EQ(event.character, 'c');
    addCall("capture_lambda");
  };

  struct Functor {
    void operator()(const TestEvent& event) {
      EXPECT_EQ(event.integer, 1);
      EXPECT_EQ(event.character, 'c');
      addCall("functor");
    }
  };

  Functor testFunctor{};

  sut.on<TestEvent>(lambda);
  sut.on<TestEvent>(captureLambda);
  sut.on<TestEvent>(Functor{});
  sut.on<TestEvent>(testFunctor);
  sut.on<TestEvent>(testFunc);

  sut.emit<TestEvent>({1, 'c'});

  EXPECT_EQ(called["functor"], 2);
  EXPECT_EQ(called["lambda"], 1);
  EXPECT_EQ(called["capture_lambda"], 1);
  EXPECT_EQ(called["function"], 1);
}

TEST(ImmediateEvents, MultipleEventTypes) {
  pllama::EventSystem_Immediate<TestEvent, AnotherEvent, ThirdEvent> sut;

  auto testEventCB = [](const TestEvent& event) {
    EXPECT_EQ(event.integer, 1);
    EXPECT_EQ(event.character, 'c');
    addCall("testEvent");
  };

  auto anotherEventCB = [](const AnotherEvent& event) {
    EXPECT_EQ(event.str, "test");
    addCall("anotherEvent");
  };

  auto thirdEventCB = [](const ThirdEvent& event) {
    EXPECT_EQ(event.boolean, true);
    addCall("thirdEvent");
  };

  sut.on<TestEvent>(testEventCB);
  sut.on<AnotherEvent>(anotherEventCB);
  sut.on<ThirdEvent>(thirdEventCB);

  sut.emit<TestEvent>({1, 'c'});
  EXPECT_EQ(called["testEvent"], 1);
  EXPECT_EQ(called["anotherEvent"], 0);
  EXPECT_EQ(called["thirdEvent"], 0);

  sut.emit<AnotherEvent>({"test"});
  EXPECT_EQ(called["testEvent"], 1);
  EXPECT_EQ(called["anotherEvent"], 1);
  EXPECT_EQ(called["thirdEvent"], 0);

  sut.emit<ThirdEvent>({true});
  EXPECT_EQ(called["testEvent"], 1);
  EXPECT_EQ(called["anotherEvent"], 1);
  EXPECT_EQ(called["thirdEvent"], 1);

  sut.emit<AnotherEvent>({"test"});
  EXPECT_EQ(called["testEvent"], 1);
  EXPECT_EQ(called["anotherEvent"], 2);
  EXPECT_EQ(called["thirdEvent"], 1);
}

TEST(ImmediateEvents, RemoveCallback) {
  pllama::EventSystem_Immediate<TestEvent> sut;

  auto testEventCB1 = [](const TestEvent& event) {
    EXPECT_EQ(event.integer, 1);
    EXPECT_EQ(event.character, 'c');
    addCall("testEvent1");
  };

  auto testEventCB2 = [](const TestEvent& event) {
    EXPECT_EQ(event.integer, 1);
    EXPECT_EQ(event.character, 'c');
    addCall("testEvent2");
  };

  auto id1 = sut.on<TestEvent>(testEventCB1);
  auto id2 = sut.on<TestEvent>(testEventCB2);

  sut.emit<TestEvent>({1, 'c'});

  EXPECT_EQ(called["testEvent1"], 1);
  EXPECT_EQ(called["testEvent2"], 1);

  sut.remove<TestEvent>(id1);

  sut.emit<TestEvent>({1, 'c'});

  EXPECT_EQ(called["testEvent1"], 1);
  EXPECT_EQ(called["testEvent2"], 2);
}
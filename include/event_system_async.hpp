#ifndef PARTY_LLAMA_EVENT_SYSTEM_ASYNC_HPP
#define PARTY_LLAMA_EVENT_SYSTEM_ASYNC_HPP

#include "event_queue.hpp"

namespace pllama {
/**
 * @brief Event system for queuing events and handling them asynchronously
 * 
 * @tparam e_types : types of events
 */
template <typename... e_types>
class EventSystem_Async {
 public:
 private:
  EventQueue<e_types...> _queue;
};
}  // namespace pllama

#endif
#ifndef PARTY_LLAMA_EVENT_SYSTEM_IMMEDIATE_HPP
#define PARTY_LLAMA_EVENT_SYSTEM_IMMEDIATE_HPP

#include <pstl/glue_algorithm_defs.h>
#include <functional>
#include <tuple>
#include <type_traits>
#include <vector>

#include "concepts.hpp"
#include "event.hpp"

/*
ISSUES:

1. Callbacks for different event types may have the same cb_UID


*/

namespace pllama {
/**
 * @brief Event system for handling events synchronously as they occur
 * 
 * @tparam e_types : Types of events
 */
template <typename... e_types>
class EventSystem_Immediate {
 public:
  /**
   * @brief Calls all callbacks for a given event type
   * 
   * @tparam e_type : event data type
   * @param data : event data
   */
  template <typename e_type, typename = std::enable_if<inTypeList<e_type, e_types...>()>>
  void emit(const e_type& data) {
    auto& cbs = get_callbacks<e_type>();
    for (auto& callback : cbs) {
      callback(data);
    }
  }

  /**
   * @brief Adds a new callback function to an event 
   *
   * @tparam e_type : event type
   * @param callback : callback function
   * @return cb_UID : id of callback
   */
  template <typename e_type, typename = std::enable_if<inTypeList<e_type, e_types...>()>>
  auto on(Callback<e_type>&& callback) -> cb_UID {
    auto& callbacks = get_callbacks<e_type>();
    callbacks.emplace_back(callback);
    return callbacks.size() - 1;
  }

  /**
   * @brief Removes a callback for an event
   * 
   * @tparam e_type : event type
   * @param cb_id : callback id
   */
  template <typename e_type, typename = std::enable_if<inTypeList<e_type, e_types...>()>>
  auto remove(cb_UID cb_id) -> bool {
    auto& callbacks = get_callbacks<e_type>();

    if (cb_id >= callbacks.size()) return false;

    callbacks.erase(callbacks.begin() + cb_id);
    return true;
  }

 private:
  std::tuple<Callback_Vec<e_types>...> _callbacks;

  /**
   * @brief Gets the vector of callbacks for an event type
   * 
   * @tparam e_type : event type
   * @return Callback_Vec<e_type>& : callbacks vector
   */
  template <typename e_type>
  auto get_callbacks() -> Callback_Vec<e_type>& {
    return std::get<Callback_Vec<e_type>>(_callbacks);
  }

 public:
  EventSystem_Immediate() = default;
  ~EventSystem_Immediate() = default;
  EventSystem_Immediate(const EventSystem_Immediate&) = default;
  EventSystem_Immediate(EventSystem_Immediate&&) noexcept = default;
  auto operator=(const EventSystem_Immediate&) -> EventSystem_Immediate& = default;
  auto operator=(EventSystem_Immediate&&) noexcept -> EventSystem_Immediate& = default;
};
}  // namespace pllama

#endif
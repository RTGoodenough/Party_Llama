#ifndef PARTY_LLAMA_EVENT_QUEUE_HPP
#define PARTY_LLAMA_EVENT_QUEUE_HPP

#include <optional>
#include <queue>

namespace pllama {
template <typename... e_types>
class EventQueue {
 public:
  /**
   * @brief Adds a new event to the queue
   *
   * @tparam e_type : event data type
   * @param event : event data
   */
  template <typename e_type>
  static void add_event(e_type &&event) {
    std::queue<e_type> &queue = get_queue<e_type>();
    queue.push(std::forward<e_type>(event));
  }

  /**
   * @brief Gets event data off of the queue
   *
   * @tparam e_type : event data type
   * @return std::optional<e_type> : event data, nullopt if no event on queue
   */
  template <typename e_type>
  static auto get_event() -> std::optional<e_type> {
    std::queue<e_type> &queue = get_queue<e_type>();
    if (queue.empty()) return std::nullopt;

    return queue.pop();
  }

 private:
  // NOLINTNEXTLINE (cppcoreguidelines-avoid-non-const-global-variables) Bug in clang-tidy (https://bugs.llvm.org/show_bug.cgi?id=48040)
  static std::tuple<std::queue<e_types>...> _queues;

  /**
   * @brief Returns the queue for the given event type
   *
   * @tparam e_type : event data type
   * @return std::queue<e_type>& : queue for event type
   */
  template <typename e_type>
  static inline auto get_queue() -> std::queue<e_type> & {
    return std::get<std::queue<e_type>>(_queues);
  }

 public:
  EventQueue() = default;
  ~EventQueue() = default;
  EventQueue(const EventQueue &) = default;
  EventQueue(EventQueue &&) noexcept = default;
  auto operator=(const EventQueue &) -> EventQueue & = default;
  auto operator=(EventQueue &&) noexcept -> EventQueue & = default;
};
}  // namespace pllama

#endif
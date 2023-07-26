#ifndef PARTY_LLAMA_CALLBACK_HPP
#define PARTY_LLAMA_CALLBACK_HPP

#include <cstdint>
#include <functional>

namespace pllama {
template <typename e_type>
using Callback = std::function<void(const e_type&)>;

using cb_UID = uint64_t;
using hn_UID = uint64_t;

template <typename e_type>
struct CB {
  uint64_t                           id;
  std::function<void(const e_type&)> cb;
};

template <typename e_type>
using Callback_Vec = std::vector<CB<e_type>>;
}  // namespace pllama

#endif
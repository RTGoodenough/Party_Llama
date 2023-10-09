/**
 * @file event.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-09
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of Party Llama which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef PARTY_LLAMA_EVENT_HPP
#define PARTY_LLAMA_EVENT_HPP

#include <cstdint>
#include <functional>

namespace pllama {
template <typename e_type>
using Handler = std::function<void(const e_type&)>;

template <typename e_type>
using Handler_Vec = std::vector<Handler<e_type>>;

using cb_UID = uint64_t;
using hn_UID = uint64_t;

}  // namespace pllama

#endif
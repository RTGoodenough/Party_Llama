/**
 * @file concepts.hpp
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

#ifndef PARTY_LLAMA_CONCEPTS_HPP
#define PARTY_LLAMA_CONCEPTS_HPP

#include <type_traits>
#include <typeinfo>

/**
 * @brief Returns if the given type is in a variadic parameter pack
 * 
 * @tparam e - type to find in pack
 * @tparam e_list - list to search
 * @return true - if in pack
 * @return false - if not in pack
 */
template <typename e, typename... e_list>
constexpr auto inTypeList() -> bool {
  constexpr bool INLIST = (std::is_same_v<e, e_list> || ...);
  static_assert(INLIST, "Event Type: Not A Part of Valid Components");
  return INLIST;
}

#endif
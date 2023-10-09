/**
 * @file work.hpp
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

#ifndef PARTY_LLAMA_WORK_HPP
#define PARTY_LLAMA_WORK_HPP

#include <functional>
#include <memory>

namespace pllama {

struct Work {
  virtual void run() = 0;

  Work(const Work&) = default;
  Work(Work&&) = default;
  auto operator=(const Work&) -> Work& = default;
  auto operator=(Work&&) -> Work& = default;
  Work() = default;
  virtual ~Work() = default;
};

template <typename d_type>
struct Task : public Work {
  Task(std::function<void(const d_type&)>& work, std::shared_ptr<d_type>& data) : _work(work), _data(data) {}

  std::function<void(const d_type&)> _work;
  std::shared_ptr<d_type>            _data;

  /**
   * @brief Runs the task with the provided data
   * 
   */
  void run() override { _work(*_data.get()); }
};
}  // namespace pllama

#endif
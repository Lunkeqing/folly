/*
 * Copyright 2018-present Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <memory>

#include <folly/fibers/FiberManagerInternal.h>
#include <folly/fibers/LoopController.h>
#include <folly/python/AsyncioExecutor.h>

namespace folly {
namespace python {

class AsyncioLoopController : public fibers::LoopController {
 public:
  explicit AsyncioLoopController(AsyncioExecutor* executor);
  ~AsyncioLoopController() override;

 private:
  // TODO: KeepAlive token to guarantee lifetime
  AsyncioExecutor* executor_;
  fibers::FiberManager* fm_{nullptr};

  void setFiberManager(fibers::FiberManager* fm) override;
  void schedule() override;
  void runLoop() override;
  void scheduleThreadSafe() override;
  void timedSchedule(std::function<void()> func, TimePoint time) override;

  friend class fibers::FiberManager;
};

} // namespace python
} // namespace folly

#include <folly/python/AsyncioLoopController-inl.h>

/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include <span>

#include "roq/service.hpp"

namespace roq {
namespace bridge {
namespace redis {

// application

class Application final : public Service {
 public:
  using Service::Service;

 protected:
  int main_helper(std::span<std::string_view> const &args);
  int main(int argc, char **argv) override;
};

}  // namespace redis
}  // namespace bridge
}  // namespace roq

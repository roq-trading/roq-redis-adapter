/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/adapter/redis/application.hpp"

using namespace std::literals;

namespace {
auto const DESCRIPTION = "Roq Redis Adapter"sv;
}  // namespace

int main(int argc, char **argv) {
  return roq::adapter::redis::Application(
             argc,
             argv,
             {
                 .description = DESCRIPTION,
                 .package_name = ROQ_PACKAGE_NAME,
                 .build_version = ROQ_BUILD_VERSION,
                 .build_number = ROQ_BUILD_NUMBER,
                 .build_type = ROQ_BUILD_TYPE,
                 .git_hash = ROQ_GIT_DESCRIBE_HASH,
             })
      .run();
}

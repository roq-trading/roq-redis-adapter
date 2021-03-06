/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include <absl/container/flat_hash_map.h>

#include <vector>

#include "roq/io/engine/libevent/context.hpp"

#include "roq/client.hpp"

#include "roq/cache/manager.hpp"

#include "roq/third_party/hiredis/context.hpp"

namespace roq {
namespace bridge {
namespace redis {

// strategy implementation

class Controller final : public client::Handler, public third_party::hiredis::Context::Handler {
 public:
  explicit Controller(client::Dispatcher &);

  Controller(Controller &&) = default;
  Controller(Controller const &) = delete;

  bool ready() const { return !zombie_ && static_cast<bool>(context_); }

 protected:
  void operator()(Event<Start> const &) override;
  void operator()(Event<Stop> const &) override;
  void operator()(Event<Timer> const &) override;

  void operator()(Event<GatewayStatus> const &) override;

  void operator()(Event<MarketStatus> const &) override;
  void operator()(Event<ReferenceData> const &) override;
  void operator()(Event<TopOfBook> const &) override;
  void operator()(Event<MarketByPriceUpdate> const &) override;
  void operator()(Event<TradeSummary> const &) override;
  void operator()(Event<StatisticsUpdate> const &) override;

  void operator()(third_party::hiredis::Context::Connected const &) override;
  void operator()(third_party::hiredis::Context::Disconnected const &) override;

  void send_ping(std::chrono::nanoseconds now);

  template <typename... Args>
  void send(fmt::format_string<Args...> const &, Args &&...);

  template <typename T, typename Callback>
  void get_market(Event<T> const &, Callback);

  cache::Manager &get_manager(MessageInfo const &);

 private:
  client::Dispatcher &dispatcher_;
  std::unique_ptr<io::engine::libevent::Context> libevent_;
  std::unique_ptr<third_party::hiredis::Context> context_;
  bool zombie_ = {};
  std::vector<char> buffer_;
  std::chrono::nanoseconds next_heartbeat_ = {};
  absl::flat_hash_map<uint8_t, cache::Manager> cache_;
  std::vector<MBPUpdate> bids_, asks_;
};

}  // namespace redis
}  // namespace bridge
}  // namespace roq

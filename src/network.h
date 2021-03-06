#pragma once

#include "shortcuts.h"
#include "options.h"
#include "cancel.h"

#include <boost/asio/awaitable.hpp>

namespace ouisync {

class Repository;

class Network {
public:
    using executor_type = net::any_io_executor;

public:
    Network(executor_type, Repository&, Options);

    void finish();

private:
    net::awaitable<void> keep_accepting(net::ip::tcp::endpoint);
    net::awaitable<void> connect(net::ip::tcp::endpoint);

    void establish_communication(net::ip::tcp::socket);

private:
    executor_type _ex;
    Repository& _repo;
    const Options _options;
    ScopedCancel _lifetime_cancel;
};

} // namespace

#pragma once

#include "shortcuts.h"
#include "cancel.h"

#define FUSE_USE_VERSION 26
#include <fuse.h>

#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/filesystem/path.hpp>
#include <thread>

namespace ouisync {

class FuseRunner {
private:
    struct Impl;

public:
    using executor_type = net::any_io_executor;

public:
    FuseRunner(executor_type ex, fs::path mountdir);

    void finish();

    ~FuseRunner();

private:
    void run_loop();

    static void* ouisync_fuse_init(struct fuse_conn_info *conn);
    static int ouisync_fuse_getattr(const char *path, struct stat *stbuf);
    static int ouisync_fuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi);
    static int ouisync_fuse_open(const char *path, struct fuse_file_info *fi);
    static int ouisync_fuse_read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi);

private:
    executor_type _ex;
    const fs::path _mountdir;
    std::thread _thread;
    net::executor_work_guard<executor_type> _work;
    std::mutex _mutex;
    ScopedCancel _scoped_cancel;

    fuse_chan *_fuse_channel = nullptr;
    fuse_args _fuse_args;
    struct fuse* _fuse;
};

} // namespace
#pragma once

#include "shortcuts.h"

#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/optional.hpp>

namespace ouisync {

class Options {
public:
    Options();

    void parse(unsigned args, char** argv);

    void write_help(std::ostream&);

    bool help;

    fs::path basedir;
    fs::path branchdir;
    fs::path objectdir;
    fs::path snapshotdir;
    fs::path remotes;
    fs::path user_id_file_path;

    Opt<fs::path> mountdir;

    Opt<net::ip::tcp::endpoint> accept_endpoint;
    Opt<net::ip::tcp::endpoint> connect_endpoint;

    struct Snapshot {
        fs::path snapshotdir;
    };

    struct LocalBranch {
        fs::path objectdir;
        fs::path snapshotdir;

        operator Snapshot() const {
            return { snapshotdir };
        }
    };

    operator LocalBranch() const {
        return { objectdir, snapshotdir };
    }

    struct RemoteBranch {
        fs::path objectdir;
        fs::path snapshotdir;

        operator Snapshot() const {
            return { snapshotdir };
        }
    };

    operator RemoteBranch() const {
        return { objectdir, snapshotdir };
    }

private:
    boost::program_options::options_description description;
};

} // namespace

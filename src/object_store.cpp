#include "object_store.h"
#include "object/blob.h"
#include "object/tree.h"

#include "variant.h"

using namespace ouisync;
using namespace std;
using object::Blob;
using object::Tree;

ObjectStore::ObjectStore(fs::path object_dir) :
    _objdir(move(object_dir))
{
    assert(fs::exists(_objdir));
    assert(fs::is_directory(_objdir));
}

bool ObjectStore::remove(const ObjectId& id) {
    sys::error_code ec;
    fs::remove(_objdir/object::path::from_id(id), ec);
    return !ec;
}

bool ObjectStore::exists(const ObjectId& id) const {
    return fs::exists(_objdir/object::path::from_id(id));
}

bool ObjectStore::is_complete(const ObjectId& id) {
    if (!exists(id)) return false;

    auto v = load<Blob, Tree>(id);

    return apply(v,
        [&] (const Blob&) { return true; },
        [&] (const Tree& tree) {
            for (auto& [_, id] : tree) {
                if (!is_complete(id)) return false;
            }
            return true;
        });
}

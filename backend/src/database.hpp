#ifndef SESABLE_HEADER_DATABASE_HPP
#define SESABLE_HEADER_DATABASE_HPP

#include <cstddef>
#include <vector>


namespace Sesable {

namespace Things {

enum class Id : std::size_t;

struct Document {
    enum class DocuKind {
        Note,
        Table
    } kind;

    // Expects a blob of unreadable AES-encrypted data sent from the client.
    std::vector<std::byte> blob;
};

struct User {};
struct Organization {};

} // end of namespace Sesable::Things


class Database {};

} // end of namespace Sesable

#endif
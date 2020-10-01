#include <string>
#include <array>

namespace ouisync {

namespace {
    template<class B> struct is_byte_type { static const bool value = false; };
    
    template<> struct is_byte_type<char> { static const bool value = true; };
    template<> struct is_byte_type<signed char> { static const bool value = true; };
    template<> struct is_byte_type<unsigned char> { static const bool value = true; };
}

inline bool is_hex(boost::string_view s)
{
    static const std::string hex_chars = "0123456789abcdefABCDEF";

    for (size_t i = 0; i < s.size(); i++) {
        if (hex_chars.find(s[i]) == std::string::npos) {
            return false;
        }
    }

    return true;
}

template<class T, size_t N> std::array<T, 2*N> to_hex(const std::array<T, N>& as)
{
    static_assert(is_byte_type<T>::value, "Not a bytestring type");

    std::array<T, 2*N> output;

    for (unsigned int i = 0; i < as.size(); i++) {
        unsigned char c = as.data()[i];
        const char* digits = "0123456789abcdef";
        output[2*i]     = digits[(c >> 4) & 0xf];
        output[2*i + 1] = digits[(c >> 0) & 0xf];
    }

    return output;
}

template<class S> std::string to_hex(const S& bytestring)
{
    static_assert(is_byte_type<decltype(*bytestring.begin())>::value, "Not a bytestring type");
    std::string output;
    for (unsigned int i = 0; i < bytestring.size(); i++) {
        unsigned char c = bytestring.data()[i];
        const char* digits = "0123456789abcdef";
        output += digits[(c >> 4) & 0xf];
        output += digits[(c >> 0) & 0xf];
    }
    return output;
}

inline
boost::optional<unsigned char> from_hex(char c)
{
    if ('0' <= c && c <= '9') {
        return c - '0';
    } else if ('a' <= c && c <= 'f') {
        return 10 + c - 'a';
    } else if ('A' <= c && c <= 'F') {
        return 10 + c - 'A';
    } else return boost::none;
}

inline
boost::optional<unsigned char> from_hex(char c1, char c2)
{
    auto on1 = from_hex(c1);
    if (!on1) return boost::none;
    auto on2 = from_hex(c2);
    if (!on2) return boost::none;
    return *on1*16+*on2;
}

inline boost::optional<std::string> from_hex(boost::string_view hex)
{
    std::string output((hex.size() >> 1) + (hex.size() & 1), '\0');

    size_t i = 0;
    while (size_t s = hex.size()) {
        boost::optional<unsigned char> oc;

        if (s == 1) { oc = from_hex(hex[0]);         hex.remove_prefix(1); }
        else        { oc = from_hex(hex[0], hex[1]); hex.remove_prefix(2); }

        if (!oc) return boost::none;

        output[i++] = *oc;
    }

    return output;
}

template<class T, size_t N>
inline boost::optional<std::array<T, N/2>> from_hex(const std::array<T, N>& hex)
{
    static_assert(is_byte_type<T>::value, "Not a bytestring type");
    // TODO: This can be generalized to odd number as well
    static_assert(N % 2 == 0, "Input number must have even number of characters");

    std::array<T, N/2> output;

    for (size_t i = 0; i < N; i += 2) {
        boost::optional<unsigned char> oc;
        oc = from_hex(hex[i], hex[i+1]);
        if (!oc) return boost::none;
    }

    return output;
}

} // namespace
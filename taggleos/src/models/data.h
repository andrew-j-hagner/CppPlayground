#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <memory>
#include <cstdint>

using DataID = std::uint64_t;

class Data
{
public:
    Data();
    Data(const std::vector<std::uint8_t> &bytes);
    Data(std::vector<std::uint8_t> &&bytes);
    Data(const std::string &text);
    Data(const Data &other);
    Data &operator=(const Data &other);
    Data(Data &&other) noexcept;
    Data &operator=(Data &&other) noexcept;
    ~Data();

    // Accessors
    DataID getId() const;
    void setId(DataID id);

    const std::vector<std::uint8_t> &getBytes() const;
    void setBytes(const std::vector<std::uint8_t> &bytes);
    void setBytes(std::vector<std::uint8_t> &&bytes);

    // Utility methods
    std::size_t size() const;
    bool empty() const;
    void clear();

    // String conversion (assumes UTF-8)
    std::string toString() const;
    void fromString(const std::string &text);

    // File operations
    bool loadFromFile(const std::string &filename);
    bool saveToFile(const std::string &filename) const;

    // Comparison operators
    bool operator==(const Data &other) const;
    bool operator!=(const Data &other) const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

#endif // DATA_H

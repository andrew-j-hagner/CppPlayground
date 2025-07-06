#include "data.h"
#include <fstream>
#include <iterator>

class Data::Impl
{
public:
    DataID id = 0;
    std::vector<std::uint8_t> bytes;
};

Data::Data()
    : m_impl(std::make_unique<Impl>())
{
}

Data::Data(const std::vector<std::uint8_t> &bytes)
    : m_impl(std::make_unique<Impl>())
{
    m_impl->bytes = bytes;
}

Data::Data(std::vector<std::uint8_t> &&bytes)
    : m_impl(std::make_unique<Impl>())
{
    m_impl->bytes = std::move(bytes);
}

Data::Data(const std::string &text)
    : m_impl(std::make_unique<Impl>())
{
    fromString(text);
}

Data::Data(const Data &other)
    : m_impl(std::make_unique<Impl>())
{
    m_impl->id = other.m_impl->id;
    m_impl->bytes = other.m_impl->bytes;
}

Data &Data::operator=(const Data &other)
{
    if (this != &other)
    {
        m_impl->id = other.m_impl->id;
        m_impl->bytes = other.m_impl->bytes;
    }
    return *this;
}

Data::Data(Data &&other) noexcept
    : m_impl(std::move(other.m_impl))
{
}

Data &Data::operator=(Data &&other) noexcept
{
    if (this != &other)
    {
        m_impl = std::move(other.m_impl);
    }
    return *this;
}

Data::~Data() = default;

DataID Data::getId() const
{
    return m_impl->id;
}

void Data::setId(DataID id)
{
    m_impl->id = id;
}

const std::vector<std::uint8_t> &Data::getBytes() const
{
    return m_impl->bytes;
}

void Data::setBytes(const std::vector<std::uint8_t> &bytes)
{
    m_impl->bytes = bytes;
}

void Data::setBytes(std::vector<std::uint8_t> &&bytes)
{
    m_impl->bytes = std::move(bytes);
}

std::size_t Data::size() const
{
    return m_impl->bytes.size();
}

bool Data::empty() const
{
    return m_impl->bytes.empty();
}

void Data::clear()
{
    m_impl->bytes.clear();
}

std::string Data::toString() const
{
    return std::string(m_impl->bytes.begin(), m_impl->bytes.end());
}

void Data::fromString(const std::string &text)
{
    m_impl->bytes.assign(text.begin(), text.end());
}

bool Data::loadFromFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    // Get file size
    file.seekg(0, std::ios::end);
    auto fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read file content
    m_impl->bytes.resize(static_cast<std::size_t>(fileSize));
    file.read(reinterpret_cast<char *>(m_impl->bytes.data()), fileSize);

    return file.good();
}

bool Data::saveToFile(const std::string &filename) const
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.write(reinterpret_cast<const char *>(m_impl->bytes.data()),
               static_cast<std::streamsize>(m_impl->bytes.size()));

    return file.good();
}

bool Data::operator==(const Data &other) const
{
    return m_impl->id == other.m_impl->id && m_impl->bytes == other.m_impl->bytes;
}

bool Data::operator!=(const Data &other) const
{
    return !(*this == other);
}

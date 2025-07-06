#include "datastore.h"
#include <unordered_map>
#include <memory>

class DataStore::Impl
{
public:
    std::unordered_map<DataID, std::vector<std::uint8_t>> storage;
};

DataStore::DataStore()
    : m_impl(std::make_unique<Impl>())
{
}

DataStore::~DataStore() = default;

bool DataStore::store(DataID id, const std::vector<std::uint8_t> &data)
{
    try
    {
        m_impl->storage[id] = data;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

std::vector<std::uint8_t> DataStore::retrieve(DataID id)
{
    auto it = m_impl->storage.find(id);
    if (it != m_impl->storage.end())
    {
        return it->second;
    }
    return {};
}

bool DataStore::remove(DataID id)
{
    return m_impl->storage.erase(id) > 0;
}

bool DataStore::exists(DataID id)
{
    return m_impl->storage.find(id) != m_impl->storage.end();
}

std::size_t DataStore::size() const
{
    return m_impl->storage.size();
}

void DataStore::clear()
{
    m_impl->storage.clear();
}

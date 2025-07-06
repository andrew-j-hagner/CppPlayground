#ifndef DATASTORE_H
#define DATASTORE_H

#include <vector>
#include <cstdint>
#include <memory>

// Forward declarations and type definitions
using DataID = std::uint64_t;
using TagID = std::uint64_t;

// Helper structs for the API
struct SearchResult
{
    DataID dataId;
    std::vector<TagID> tags;
};

struct Stats
{
    std::size_t totalTags = 0;
    std::size_t totalData = 0;
    std::size_t totalAssociations = 0;
};

struct DeleteResult
{
    bool success = false;
    std::vector<DataID> affectedDataIds;
};

class DataStore
{
public:
    DataStore();
    ~DataStore();

    // Basic storage operations
    bool store(DataID id, const std::vector<std::uint8_t> &data);
    std::vector<std::uint8_t> retrieve(DataID id);
    bool remove(DataID id);
    bool exists(DataID id);

    // Metadata operations
    std::size_t size() const;
    void clear();

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

#endif // DATASTORE_H

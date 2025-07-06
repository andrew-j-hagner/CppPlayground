#include "tagmanager.h"
#include "datastore.h"
#include <unordered_map>
#include <algorithm>

// Implementation class using PIMPL idiom
class TagManager::Impl
{
public:
    Impl() = default;
    ~Impl() = default;

    std::unordered_map<TagID, Tag> tags;
    std::unordered_map<DataID, Data> dataStore;
    std::unordered_map<DataID, std::vector<TagID>> dataTagMap;

    TagID nextTagId = 1;
    DataID nextDataId = 1;
};

TagManager::TagManager()
    : m_impl(std::make_unique<Impl>())
{
}

TagManager::~TagManager() = default;

Result<bool> TagManager::save(const Data &data, const std::vector<Tag> &tags)
{
    try
    {
        // Generate new data ID
        DataID newDataId = m_impl->nextDataId++;

        // Store the data
        Data newData = data;
        newData.setId(newDataId);
        m_impl->dataStore[newDataId] = newData;

        // Store tag associations
        std::vector<TagID> tagIds;
        for (const auto &tag : tags)
        {
            tagIds.push_back(tag.getId());
        }
        m_impl->dataTagMap[newDataId] = tagIds;

        return Result<bool>(true);
    }
    catch (const std::exception &e)
    {
        return Result<bool>(Result<bool>::Status::Error, e.what());
    }
}

Result<std::vector<SearchResult>> TagManager::search(const std::vector<Tag> &tags)
{
    try
    {
        std::vector<SearchResult> results;

        // Convert tags to IDs
        std::vector<TagID> searchTagIds;
        for (const auto &tag : tags)
        {
            searchTagIds.push_back(tag.getId());
        }

        // Search through data-tag mappings
        for (const auto &[dataId, tagIds] : m_impl->dataTagMap)
        {
            // Check if all search tags are present
            bool allTagsMatch = true;
            for (const auto &searchTagId : searchTagIds)
            {
                if (std::find(tagIds.begin(), tagIds.end(), searchTagId) == tagIds.end())
                {
                    allTagsMatch = false;
                    break;
                }
            }

            if (allTagsMatch)
            {
                SearchResult result;
                result.dataId = dataId;
                result.tags = tagIds;
                results.push_back(result);
            }
        }

        return Result<std::vector<SearchResult>>(results);
    }
    catch (const std::exception &e)
    {
        return Result<std::vector<SearchResult>>(Result<std::vector<SearchResult>>::Status::Error, e.what());
    }
}

Result<Data> TagManager::load(const DataID &id)
{
    try
    {
        auto it = m_impl->dataStore.find(id);
        if (it != m_impl->dataStore.end())
        {
            return Result<Data>(it->second);
        }
        else
        {
            return Result<Data>(Result<Data>::Status::Problem, "Data not found");
        }
    }
    catch (const std::exception &e)
    {
        return Result<Data>(Result<Data>::Status::Error, e.what());
    }
}

Result<Stats> TagManager::stats()
{
    try
    {
        Stats stats;
        stats.totalTags = m_impl->tags.size();
        stats.totalData = m_impl->dataStore.size();
        stats.totalAssociations = m_impl->dataTagMap.size();

        return Result<Stats>(stats);
    }
    catch (const std::exception &e)
    {
        return Result<Stats>(Result<Stats>::Status::Error, e.what());
    }
}

Result<TagID> TagManager::addTag(const Tag &tag)
{
    try
    {
        TagID newId = m_impl->nextTagId++;
        Tag newTag = tag;
        newTag.setId(newId);

        m_impl->tags[newId] = newTag;

        return Result<TagID>(newId);
    }
    catch (const std::exception &e)
    {
        return Result<TagID>(Result<TagID>::Status::Error, e.what());
    }
}

Result<DeleteResult> TagManager::deleteTag(const Tag &tag)
{
    try
    {
        TagID tagId = tag.getId();

        // Remove tag from storage
        auto it = m_impl->tags.find(tagId);
        if (it == m_impl->tags.end())
        {
            return Result<DeleteResult>(Result<DeleteResult>::Status::Problem, "Tag not found");
        }

        m_impl->tags.erase(it);

        // Find all data affected by this tag deletion
        std::vector<DataID> affectedDataIds;
        for (auto &[dataId, tagIds] : m_impl->dataTagMap)
        {
            auto tagIt = std::find(tagIds.begin(), tagIds.end(), tagId);
            if (tagIt != tagIds.end())
            {
                tagIds.erase(tagIt);
                affectedDataIds.push_back(dataId);
            }
        }

        DeleteResult result;
        result.success = true;
        result.affectedDataIds = affectedDataIds;

        return Result<DeleteResult>(result);
    }
    catch (const std::exception &e)
    {
        return Result<DeleteResult>(Result<DeleteResult>::Status::Error, e.what());
    }
}

Result<std::vector<Tag>> TagManager::getAllTags()
{
    try
    {
        std::vector<Tag> tags;
        for (const auto &[id, tag] : m_impl->tags)
        {
            tags.push_back(tag);
        }
        return Result<std::vector<Tag>>(tags);
    }
    catch (const std::exception &e)
    {
        return Result<std::vector<Tag>>(Result<std::vector<Tag>>::Status::Error, e.what());
    }
}

Result<Tag> TagManager::getTag(const TagID &id)
{
    try
    {
        auto it = m_impl->tags.find(id);
        if (it != m_impl->tags.end())
        {
            return Result<Tag>(it->second);
        }
        else
        {
            return Result<Tag>(Result<Tag>::Status::Problem, "Tag not found");
        }
    }
    catch (const std::exception &e)
    {
        return Result<Tag>(Result<Tag>::Status::Error, e.what());
    }
}

Result<bool> TagManager::updateTag(const Tag &tag)
{
    try
    {
        TagID id = tag.getId();
        auto it = m_impl->tags.find(id);
        if (it != m_impl->tags.end())
        {
            it->second = tag;
            return Result<bool>(true);
        }
        else
        {
            return Result<bool>(Result<bool>::Status::Problem, "Tag not found");
        }
    }
    catch (const std::exception &e)
    {
        return Result<bool>(Result<bool>::Status::Error, e.what());
    }
}

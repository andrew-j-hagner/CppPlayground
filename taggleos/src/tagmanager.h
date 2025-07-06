#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <vector>
#include <memory>
#include <string>
#include <optional>
#include "models/tag.h"
#include "models/data.h"
#include "datastore.h"

// Result template for error handling
template <typename T>
class Result
{
public:
    enum class Status
    {
        Success,
        Error,
        Problem
    };

    Result(T value) : m_value(std::move(value)), m_status(Status::Success) {}
    Result(Status status, const std::string &message = "")
        : m_status(status), m_errorMessage(message) {}

    bool isSuccess() const { return m_status == Status::Success; }
    bool isError() const { return m_status == Status::Error; }
    bool isProblem() const { return m_status == Status::Problem; }

    const T &value() const { return m_value; }
    const std::string &errorMessage() const { return m_errorMessage; }

private:
    T m_value;
    Status m_status;
    std::string m_errorMessage;
};

class TagManager
{
public:
    TagManager();
    ~TagManager();

    // Core API methods from design
    Result<bool> save(const Data &data, const std::vector<Tag> &tags);
    Result<std::vector<SearchResult>> search(const std::vector<Tag> &tags);
    Result<Data> load(const DataID &id);
    Result<Stats> stats();
    Result<TagID> addTag(const Tag &tag);
    Result<DeleteResult> deleteTag(const Tag &tag);

    // Additional management methods
    Result<std::vector<Tag>> getAllTags();
    Result<Tag> getTag(const TagID &id);
    Result<bool> updateTag(const Tag &tag);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

#endif // TAGMANAGER_H

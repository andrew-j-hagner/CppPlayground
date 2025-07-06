#ifndef TAG_H
#define TAG_H

#include <string>
#include <vector>
#include <memory>
#include <cstdint>

using TagID = std::uint64_t;

class Tag
{
public:
    Tag();
    Tag(const std::string &name);
    Tag(TagID id, const std::string &name);
    Tag(const Tag &other);
    Tag &operator=(const Tag &other);
    Tag(Tag &&other) noexcept;
    Tag &operator=(Tag &&other) noexcept;
    ~Tag();

    // Accessors
    TagID getId() const;
    void setId(TagID id);

    const std::string &getName() const;
    void setName(const std::string &name);

    // Hierarchical structure support
    std::shared_ptr<Tag> getParent() const;
    void setParent(std::shared_ptr<Tag> parent);

    const std::vector<std::shared_ptr<Tag>> &getChildren() const;
    void addChild(std::shared_ptr<Tag> child);
    void removeChild(std::shared_ptr<Tag> child);
    void clearChildren();

    // Utility methods
    bool hasParent() const;
    bool hasChildren() const;
    std::size_t getChildCount() const;

    // Comparison operators
    bool operator==(const Tag &other) const;
    bool operator!=(const Tag &other) const;
    bool operator<(const Tag &other) const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

#endif // TAG_H

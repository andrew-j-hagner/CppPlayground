#include "tag.h"
#include <algorithm>

class Tag::Impl
{
public:
    TagID id = 0;
    std::string name;
    std::shared_ptr<Tag> parent;
    std::vector<std::shared_ptr<Tag>> children;
};

Tag::Tag()
    : m_impl(std::make_unique<Impl>())
{
}

Tag::Tag(const std::string &name)
    : m_impl(std::make_unique<Impl>())
{
    m_impl->name = name;
}

Tag::Tag(TagID id, const std::string &name)
    : m_impl(std::make_unique<Impl>())
{
    m_impl->id = id;
    m_impl->name = name;
}

Tag::Tag(const Tag &other)
    : m_impl(std::make_unique<Impl>())
{
    m_impl->id = other.m_impl->id;
    m_impl->name = other.m_impl->name;
    m_impl->parent = other.m_impl->parent;
    m_impl->children = other.m_impl->children;
}

Tag &Tag::operator=(const Tag &other)
{
    if (this != &other)
    {
        m_impl->id = other.m_impl->id;
        m_impl->name = other.m_impl->name;
        m_impl->parent = other.m_impl->parent;
        m_impl->children = other.m_impl->children;
    }
    return *this;
}

Tag::Tag(Tag &&other) noexcept
    : m_impl(std::move(other.m_impl))
{
}

Tag &Tag::operator=(Tag &&other) noexcept
{
    if (this != &other)
    {
        m_impl = std::move(other.m_impl);
    }
    return *this;
}

Tag::~Tag() = default;

TagID Tag::getId() const
{
    return m_impl->id;
}

void Tag::setId(TagID id)
{
    m_impl->id = id;
}

const std::string &Tag::getName() const
{
    return m_impl->name;
}

void Tag::setName(const std::string &name)
{
    m_impl->name = name;
}

std::shared_ptr<Tag> Tag::getParent() const
{
    return m_impl->parent;
}

void Tag::setParent(std::shared_ptr<Tag> parent)
{
    m_impl->parent = parent;
}

const std::vector<std::shared_ptr<Tag>> &Tag::getChildren() const
{
    return m_impl->children;
}

void Tag::addChild(std::shared_ptr<Tag> child)
{
    if (child)
    {
        m_impl->children.push_back(child);
        child->setParent(std::make_shared<Tag>(*this));
    }
}

void Tag::removeChild(std::shared_ptr<Tag> child)
{
    if (child)
    {
        auto it = std::find(m_impl->children.begin(), m_impl->children.end(), child);
        if (it != m_impl->children.end())
        {
            m_impl->children.erase(it);
            child->setParent(nullptr);
        }
    }
}

void Tag::clearChildren()
{
    for (auto &child : m_impl->children)
    {
        if (child)
        {
            child->setParent(nullptr);
        }
    }
    m_impl->children.clear();
}

bool Tag::hasParent() const
{
    return m_impl->parent != nullptr;
}

bool Tag::hasChildren() const
{
    return !m_impl->children.empty();
}

std::size_t Tag::getChildCount() const
{
    return m_impl->children.size();
}

bool Tag::operator==(const Tag &other) const
{
    return m_impl->id == other.m_impl->id && m_impl->name == other.m_impl->name;
}

bool Tag::operator!=(const Tag &other) const
{
    return !(*this == other);
}

bool Tag::operator<(const Tag &other) const
{
    if (m_impl->id != other.m_impl->id)
    {
        return m_impl->id < other.m_impl->id;
    }
    return m_impl->name < other.m_impl->name;
}

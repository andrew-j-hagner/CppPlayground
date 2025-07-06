#include "tagwidget.h"

TagWidget::TagWidget(QWidget *parent)
    : QWidget(parent), m_mainLayout(nullptr), m_buttonLayout(nullptr), m_tagTree(nullptr), m_tagNameEdit(nullptr), m_addTagButton(nullptr), m_removeTagButton(nullptr), m_titleLabel(nullptr), m_contextMenu(nullptr), m_renameAction(nullptr), m_addChildAction(nullptr), m_removeAction(nullptr), m_currentItem(nullptr)
{
    setupUI();
    setupContextMenu();
    connectSignals();
    populateTree();
}

TagWidget::~TagWidget() = default;

void TagWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);

    // Title
    m_titleLabel = new QLabel("Tags", this);
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 14px; margin-bottom: 5px;");
    m_mainLayout->addWidget(m_titleLabel);

    // Tag tree
    m_tagTree = new QTreeWidget(this);
    m_tagTree->setHeaderLabel("Tag Hierarchy");
    m_tagTree->setContextMenuPolicy(Qt::CustomContextMenu);
    m_tagTree->setAlternatingRowColors(true);
    m_tagTree->setRootIsDecorated(true);
    m_tagTree->setSelectionMode(QAbstractItemView::SingleSelection);
    m_mainLayout->addWidget(m_tagTree);

    // Input section
    m_tagNameEdit = new QLineEdit(this);
    m_tagNameEdit->setPlaceholderText("Enter tag name...");
    m_mainLayout->addWidget(m_tagNameEdit);

    // Button layout
    m_buttonLayout = new QHBoxLayout();

    m_addTagButton = new QPushButton("Add Tag", this);
    m_addTagButton->setDefault(true);
    m_buttonLayout->addWidget(m_addTagButton);

    m_removeTagButton = new QPushButton("Remove Tag", this);
    m_removeTagButton->setEnabled(false);
    m_buttonLayout->addWidget(m_removeTagButton);

    m_mainLayout->addLayout(m_buttonLayout);

    // Set layout margins
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    m_mainLayout->setSpacing(5);
}

void TagWidget::setupContextMenu()
{
    m_contextMenu = new QMenu(this);

    m_renameAction = new QAction("Rename", this);
    m_addChildAction = new QAction("Add Child Tag", this);
    m_removeAction = new QAction("Remove", this);

    m_contextMenu->addAction(m_renameAction);
    m_contextMenu->addAction(m_addChildAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(m_removeAction);
}

void TagWidget::connectSignals()
{
    connect(m_addTagButton, &QPushButton::clicked, this, &TagWidget::onAddTagClicked);
    connect(m_removeTagButton, &QPushButton::clicked, this, &TagWidget::onRemoveTagClicked);
    connect(m_tagNameEdit, &QLineEdit::returnPressed, this, &TagWidget::onAddTagClicked);

    connect(m_tagTree, &QTreeWidget::itemClicked, this, &TagWidget::onTreeItemClicked);
    connect(m_tagTree, &QTreeWidget::itemDoubleClicked, this, &TagWidget::onTreeItemDoubleClicked);
    connect(m_tagTree, &QTreeWidget::customContextMenuRequested, this, &TagWidget::showContextMenu);

    connect(m_renameAction, &QAction::triggered, this, &TagWidget::onRenameTag);
    connect(m_addChildAction, &QAction::triggered, this, &TagWidget::onAddChildTag);
    connect(m_removeAction, &QAction::triggered, this, &TagWidget::onRemoveSelectedTag);
}

void TagWidget::populateTree()
{
    m_tagTree->clear();

    // Add some sample tags for demonstration
    auto rootItem = new QTreeWidgetItem(m_tagTree);
    rootItem->setText(0, "Documents");
    rootItem->setIcon(0, style()->standardIcon(QStyle::SP_DirIcon));

    auto childItem1 = new QTreeWidgetItem(rootItem);
    childItem1->setText(0, "Work");
    childItem1->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    auto childItem2 = new QTreeWidgetItem(rootItem);
    childItem2->setText(0, "Personal");
    childItem2->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    auto mediaItem = new QTreeWidgetItem(m_tagTree);
    mediaItem->setText(0, "Media");
    mediaItem->setIcon(0, style()->standardIcon(QStyle::SP_DirIcon));

    auto photoItem = new QTreeWidgetItem(mediaItem);
    photoItem->setText(0, "Photos");
    photoItem->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    auto videoItem = new QTreeWidgetItem(mediaItem);
    videoItem->setText(0, "Videos");
    videoItem->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    m_tagTree->expandAll();
}

void TagWidget::onAddTagClicked()
{
    QString tagName = m_tagNameEdit->text().trimmed();
    if (tagName.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please enter a tag name.");
        return;
    }

    if (findItem(tagName))
    {
        QMessageBox::warning(this, "Warning", "Tag already exists.");
        return;
    }

    // Add tag to tree
    QTreeWidgetItem *parentItem = m_tagTree->currentItem();
    QTreeWidgetItem *newItem;

    if (parentItem)
    {
        newItem = new QTreeWidgetItem(parentItem);
    }
    else
    {
        newItem = new QTreeWidgetItem(m_tagTree);
    }

    newItem->setText(0, tagName);
    newItem->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    // Clear input
    m_tagNameEdit->clear();

    // Expand parent if needed
    if (parentItem)
    {
        parentItem->setExpanded(true);
    }

    // Select the new item
    m_tagTree->setCurrentItem(newItem);

    emit tagAdded(tagName);
}

void TagWidget::onRemoveTagClicked()
{
    QTreeWidgetItem *currentItem = m_tagTree->currentItem();
    if (!currentItem)
    {
        QMessageBox::warning(this, "Warning", "Please select a tag to remove.");
        return;
    }

    QString tagName = currentItem->text(0);

    int ret = QMessageBox::question(this, "Confirm Removal",
                                    QString("Are you sure you want to remove the tag '%1'?").arg(tagName),
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (ret == QMessageBox::Yes)
    {
        delete currentItem;
        m_removeTagButton->setEnabled(false);
        emit tagRemoved(tagName);
    }
}

void TagWidget::onTreeItemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)

    m_currentItem = item;
    m_removeTagButton->setEnabled(item != nullptr);

    if (item)
    {
        emit tagSelected(item->text(0));
    }
}

void TagWidget::onTreeItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)

    if (item)
    {
        onRenameTag();
    }
}

void TagWidget::showContextMenu(const QPoint &pos)
{
    QTreeWidgetItem *item = m_tagTree->itemAt(pos);
    if (item)
    {
        m_currentItem = item;
        m_contextMenu->exec(m_tagTree->mapToGlobal(pos));
    }
}

void TagWidget::onRenameTag()
{
    if (!m_currentItem)
        return;

    QString oldName = m_currentItem->text(0);
    bool ok;
    QString newName = QInputDialog::getText(this, "Rename Tag",
                                            "Enter new name:", QLineEdit::Normal, oldName, &ok);

    if (ok && !newName.isEmpty() && newName != oldName)
    {
        if (findItem(newName))
        {
            QMessageBox::warning(this, "Warning", "Tag name already exists.");
            return;
        }

        m_currentItem->setText(0, newName);
        emit tagRenamed(oldName, newName);
    }
}

void TagWidget::onAddChildTag()
{
    if (!m_currentItem)
        return;

    bool ok;
    QString tagName = QInputDialog::getText(this, "Add Child Tag",
                                            "Enter tag name:", QLineEdit::Normal, "", &ok);

    if (ok && !tagName.isEmpty())
    {
        if (findItem(tagName))
        {
            QMessageBox::warning(this, "Warning", "Tag already exists.");
            return;
        }

        auto newItem = new QTreeWidgetItem(m_currentItem);
        newItem->setText(0, tagName);
        newItem->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

        m_currentItem->setExpanded(true);
        m_tagTree->setCurrentItem(newItem);

        emit tagAdded(tagName);
    }
}

void TagWidget::onRemoveSelectedTag()
{
    if (m_currentItem)
    {
        onRemoveTagClicked();
    }
}

void TagWidget::refreshTags()
{
    populateTree();
}

void TagWidget::addTag(const QString &name, const QString &parent)
{
    if (findItem(name))
    {
        return; // Tag already exists
    }

    QTreeWidgetItem *parentItem = nullptr;
    if (!parent.isEmpty())
    {
        parentItem = findItem(parent);
    }

    QTreeWidgetItem *newItem;
    if (parentItem)
    {
        newItem = new QTreeWidgetItem(parentItem);
        parentItem->setExpanded(true);
    }
    else
    {
        newItem = new QTreeWidgetItem(m_tagTree);
    }

    newItem->setText(0, name);
    newItem->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));
}

void TagWidget::removeTag(const QString &name)
{
    QTreeWidgetItem *item = findItem(name);
    if (item)
    {
        delete item;
    }
}

QTreeWidgetItem *TagWidget::findItem(const QString &name)
{
    auto items = m_tagTree->findItems(name, Qt::MatchRecursive);
    return items.isEmpty() ? nullptr : items.first();
}

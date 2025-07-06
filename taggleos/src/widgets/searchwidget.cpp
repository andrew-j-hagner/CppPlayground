#include "searchwidget.h"
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QTimer>

SearchWidget::SearchWidget(QWidget *parent)
    : QWidget(parent), m_mainLayout(nullptr), m_splitter(nullptr), m_searchGroup(nullptr), m_searchLayout(nullptr), m_searchButtonLayout(nullptr), m_searchEdit(nullptr), m_searchButton(nullptr), m_clearButton(nullptr), m_searchModeCombo(nullptr), m_progressBar(nullptr), m_resultsGroup(nullptr), m_resultsLayout(nullptr), m_resultsList(nullptr), m_resultsCountLabel(nullptr), m_previewGroup(nullptr), m_previewLayout(nullptr), m_previewEdit(nullptr), m_previewTagsLabel(nullptr)
{
    setupUI();
    connectSignals();
}

SearchWidget::~SearchWidget() = default;

void SearchWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);

    // Create main splitter
    m_splitter = new QSplitter(Qt::Vertical, this);

    setupSearchArea();
    setupResultsArea();
    setupPreviewArea();

    // Add areas to splitter
    m_splitter->addWidget(m_searchGroup);
    m_splitter->addWidget(m_resultsGroup);
    m_splitter->addWidget(m_previewGroup);

    // Set splitter proportions
    m_splitter->setSizes({150, 300, 200});
    m_splitter->setStretchFactor(0, 0);
    m_splitter->setStretchFactor(1, 1);
    m_splitter->setStretchFactor(2, 0);

    m_mainLayout->addWidget(m_splitter);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
}

void SearchWidget::setupSearchArea()
{
    m_searchGroup = new QGroupBox("Search", this);
    m_searchLayout = new QVBoxLayout(m_searchGroup);

    // Search mode combo
    m_searchModeCombo = new QComboBox(this);
    m_searchModeCombo->addItems({"Search by Tags", "Search by Content", "Search All"});
    m_searchLayout->addWidget(m_searchModeCombo);

    // Search input
    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("Enter search terms or tags...");
    m_searchLayout->addWidget(m_searchEdit);

    // Button layout
    m_searchButtonLayout = new QHBoxLayout();

    m_searchButton = new QPushButton("Search", this);
    m_searchButton->setDefault(true);
    m_searchButton->setEnabled(false);
    m_searchButtonLayout->addWidget(m_searchButton);

    m_clearButton = new QPushButton("Clear", this);
    m_searchButtonLayout->addWidget(m_clearButton);

    m_searchButtonLayout->addStretch();
    m_searchLayout->addLayout(m_searchButtonLayout);

    // Progress bar
    m_progressBar = new QProgressBar(this);
    m_progressBar->setVisible(false);
    m_progressBar->setRange(0, 0); // Indeterminate progress
    m_searchLayout->addWidget(m_progressBar);
}

void SearchWidget::setupResultsArea()
{
    m_resultsGroup = new QGroupBox("Results", this);
    m_resultsLayout = new QVBoxLayout(m_resultsGroup);

    // Results count label
    m_resultsCountLabel = new QLabel("No results", this);
    m_resultsCountLabel->setStyleSheet("color: gray; font-style: italic;");
    m_resultsLayout->addWidget(m_resultsCountLabel);

    // Results list
    m_resultsList = new QListWidget(this);
    m_resultsList->setAlternatingRowColors(true);
    m_resultsList->setSelectionMode(QAbstractItemView::SingleSelection);
    m_resultsLayout->addWidget(m_resultsList);
}

void SearchWidget::setupPreviewArea()
{
    m_previewGroup = new QGroupBox("Preview", this);
    m_previewLayout = new QVBoxLayout(m_previewGroup);

    // Preview text
    m_previewEdit = new QTextEdit(this);
    m_previewEdit->setReadOnly(true);
    m_previewEdit->setPlaceholderText("Select a result to preview...");
    m_previewEdit->setMaximumHeight(120);
    m_previewLayout->addWidget(m_previewEdit);

    // Tags label
    m_previewTagsLabel = new QLabel("Tags: None", this);
    m_previewTagsLabel->setStyleSheet("color: #666; font-size: 11px;");
    m_previewTagsLabel->setWordWrap(true);
    m_previewLayout->addWidget(m_previewTagsLabel);
}

void SearchWidget::connectSignals()
{
    connect(m_searchButton, &QPushButton::clicked, this, &SearchWidget::onSearchClicked);
    connect(m_clearButton, &QPushButton::clicked, this, &SearchWidget::onClearClicked);
    connect(m_searchEdit, &QLineEdit::returnPressed, this, &SearchWidget::onSearchClicked);
    connect(m_searchEdit, &QLineEdit::textChanged, this, &SearchWidget::onSearchTextChanged);

    connect(m_resultsList, &QListWidget::itemClicked, this, &SearchWidget::onResultItemClicked);
    connect(m_resultsList, &QListWidget::itemDoubleClicked, this, &SearchWidget::onResultItemDoubleClicked);
}

void SearchWidget::onSearchClicked()
{
    QString query = m_searchEdit->text().trimmed();
    if (query.isEmpty())
    {
        return;
    }

    setSearchInProgress(true);
    emit searchRequested(query);

    // Simulate search delay (in real implementation, this would be handled by the search completion)
    QTimer::singleShot(1000, this, [this]()
                       {
        setSearchInProgress(false);
        
        // Add some sample results for demonstration
        addResult("1", "Sample document about C++ programming", {"Programming", "C++", "Tutorial"});
        addResult("2", "Meeting notes from project discussion", {"Work", "Meeting", "Project"});
        addResult("3", "Recipe for chocolate cake", {"Cooking", "Recipe", "Dessert"});
        addResult("4", "Photo from vacation in Italy", {"Travel", "Italy", "Photos"});
        
        m_resultsCountLabel->setText(QString("Found %1 results").arg(m_resultsList->count())); });
}

void SearchWidget::onClearClicked()
{
    m_searchEdit->clear();
    clearResults();
    m_previewEdit->clear();
    m_previewTagsLabel->setText("Tags: None");
    m_resultsCountLabel->setText("No results");
}

void SearchWidget::onResultItemClicked()
{
    QListWidgetItem *item = m_resultsList->currentItem();
    if (!item)
        return;

    // Get item data
    QString id = item->data(Qt::UserRole).toString();
    QString preview = item->data(Qt::UserRole + 1).toString();
    QStringList tags = item->data(Qt::UserRole + 2).toStringList();

    m_currentItemId = id;

    // Update preview
    m_previewEdit->setPlainText(preview);
    m_previewTagsLabel->setText(QString("Tags: %1").arg(tags.join(", ")));

    emit itemSelected(id);
}

void SearchWidget::onResultItemDoubleClicked()
{
    onResultItemClicked();
    // TODO: Open item in detailed view or editor
}

void SearchWidget::onSearchTextChanged(const QString &text)
{
    updateSearchButton();
}

void SearchWidget::updateSearchButton()
{
    m_searchButton->setEnabled(!m_searchEdit->text().trimmed().isEmpty());
}

void SearchWidget::clearResults()
{
    m_resultsList->clear();
    m_currentItemId.clear();
}

void SearchWidget::addResult(const QString &id, const QString &preview, const QStringList &tags)
{
    auto item = new QListWidgetItem(m_resultsList);

    // Set display text
    QString displayText = QString("ID: %1\n%2").arg(id, preview);
    if (preview.length() > 100)
    {
        displayText = QString("ID: %1\n%2...").arg(id, preview.left(100));
    }
    item->setText(displayText);

    // Store data
    item->setData(Qt::UserRole, id);
    item->setData(Qt::UserRole + 1, preview);
    item->setData(Qt::UserRole + 2, tags);

    // Set tooltip
    item->setToolTip(QString("ID: %1\nTags: %2\nPreview: %3")
                         .arg(id, tags.join(", "), preview));

    // Set icon based on content type
    if (tags.contains("Photos", Qt::CaseInsensitive))
    {
        item->setIcon(style()->standardIcon(QStyle::SP_DesktopIcon));
    }
    else if (tags.contains("Document", Qt::CaseInsensitive))
    {
        item->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
    }
    else
    {
        item->setIcon(style()->standardIcon(QStyle::SP_ComputerIcon));
    }
}

void SearchWidget::setSearchInProgress(bool inProgress)
{
    m_progressBar->setVisible(inProgress);
    m_searchButton->setEnabled(!inProgress && !m_searchEdit->text().trimmed().isEmpty());
    m_searchEdit->setEnabled(!inProgress);
}

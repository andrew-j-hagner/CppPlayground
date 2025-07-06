#include "mainwindow.h"
#include "tagmanager.h"
#include "widgets/tagwidget.h"
#include "widgets/searchwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_centralWidget(nullptr), m_mainSplitter(nullptr), m_tagWidget(nullptr), m_searchWidget(nullptr), m_statusLabel(nullptr), m_tagManager(std::make_unique<TagManager>())
{
    setupUI();
    setupMenuBar();
    setupStatusBar();
    connectSignals();

    // Set window properties
    setWindowTitle("Taggleos - Tag-Based Storage System");
    setMinimumSize(800, 600);
    resize(1200, 800);
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUI()
{
    // Create central widget
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    // Create main splitter
    m_mainSplitter = new QSplitter(Qt::Horizontal, this);

    // Create widgets
    m_tagWidget = new TagWidget(this);
    m_searchWidget = new SearchWidget(this);

    // Add widgets to splitter
    m_mainSplitter->addWidget(m_tagWidget);
    m_mainSplitter->addWidget(m_searchWidget);

    // Set splitter proportions
    m_mainSplitter->setSizes({300, 900});

    // Create layout
    auto *layout = new QVBoxLayout(m_centralWidget);
    layout->addWidget(m_mainSplitter);
    layout->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::setupMenuBar()
{
    // File menu
    auto *fileMenu = menuBar()->addMenu("&File");

    m_openAction = new QAction("&Open...", this);
    m_openAction->setShortcut(QKeySequence::Open);
    fileMenu->addAction(m_openAction);

    m_saveAction = new QAction("&Save Data...", this);
    m_saveAction->setShortcut(QKeySequence::Save);
    fileMenu->addAction(m_saveAction);

    fileMenu->addSeparator();

    m_exitAction = new QAction("E&xit", this);
    m_exitAction->setShortcut(QKeySequence::Quit);
    fileMenu->addAction(m_exitAction);

    // Help menu
    auto *helpMenu = menuBar()->addMenu("&Help");

    m_aboutAction = new QAction("&About", this);
    helpMenu->addAction(m_aboutAction);
}

void MainWindow::setupStatusBar()
{
    m_statusLabel = new QLabel("Ready");
    statusBar()->addWidget(m_statusLabel);
}

void MainWindow::connectSignals()
{
    // Menu actions
    connect(m_openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(m_saveAction, &QAction::triggered, this, &MainWindow::saveData);
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
    connect(m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout);

    // Widget signals
    connect(m_searchWidget, &SearchWidget::searchRequested, this, &MainWindow::onDataSearched);
    connect(m_tagWidget, &TagWidget::tagAdded, this, &MainWindow::onTagAdded);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open Data File", "", "All Files (*.*)");

    if (!fileName.isEmpty())
    {
        m_statusLabel->setText(QString("Opened: %1").arg(fileName));
        // TODO: Implement file loading logic
    }
}

void MainWindow::saveData()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save Data", "", "Data Files (*.dat)");

    if (!fileName.isEmpty())
    {
        m_statusLabel->setText(QString("Saved: %1").arg(fileName));
        // TODO: Implement file saving logic
    }
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "About Taggleos",
                       "Taggleos v1.0.0\n\n"
                       "A tag-based storage system for organizing and searching data.\n\n"
                       "Built with Qt6 and C++20");
}

void MainWindow::onDataSearched(const QString &query)
{
    m_statusLabel->setText(QString("Searching for: %1").arg(query));
    // TODO: Implement search logic with TagManager
}

void MainWindow::onTagAdded(const QString &tagName)
{
    m_statusLabel->setText(QString("Added tag: %1").arg(tagName));
    // TODO: Implement tag addition logic with TagManager
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <memory>

// Forward declarations
class TagManager;
class TagWidget;
class SearchWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void openFile();
    void saveData();
    void showAbout();
    void onDataSearched(const QString &query);
    void onTagAdded(const QString &tagName);

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void connectSignals();

    // UI Components
    QWidget *m_centralWidget;
    QSplitter *m_mainSplitter;
    TagWidget *m_tagWidget;
    SearchWidget *m_searchWidget;
    QLabel *m_statusLabel;

    // Menu actions
    QAction *m_openAction;
    QAction *m_saveAction;
    QAction *m_exitAction;
    QAction *m_aboutAction;

    // Core components
    std::unique_ptr<TagManager> m_tagManager;
};

#endif // MAINWINDOW_H

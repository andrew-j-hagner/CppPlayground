#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QTextEdit>
#include <QSplitter>
#include <QGroupBox>
#include <QProgressBar>
#include <QComboBox>

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent = nullptr);
    ~SearchWidget() override;

    void clearResults();
    void addResult(const QString &id, const QString &preview, const QStringList &tags);
    void setSearchInProgress(bool inProgress);

signals:
    void searchRequested(const QString &query);
    void itemSelected(const QString &id);
    void tagFilterChanged(const QStringList &tags);

private slots:
    void onSearchClicked();
    void onClearClicked();
    void onResultItemClicked();
    void onResultItemDoubleClicked();
    void onSearchTextChanged(const QString &text);

private:
    void setupUI();
    void setupSearchArea();
    void setupResultsArea();
    void setupPreviewArea();
    void connectSignals();
    void updateSearchButton();

    // UI Components
    QVBoxLayout *m_mainLayout;
    QSplitter *m_splitter;

    // Search area
    QGroupBox *m_searchGroup;
    QVBoxLayout *m_searchLayout;
    QHBoxLayout *m_searchButtonLayout;
    QLineEdit *m_searchEdit;
    QPushButton *m_searchButton;
    QPushButton *m_clearButton;
    QComboBox *m_searchModeCombo;
    QProgressBar *m_progressBar;

    // Results area
    QGroupBox *m_resultsGroup;
    QVBoxLayout *m_resultsLayout;
    QListWidget *m_resultsList;
    QLabel *m_resultsCountLabel;

    // Preview area
    QGroupBox *m_previewGroup;
    QVBoxLayout *m_previewLayout;
    QTextEdit *m_previewEdit;
    QLabel *m_previewTagsLabel;

    // Current selection
    QString m_currentItemId;
};

#endif // SEARCHWIDGET_H

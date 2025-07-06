#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QMessageBox>

class TagWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TagWidget(QWidget *parent = nullptr);
    ~TagWidget() override;

    void refreshTags();
    void addTag(const QString &name, const QString &parent = QString());
    void removeTag(const QString &name);

signals:
    void tagSelected(const QString &tagName);
    void tagAdded(const QString &tagName);
    void tagRemoved(const QString &tagName);
    void tagRenamed(const QString &oldName, const QString &newName);

private slots:
    void onAddTagClicked();
    void onRemoveTagClicked();
    void onTreeItemClicked(QTreeWidgetItem *item, int column);
    void onTreeItemDoubleClicked(QTreeWidgetItem *item, int column);
    void showContextMenu(const QPoint &pos);
    void onRenameTag();
    void onAddChildTag();
    void onRemoveSelectedTag();

private:
    void setupUI();
    void setupContextMenu();
    void connectSignals();
    void populateTree();
    QTreeWidgetItem *findItem(const QString &name);

    // UI Components
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_buttonLayout;
    QTreeWidget *m_tagTree;
    QLineEdit *m_tagNameEdit;
    QPushButton *m_addTagButton;
    QPushButton *m_removeTagButton;
    QLabel *m_titleLabel;

    // Context menu
    QMenu *m_contextMenu;
    QAction *m_renameAction;
    QAction *m_addChildAction;
    QAction *m_removeAction;

    // Current selection
    QTreeWidgetItem *m_currentItem;
};

#endif // TAGWIDGET_H

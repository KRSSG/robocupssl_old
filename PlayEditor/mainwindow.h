#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "highlighter.h"

class QAbstractItemModel;
class QComboBox;
class QCompleter;
class QLabel;
class QLineEdit;
class QProgressBar;
class QDockWidget;
class QTextBrowser;

class TextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void build();

private:
    void createMenu();
    void createStatusBar();
    void createDockWindows();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QAbstractItemModel *modelFromFile(const QString& fileName);

    QCompleter *playCompleter;
    QString curFile;
    TextEdit *textEdit;
    Highlighter *highlighter;
    QTextBrowser *buildOutput;
    QMenu* viewMenu;
    QDockWidget *dock;
};

#endif // MAINWINDOW_H

#include <QtGui>
#include "mainwindow.h"
#include "textedit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), playCompleter(0)
{
    textEdit = new TextEdit;
    createMenu();
    createStatusBar();

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    //font.setPointSize(10);
    textEdit->setFont(font);

    playCompleter = new QCompleter(this);
    playCompleter->setModel(modelFromFile(":/resources/wordlist.txt"));
    playCompleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    playCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    playCompleter->setWrapAround(false);
    textEdit->setCompleter(playCompleter);

    highlighter = new Highlighter(textEdit->document());

    setCentralWidget(textEdit);
    createDockWindows();
    resize(700, 500);
    setWindowTitle(tr("Play Editor"));
}

void MainWindow::createMenu()
{
    QAction *exitAction = new QAction(tr("&Exit"), this);
    exitAction->setStatusTip(tr("Exit Play Editor"));
    QAction *newAction = new QAction(tr("&New"), this);
    newAction->setStatusTip(tr("New Document"));
    newAction->setShortcuts(QKeySequence::New);
    QAction *openAction = new QAction(tr("&Open"), this);
    openAction->setStatusTip(tr("Open Document"));
    openAction->setShortcuts(QKeySequence::Open);
    QAction *saveAction = new QAction(tr("&Save"), this);
    saveAction->setStatusTip(tr("Save play"));
    saveAction->setShortcuts(QKeySequence::Save);
    QAction *saveAsAction = new QAction(tr("Save &As"), this);
    saveAsAction->setStatusTip(tr("Save as.."));
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    QAction *buildAction = new QAction(tr("&Build"), this);
    buildAction->setShortcut(QKeySequence(tr("Ctrl+B")));
    buildAction->setStatusTip(tr("Build the play file."));
    QAction *aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("About Play Editor"));
    QAction *aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("About Qt"));
    QAction *copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcuts(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy selection tocompletingT clipboard"));
    QAction *cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setShortcuts(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut selection to clipboard"));
    QAction *pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setShortcuts(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste clipboard into selection"));

    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(saveAction, SIGNAL(triggered()), this , SLOT(save()));
    connect(saveAsAction, SIGNAL(triggered()), this , SLOT(saveAs()));
    connect(buildAction, SIGNAL(triggered()), this, SLOT(build()));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(copyAction, SIGNAL(triggered()), textEdit, SLOT(copy()));
    connect(cutAction, SIGNAL(triggered()), textEdit, SLOT(cut()));
    connect(pasteAction, SIGNAL(triggered()), textEdit, SLOT(paste()));

    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(exitAction);

    QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    QMenu* buildMenu = menuBar()->addMenu(tr("&Build"));
    buildMenu->addAction(buildAction);

    viewMenu = menuBar()->addMenu(tr("&View"));

    QMenu* helpMenu = menuBar()->addMenu(tr("&About"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createDockWindows()
{
    dock = new QDockWidget(tr("Build Output"), this);
    dock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    buildOutput = new QTextBrowser(dock);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    buildOutput->setFont(font);

    dock->setWidget(buildOutput);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());
    dock->setVisible(false);
 }

QAbstractItemModel *MainWindow::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(playCompleter);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << line.trimmed()+" ";
    }

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    return new QStringListModel(words, playCompleter);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("Play Editor for KGP_KUBS STP Architecture. "
                                             "Press Ctrl+Space for auto-completion list. "
                                             ));
}

void MainWindow::build()
{
    //TODO: implement build.
    /*
    QTextDocument * document = textEdit->document();
    QTextCursor newCursor(document);
    while (!newCursor.isNull() && !newCursor.atEnd()) {
           newCursor = document->find("/t", newCursor);

           if (!newCursor.isNull()) {
              newCursor.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor);

              newCursor.removeSelectedText();
              newCursor.insertText(" ");
          }
    }
    textEdit->setDocument(document);
    */
    dock->setVisible(true);
    buildOutput->setText(tr("Build yet to be implemented."));
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open"),tr(""),tr("Plays (*.play)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),tr("new.play"),tr("Plays (*.play)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool MainWindow::maybeSave()
{
    if (textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                                   tr("The document has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Play Editor"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "new.play";
    setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}








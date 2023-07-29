#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QTextEdit>
#include "highlighter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionFont_triggered();

    void on_actionbold_triggered(bool bold);

    void on_actionItalic_triggered(bool checked);

    void on_actionunderline_triggered(bool checked);

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionredo_triggered();

    void on_actionundo_triggered();

    void on_actionCplushightlight_triggered();

    void on_actionDefault_triggered();

private:
    Ui::Notepad *ui;
    QString currentFile;
    Highlighter *highlighter;

};
#endif // NOTEPAD_H



#include "notepad.h"
#include "./ui_notepad.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(15);
    ui->textEdit->setFont(font);
}

Notepad::~Notepad()
{
    delete ui;
}



void Notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void Notepad::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void Notepad::on_actionSave_triggered()
{
    QString fileName;
    if(currentFile.isEmpty()){
        fileName = QFileDialog::getSaveFileName(this, tr("Save"), "new", tr("Text files (*.txt)"));
        if(fileName.isEmpty())
            return;
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void Notepad::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), "new", tr("Text files (*.txt)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void Notepad::on_actionPrint_triggered()
{
    #if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
        QPrinter printDev;
    #if QT_CONFIG(printdialog)
        QPrintDialog dialog(&printDev, this);
        if (dialog.exec() == QDialog::Rejected)
            return;
    #endif // QT_CONFIG(printdialog)
        ui->textEdit->print(&printDev);
    #endif // QT_CONFIG(printer)
}


void Notepad::on_actionExit_triggered()
{
    QCoreApplication::quit();
}


void Notepad::on_actionFont_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if(fontSelected){
        ui->textEdit->setFont(font);
    }
}

void Notepad::on_actionbold_triggered(bool bold)
{
    bold ? ui->textEdit->setFontWeight(QFont::Bold) :
        ui->textEdit->setFontWeight(QFont::Normal);
}


void Notepad::on_actionItalic_triggered(bool italic)
{
    ui->textEdit->setFontItalic(italic);
}


void Notepad::on_actionunderline_triggered(bool underline)
{
    ui->textEdit->setFontUnderline(underline);
}


void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void Notepad::on_actionredo_triggered()
{
    ui->textEdit->redo();
}


void Notepad::on_actionundo_triggered()
{
    ui->textEdit->undo();
}


void Notepad::on_actionCplushightlight_triggered()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(15);
    ui->textEdit->setFont(font);
    highlighter = new Highlighter(ui->textEdit->document());
}


void Notepad::on_actionDefault_triggered()
{
    delete highlighter;
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(15);
    ui->textEdit->setFont(font);
}


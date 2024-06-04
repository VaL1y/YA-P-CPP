// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_loadButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Text Files (*.txt)"));
    if (!filename.isEmpty()) {
        dictionary.addWordsFromFile(filename.toStdString());
        updateDisplay(dictionary.getWordsAlphabetically());
    }
}

void MainWindow::on_saveButton_clicked() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("Text Files (*.txt)"));
    if (!filename.isEmpty()) {
        dictionary.saveToFile(filename.toStdString());
    }
}

void MainWindow::on_addButton_clicked() {
    QString word = ui->wordLineEdit->text();
    if (!word.isEmpty()) {
        dictionary.addWord(word.toStdString());
        updateDisplay(dictionary.getWordsAlphabetically());
    }
}

void MainWindow::on_sortAlphaButton_clicked() {
    updateDisplay(dictionary.getWordsAlphabetically());
}

void MainWindow::on_sortFreqButton_clicked() {
    updateDisplay(dictionary.getWordsByFrequency());
}

void MainWindow::updateDisplay(const std::vector<std::pair<std::string, int>>& words) {
    QStringList wordList;
    for (const auto& entry : words) {
        wordList.append(QString::fromStdString(entry.first) + ": " + QString::number(entry.second));
    }
    QStringListModel *model = new QStringListModel(this);
    model->setStringList(wordList);
    ui->listView->setModel(model);
}


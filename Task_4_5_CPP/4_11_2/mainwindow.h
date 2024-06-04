//
// Created by Валерий on 02.06.2024.
//

#ifndef INC_4_11_2_MAINWINDOW_H
#define INC_4_11_2_MAINWINDOW_H

#include <QMainWindow>
#include "dictionary.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_clearButton_clicked();
    void on_addLoadButton_clicked();
    void on_saveButton_clicked();
    void on_addButton_clicked();
    void on_sortAlphaButton_clicked();
    void on_sortFreqButton_clicked();

private:
    Ui::MainWindow *ui;
    Dictionary dictionary;
    void updateDisplay(const std::vector<std::pair<std::string, int>>& words);
};

#endif //INC_4_11_2_MAINWINDOW_H

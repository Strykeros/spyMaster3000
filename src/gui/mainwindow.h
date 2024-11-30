#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../core/lib.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AlgoArgsBuilder builder;

private slots:
    void onInputGiven();
    void onKeyGiven();
    void onEncryptBtnClicked();
    void onDecryptBtnClicked();
};
#endif // MAINWINDOW_H

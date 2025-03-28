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
    QString keyMaxCharLength;

private slots:
    void setKeyMaxCharLength(bool setInfinite);
    void onAlgoChanged(int index);
    void onInputGiven();
    void onKeyChanged(const QString &text);
    void onEncryptBtnClicked();
    void onDecryptBtnClicked();
    void onInputComboBoxChanged(const QString& text);
    void IVGiven();
    void CipherModeIndexChanged(int index);
    void onIVRandomBtnClicked();
    void setDisabledIVInput(bool setDisabled);
    void onHashKeyChecked(int state);
};
#endif // MAINWINDOW_H

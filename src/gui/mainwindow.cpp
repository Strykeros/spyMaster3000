#include <iostream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../util/util.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
	, builder(AlgoArgsBuilder(Algo::AES128))
{
    ui->setupUi(this);

	ui->key_err_label->hide();
	ui->input_err_label->hide();
    connect(ui->key_textbox, SIGNAL(editingFinished()), this, SLOT(onKeyGiven()));
    connect(ui->input_textbox, SIGNAL(textChanged()), this, SLOT(onInputGiven()));
    connect(ui->encrypt_btn, SIGNAL(clicked()), this, SLOT(onEncryptBtnClicked()));
    connect(ui->decrypt_btn, SIGNAL(clicked()), this, SLOT(onDecryptBtnClicked()));
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInputGiven() {
	try {
		builder.setInputAsPlainText(ui->input_textbox->toPlainText().toStdString());
		ui->input_err_label->hide();
	}
	catch (std::string err){
		ui->input_err_label->setText(err.c_str());
		ui->input_err_label->show();
	}
}

void MainWindow::onKeyGiven() {
	try {
		builder.setKey(ui->key_textbox->text().toStdString());
		ui->key_err_label->hide();
	}
	catch (std::string err){
		ui->key_err_label->setText(err.c_str());
		ui->key_err_label->show();
	}
}

void MainWindow::onEncryptBtnClicked() {
	AlgoArgs args;
	try {
		args = builder.build();
	}
	catch (std::string err) {
		std::cout << err << "\n";	
		return;
	}
	
	std::string encrypted = util::strToHex(spymaster::encryptText(args));
	ui->output_textbox->insertPlainText(QString::fromStdString(encrypted));
}

void MainWindow::onDecryptBtnClicked() {
	AlgoArgs args;
	try {
		args = builder.build();
	}
	catch (std::string err) {
		std::cout << err << "\n";	
		return;
	}
	
	std::string encrypted = spymaster::decryptText(args);
	ui->output_textbox->insertPlainText(QString::fromStdString(encrypted));
}


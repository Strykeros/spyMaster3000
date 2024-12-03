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
	
	// SET DEFAULTS
	ui->key_err_label->hide();
	ui->input_err_label->hide();
	ui->c_mode_err_label->hide();

	setKeyMaxCharLength();
	CipherModeIndexChanged(0);
	ui->key_size_label->setText("0 / " + keyMaxCharLength);

	// SET UP WIDGET CALLBACKS (signals)
    connect(ui->key_textbox, SIGNAL(editingFinished()), this, SLOT(onKeyGiven()));
    connect(ui->key_textbox, SIGNAL(textChanged(const QString&)), this, SLOT(onKeyChanged(const QString&)));
    connect(ui->input_textbox, SIGNAL(textChanged()), this, SLOT(onInputGiven()));
    connect(ui->encrypt_btn, SIGNAL(clicked()), this, SLOT(onEncryptBtnClicked()));
    connect(ui->decrypt_btn, SIGNAL(clicked()), this, SLOT(onDecryptBtnClicked()));
    connect(ui->input_comboBox, SIGNAL(currentTextChanged(const QString&)), this, SLOT(onInputComboBoxChanged(const QString &)));
    connect(ui->algo_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onAlgoChanged(int)));
    connect(ui->iv_textbox, SIGNAL(editingFinished()), this, SLOT(IVGiven()));
    connect(ui->c_mode_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(CipherModeIndexChanged(int)));
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CipherModeIndexChanged(int index) {
	// MUST BE THE SAME ORDER AS SHOWN IN THE SELECTION COMBOBOX 
	static const CipherMode cipherModes[] = {CipherMode::ECB, CipherMode::CBC, CipherMode::CTR};
	try {
		builder.setCipherMode(cipherModes[index]);
	}
	catch (...){
		std::cout << "Error changing cipher modes (this should not happen)\n";
	}
}
void MainWindow::IVGiven() {
	try {
		builder.setIV(ui->iv_textbox->text().toStdString());
		ui->c_mode_err_label->hide();
	}
	catch (std::string err){
		ui->c_mode_err_label->setText(err.c_str());
		ui->c_mode_err_label->show();
	}

}
void MainWindow::setKeyMaxCharLength() {
	keyMaxCharLength = QString::number(builder.getKeyRequiredBitSize() / 8);
}

void MainWindow::onAlgoChanged(int index) {
	// MUST BE THE SAME ORDER AS SHOWN IN THE SELECTION COMBOBOX 
	static const Algo algos[] = {Algo::AES128, Algo::CAESER, Algo::PLAYFAIR, Algo::DES};

	std::cout << "Selected " << getAlgoSpec(algos[index])->name << "\n";

	builder.reset(algos[index]);

	// update ui
	onInputGiven();
	onKeyGiven();
	setKeyMaxCharLength();
	onKeyChanged(ui->key_textbox->text());
}

void MainWindow::onInputComboBoxChanged(const QString& text) {
	onInputGiven();
}

void MainWindow::onInputGiven() {
	try {

		if(ui->input_comboBox->currentText() == "Text") {
			builder.setInputFromASCII(ui->input_textbox->toPlainText().toStdString());
		}
		else {
			builder.setInputFromHex(ui->input_textbox->toPlainText().toStdString());
		}
		ui->input_err_label->hide();
	}
	catch (std::string err){
		ui->input_err_label->setText(err.c_str());
		ui->input_err_label->show();
	}
}

void MainWindow::onKeyChanged(const QString &text) { 
	ui->key_size_label->setText(
		QString::number(text.length()) + " / " + keyMaxCharLength
	);	
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
	std::cout << "encrypted: " << encrypted << "\n";
	ui->output_textbox->insertPlainText(QString::fromStdString(encrypted));
}


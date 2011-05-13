#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QString>
#include <QSettings>
#include "ui/filechooseedit.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	ui->NewFNameEdit->setCaption(QString::fromLocal8Bit("Сохранить документ"));
	ui->NewFNameEdit->setFileMask(QString::fromLocal8Bit("Файл разметки (*.xml)"));
        ui->NewLibCombo->setFileMask(QString::fromLocal8Bit("Файл разметки (*.xml)"));

	ui->NewFramesEdit->setCaption(QString::fromLocal8Bit("Открыть источник кадров"));
	ui->NewFramesEdit->setMode(FileChooseEdit::MOpen);

        loadRecent();
	connectSignals();
	createModels();
	document.setComment(ui->NewCommentText);

	loadSettings();
	ui->ObjUsedList->setMother(ui->ObjLibList);
}

MainWindow::~MainWindow()
{
	writeSettings();
    delete ui;
}

void MainWindow::createModels()
{

}

void MainWindow::connectSignals()
{
	QObject::connect(ui->NewFNameEdit, SIGNAL(textChanged(QString)), &document, SLOT(setFileName(QString)));
	QObject::connect(&document, SIGNAL(FileNameChanged(QString)), ui->NewFNameEdit, SLOT(setText(QString)));

	QObject::connect(ui->NewFramesEdit, SIGNAL(textChanged(QString)), &document, SLOT(setFrameSource(QString)));
	QObject::connect(&document, SIGNAL(FrameSourceChanged(QString)), ui->NewFramesEdit, SLOT(setText(QString)));

        QObject::connect(ui->NewLibCombo, SIGNAL(editTextChanged(QString)), &document, SLOT(setLibrary(QString)));
	QObject::connect(&document, SIGNAL(LibraryChanged(QString)), ui->NewLibCombo, SLOT(setEditText(QString)));

	QObject::connect(ui->NewCreateButton, SIGNAL(clicked()), &document, SLOT(create()));
        QObject::connect(&document, SIGNAL(ParametersChecked(bool)), ui->NewCreateButton, SLOT(setEnabled(bool)));

	QObject::connect(&document, SIGNAL(locked(bool)), ui->NewLibButton, SLOT(setDisabled(bool)));
	QObject::connect(&document, SIGNAL(locked(bool)), ui->NewLibCombo, SLOT(setDisabled(bool)));
	QObject::connect(&document, SIGNAL(locked(bool)), ui->NewFramesEdit, SLOT(setDisabled(bool)));
	QObject::connect(&document, SIGNAL(locked(bool)), ui->NewFramesButton, SLOT(setDisabled(bool)));
	QObject::connect(&document, SIGNAL(locked(bool)), ui->NewClearButton, SLOT(setDisabled(bool)));
	QObject::connect(&document, SIGNAL(locked(bool)), ui->NewCreateButton, SLOT(setDisabled(bool)));

	QObject::connect(ui->FPSSpin, SIGNAL(valueChanged(int)), &document, SLOT(setFPS(int)));
	QObject::connect(&document, SIGNAL(FPSChanged(int)), ui->FPSSpin, SLOT(setValue(int)));

	QObject::connect(ui->FrameBiasSpin, SIGNAL(valueChanged(int)), &document, SLOT(setFrameBias(int)));
	QObject::connect(&document, SIGNAL(FrameBiasChanged(int)), ui->FrameBiasSpin, SLOT(setValue(int)));

	QObject::connect(ui->FrameSpeedSpin, SIGNAL(valueChanged(int)), &document, SLOT(setFrameSpeed(int)));
	QObject::connect(&document, SIGNAL(FrameSpeedChanged(int)), ui->FrameSpeedSpin, SLOT(setValue(int)));

	QObject::connect(ui->FrameSpeedSpin, SIGNAL(valueChanged(int)), &document, SLOT(setFrameSpeed(int)));
	QObject::connect(&document, SIGNAL(FrameSpeedChanged(int)), ui->FrameSpeedSpin, SLOT(setValue(int)));

	QObject::connect(ui->ObjAddButton, SIGNAL(clicked()), ui->ObjUsedList, SLOT(on_right_clicked()));
	QObject::connect(ui->ObjRemoveButton, SIGNAL(clicked()), ui->ObjUsedList, SLOT(on_left_clicked()));

        //for recent docs
        QObject::connect(&document, SIGNAL(created(QString)), recentdocs, SLOT(addFilename(QString)));
        QObject::connect(recentdocs, SIGNAL(dataChanged()), ui->listView, SLOT(reset()));
}


void MainWindow::writeSettings()
{
	QSettings settings;
	settings.beginGroup("MainWindow");
	settings.setValue("size", size());
	settings.setValue("pos", pos());
	settings.setValue("page", ui->stacked->currentIndex());
	settings.endGroup();
}

void MainWindow::loadSettings()
{
	QSettings settings;

	settings.beginGroup("MainWindow");
	resize(settings.value("size", QSize(800, 480)).toSize());
	move(settings.value("pos", QPoint(200, 200)).toPoint());
	ui->stacked->setCurrentIndex(settings.value("page", 0).toInt());
	settings.endGroup();
}

void MainWindow::loadRecent()
{
        recentdocs = new RecentDocs(this);
        ui->listView->setModel(recentdocs);
}

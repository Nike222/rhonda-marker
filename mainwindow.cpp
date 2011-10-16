#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//кнопка обзора к словарю
void MainWindow::on_toolButton_clicked()
{

    QString filename=QFileDialog::getOpenFileName (this, QString::fromLocal8Bit("Выберите словарь"),
                                                   QDir::currentPath(),
                                                    QString::fromLocal8Bit("Документ XML (*.xml)"));

    if (!filename.isEmpty()) ui->lineEdit->setText(filename);


}

//кнопка обзора к проекту
void MainWindow::on_toolButton_2_clicked()
{

     QString filename=QFileDialog::getOpenFileName (this, QString::fromLocal8Bit("Выберите проект"),
                                                    QDir::currentPath(),
                                                     QString::fromLocal8Bit("Документ XML (*.xml)"));
if (!filename.isEmpty()) ui->lineEdit_2->setText(filename);
}
//кнопка к источнику
void MainWindow::on_toolButton_3_clicked()
{

     int a=0;
     //QMessageBox::question(0,QString::fromLocal8Bit("Информация"),QString::fromLocal8Bit("Только русские символы. Мы в России"));
   a=QMessageBox::question(this,QString::fromLocal8Bit("Выбор источника"),QString::fromLocal8Bit("Открываем картинку ?"),QMessageBox::Ok,4);

   if(a==1)
   {
       QString filename=QFileDialog::getOpenFileName (this, QString::fromLocal8Bit("Выберите объекты"),
                                                   QDir::currentPath(),
                                                    QString::fromLocal8Bit("Изображение (*.png *.xpm *.jpg *.jpeg)") );
       if (!filename.isEmpty()) ui->lineEdit_3->setText(filename);
   }
   if(a==4)
   { QString directory = QFileDialog::getExistingDirectory(this,
                                QString::fromLocal8Bit("Выберите папку"), QDir::currentPath());
     if (!directory.isEmpty()) ui->lineEdit_3->setText(directory);
   }

}

void MainWindow::on_toolButton_5_clicked()
{
    QMenu *menu = new QMenu(tr("Menu"), this);

   menu->addAction(QString::fromLocal8Bit("&Файл"),this,SLOT(on_vibf_clicked()));
   menu->addAction(QString::fromLocal8Bit("&Папка"),this,SLOT(on_vibdir_clicked()));
  ui->toolButton_5->setMenu(menu);
 ui->toolButton_5->showMenu();
}
//выбор изображения
void MainWindow::on_vibf_clicked()
{
    QString filename=QFileDialog::getOpenFileName (this, QString::fromLocal8Bit("Выберите источник"),
                                                QDir::currentPath(),
                                                 QString::fromLocal8Bit("Изображение (*.png *.xpm *.jpg *.jpeg)") );
    if (!filename.isEmpty()) ui->lineEdit_3->setText(filename);
 }
//выбор директории
void MainWindow::on_vibdir_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                                    QString::fromLocal8Bit("Выберите папку"), QDir::currentPath());
         if (!directory.isEmpty()) ui->lineEdit_3->setText(directory);
 }
//переъод далее из первой настройки
void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
//переход назад из первой настройки
void MainWindow::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

//кнопка выбрать пушовская с меню
void MainWindow::on_pushButton_5_clicked()
{
    QMenu *menu = new QMenu(tr("Menu"), this);

   menu->addAction(QString::fromLocal8Bit("&Файл"),this,SLOT(on_vibf_clicked()));
   menu->addAction(QString::fromLocal8Bit("&Папка"),this,SLOT(on_vibdir_clicked()));
  ui->pushButton_5->setMenu(menu);
  ui->pushButton_5->showMenu();
}

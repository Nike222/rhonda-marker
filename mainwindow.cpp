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

//������ ������ � �������
void MainWindow::on_toolButton_clicked()
{

    QString filename=QFileDialog::getOpenFileName (this, QString::fromLocal8Bit("�������� �������"),
                                                   QDir::currentPath(),
                                                    QString::fromLocal8Bit("�������� XML (*.xml)"));

    if (!filename.isEmpty()) ui->lineEdit->setText(filename);


}

//������ ������ � �������
void MainWindow::on_toolButton_2_clicked()
{

     QString filename=QFileDialog::getOpenFileName (this, QString::fromLocal8Bit("�������� ������"),
                                                    QDir::currentPath(),
                                                     QString::fromLocal8Bit("�������� XML (*.xml)"));
if (!filename.isEmpty()) ui->lineEdit_2->setText(filename);
}
//������ � ���������
void MainWindow::on_toolButton_3_clicked()
{

     int a=0;
     //QMessageBox::question(0,QString::fromLocal8Bit("����������"),QString::fromLocal8Bit("������ ������� �������. �� � ������"));
   a=QMessageBox::question(this,QString::fromLocal8Bit("����� ���������"),QString::fromLocal8Bit("��������� �������� ?"),QMessageBox::Ok,4);

   if(a==1)
   {
       QString filename=QFileDialog::getOpenFileName (this, QString::fromLocal8Bit("�������� �������"),
                                                   QDir::currentPath(),
                                                    QString::fromLocal8Bit("����������� (*.png *.xpm *.jpg *.jpeg)") );
       if (!filename.isEmpty()) ui->lineEdit_3->setText(filename);
   }
   if(a==4)
   { QString directory = QFileDialog::getExistingDirectory(this,
                                QString::fromLocal8Bit("�������� �����"), QDir::currentPath());
     if (!directory.isEmpty()) ui->lineEdit_3->setText(directory);
   }

}

void MainWindow::on_toolButton_5_clicked()
{
    QMenu *menu = new QMenu(tr("Menu"), this);

   menu->addAction(QString::fromLocal8Bit("&����"),this,SLOT(on_vibf_clicked()));
   menu->addAction(QString::fromLocal8Bit("&�����"),this,SLOT(on_vibdir_clicked()));
  ui->toolButton_5->setMenu(menu);
 ui->toolButton_5->showMenu();
}
//����� �����������
void MainWindow::on_vibf_clicked()
{
    QString filename=QFileDialog::getOpenFileName (this, QString::fromLocal8Bit("�������� ��������"),
                                                QDir::currentPath(),
                                                 QString::fromLocal8Bit("����������� (*.png *.xpm *.jpg *.jpeg)") );
    if (!filename.isEmpty()) ui->lineEdit_3->setText(filename);
 }
//����� ����������
void MainWindow::on_vibdir_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                                    QString::fromLocal8Bit("�������� �����"), QDir::currentPath());
         if (!directory.isEmpty()) ui->lineEdit_3->setText(directory);
 }
//������� ����� �� ������ ���������
void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
//������� ����� �� ������ ���������
void MainWindow::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

//������ ������� ��������� � ����
void MainWindow::on_pushButton_5_clicked()
{
    QMenu *menu = new QMenu(tr("Menu"), this);

   menu->addAction(QString::fromLocal8Bit("&����"),this,SLOT(on_vibf_clicked()));
   menu->addAction(QString::fromLocal8Bit("&�����"),this,SLOT(on_vibdir_clicked()));
  ui->pushButton_5->setMenu(menu);
  ui->pushButton_5->showMenu();
}

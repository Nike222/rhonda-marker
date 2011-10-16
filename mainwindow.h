#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QDialog>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
     QDir currentDir;

private slots:
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_toolButton_5_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_clicked();
    void on_vibf_clicked();
    void on_vibdir_clicked();
};

#endif // MAINWINDOW_H

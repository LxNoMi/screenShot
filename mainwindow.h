#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include<QTimer>
#include<QPixmap>
#include<QDesktopWidget>
#include<QMessageBox>
#include<QDebug>
#include<QFileDialog>
#include<QClipboard>
#include<QContextMenuEvent>
#include<QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent *);

private slots:
    void on_pushButton_clicked();
    void shotScrennSlot();
    void savePictureSlot();
    void startProcessSlot();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QPixmap pixmap;
};

#endif // MAINWINDOW_H

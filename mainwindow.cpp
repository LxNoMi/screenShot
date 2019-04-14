#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMenu>
#include<QAction>
#include<QCursor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->savePictureButton,SIGNAL(clicked()),this,SLOT(savePictureSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->checkBox->isChecked())
    {
        this->hide();
        this->timer=new QTimer;
        QObject::connect(this->timer,SIGNAL(timeout()),this,SLOT(shotScrennSlot()));
        this->timer->start(ui->spinBox->value()*1000);
    }
    else
    {
        qApp->beep();//发出警告
    }
}

//截图
void MainWindow::shotScrennSlot()
{
    this->pixmap=QPixmap::grabWindow(QApplication::desktop()->winId());
    ui->scrennLabel->setPixmap(this->pixmap.scaled(ui->scrennLabel->size()));
    QClipboard *clipBoard=QApplication::clipboard();
    clipBoard->setPixmap(this->pixmap);
    this->show();
    this->timer->stop();
}

//保存图片
void MainWindow::savePictureSlot()
{
    QString PicName=QFileDialog::getSaveFileName(this,"保存文件:",QDir::currentPath());
    this->pixmap.save(PicName);
}

//contextMenuEvent(...)
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu=new QMenu(this);
    QAction *action=new QAction(this);
    QAction *processAction=new QAction;
    QObject::connect(action,SIGNAL(triggered()),this,SLOT(savePictureSlot()));
    QObject::connect(processAction,SIGNAL(triggered()),this,SLOT(startProcessSlot()));
    processAction->setText("记事本");
    action->setText("另存为");
    menu->addAction(action);
    menu->addSeparator();
    menu->addAction(processAction);
    menu->exec(QCursor::pos());
}

//启动记事本
void MainWindow::startProcessSlot()
{
    QProcess *process=new QProcess;
    process->start("notepad.exe");
}

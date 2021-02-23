#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,  800);
    this->setWindowTitle("秒表");
//    ui->lcdNumber->value();
    this->p_Timer = new QTimer(this);
    connect(this->p_Timer, SIGNAL(timeout()), this, SLOT(updateTimeAndDisplay()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTimeAndDisplay()
{
    QTime current = QTime::currentTime();
    int t = this->baseTime.msecsTo(current);
    QTime showTime(0, 0, 0, 0);
    showTime = showTime.addMSecs(t);
    str = showTime.toString("hh:mm:ss:zzz");
    ui->lcdNumber->display(str);
}

//开始
void MainWindow::on_Btn_Start_clicked()
{
    this->baseTime = QTime::currentTime();
    this->p_Timer->start(1);
    this->ui->Btn_Start->setEnabled(false);
}
//停止
void MainWindow::on_Btn_Stop_clicked()
{
    if(ui->Btn_Stop->text() == "停止")
    {
        ui->Btn_Stop->setText("清零");
        this->p_Timer->stop();
        this->ui->Btn_pause->setEnabled(false);
    }
    else
    {
        this->ui->lcdNumber->display("00:00:00:000");
        this->ui->textBrowser->clear();
        this->ui->Btn_Stop->setText("停止");
        this->ui->Btn_Start->setEnabled(true);
        this->ui->Btn_pause->setEnabled(true);
    }
}
//暂停
void MainWindow::on_Btn_pause_clicked()
{
    static QTime pauseTime;
    //点击暂停停下来，在次点击继续计时
    if(ui->Btn_pause->text() == "暂停")
    {
        pauseTime = QTime::currentTime();
        this->p_Timer->stop();
        ui->Btn_pause->setText("继续");
        this->ui->Btn_Stop->setEnabled(false);
    }
    else
    {
        QTime cut = QTime::currentTime();
        int t = pauseTime.msecsTo(cut);
        this->baseTime = this->baseTime.addMSecs(t);
        this->p_Timer->start(1);
        ui->Btn_pause->setText("暂停");
        this->ui->Btn_Start->setEnabled(true);
        this->ui->Btn_Stop->setEnabled(true);
    }

}
//打点
static int i = 0;
void MainWindow::on_Btn_log_clicked()
{
    i++;
    ui->textBrowser->append(QString("第%1次是:%2").arg(i).arg(str));
}

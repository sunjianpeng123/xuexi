#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    //更新时间
    void updateTimeAndDisplay();
private slots:
    void on_Btn_Start_clicked();

    void on_Btn_Stop_clicked();

    void on_Btn_pause_clicked();

    void on_Btn_log_clicked();

private:
    QTimer *p_Timer;//定时器
    QTime baseTime;
    QString str;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QListWidgetItem>
#include <QLabel>

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
    QProcess *myProcess;
    QLabel * storagePathLabel;
    QString program;
    QString fileNameTemp;
    QString storagePath;
    int pattern; //模式 0：单个  1：一键

    void setView();
    void getStoragePath();
private slots:
    void LinkDevices();
    void GetWifiMac();
    void GetEthernetMac();
    void GetModuleName();
    void GetSerialNumber();
    void GetAndroidVersion();
    void GetScreenResolution();
    void GetICType();
    void GetAllInfo();
    void GetAllApkPackageName();
    void SaveLog();
    void PullFile();
    void PushFile();
    void InstallAPK();
    void UninstallAPK();
    void ListWeightCopy(QListWidgetItem*);
    void CaptureScreen();
    void Vedio();
    void Restart();
    void NetworkConnect();
    void Recovery();
    void Fastboot();
    void About();

    //命令执行结束调用
    void FinishSolute(int);

};

#endif // MAINWINDOW_H

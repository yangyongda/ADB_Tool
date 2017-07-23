#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pattern = 0;
    //程序路径
    myProcess = new QProcess(this);
    program =  QDir::currentPath()+QDir::separator()+"adb"+QDir::separator()+"adb.exe";
    //设置界面
    setView();

    connect(ui->Link_Devices,SIGNAL(triggered(bool)),this,SLOT(LinkDevices()));
    connect(ui->WIFI_MAC,SIGNAL(triggered(bool)),this,SLOT(GetWifiMac()));
    connect(ui->Ethernet_MAC,SIGNAL(triggered(bool)),this,SLOT(GetEthernetMac()));
    connect(ui->Device_Module,SIGNAL(triggered(bool)),this,SLOT(GetModuleName()));
    connect(ui->SerialNumber,SIGNAL(triggered(bool)),this,SLOT(GetSerialNumber()));
    connect(ui->AndroidVersion,SIGNAL(triggered(bool)),this,SLOT(GetAndroidVersion()));
    connect(ui->Resolution,SIGNAL(triggered(bool)),this,SLOT(GetScreenResolution()));
    connect(ui->ICType,SIGNAL(triggered(bool)),this,SLOT(GetICType()));
    connect(ui->getAll_Info_btn,SIGNAL(clicked(bool)),this,SLOT(GetAllInfo()));
    connect(ui->Apk_List,SIGNAL(triggered(bool)),this,SLOT(GetAllApkPackageName()));
    connect(ui->Log,SIGNAL(triggered(bool)),this,SLOT(SaveLog()));
    connect(ui->PullFile,SIGNAL(triggered(bool)),this,SLOT(PullFile()));
    connect(ui->PushFile,SIGNAL(triggered(bool)),this,SLOT(PushFile()));
    connect(ui->InstallAPK,SIGNAL(triggered(bool)),this,SLOT(InstallAPK()));
    connect(ui->UninstallAPK,SIGNAL(triggered(bool)),this,SLOT(UninstallAPK()));
    connect(ui->apk_listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(ListWeightCopy(QListWidgetItem*)));
    connect(ui->Capture,SIGNAL(triggered(bool)),this,SLOT(CaptureScreen()));
    connect(ui->Vedio,SIGNAL(triggered(bool)),this,SLOT(Vedio()));
    connect(ui->Restart,SIGNAL(triggered(bool)),this,SLOT(Restart()));
    connect(ui->NetWorkConnect,SIGNAL(triggered(bool)),this,SLOT(NetworkConnect()));
    connect(ui->Recovery,SIGNAL(triggered(bool)),this,SLOT(Recovery()));
    connect(ui->FastBoot,SIGNAL(triggered(bool)),this,SLOT(Fastboot()));
    connect(ui->About,SIGNAL(triggered(bool)),this,SLOT(About()));
    connect(myProcess,SIGNAL(finished(int)),this,SLOT(FinishSolute(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setView()
{
    setWindowTitle("ADB Tool");
    //设置为固定宽高
    this->setMinimumWidth(900);
    this->setMaximumWidth(900);
    this->setMinimumHeight(560);
    this->setMaximumHeight(560);
    //拉伸下拉列表框的大小
    ui->horizontalLayout->setStretch(1,10);
    //设置centralWidget的背景，并且不影响子控件的背景
    ui->centralWidget->setStyleSheet("QWidget#centralWidget{background-image: url(:/image/image/background.png);}");

    ui->statusBar->showMessage(QStringLiteral("欢迎使用ADB Tool"));

}

void MainWindow::LinkDevices()
{
    ui->DeviceList->clear();
    QStringList arguments;
    arguments<<"devices";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","8");
        myProcess->start(program, arguments);

    }

}

void MainWindow::GetWifiMac()
{
    QStringList arguments;
    arguments<<"shell"<<"cat"<<"/sys/class/net/wlan0/address";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","9");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }

}

void MainWindow::GetEthernetMac()
{
    QStringList arguments;
    arguments<<"shell"<<"cat"<<"/sys/class/net/eth0/address";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","10");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();

    }
}

void MainWindow::GetModuleName()
{
    QStringList arguments;
    arguments<<"shell"<<"getprop"<<"ro.product.model";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","11");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void MainWindow::GetSerialNumber()
{
    QStringList arguments;
    arguments<<"shell"<<"getprop"<<"ro.serialno";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","12");
        myProcess->start(program, arguments);
    }
}

void MainWindow::GetAndroidVersion()
{
    QStringList arguments;
    arguments<<"shell"<<"getprop"<<"ro.build.version.release";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","13");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void MainWindow::GetScreenResolution()
{
    QStringList arguments;
    arguments<<"shell"<<"wm"<<"size";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","14");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void MainWindow::GetICType()
{
    QStringList arguments;
    arguments<<"shell"<<"getprop"<<"ro.hardware";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","15");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void MainWindow::GetAllInfo()
{
    pattern = 1;
    GetWifiMac();
    myProcess->waitForFinished();
    GetSerialNumber();
    myProcess->waitForFinished();
    GetScreenResolution();
    myProcess->waitForFinished();
    GetAndroidVersion();
    myProcess->waitForFinished();
    GetEthernetMac();
    myProcess->waitForFinished();
    GetModuleName();
    myProcess->waitForFinished();
    GetICType();
    if(pattern)
        ui->statusBar->showMessage(QStringLiteral("一键获取所有信息完成"),2000);
    pattern = 0;
}

void MainWindow::GetAllApkPackageName()
{
    QStringList arguments;
    arguments<<"shell"<<"pm"<<"list"<<"packages";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","16");
        ui->apk_listWidget->clear();
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void MainWindow::SaveLog()
{
    QString fileName = QFileDialog::getSaveFileName(this,QStringLiteral("保存Log文件到"),"D:\\",
                                 tr("Text files (*.txt);"));
    //qDebug() <<fileName;

    QStringList arguments;
    arguments<<"logcat"<<"-v"<<"threadtime";
    if(myProcess != NULL && program != NULL && fileName != "")
    {
        myProcess->setStandardOutputFile(fileName);
        myProcess->start(program, arguments);
        if(QMessageBox::information(this,QStringLiteral("读取Log中...."),
                                    QStringLiteral("是否停止读取？"))==QMessageBox::Ok)
        {
           myProcess->close();
           myProcess = new QProcess(this);
           connect(myProcess,SIGNAL(finished(int)),this,SLOT(FinishSolute(int)));
        }

    }


}

void MainWindow::PullFile()
{
    bool ok;
    QString fileName;
    QStringList arguments;
    QString remotePath = QInputDialog::getText(this,QStringLiteral("系统目录"),
                                               QStringLiteral("请输入要读取的系统文件:"),
                                               QLineEdit::Normal,
                                               QStringLiteral("/sdcard/"), &ok);
    if(ok && !remotePath.isEmpty())
    {
       fileName = QFileDialog::getSaveFileName(this,QStringLiteral("保存文件到"),"D:\\");
    }
    else
    {
       return;
    }

    arguments<<"pull"<<remotePath<<fileName;
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","1");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();

    }
}

void MainWindow::PushFile()
{
    bool ok = false;
    QString remotePath;
    QStringList arguments;
    QString fileName = QFileDialog::getOpenFileName(this,QStringLiteral("选择要发送的文件"),"D:\\");

    if(!fileName.isEmpty())
    {
        remotePath = QInputDialog::getText(this,QStringLiteral("系统目录"),
                                                   QStringLiteral("请输入要发送到的目录:"),
                                                   QLineEdit::Normal,
                                                   QStringLiteral("/sdcard/"), &ok);
    }

    arguments<<"push"<<fileName<<remotePath;
    if(myProcess != NULL && program != NULL && ok)
    {
        myProcess->setProperty("process","2");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
    }
}

void MainWindow::InstallAPK()
{
    QStringList arguments;
    QString fileName = QFileDialog::getOpenFileName(this,QStringLiteral("选择要安装的文件"),"D:\\");
    arguments<<"install"<<fileName;
    if(myProcess != NULL && program != NULL && !fileName.isEmpty())
    {
        myProcess->setProperty("process","3");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void MainWindow::UninstallAPK()
{
    bool ok;
    QStringList arguments;
    QString packageName = QInputDialog::getText(this,QStringLiteral("应用包名"),
                                                          QStringLiteral("请输入要卸载的应用的包名:"),
                                                          QLineEdit::Normal,
                                                          QStringLiteral("com."), &ok);
    arguments<<"uninstall"<<packageName;
    if(myProcess != NULL && program != NULL && !packageName.isEmpty() && ok)
    {
        myProcess->setProperty("process","4");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();

    }
}

void MainWindow::ListWeightCopy(QListWidgetItem * item)
{
    QClipboard *clipboard = QApplication::clipboard();   //获取系统剪贴板指针
    clipboard->clear();                                 //清空剪贴板中的内容
    clipboard->setText(item->text());                  //设置剪贴板内容
}

void MainWindow::CaptureScreen()
{
    QString fileName = QFileDialog::getSaveFileName(this,QStringLiteral("保存文件到"),"D:\\",
                                 tr("Images (*.png);"));
    //qDebug() <<fileName;

    QStringList arguments;
    arguments<<"shell"<<"screencap"<<"-p"<<"/sdcard/sc.png";
    if(myProcess != NULL && program != NULL && fileName != "")
    {
        myProcess->setProperty("process","5");
        fileNameTemp = fileName;
        myProcess->start(program, arguments);
    }
}

void MainWindow::Vedio()
{
    QString fileName = QFileDialog::getSaveFileName(this,QStringLiteral("保存视频文件到"),"D:\\",
                                 tr("Vedio files (*.mp4);"));
    //qDebug() <<fileName;

    QStringList arguments;
    arguments<<"shell"<<"screenrecord"<<"/sdcard/1.mp4";
    if(myProcess != NULL && program != NULL && fileName != "")
    {
        myProcess->start(program, arguments);
        if(QMessageBox::information(this,QStringLiteral("录屏中...."),
                                    QStringLiteral("是否停止录屏？"))==QMessageBox::Ok)
        {
           myProcess->close();
           myProcess = new QProcess(this);
           connect(myProcess,SIGNAL(finished(int)),this,SLOT(FinishSolute(int)));
           arguments.clear();
           arguments<<"pull"<<"/sdcard/1.mp4"<<fileName;
           myProcess->start(program, arguments);
        }

    }

}

void MainWindow::Restart()
{
    QStringList arguments;
    arguments<<"reboot";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->start(program, arguments);
    }
}

void MainWindow::NetworkConnect()
{
    bool ok;
    QStringList arguments;
    QString IP = QInputDialog::getText(this,QStringLiteral("设备IP"),
                                                          QStringLiteral("请输入连接的设备的IP:"),
                                                          QLineEdit::Normal,
                                                          QStringLiteral("192.168."), &ok);
    arguments<<"connect"<<IP;
    if(myProcess != NULL && program != NULL && !IP.isEmpty() && ok)
    {
        myProcess->setProperty("process","7");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();

    }
}

void MainWindow::Recovery()
{
    QStringList arguments;
    arguments<<"reboot"<<"recovery";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->start(program, arguments);
    }
}

void MainWindow::Fastboot()
{
    QStringList arguments;
    arguments<<"reboot"<<"bootloader";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->start(program, arguments);
    }
}

void MainWindow::About()
{
    QMessageBox::about(this,QStringLiteral("关于"),QStringLiteral("<font size='26' color='blue'>欢迎使用ADB Tool</font>\
                         <font size='5' color='black'><div style='text-align:center'>版本：V1.0</div></font>\
                         <font size='5' color='black'><div style='text-align:center'>作者：杨永达</div></font>"));
}

void MainWindow::FinishSolute(int)
{
    if(myProcess->property("process") == "1")
    {
        QMessageBox::information(this,QStringLiteral("传输结束"),QStringLiteral("文件传输结束"));
        ui->statusBar->showMessage(QStringLiteral("文件传输完成"),2000);
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "2")
    {
        QMessageBox::information(this,QStringLiteral("传输结束"),QStringLiteral("文件传输结束"));
        ui->statusBar->showMessage(QStringLiteral("文件传输完成"),2000);
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "3")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        if(output.contains("INSTALL_FAILED_OLDER_SDK"))
        {
            QMessageBox::warning(this, QStringLiteral("SDK版本问题"),QStringLiteral("请确认系统版本是否低于APK要求的最低SDK"));
            ui->statusBar->showMessage(QStringLiteral("安装失败"),2000);
        }
        else
        {
            ui->statusBar->showMessage(QStringLiteral("安装成功"),2000);
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "4")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        if(output.contains("DELETE_FAILED_INTERNAL_ERROR"))
        {
            QMessageBox::warning(this, QStringLiteral("卸载失败"),QStringLiteral("请确认输入的包名正确或是否是系统应用"));
            ui->statusBar->showMessage(QStringLiteral("卸载失败"),2000);

        }
        else
        {
            ui->statusBar->showMessage(QStringLiteral("卸载成功"),2000);
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "5")
    {
        QStringList arguments;
        myProcess->close();
        myProcess = new QProcess(this);
        myProcess->setProperty("process","6");
        connect(myProcess,SIGNAL(finished(int)),this,SLOT(FinishSolute(int)));
        arguments<<"pull"<<"/sdcard/sc.png"<<fileNameTemp;
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
    }
    else if(myProcess->property("process") == "6")
    {
        ui->statusBar->showMessage(QStringLiteral("截图完成"),2000);
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "7")
    {
        //qDebug() <<myProcess->readAllStandardOutput();
        QString output = QString(myProcess->readAllStandardOutput());
        if(output.contains("unable to connect to"))
        {
            QMessageBox::warning(this, QStringLiteral("连接失败"),QStringLiteral("请确认IP是否正确"));
            ui->statusBar->showMessage(QStringLiteral("连接失败"),2000);

        }
        else
        {
            ui->statusBar->showMessage(QStringLiteral("连接成功"),2000);
        }

        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "8")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split("\r\n");
        foreach (QString str, strList) {
            if(str.contains("\tdevice"))
            {
                QStringList deviceName = str.split("\t");
                ui->DeviceList->addItem(deviceName.at(0));
                ui->statusBar->showMessage(QStringLiteral("扫描已连接的设备结束"),2000);
            }
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "9")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        if(!output.contains("No such file or directory")){
            QStringList strList = output.split("\r\n");
            foreach (QString str, strList) {
                if(str.contains(":"))
                {
                    ui->WIFI_MAC_lineEdit->setText(str);
                    if(!pattern)
                        ui->statusBar->showMessage(QStringLiteral("获取WIFI MAC完成"),2000);
                }
            }
        }else{
            ui->WIFI_MAC_lineEdit->setText(QStringLiteral("请检查WIFI模块是否正常"));
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "10")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        if(!output.contains("No such file or directory")){
            QStringList strList = output.split("\r\n");
            foreach (QString str, strList) {
                if(str.contains(":"))
                {
                    ui->EthernetMAC_lineEdit->setText(str);
                    if(!pattern)
                        ui->statusBar->showMessage(QStringLiteral("获取以太网 MAC完成"),2000);
                }
            }
        }else {
            ui->EthernetMAC_lineEdit->setText(QStringLiteral("请检查以太网模块是否正常"));
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "11")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split("\r\n");
        foreach (QString str, strList) {
            if(str.contains("\r"))
            {
               ui->ModuleName_lineEdit->setText(str);
               if(!pattern)
                   ui->statusBar->showMessage(QStringLiteral("获取设备型号完成"),2000);
            }
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "12")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        ui->SerialNumber_lineEdit->setText(output);
        if(!pattern)
            ui->statusBar->showMessage(QStringLiteral("获取序列号完成"),2000);
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "13")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split("\r\n");
        foreach (QString str, strList) {
            if(str.contains("\r"))
            {
               ui->Android_Version_lineEdit->setText(str);
               if(!pattern)
                   ui->statusBar->showMessage(QStringLiteral("获取Android版本完成"),2000);
            }
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "14")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split(":");
        foreach (QString str, strList) {
            if(str.contains("\r"))
            {
               ui->Resolution_lineEdit->setText(str);
               if(!pattern)
                   ui->statusBar->showMessage(QStringLiteral("获取屏幕分辨率完成"),2000);
            }
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "15")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split("\r\n");
        foreach (QString str, strList) {
            if(str.contains("\r")){
                ui->ICType_lineEdit->setText(str);
                if(!pattern)
                   ui->statusBar->showMessage(QStringLiteral("获取主芯片型号完成"),2000);
            }
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "16")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split("\r\n");
        foreach (QString str, strList) {
            if(str.contains("\r"))
            {
                //qDebug() <<str.length();
               ui->apk_listWidget->addItem(str.mid(8,str.length()-9));
               ui->statusBar->showMessage(QStringLiteral("已获取所有APK包名"),2000);
            }
        }
        myProcess->setProperty("process",0);
    }
}

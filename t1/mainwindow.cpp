#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <iostream>
#include <string>
#include <QGridLayout>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *centerWindow = new QWidget;
    this->setCentralWidget(centerWindow);
    layout = new QGridLayout(this);
    l = new QGridLayout();
    l->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,100,100);
    layout->setColumnMinimumWidth(8,8);
    layout->setRowMinimumHeight(8,8);
    for(int i = 0;i < 81;i++)
    {
        s[i] = new QPushButton();
        connect(s[i],SIGNAL(clicked(bool)),this,SLOT(Input()));
        s[i]->setFixedSize(QSize(60,60));
        if(i < 10)
            s[i]->setObjectName("s0" + QString::number(i));
        else
            s[i]->setObjectName("s" + QString::number(i));
        s[i]->setText("");
        layout->addWidget(s[i]);
    }
    for(int i = 0;i < 9;i++)
    {
        button[i] = new QPushButton(QString::number(i + 1));
        button[i]->setFixedSize(40,40);
        button[i]->setCheckable(true);
        button[i]->setObjectName("num"+ QString::number(i));
        layout->addWidget(button[i]);
        connect(button[i],SIGNAL(clicked(bool)),this,SLOT(SelectInput()));
    }

    QPushButton *answer = new QPushButton();
    connect(answer,SIGNAL(clicked(bool)),this,SLOT(begin()));
    l->addWidget(answer);
    answer->setText("解题");


    QPushButton *quit = new QPushButton();
    connect(quit,SIGNAL(clicked(bool)),this,SLOT(exit()));
    l->addWidget(quit);
    quit->setText("退出");


    QPushButton *clear = new QPushButton();
    connect(clear,SIGNAL(clicked(bool)),this,SLOT(clear()));
    l->addWidget(clear);
    clear->setText("清除");


    layout->addLayout(l,10,9);
    centerWindow->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit()
{
    close();
}

void MainWindow::SelectInput()
{
    QString BtName = QObject::sender()->objectName();
    QString Number = BtName[3];
    int a = Number.toInt();
    if(button[a]->isChecked())
    {
        for(int i = 0;i < 10;i++)
        {
            if(i == a) continue;
            if(this->button[i]->isChecked())
            {
                this->button[i]->setChecked(false);
            }
        }
    }
}

void MainWindow::Input()
{
    QString BtName = QObject::sender()->objectName();
    QString Number1 = BtName[1];
    QString Number2 = BtName[2];
    Number1 += Number2;
    int num = 0;
    int a = Number1.toInt();
        for (int var = 0; var < 9; ++var) {
            if(button[var]->isChecked())
                num = var + 1;
        }
        if(s[a]->text() == QString::number(num))
            s[a]->setText("");
        else if(num == 0)
            s[a]->setText("");
        else
            s[a]->setText(QString::number(num));
      for(int i = 0;i < 9;i++)
      {
          for(int j = 0;j < 9;j++)
          {
              qDebug() << P[i][j];
              P[i][j] = s[9 * i + j]->text();
          }
      }
}

void MainWindow::Answer(int n)
{
    // 成功
        if(n > 80){
            flag = true;
            return;
        }
        int x = n / 9, y = n % 9;
        // 有值 跳过
        if(P[x][y] != ""){
            Answer(n + 1);
            return;
        }
        // 遍历
        for(int i = 1; i <= 9; i++){
            // 判断
            if(check(n, i)){
                // 判断成功 赋值
                P[x][y] = QString::number(i);
                Answer(n + 1);//判断填入当前数后的分支
                // 退出时判断是否完成  完成时退出
                if(flag){
                    return;
                }
                // 未完成 重置棋盘
                P[x][y] = "";
            }
        }
}

bool MainWindow::check(int n, int num)
{
    // 行
        for(int i = 0; i < 9; i ++){
            if(P[n/9][i] == QString::number(num)){
                return false;
            }
        }
        // 列
        for(int i = 0; i < 9; i ++) {
            if(P[i][n%9] == QString::number(num)){
                return false;
            }
        }

        // 宫
        int x = n / 9 / 3 * 3;
        int y = n % 9 / 3 * 3;
        for(int i = 0; i < 3; i ++) {
            for(int j = 0; j < 3; j ++) {
                if(P[x+i][y+j] == QString::number(num)) {
                    return false;
                }
            }
        }
        return true;
}

void MainWindow::begin()
{
    Answer(0);
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            s[i * 9 + j]->setText(P[i][j]);
        }
    }
}

void MainWindow::clear()
{
    for(int i = 0;i < 81;i++)
    {
        s[i]->setText("");
    }
}
























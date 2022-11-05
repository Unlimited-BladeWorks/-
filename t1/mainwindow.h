#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>
#include <QGridLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool check(int n, int num);
    void Answer(int n);
    ~MainWindow();

private slots:

    void exit();

    void SelectInput();

    void Input();

    void begin();

    void clear();

private:
    Ui::MainWindow *ui;
    QPushButton *button[9];
    QPushButton *s[81];
    QGridLayout *layout;
    QGridLayout *l;
    bool flag = false;
    QString P[9][9];
};
#endif // MAINWINDOW_H

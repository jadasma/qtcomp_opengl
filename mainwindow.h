#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



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

public slots:


private slots:
    void on_verticalSlider_actionTriggered(int action);
    void on_verticalSlider_2_actionTriggered(int action);
    void on_verticalSlider_3_actionTriggered(int action);
};

#endif // MAINWINDOW_H

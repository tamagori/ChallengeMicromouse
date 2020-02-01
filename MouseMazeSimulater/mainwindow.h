#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <drawmaze.h>
#include <simulatemazerun.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_drawMazeButton_clicked();

    void on_SimulateStart_clicked();

    void on_quitButton_clicked();

private:
    bool maze_read = false;
    SimulateMazeRun *simulate_run;
    Ui::MainWindow *ui;
    DrawMaze *drawmaze;
    QGraphicsScene *scene;
    uint8_t maze[MAZESIZE_X][MAZESIZE_Y];

    void init();
};
#endif // MAINWINDOW_H

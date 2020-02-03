#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;

    delete drawmaze;
    delete simulate_run;
}

void MainWindow::init()
{
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint);

    scene = new QGraphicsScene;

    ui->filePathEdit->setReadOnly(true);
    ui->actionHistoryEdit->setReadOnly(true);

    for(int i = 0; i < MAZESIZE_X; i++) {
        for(int j =0; j < MAZESIZE_Y; j++ ){
            maze[i][j] = 0;
        }
    }

    drawmaze = new DrawMaze();

    simulate_run = new SimulateMazeRun();
    simulate_run->setGoal(GOAL_X,GOAL_Y);

    drawmaze->init(scene);

    ui->graphicsView->setScene(scene);

    ui->SellSimuMode->addItem("leftHandSearch");
    ui->SellSimuMode->addItem("adachiSearch");
    ui->SellSimuMode->setCurrentText("adachiSearch");
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text File (*.txt);;"));

    if ( !fileName.isEmpty() ){
        QFile file(fileName);
        if ( !file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this, tr("Error"), tr("This System could not open File"));
            return;
        }

        QTextStream stream(&file);

        for ( int x = 0; x < MAZESIZE_X; x++ ){
            QString str = stream.readLine();
            ui->actionHistoryEdit->insertPlainText(str);
            ui->actionHistoryEdit->insertPlainText("\n");
            QList<QString> list = str.split(" ");
            for ( int y = 0; y < MAZESIZE_Y; y++ ){
                maze[x][y] = list[y].toInt();
            }
        }

        maze_read = true;
    } else {
        ui->actionHistoryEdit->setText("Not Exsit File");
    }
}

void MainWindow::on_drawMazeButton_clicked()
{
    drawmaze->drawWall(scene, maze);

    ui->graphicsView->setScene(scene);

    QMessageBox *box = new QMessageBox;
    box->setText("You push draw Maze Button");
    box->exec();
}

void MainWindow::on_SimulateStart_clicked()
{
    int Index = ui->SellSimuMode->currentIndex();

    if(maze_read){
        simulate_run->copyNowMazeData(maze);

        switch (Index)
        {
        case 0: /* leftHandSearch */
            simulate_run->leftHandSearch(scene);
            break;
        case 1: /* adachiSearch */
            simulate_run->adachiSearch(scene);
            break;
        default:
            simulate_run->leftHandSearch(scene);
            break;
        }
#if 0
        //simulate_run->leftHandSearch(scene);
        simulate_run->adachiSearch(scene);
#endif
        ui->graphicsView->setScene(scene);
    } else {
        ui->actionHistoryEdit->setText("Not Include Maze Data");
    }
}

void MainWindow::on_quitButton_clicked()
{
    qApp->quit();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player =new QMediaPlayer(this);
    vw=new QVideoWidget(this);
    audioOutput = new QAudioOutput(this);
    player->setVideoOutput(vw);
    player->setAudioOutput(audioOutput);
    this->setCentralWidget(vw);
    audioOutput->setVolume(80);

    player->setSource(QUrl::fromLocalFile("G:/anneMedintro.mp4"));
    player->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}


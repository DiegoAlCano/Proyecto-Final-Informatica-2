#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <cstdlib>
#include <ctime>
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);

    this->vista = new QGraphicsView(this);
    vista->resize(0,0);

    QImage fondoMenu(":/Recursos/FondoMenu.png");
    escena->setSceneRect(0,0,fondoMenu.width(),fondoMenu.height());
    ui->graphicsView->setBackgroundBrush(QBrush(fondoMenu));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    QImage background(":/Recursos/FondoNivel1.png");
    escena->setBackgroundBrush(QBrush(background));
    escena->setSceneRect(0, 0, background.width(), background.height());

    vista->setScene(escena);
    vista->resize(background.width()+20,background.height()+20);

    Heroe *Homero = new Heroe(0,0,150,160,100,0,":/Recursos/SpriteHomeroCaminando.png");
    escena->addItem(Homero);
    Homero->setPos(0,450);
    Homero->setFlag(QGraphicsItem::ItemIsFocusable);
    Homero->setFocus();

    //Creacion Donas

    // Inicializar la semilla para posiciones aleatorias
    std::srand(std::time(nullptr));

    // Temporizador para crear donas
    QTimer *donaTimer = new QTimer(this);
    connect(donaTimer, &QTimer::timeout, this, [=]() {
        Consumible *dona = new Consumible(":/Recursos/Dona.png",25,0,1);

        // Generar una posición aleatoria en el eje x (ajustando al ancho de la escena)
        int randomX = std::rand() % 540;
        dona->setPos(randomX, 0);        // Comienza en la parte superior de la escena

        // Añadir la dona a la escena
        escena->addItem(dona);
    });

    donaTimer->start(1500);  // Crear una dona cada segundo

    //Creacion Enemigos

    // Temporizador para crear enemigos desde los bordes
    QTimer *enemigoTimer = new QTimer(this);
    connect(enemigoTimer, &QTimer::timeout, this, [=]() {
        bool lado = (rand() % 2 == 0);
        Enemigo *enemigo = new Enemigo(lado,0,0,100,50,":/Recursos/Enemigo1.png");

        // Añadir el enemigo a la escena
        escena->addItem(enemigo);
    });

    enemigoTimer->start(3000);  // Crear un enemigo cada 3 segundos
}


void MainWindow::on_pushButton_7_clicked()
{
    QImage background(":/Recursos/FondoNivel2.png");
    escena->setBackgroundBrush(QBrush(background));
    escena->setSceneRect(0, 0, background.width(), background.height());

    vista->setScene(escena);
    vista->resize(background.width()+20,background.height()+20);

    Heroe *Bart = new Heroe(0,0,150,160,100,50,":/Recursos/SpriteBartCaminando.png");
    escena->addItem(Bart);
    Bart->setPos(0,450);
    Bart->setFlag(QGraphicsItem::ItemIsFocusable);
    Bart->setFocus();

    //Creacion Donas

    // Inicializar la semilla para posiciones aleatorias
    std::srand(std::time(nullptr));

    // Temporizador para crear donas
    QTimer *donaTimer = new QTimer(this);
    connect(donaTimer, &QTimer::timeout, this, [=]() {
        Consumible *Piedras = new Consumible(":/Recursos/Piedras.png",10,15,10);

        // Generar una posición aleatoria en el eje x (ajustando al ancho de la escena)
        int randomX = std::rand() % 540;
        Piedras->setPos(randomX, 0);        // Comienza en la parte superior de la escena

        // Añadir la dona a la escena
        escena->addItem(Piedras);
    });

    donaTimer->start(10000);  // Crear una dona cada segundo

    //Creacion Enemigos

    // Temporizador para crear enemigos desde los bordes
    QTimer *enemigoTimer = new QTimer(this);
    connect(enemigoTimer, &QTimer::timeout, this, [=]() {
        bool lado = (rand() % 2 == 0);
        Enemigo *enemigo = new Enemigo(lado,0,0,100,50,":/Recursos/Enemigo1.png");

        // Añadir el enemigo a la escena
        escena->addItem(enemigo);
    });

    enemigoTimer->start(3000);  // Crear un enemigo cada 3 segundos
}


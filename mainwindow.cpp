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

    this->vista = new QGraphicsView(this);
    this->escena = new QGraphicsScene(this);

    QPixmap background(":/Recursos/FondoNivel1.png");
    escena->setBackgroundBrush(QBrush(background));
    escena->setSceneRect(0, 0, background.width(), background.height());

    vista->setScene(escena);
    vista->resize(background.width(),background.height());
    Heroe *Homero = new Heroe;
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
    Consumible *dona = new Consumible();

        // Generar una posición aleatoria en el eje x (ajustando al ancho de la escena)
        int randomX = std::rand() % 540;
        dona->setPos(randomX, 0);        // Comienza en la parte superior de la escena

        // Añadir la dona a la escena
        escena->addItem(dona);
    });

    donaTimer->start(1000);  // Crear una dona cada segundo

    //Creacion Enemigos

    // Temporizador para crear enemigos desde los bordes
    QTimer *enemigoTimer = new QTimer(this);
    connect(enemigoTimer, &QTimer::timeout, this, [=]() {
        bool lado = (rand() % 2 == 0);
        Enemigo *enemigo = new Enemigo(lado);

        // Añadir el enemigo a la escena
        escena->addItem(enemigo);
    });

    enemigoTimer->start(3000);  // Crear un enemigo cada 2 segundos

}

MainWindow::~MainWindow()
{
    delete ui;
}

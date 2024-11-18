#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <cstdlib>
#include <ctime>
#include "QDebug"
#include <time.h>

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
        Consumible *dona = new Consumible(":/Recursos/Dona.png",25,0,0);

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
        Enemigo *enemigo = new Enemigo(lado,0,0,125,125,15,8,":/Recursos/SpriteEnemigo.png");

        // Añadir el enemigo a la escena
        escena->addItem(enemigo);
    });

    enemigoTimer->start(2000);  // Crear un enemigo cada cierto tiempo

    // Mostrar y actualizar el tiempo transcurrido
    QGraphicsTextItem *tiempoText = new QGraphicsTextItem();
    tiempoText->setDefaultTextColor(Qt::white);
    tiempoText->setFont(QFont("Algerian", 20));
    tiempoText->setPos(150,0);
    escena->addItem(tiempoText);

    int *tiempoRestante = new int(300);  // 5 minutos en segundos
    QTimer *duracionNivel = new QTimer(this);
    connect(duracionNivel, &QTimer::timeout, this, [=]() {
        if (*tiempoRestante > 0) {
            *tiempoRestante -= 1;
            int minutos = *tiempoRestante / 60;
            int segundos = *tiempoRestante % 60;
            tiempoText->setPlainText(QString("Tiempo: %1:%2")
                                         .arg(minutos, 2, 10, QChar('0'))
                                         .arg(segundos, 2, 10, QChar('0')));
        }

        else {
            duracionNivel->stop();
            tiempoText->setPlainText("¡Tiempo agotado!");
            Homero->disminuirVida(Homero->getVida());
        }
    });
    duracionNivel->start(1000);  // Actualizar cada segundo


    //Donas Consumidas
    QGraphicsTextItem *DonasText = new QGraphicsTextItem();
    DonasText->setDefaultTextColor(Qt::white);
    DonasText->setFont(QFont("Algerian", 20));
    DonasText->setPos(350,0);
    escena->addItem(DonasText);

    QTimer *actualizarDonas = new QTimer(this);
    connect(actualizarDonas, &QTimer::timeout, this, [=](){
        unsigned short int donasComidas = Homero->getScore();

        DonasText->setPlainText(QString("Donas: %1").arg(donasComidas));

    });
    actualizarDonas->start(500);


    QGraphicsTextItem *VidaText = new QGraphicsTextItem();
    VidaText->setDefaultTextColor(Qt::white);
    VidaText->setFont(QFont("Algerian", 20));
    VidaText->setPos(5,0);
    escena->addItem(VidaText);

    QTimer *actualizarVida = new QTimer(this);
    connect(actualizarVida, &QTimer::timeout, this, [=](){
        short int vidaActual = Homero->getVida();
        VidaText->setPlainText(QString("Vida: %1").arg(vidaActual));
        if (vidaActual <= 0) {
            actualizarVida->stop();
            duracionNivel->stop();
            donaTimer->stop();
            enemigoTimer->stop();
            actualizarDonas->stop();
            escena->clear();
            qDebug() << "La vida ha llegado a 0. Sal del nivel.";


        }
    });
    actualizarVida->start(100);

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
        Enemigo *enemigo = new Enemigo(lado,0,0,125,125,15,6,":/Recursos/SpriteEnemigo.png");

        // Añadir el enemigo a la escena
        escena->addItem(enemigo);
    });

    enemigoTimer->start(3000);  // Crear un enemigo cada 3 segundos
}

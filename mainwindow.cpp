#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <cstdlib>
#include <ctime>
#include "QDebug"
#include <time.h>
#include <QPushButton>
#include <QGraphicsProxyWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(670,670);

    this->escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);

    this->vista = new QGraphicsView(this);
    vista->resize(0,0);

    QImage fondoMenu(":/Recursos/FondoMenu.png");
    escena->setSceneRect(0,0,fondoMenu.width(),fondoMenu.height());
    ui->graphicsView->setBackgroundBrush(QBrush(fondoMenu));

    BotonNivel1 = new QPushButton("EL INFIERNO DE LAS ROSQUILLAS");
    BotonNivel1->setFixedSize(300, 25); // Establecer tamaño del botón
    BotonNivel1->setFont(QFont("Algerian", 10, QFont::Bold)); // Cambiar fuente y tamaño de texto

    QGraphicsProxyWidget *proxyIniciarN1 = escena->addWidget(BotonNivel1);
    proxyIniciarN1->setPos(160, 310); // Posición del botón en la escena

    BotonNivel2 = new QPushButton("PESADILLA EN EL AUTOBUS");
    BotonNivel2->setFixedSize(300, 25); // Establecer tamaño del botón
    BotonNivel2->setFont(QFont("Algerian", 10, QFont::Bold)); // Cambiar fuente y tamaño de texto

    QGraphicsProxyWidget *proxyIniciarN2 = escena->addWidget(BotonNivel2);
    proxyIniciarN2->setPos(160, 350); // Posición del botón en la escena

    BotonNivel3 = new QPushButton("EL REY DE LOS VAMPIROS");
    BotonNivel3->setFixedSize(300, 25); // Establecer tamaño del botón
    BotonNivel3->setFont(QFont("Algerian", 10, QFont::Bold)); // Cambiar fuente y tamaño de texto

    QGraphicsProxyWidget *proxyIniciarN3 = escena->addWidget(BotonNivel3);
    proxyIniciarN3->setPos(160, 390); // Posición del botón en la escena

    BotonSalir = new QPushButton("SALIR");
    BotonSalir->setFixedSize(300, 25); // Establecer tamaño del botón
    BotonSalir->setFont(QFont("Algerian", 10, QFont::Bold)); // Cambiar fuente y tamaño de texto

    QGraphicsProxyWidget *proxySalir = escena->addWidget(BotonSalir);
    proxySalir->setPos(160, 430); // Posición del botón en la escena

    connect(BotonNivel1, &QPushButton::clicked, this, &MainWindow::iniciarNivel1);
    connect(BotonNivel2, &QPushButton::clicked, this, &MainWindow::iniciarNivel2);
    connect(BotonSalir, &QPushButton::clicked, this, &MainWindow::salirJuego);
}

void MainWindow::iniciarNivel1()
{
    quitarBotones();

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

    //Barras de Vida
    QGraphicsRectItem *barraVidaRoja = new QGraphicsRectItem(0,0,100,20);
    barraVidaRoja->setPos(50, 10); // Posición en la escena
    barraVidaRoja->setBrush(QBrush(Qt::red));
    escena->addItem(barraVidaRoja);

    QGraphicsRectItem *barraVidaAmarilla = new QGraphicsRectItem();
    barraVidaAmarilla->setPos(50, 10); // Posición en la escena
    barraVidaAmarilla->setBrush(QBrush(Qt::yellow));
    escena->addItem(barraVidaAmarilla);

    // Mostrar y actualizar el tiempo transcurrido
    QGraphicsTextItem *tiempoText = new QGraphicsTextItem();
    tiempoText->setDefaultTextColor(Qt::white);
    tiempoText->setFont(QFont("Algerian", 20));
    tiempoText->setPos(500,0);
    escena->addItem(tiempoText);

    int *tiempoRestante = new int(300);  // 5 minutos en segundos
    QTimer *duracionNivel = new QTimer(this);
    connect(duracionNivel, &QTimer::timeout, this, [=]() {
        if (*tiempoRestante > 0) {
            *tiempoRestante -= 1;
            int minutos = *tiempoRestante / 60;
            int segundos = *tiempoRestante % 60;
            tiempoText->setPlainText(QString("%1:%2")
                                         .arg(minutos, 2, 10, QChar('0'))
                                         .arg(segundos, 2, 10, QChar('0')));
        }

        else {
            duracionNivel->stop();
            Homero->disminuirVida(Homero->getVida());
        }
    });
    duracionNivel->start(1000);  // Actualizar cada segundo


    QGraphicsTextItem *VidaText = new QGraphicsTextItem();
    VidaText->setDefaultTextColor(Qt::white);
    VidaText->setFont(QFont("Algerian", 20));
    VidaText->setPos(0,0);
    escena->addItem(VidaText);

    //Donas Consumidas
    QGraphicsTextItem *DonasText = new QGraphicsTextItem();
    DonasText->setDefaultTextColor(Qt::white);
    DonasText->setFont(QFont("Algerian", 20));
    DonasText->setPos(300,0);
    escena->addItem(DonasText);

    QTimer *actualizarInfo = new QTimer(this);
    connect(actualizarInfo, &QTimer::timeout, this, [=](){
        short int vidaActual = Homero->getVida();
        unsigned short int donasComidas = Homero->getScore();

        mostrarVida(barraVidaAmarilla,vidaActual);

        VidaText->setPlainText(QString("HP:                %1/100").arg(vidaActual));
        DonasText->setPlainText(QString("Donas: %1").arg(donasComidas));
        if (vidaActual <= 0) {

            actualizarInfo->stop();
            duracionNivel->stop();
            donaTimer->stop();
            enemigoTimer->stop();
            actualizarInfo->stop();

            escena->removeItem(Homero);
            escena->removeItem(VidaText);
            escena->removeItem(DonasText);
            escena->removeItem(tiempoText);
            escena->removeItem(barraVidaAmarilla);
            escena->removeItem(barraVidaRoja);

            qDebug() << "La vida ha llegado a 0. Sal del nivel.";
            mostrarGameOver();
        }

        else if(donasComidas==100){

            duracionNivel->stop();
            donaTimer->stop();
            enemigoTimer->stop();
            actualizarInfo->stop();

            escena->removeItem(Homero);
            escena->removeItem(DonasText);
            escena->removeItem(tiempoText);
            escena->removeItem(VidaText);
            escena->removeItem(barraVidaAmarilla);
            escena->removeItem(barraVidaRoja);

            mostrarVictoria();

        }
    });
    actualizarInfo->start(100);

}


void MainWindow::iniciarNivel2()
{
    quitarBotones();

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

    donaTimer->start(10000);

    //Creacion Enemigos

    // Temporizador para crear enemigos desde los bordes
    QTimer *enemigoTimer = new QTimer(this);
    connect(enemigoTimer, &QTimer::timeout, this, [=]() {
        bool lado = (rand() % 2 == 0);
        Enemigo *enemigo = new Enemigo(lado,0,0,125,125,15,6,":/Recursos/SpriteEnemigo.png");

        // Añadir el enemigo a la escena
        escena->addItem(enemigo);
    });

    enemigoTimer->start(3000);
}

void MainWindow::MenuPrincipal()
{

    QImage fondoMenu(":/Recursos/FondoMenu.png");
    escena->setBackgroundBrush(QBrush(fondoMenu));
    escena->setSceneRect(0,0,fondoMenu.width(),fondoMenu.height());
    ui->graphicsView->setBackgroundBrush(QBrush(fondoMenu));
    vista->setScene(escena);

    BotonNivel1->show();
    BotonNivel2->show();
    BotonNivel3->show();
    BotonSalir->show();

}


void MainWindow::quitarBotones()
{

    BotonNivel1->hide();
    BotonNivel2->hide();
    BotonNivel3->hide();
    BotonSalir->hide();

}

void MainWindow::mostrarGameOver()
{

    QGraphicsPixmapItem* gameOverImage = new QGraphicsPixmapItem(QPixmap(":/Recursos/GameOver.png"));
    gameOverImage->setPos(-10, 0);
    escena->addItem(gameOverImage);

    QTimer::singleShot(5000, this, [=]() {
        escena->removeItem(gameOverImage);
        MenuPrincipal();
    });

}

void MainWindow::mostrarVictoria()
{
    QGraphicsPixmapItem* VictoryImage = new QGraphicsPixmapItem(QPixmap(":/Recursos/FondoVictoria.png"));
    VictoryImage->setPos(-10, 0);
    escena->addItem(VictoryImage);

    QTimer::singleShot(5000, this, [=]() {
        escena->removeItem(VictoryImage);
        MenuPrincipal();
    });
}

void MainWindow::mostrarVida(QGraphicsRectItem *barraVidaAmarilla ,int vidaActual)
{
    short int vidaDisponible = 100-vidaActual;

    barraVidaAmarilla->setRect(100-vidaDisponible,0,vidaDisponible,20);
}


void MainWindow::salirJuego()
{
    close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

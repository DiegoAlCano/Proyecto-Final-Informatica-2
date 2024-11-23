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
    BotonNivel1->setFixedSize(300, 25);
    BotonNivel1->setFont(QFont("Algerian", 10, QFont::Bold));

    QGraphicsProxyWidget *proxyIniciarN1 = escena->addWidget(BotonNivel1);
    proxyIniciarN1->setPos(160, 310); // Posición del botón en la escena

    BotonNivel2 = new QPushButton("PESADILLA EN EL AUTOBUS");
    BotonNivel2->setFixedSize(300, 25);
    BotonNivel2->setFont(QFont("Algerian", 10, QFont::Bold));

    QGraphicsProxyWidget *proxyIniciarN2 = escena->addWidget(BotonNivel2);
    proxyIniciarN2->setPos(160, 350);

    BotonNivel3 = new QPushButton("EL REY DE LOS VAMPIROS");
    BotonNivel3->setFixedSize(300, 25);
    BotonNivel3->setFont(QFont("Algerian", 10, QFont::Bold));

    QGraphicsProxyWidget *proxyIniciarN3 = escena->addWidget(BotonNivel3);
    proxyIniciarN3->setPos(160, 390);

    BotonSalir = new QPushButton("SALIR");
    BotonSalir->setFixedSize(300, 25);
    BotonSalir->setFont(QFont("Algerian", 10, QFont::Bold));

    QGraphicsProxyWidget *proxySalir = escena->addWidget(BotonSalir);
    proxySalir->setPos(160, 430); // Posición del botón en la escena

    connect(BotonNivel1, &QPushButton::clicked, this, &MainWindow::iniciarNivel1);
    connect(BotonNivel2, &QPushButton::clicked, this, &MainWindow::iniciarNivel2);
    connect(BotonNivel3, &QPushButton::clicked, this, &MainWindow::iniciarNivel3);
    connect(BotonSalir, &QPushButton::clicked, this, &MainWindow::salirJuego);
}

void MainWindow::iniciarNivel1()
{
    quitarBotones();

    QGraphicsScene *escenaNivel1 = new QGraphicsScene(this);

    QImage background(":/Recursos/FondoNivel1.png");
    escenaNivel1->setBackgroundBrush(QBrush(background));
    escenaNivel1->setSceneRect(0, 0, background.width(), background.height());

    vista->setScene(escenaNivel1);
    vista->resize(background.width()+20,background.height()+20);

    //Creacion de Personajes y consumibles
//-----------------------------------------------------------------------------------------------------------------------
    Heroe *Homero = new Heroe(0,0,150,160,100,0,":/Recursos/SpritesHomero.png");
    escenaNivel1->addItem(Homero);
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
        escenaNivel1->addItem(dona);
    });

    donaTimer->start(1500);  // Crear una dona cada segundo

    //Creacion Enemigos

    // Temporizador para crear enemigos desde los bordes
    QTimer *enemigoTimer = new QTimer(this);
    connect(enemigoTimer, &QTimer::timeout, this, [=]() {
        bool lado = (rand() % 2 == 0);
        Enemigo *enemigo = new Enemigo(lado,0,0,125,125,15,9,":/Recursos/SpriteEnemigo.png");

        // Añadir el enemigo a la escena
        escenaNivel1->addItem(enemigo);
    });

    enemigoTimer->start(2000);  // Crear un enemigo cada cierto tiempo

    QTimer *enemigoVoladorTimer = new QTimer(this);
    connect(enemigoVoladorTimer, &QTimer::timeout, this, [=]() {
        Enemigo *enemigoVolador = new Enemigo(0,0,146,50,20,":/Recursos/EnemigoVolador.png");

        // Añadir el enemigo a la escena
        escenaNivel1->addItem(enemigoVolador);
    });

    enemigoVoladorTimer->start(10000);

//-----------------------------------------------------------------------------------------------------------------------

    //ELEMENTOS GRAFICOS

//-----------------------------------------------------------------------------------------------------------------------
    //Barras de Vida
    QGraphicsRectItem *barraVidaRoja = new QGraphicsRectItem(0,0,100,20);
    barraVidaRoja->setPos(50, 10); // Posición en la escena
    barraVidaRoja->setBrush(QBrush(Qt::red));
    escenaNivel1->addItem(barraVidaRoja);

    QGraphicsRectItem *barraVidaAmarilla = new QGraphicsRectItem();
    barraVidaAmarilla->setPos(50, 10); // Posición en la escena
    barraVidaAmarilla->setBrush(QBrush(Qt::yellow));
    escenaNivel1->addItem(barraVidaAmarilla);

    QPixmap Dona(":/Recursos/Dona.png");
    QPixmap DonaRedimensionada = Dona.scaled(45,45,Qt::KeepAspectRatio);
    QGraphicsPixmapItem *itemDona = new QGraphicsPixmapItem(DonaRedimensionada);
    itemDona->setPos(320, -5); // Posición en la escena
    escenaNivel1->addItem(itemDona);

    QPixmap Corazon(":/Recursos/corazon.png");
    QPixmap CorazonRedimensionado = Corazon.scaled(45,45,Qt::KeepAspectRatio);
    QGraphicsPixmapItem *itemCorazon = new QGraphicsPixmapItem(CorazonRedimensionado);
    itemCorazon->setPos(0, -5); // Posición en la escena
    escenaNivel1->addItem(itemCorazon);

    QPixmap Reloj(":/Recursos/Reloj.png");
    QPixmap RelojRedimensionado = Reloj.scaled(45,45,Qt::KeepAspectRatio);
    QGraphicsPixmapItem *itemReloj = new QGraphicsPixmapItem(RelojRedimensionado);
    itemReloj->setPos(480, -5); // Posición en la escena
    escenaNivel1->addItem(itemReloj);
//-----------------------------------------------------------------------------------------------------------------------

    //ELEMENTOS DE TEXTO

//-----------------------------------------------------------------------------------------------------------------------
    // Mostrar y actualizar el tiempo transcurrido
    QGraphicsTextItem *tiempoText = new QGraphicsTextItem();
    tiempoText->setDefaultTextColor(Qt::white);
    tiempoText->setFont(QFont("Algerian", 20));
    tiempoText->setPos(520,0);
    escenaNivel1->addItem(tiempoText);

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

        //Condicion de Derrota (Le quito toda la vida al heroe)
        else {
            duracionNivel->stop();
            Homero->disminuirVida(100);
        }
    });
    duracionNivel->start(1000);  // Actualizar cada segundo

    //Vida Disponible
    QGraphicsTextItem *VidaText = new QGraphicsTextItem();
    VidaText->setDefaultTextColor(Qt::white);
    VidaText->setFont(QFont("Algerian", 20));
    VidaText->setPos(150,0);
    escenaNivel1->addItem(VidaText);

    //Donas Consumidas
    QGraphicsTextItem *DonasText = new QGraphicsTextItem();
    DonasText->setDefaultTextColor(Qt::white);
    DonasText->setFont(QFont("Algerian", 20));
    DonasText->setPos(365,0);
    escenaNivel1->addItem(DonasText);

    QTimer *actualizarInfo = new QTimer(this);
    connect(actualizarInfo, &QTimer::timeout, this, [=](){
        short int vidaActual = Homero->getVida();
        short int donasComidas = Homero->getScore();

        mostrarVida(barraVidaAmarilla,vidaActual);

        VidaText->setPlainText(QString("%1/100").arg(vidaActual));
        DonasText->setPlainText(QString("X %1").arg(donasComidas));
        //Condicion de Derrota
        if (vidaActual <= 0) {

            actualizarInfo->stop();
            duracionNivel->stop();
            donaTimer->stop();
            enemigoTimer->stop();
            actualizarInfo->stop();
            enemigoVoladorTimer->stop();

            escenaNivel1->clear();

            qDebug() << "La vida ha llegado a 0. Sal del nivel.";
            mostrarGameOver(escenaNivel1);
        }
        //Condicion de Victoria
        else if(donasComidas==100){

            duracionNivel->stop();
            donaTimer->stop();
            enemigoTimer->stop();
            actualizarInfo->stop();
            enemigoVoladorTimer->stop();

            escenaNivel1->clear();

            mostrarVictoria(escenaNivel1);

        }
    });
    actualizarInfo->start(100);
//-----------------------------------------------------------------------------------------------------------------------

}


void MainWindow::iniciarNivel2()
{
    quitarBotones();

    QImage background(":/Recursos/FondoNivel2.png");
    escena->setBackgroundBrush(QBrush(background));
    escena->setSceneRect(0, 0, background.width(), background.height());

    vista->setScene(escena);
    vista->resize(background.width()+20,background.height()+20);

    Heroe *Bart = new Heroe(0,0,150,160,100,50,":/Recursos/SpritesBart.png");
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
        Enemigo *enemigo = new Enemigo(lado,0,0,130,130,15,6,":/Recursos/SpriteGremlin.png");

        // Añadir el enemigo a la escena
        escena->addItem(enemigo);
    });

    enemigoTimer->start(3000);
}

void MainWindow::iniciarNivel3()
{
    quitarBotones();

    bool Sala1 = true;  //La idea es alcanzar un logro o score en cada sala para desbloquear la siguiente
    bool Sala2 = true;  //Con estos boleanos verifico si se logro el requisito para pasar a la siguiente sala

    fondoCambiado1 = false;
    fondoCambiado2 = false;

    QGraphicsScene *escenaNivel3 = new QGraphicsScene(this);

    QImage background(":/Recursos/FondoNivel3.png");
    escenaNivel3->setBackgroundBrush(QBrush(background));
    escenaNivel3->setSceneRect(0, 0, background.width(), background.height());

    vista->setScene(escenaNivel3);
    vista->resize(background.width() + 20, background.height() + 20);

    Heroe *Homero = new Heroe(0, 0, 150, 160, 100, 12, ":/Recursos/SpritesHomero.png");
    escenaNivel3->addItem(Homero);
    Homero->setPos(0, 450);
    Homero->setFlag(QGraphicsItem::ItemIsFocusable);
    Homero->setFocus();

    QTimer *FlechasTimer = new QTimer(this);
    connect(FlechasTimer, &QTimer::timeout, this, [=]() {
        Consumible *Flechas = new Consumible(":/Recursos/Flechas.png",10,15,10);

        // Generar una posición aleatoria en el eje x (ajustando al ancho de la escena)
        int randomX = std::rand() % 540;
        Flechas->setPos(randomX, 0);        // Comienza en la parte superior de la escena

        // Añadir la dona a la escena
        escenaNivel3->addItem(Flechas);
    });

    FlechasTimer->start(10000);

    /*
    QTimer *enemigoTimer = new QTimer(this);
    connect(enemigoTimer, &QTimer::timeout, this, [=]() {
        bool lado = (rand() % 2 == 0);
        Enemigo *enemigo = new Enemigo(lado,0,0,150,160,15,10,":/Recursos/Enemigo2.png");

        // Añadir el enemigo a la escena
        escenaNivel3->addItem(enemigo);
    });
    enemigoTimer->start(3000);
    */

    QTimer *posHeroe = new QTimer(this);
    connect(posHeroe, &QTimer::timeout, this, [=]() {
        qreal posicionHeroX = Homero->getPosX(); // Obtener posición X del héroe


        if (posicionHeroX >= 554) {
            if(!fondoCambiado1 and !fondoCambiado2 and Sala1){
                QImage background2(":/Recursos/Fondo2Nivel3.PNG");
                escenaNivel3->setBackgroundBrush(QBrush(background2));
                fondoCambiado1 = true; // Marcar que el fondo ha cambiad
                fondoCambiado2 = false;
                Homero->modificarPosX(-40);
            }
            else if(fondoCambiado1 and Sala2){
                QImage background2(":/Recursos/Fondo3Nivel3.png");
                escenaNivel3->setBackgroundBrush(QBrush(background2));
                fondoCambiado2 = true; // Marcar que el fondo ha cambiad
                fondoCambiado1 = false;
                Homero->modificarPosX(-40);
            }

        }

        else if (posicionHeroX <= -54) {
            if(fondoCambiado2){
                QImage background2(":/Recursos/Fondo2Nivel3.PNG");
                escenaNivel3->setBackgroundBrush(QBrush(background2));
                fondoCambiado1 = true; // Marcar que el fondo ha cambiad
                fondoCambiado2 = false;
                Homero->setPos(550,450);
                Homero->modificarPosX(550);
            }
            else if(fondoCambiado1){
                escenaNivel3->setBackgroundBrush(QBrush(background));
                fondoCambiado1 = false; // Revertir el cambio de fondo
                fondoCambiado2 = false;
                Homero->setPos(550,450);
                Homero->modificarPosX(550);
            }

        }
    });

    posHeroe->start(100);

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

void MainWindow::mostrarGameOver(QGraphicsScene *escenaActual)
{

    QGraphicsPixmapItem* gameOverImage = new QGraphicsPixmapItem(QPixmap(":/Recursos/GameOver.png"));
    gameOverImage->setPos(-10, 0);
    escenaActual->addItem(gameOverImage);

    QTimer::singleShot(5000, this, [=]() {
        escenaActual->removeItem(gameOverImage);
        MenuPrincipal();
    });

}

void MainWindow::mostrarVictoria(QGraphicsScene *escenaActual)
{
    QGraphicsPixmapItem* VictoryImage = new QGraphicsPixmapItem(QPixmap(":/Recursos/FondoVictoria.png"));
    VictoryImage->setPos(-10, 0);
    escenaActual->addItem(VictoryImage);

    QTimer::singleShot(5000, this, [=]() {
        escenaActual->removeItem(VictoryImage);
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


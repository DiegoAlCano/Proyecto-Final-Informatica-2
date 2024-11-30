#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <cstdlib>
#include <ctime>
#include "QDebug"
#include <time.h>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "Heroe.h"

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
    Heroe *Homero = new Heroe('1',450,0,0,150,160,100,0,":/Recursos/SpritesHomero.png");
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
    timers.append(donaTimer);

    //Creacion Enemigos

    // Temporizador para crear enemigos desde los bordes
    QTimer *enemigoTimer = new QTimer(this);
    connect(enemigoTimer, &QTimer::timeout, this, [=]() {
        bool lado = (rand() % 2 == 0);
        Enemigo *enemigo = new Enemigo(lado,0,0,125,125,15,9,505,7,":/Recursos/SpriteEnemigo.png");

        // Añadir el enemigo a la escena
        escenaNivel1->addItem(enemigo);
    });

    enemigoTimer->start(2000);  // Crear un enemigo cada cierto tiempo
    timers.append(enemigoTimer);

    QTimer *enemigoVoladorTimer = new QTimer(this);
    connect(enemigoVoladorTimer, &QTimer::timeout, this, [=]() {
        Enemigo *enemigoVolador = new Enemigo(1,0,0,146,50,20,6,":/Recursos/EnemigoVolador.png");

        // Añadir el enemigo a la escena
        escenaNivel1->addItem(enemigoVolador);
    });

    enemigoVoladorTimer->start(10000);
    timers.append(enemigoVoladorTimer);

    //-----------------------------------------------------------------------------------------------------------------------

    //ELEMENTOS GRAFICOS

    //-----------------------------------------------------------------------------------------------------------------------
    //Barras de Vida
    QGraphicsRectItem *barraVidaRoja = nullptr;
    QGraphicsRectItem *barraVidaAmarilla = nullptr;
    añadirBarrasVida(escenaNivel1,50,10,barraVidaRoja,barraVidaAmarilla);

    añadirElementoGrafico(escenaNivel1,320,-5,45,45,":/Recursos/Dona.png");
    añadirElementoGrafico(escenaNivel1,0,-5,45,45,":/Recursos/corazon.png");
    añadirElementoGrafico(escenaNivel1,480,-5,45,45,":/Recursos/Reloj.png");
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
    timers.append(duracionNivel);

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

            detenerTimers();

            escenaNivel1->clear();

            qDebug() << "La vida ha llegado a 0. Sal del nivel.";
            mostrarGameOver(escenaNivel1);
        }
        //Condicion de Victoria
        else if(donasComidas==100){

            detenerTimers();

            escenaNivel1->clear();

            mostrarVictoria(escenaNivel1);

        }
    });
    actualizarInfo->start(100);
    timers.append(actualizarInfo);
    //-----------------------------------------------------------------------------------------------------------------------

}


void MainWindow::iniciarNivel2()
{
    quitarBotones();

    QGraphicsScene *escenaNivel2 = new QGraphicsScene(this);

    QImage background(":/Recursos/FondoNivel2.png");
    escenaNivel2->setBackgroundBrush(QBrush(background));
    escenaNivel2->setSceneRect(0, 0, background.width(), background.height());

    vista->setScene(escenaNivel2);
    vista->resize(background.width()+20,background.height()+20);

    //Creacion de Personaje y Enemigos
    //--------------------------------------------------------------------------------------------------------------
    Heroe *Bart = new Heroe('2',130,0,0,150,160,100,15,":/Recursos/SpritesBart.png");
    escenaNivel2->addItem(Bart);
    Bart->setPos(100,130);
    Bart->setFlag(QGraphicsItem::ItemIsFocusable);
    Bart->setFocus();


    // Temporizador para crear enemigos desde los bordes
    QTimer *enemigoTimer = new QTimer(this);
    connect(enemigoTimer, &QTimer::timeout, this, [=]() {
        bool lado = (rand() % 2 == 0);
        Enemigo *enemigo = new Enemigo(lado,0,0,130,130,20,13,130,550,135,10,7,":/Recursos/SpriteGremlin.png");

        // Añadir el enemigo a la escena
        escenaNivel2->addItem(enemigo);
        connect(enemigo, &Enemigo::enemigoEliminado, Bart, &Heroe::aumentarScore);
    });
    enemigoTimer->start(2000);
    timers.append(enemigoTimer);

    //Creacion de elementos Graficos
    //-------------------------------------------------------------------------------------------------------------
    QGraphicsRectItem *barraVidaRoja = nullptr;
    QGraphicsRectItem *barraVidaAmarilla = nullptr;
    añadirBarrasVida(escenaNivel2,50,10,barraVidaRoja,barraVidaAmarilla);

    añadirElementoGrafico(escenaNivel2, 0,-5,45,45,":/Recursos/corazon.png");
    añadirElementoGrafico(escenaNivel2,300,0,45,45,":/Recursos/piedra.png");
    añadirElementoGrafico(escenaNivel2,450,0,45,45,":/Recursos/ImagenGremlin.png");

    //Creacion de elementos de texto
    //------------------------------------------------------------------------------------------------------------
    QGraphicsTextItem *VidaText = new QGraphicsTextItem();
    VidaText->setDefaultTextColor(Qt::white);
    VidaText->setFont(QFont("Algerian", 20));
    VidaText->setPos(150,0);
    escenaNivel2->addItem(VidaText);

    QGraphicsTextItem *MunicionText = new QGraphicsTextItem();
    MunicionText->setDefaultTextColor(Qt::white);
    MunicionText->setFont(QFont("Algerian", 20));
    MunicionText->setPos(350,0);
    escenaNivel2->addItem(MunicionText);

    QGraphicsTextItem *ScoreActualText = new QGraphicsTextItem();
    ScoreActualText->setDefaultTextColor(Qt::white);
    ScoreActualText->setFont(QFont("Algerian", 20));
    ScoreActualText->setPos(500,0);
    escenaNivel2->addItem(ScoreActualText);

    //Actualizacion de estado del nivel
    //-------------------------------------------------------------------------------------------------------------
    QTimer *actualizarInfo = new QTimer(this);
    connect(actualizarInfo, &QTimer::timeout, this, [=](){
        unsigned short int vidaActual = Bart->getVida();
        unsigned short int municionActual = Bart->getMunicion();
        unsigned short int scoreActual = Bart->getScore();

        mostrarVida(barraVidaAmarilla,vidaActual);

        VidaText->setPlainText(QString("%1/100").arg(vidaActual));
        MunicionText->setPlainText(QString("x%1").arg(municionActual));
        ScoreActualText->setPlainText(QString("x%1").arg(scoreActual));
        //Condicion de Derrota
        if(scoreActual == 12){
            detenerTimers();

            escenaNivel2->clear();

            iniciarSegundaParteNivel2(escenaNivel2);
        }

        else if (vidaActual <= 0 or (municionActual == 0 and scoreActual<12)) {
            detenerTimers();
            escenaNivel2->clear();

            mostrarGameOver(escenaNivel2);
        }
    });
    actualizarInfo->start(100);
    timers.append(actualizarInfo);

}

void MainWindow::iniciarNivel3()
{
    quitarBotones();

    fondoCambiado1 = false;
    fondoCambiado2 = false;

    sala1 = false;
    sala2 = false;

    QGraphicsScene *escenaNivel3 = new QGraphicsScene(this);

    QImage background(":/Recursos/FondoNivel3.png");
    escenaNivel3->setBackgroundBrush(QBrush(background));
    escenaNivel3->setSceneRect(0, 0, background.width(), background.height());

    vista->setScene(escenaNivel3);
    vista->resize(background.width() + 20, background.height() + 20);

    //Creacion de Personaje y consumibles
    //-------------------------------------------------------------------------------------------------------------
    Heroe *Homero = new Heroe('3',450,0, 0, 150, 160, 100, 12, ":/Recursos/SpritesHomero.png");
    escenaNivel3->addItem(Homero);
    Homero->setPos(0, 450);
    Homero->setFlag(QGraphicsItem::ItemIsFocusable);
    Homero->setFocus();

    QTimer *FlechasTimer = new QTimer(this);
    connect(FlechasTimer, &QTimer::timeout, this, [=]() {
        Consumible *Flechas = new Consumible(":/Recursos/Flechas.png",10,15,20);

        // Generar una posición aleatoria en el eje x (ajustando al ancho de la escena)
        int randomX = std::rand() % 540;
        Flechas->setPos(randomX, 0);        // Comienza en la parte superior de la escena

        // Añadir la dona a la escena
        escenaNivel3->addItem(Flechas);
    });
    FlechasTimer->start(25000);
    timers.append(FlechasTimer);

    //Creacion de elementos Graficos
    //-------------------------------------------------------------------------------------------------------------
    QGraphicsRectItem *barraVidaRoja = nullptr;
    QGraphicsRectItem *barraVidaAmarilla = nullptr;
    añadirBarrasVida(escenaNivel3,50,10,barraVidaRoja,barraVidaAmarilla);

    añadirElementoGrafico(escenaNivel3, 0,-5,45,45,":/Recursos/corazon.png");
    añadirElementoGrafico(escenaNivel3,280,-13,90,90,":/Recursos/Flecha.png");
    añadirElementoGrafico(escenaNivel3,450,-5,60,60,":/Recursos/Calavera.png");

    //Creacion de Elementos de texto
    //-------------------------------------------------------------------------------------------------------------
    QGraphicsTextItem *VidaText = new QGraphicsTextItem();
    VidaText->setDefaultTextColor(Qt::white);
    VidaText->setFont(QFont("Algerian", 20));
    VidaText->setPos(150,0);
    escenaNivel3->addItem(VidaText);

    QGraphicsTextItem *MunicionText = new QGraphicsTextItem();
    MunicionText->setDefaultTextColor(Qt::white);
    MunicionText->setFont(QFont("Algerian", 20));
    MunicionText->setPos(350,0);
    escenaNivel3->addItem(MunicionText);

    QGraphicsTextItem *ScoreActualText = new QGraphicsTextItem();
    ScoreActualText->setDefaultTextColor(Qt::white);
    ScoreActualText->setFont(QFont("Algerian", 20));
    ScoreActualText->setPos(500,0);
    escenaNivel3->addItem(ScoreActualText);

    //Creacion de Timers para la aparicion de enemigos
    //-------------------------------------------------------------------------------------------------------------
    QTimer *enemigoTimer = new QTimer(this);
    QTimer *rataTimer = new QTimer(this);
    QTimer *murcielagoTimer = new QTimer(this);
    QTimer *manoTimer = new QTimer(this);
    QTimer *zombieTimer = new QTimer(this);
    QTimer *DraculaTimer = new QTimer(this);

    //Se gregan los timers a la lista de timers
    timers.append(enemigoTimer);
    timers.append(rataTimer);
    timers.append(murcielagoTimer);
    timers.append(manoTimer);
    timers.append(zombieTimer);
    timers.append(DraculaTimer);
    //-------------------------------------------------------------------------------------------------------------

    //Creacion de enemigos segun la sala y estado actual del nivel
    //-------------------------------------------------------------------------------------------------------------
    QTimer *estadoActual = new QTimer(this);
    connect(estadoActual, &QTimer::timeout, this, [=]() {
        if (!fondoCambiado1 && !fondoCambiado2 and !sala1) {
            if (!enemigoTimer->isActive()) { // Asegurar que solo se inicialicen una vez
                connect(enemigoTimer, &QTimer::timeout, this, [=]() {
                    bool lado = (rand() % 2 == 0);
                    Enemigo *enemigo = new Enemigo(lado, 0, 0, 150, 160, 20, 10, 0, 600, 440, 20, 8, ":/Recursos/Enemigo2.png");
                    escenaNivel3->addItem(enemigo);
                    connect(enemigo, &Enemigo::enemigoEliminado, Homero, &Heroe::aumentarScore);
                });
                enemigoTimer->start(4000);
            }

            if (!rataTimer->isActive()) { // Asegurar que solo se inicialicen una vez
                connect(rataTimer, &QTimer::timeout, this, [=]() {
                    bool lado = (rand() % 2 == 0);
                    Enemigo *enemigoRata = new Enemigo(lado, 0, 0, 125, 100, 10, 9, 525, 5, ":/Recursos/EnemigoRata.png");
                    escenaNivel3->addItem(enemigoRata);
                });
                rataTimer->start(2000);
            }
        }

        if (fondoCambiado1 && !fondoCambiado2 and !sala2){
            if(!murcielagoTimer->isActive()){
                connect(murcielagoTimer, &QTimer::timeout, this, [=]() {
                    Enemigo *murcielago = new Enemigo(20,0,0,146,50,20,6,":/Recursos/EnemigoVolador.png");
                    escenaNivel3->addItem(murcielago);
                    connect(murcielago, &Enemigo::enemigoEliminado, Homero, &Heroe::aumentarScore);
                });
                murcielagoTimer->start(3500);
            }

            if (!manoTimer->isActive()) {
                connect(manoTimer, &QTimer::timeout, this, [=]() {
                    // Generar un número aleatorio entre -50 y 550
                    int randomX = (std::rand() % 601) - 50; // 601 = 550 - (-50) + 1

                    Enemigo *mano = new Enemigo(randomX, 0, 0, 100, 200, 10, 11);
                    escenaNivel3->addItem(mano);
                });
                manoTimer->start(2000);
            }

        }
        if (!fondoCambiado1 && fondoCambiado2 and sala2){

            if (!zombieTimer->isActive()) { // Asegurar que solo se inicialicen una vez
                connect(zombieTimer, &QTimer::timeout, this, [=]() {
                    bool lado = (rand() % 2 == 0);
                    Enemigo *zombie = new Enemigo(lado, 0, 0, 150, 160, 20, 7, 0, 550, 420, 20, 8, ":/Recursos/zombie.png");
                    zombie->setScale(1.25);
                    escenaNivel3->addItem(zombie);
                    connect(zombie, &Enemigo::enemigoEliminado, Homero, &Heroe::aumentarScore);
                });
                zombieTimer->start(3500);
            }
            Homero->setNivel('4');
        }


    });

    estadoActual->start(100);
    timers.append(estadoActual);
    //-------------------------------------------------------------------------------------------------------------

    //Verificacion de la posicion actual del heroe e informacion relacionada
    //-------------------------------------------------------------------------------------------------------------
    QTimer *posHeroe = new QTimer(this);
    connect(posHeroe, &QTimer::timeout, this, [=]() {
        qreal posicionHeroX = Homero->getPosX();
        unsigned short int vidaActual = Homero->getVida();
        unsigned short int municionActual = Homero->getMunicion();
        unsigned short int scoreActual = Homero->getScore();

        mostrarVida(barraVidaAmarilla,vidaActual);

        VidaText->setPlainText(QString("%1/100").arg(vidaActual));
        MunicionText->setPlainText(QString("x%1").arg(municionActual));
        ScoreActualText->setPlainText(QString("x%1").arg(scoreActual));

        if(vidaActual==0){
            detenerTimers();
            escenaNivel3->clear();
            mostrarGameOver(escenaNivel3);

        }

        if(scoreActual==1){
            sala1 = true;
            rataTimer->stop();
            enemigoTimer->stop();
        }

        if(scoreActual==1){
            sala2 = true;
            murcielagoTimer->stop();
            manoTimer->stop();
        }
        bool inicialDracula = false;
        if(scoreActual == 3){
            zombieTimer->stop();
            inicialDracula = true;

        }
        static bool DraculaCreado = false;
        if(inicialDracula){
            if (!DraculaTimer->isActive() && !DraculaCreado) {  // Asegurar que solo se cree una vez
                connect(DraculaTimer, &QTimer::timeout, this, [=]() {
                    Enemigo *Dracula = new Enemigo(300,0,130,150,160,30,2,8,":/Recursos/Dracula.png");
                    escenaNivel3->addItem(Dracula);
                    Dracula->setPos(550,400);
                    Dracula->setScale(1.25);
                    connect(Dracula, &Enemigo::enemigoEliminado, Homero, &Heroe::aumentarScore);

                    // Establecer Dracula a true para evitar crear más Draculas
                    DraculaCreado = true;
                });
                DraculaTimer->start(3500);
            }
            if (!manoTimer->isActive()) {
                connect(manoTimer, &QTimer::timeout, this, [=]() {
                    // Generar un número aleatorio entre -50 y 550
                    int randomX = (std::rand() % 601) - 50; // 601 = 550 - (-50) + 1

                    Enemigo *mano = new Enemigo(randomX, 0, 0, 100, 200, 10, 11);
                    escenaNivel3->addItem(mano);
                });
                manoTimer->start(4500);
            }



        }
        if(DraculaCreado){
            DraculaTimer->stop();
        }


        if (posicionHeroX >= 554) {
            if(!fondoCambiado1 and !fondoCambiado2 and sala1){
                QImage background2(":/Recursos/Fondo2Nivel3.PNG");
                escenaNivel3->setBackgroundBrush(QBrush(background2));
                fondoCambiado1 = true; // Marcar que el fondo ha cambiad
                fondoCambiado2 = false;
                Homero->modificarPosX(-40);
            }

            else if(fondoCambiado1 and sala2){
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
            else if(fondoCambiado1 and sala2){
                escenaNivel3->setBackgroundBrush(QBrush(background));
                fondoCambiado1 = false; // Revertir el cambio de fondo
                fondoCambiado2 = false;
                Homero->setPos(550,450);
                Homero->modificarPosX(550);
            }

        }

    });
    posHeroe->start(100);
    timers.append(posHeroe);
    //-------------------------------------------------------------------------------------------------------------
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

void MainWindow::mostrarVida(QGraphicsRectItem *barraVidaAmarilla , int vidaActual)
{
    short int vidaDisponible = 100-vidaActual;

    barraVidaAmarilla->setRect(100-vidaDisponible,0,vidaDisponible,20);
}

void MainWindow::iniciarSegundaParteNivel2(QGraphicsScene *escenaActual)
{
    Heroe *Bart = new Heroe('1',450,0,0,150,160,100,10,":/Recursos/SpritesBart.png");
    escenaActual->addItem(Bart);
    Bart->setPos(0,450);
    Bart->setFlag(QGraphicsItem::ItemIsFocusable);
    Bart->setFocus();

    //Creacion Enemigos
    Enemigo *enemigoMain = new Enemigo(300,0,130,130,130,30,27,7,":/Recursos/SpriteGremlin.png");
    escenaActual->addItem(enemigoMain);
    enemigoMain->setPos(550,460);

    // Temporizador para crear donas
    QTimer *PiedrasTimer = new QTimer(this);
    connect(PiedrasTimer, &QTimer::timeout, this, [=]() {
        Consumible *Piedras = new Consumible(":/Recursos/Piedras.png",10,5,0);
        int randomX = std::rand() % 540;
        Piedras->setPos(randomX, 0);
        escenaActual->addItem(Piedras);
    });
    PiedrasTimer->start(10000);
    timers.append(PiedrasTimer);

    QGraphicsRectItem *barraVidaRoja = nullptr;
    QGraphicsRectItem *barraVidaAmarilla = nullptr;
    añadirBarrasVida(escenaActual,50,10,barraVidaRoja,barraVidaAmarilla);

    añadirElementoGrafico(escenaActual, 0,-5,45,45,":/Recursos/corazon.png");
    añadirElementoGrafico(escenaActual,300,0,45,45,":/Recursos/piedra.png");
    añadirElementoGrafico(escenaActual,450,0,45,45,":/Recursos/ImagenGremlin.png");

    QGraphicsTextItem *VidaText = new QGraphicsTextItem();
    VidaText->setDefaultTextColor(Qt::white);
    VidaText->setFont(QFont("Algerian", 20));
    VidaText->setPos(150,0);
    escenaActual->addItem(VidaText);

    QGraphicsTextItem *MunicionText = new QGraphicsTextItem();
    MunicionText->setDefaultTextColor(Qt::white);
    MunicionText->setFont(QFont("Algerian", 20));
    MunicionText->setPos(350,0);
    escenaActual->addItem(MunicionText);

    QGraphicsTextItem *vidaEnemigoText = new QGraphicsTextItem();
    vidaEnemigoText->setDefaultTextColor(Qt::white);
    vidaEnemigoText->setFont(QFont("Algerian", 20));
    vidaEnemigoText->setPos(500,0);
    escenaActual->addItem(vidaEnemigoText);

    QTimer *actualizarInfo = new QTimer(this);
    connect(actualizarInfo, &QTimer::timeout, this, [=](){
        unsigned short int vidaActual = Bart->getVida();
        unsigned short int municionActual = Bart->getMunicion();
        unsigned short int vidaEnemigo = enemigoMain->getVida();

        mostrarVida(barraVidaAmarilla,vidaActual);

        VidaText->setPlainText(QString("%1/100").arg(vidaActual));
        MunicionText->setPlainText(QString("x%1").arg(municionActual));
        vidaEnemigoText->setPlainText(QString("%1").arg(vidaEnemigo));
        //Condicion de Derrota
        if (vidaActual <= 0) {

            detenerTimers();
            escenaActual->clear();

            mostrarGameOver(escenaActual);
        }

        else if(vidaEnemigo == 0){
            detenerTimers();
            escenaActual->clear();

            mostrarVictoria(escenaActual);
        }
    });
    actualizarInfo->start(100);
    timers.append(actualizarInfo);
}

void MainWindow::añadirElementoGrafico(QGraphicsScene *escenaActual, int posX,int posY,int scaleX, int scaleY, const QString &rutaImagen)
{
    QPixmap imagen(rutaImagen);
    QPixmap imagenRedimensionada = imagen.scaled(scaleX,scaleY,Qt::KeepAspectRatio);
    QGraphicsPixmapItem *itemImagen = new QGraphicsPixmapItem(imagenRedimensionada);
    itemImagen->setPos(posX, posY);
    escenaActual->addItem(itemImagen);
}

void MainWindow::añadirBarrasVida(QGraphicsScene *escenaActual, int posX, int posY, QGraphicsRectItem *&barraVidaRoja, QGraphicsRectItem *&barraVidaAmarilla)
{
    barraVidaRoja = new QGraphicsRectItem(0,0,100,20);
    barraVidaRoja->setPos(posX, posY); // Posición en la escena
    barraVidaRoja->setBrush(QBrush(Qt::red));
    escenaActual->addItem(barraVidaRoja);

    barraVidaAmarilla = new QGraphicsRectItem();
    barraVidaAmarilla->setPos(posX, posY); // Posición en la escena
    barraVidaAmarilla->setBrush(QBrush(Qt::yellow));
    escenaActual->addItem(barraVidaAmarilla);
}

void MainWindow::detenerTimers()
{
    for (QTimer *timer : timers) {

        timer->stop();

        delete timer;
    }
    timers.clear();
}


void MainWindow::salirJuego()
{
    close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

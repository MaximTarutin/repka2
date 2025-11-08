#include "level_03.h"
#include "qmediaplayer.h"
#include "qpushbutton.h"
#include <ctime>
#include <QMouseEvent>

Level_03::Level_03(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
}

Level_03::~Level_03()
{
    delete background;
    background = nullptr;
    delete output;
    output = nullptr;
    delete sound;
    sound = nullptr;
    delete button_back;
    button_back = nullptr;
    delete table;
    table = nullptr;
    delete mysl;
    mysl = nullptr;
    delete babka;
    babka = nullptr;
    delete kolobok;
    kolobok = nullptr;
    for(int i=0; i<=5; i++)
    {
        delete tazik[i];
        tazik[i] = nullptr;        
    }
    for(int i=0; i<=7; i++)
    {
        delete produkt_mysl[i];
        produkt_mysl[i] = nullptr;
        delete produkt[i];
        produkt[i] = nullptr;
    }
}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Level_03::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
}

// ------------------ Получаем ширину и высоту экрана ----------------------

void Level_03::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_03::get_height(int h)
{
    HEIGHT_SCREEN = h;
}


// ------------------------- Инициализация уровня --------------------------------------

void Level_03::initial()
{
    produkt_value = {0,1,2,3,4,5,6,7};
    produkt_mysl_value = {0,1,2,3,4,5,6,7};

    background = new QLabel(this);
    background->setStyleSheet("border-image: url(:/resource/lev_03/level_3.jpg);");
    this->setCentralWidget(background);
    background->show();

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    sound = new QMediaPlayer(this);
    output = new QAudioOutput();
    sound->setAudioOutput(output);
    output->setVolume(1);

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    table = new PicObject(":/resource/lev_03/stol.png", this);
    table->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/5);
    table->move(WIDTH_SCREEN/2-WIDTH_SCREEN/20, HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
    table->show();

    babka = new PicObject(":/resource/lev_03/babka.png", this);
    babka->resize_object(WIDTH_SCREEN/8, HEIGHT_SCREEN/3);
    babka->move(WIDTH_SCREEN/2+WIDTH_SCREEN/4, HEIGHT_SCREEN/2+HEIGHT_SCREEN/10);
    babka->show();

    mysl = new PicObject(":/resource/lev_02/mysl.png", this);
    mysl->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/5);
    mysl->move(babka->x()+babka->width()/2, babka->y()-mysl->height());
    mysl->show();

    kolobok = new PicObject(":/resource/lev_03/kolobok.png", this);
    kolobok->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/12);
    kolobok->hide();

    tazik[0] = new PicObject(":/resource/lev_03/tazik-01.png", this);       // Пустой тазик
    tazik[1] = new PicObject(":/resource/lev_03/tazik-02.png", this);       // Тазик с молоком
    tazik[2] = new PicObject(":/resource/lev_03/tazik-03.png", this);       // Тазик добавили масло
    tazik[3] = new PicObject(":/resource/lev_03/tazik-04.png", this);       // Тазик добавили яйца
    tazik[4] = new PicObject(":/resource/lev_03/tazik-05.png", this);       // Тазик добавили муку и соль
    tazik[5] = new PicObject(":/resource/lev_03/tazik-06.png", this);       // тазик со взбитым тестом

    for(int i=0; i<=5; i++)
    {
        tazik[i]->resize_object(WIDTH_SCREEN/16, HEIGHT_SCREEN/12);
        tazik[i]->move(table->x()+table->width()/3,
                       table->y()-tazik[i]->height()/2-tazik[i]->height()/6);
        tazik[i]->hide();
    }

    // ингридиенты о чем думает бабка

    produkt_mysl[0] = new PicObject(":/resource/lev_03/tazik-01.png", mysl);
    produkt_mysl[0]->resize_object(WIDTH_SCREEN/16, HEIGHT_SCREEN/12);
    produkt_mysl[1] = new PicObject(":/resource/lev_03/milk.png", mysl);
    produkt_mysl[1]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
    produkt_mysl[2] = new PicObject(":/resource/lev_03/oil.png", mysl);
    produkt_mysl[2]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
    produkt_mysl[3] = new PicObject(":/resource/lev_03/egs.png", mysl);
    produkt_mysl[3]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/15);
    produkt_mysl[4] = new PicObject(":/resource/lev_03/muka.png", mysl);
    produkt_mysl[4]->resize_object(WIDTH_SCREEN/30, HEIGHT_SCREEN/15);
    produkt_mysl[5] = new PicObject(":/resource/lev_03/sol.png", mysl);
    produkt_mysl[5]->resize_object(WIDTH_SCREEN/50, HEIGHT_SCREEN/20);
    produkt_mysl[6] = new PicObject(":/resource/lev_03/venchik.png", mysl);
    produkt_mysl[6]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
    produkt_mysl[7] = new PicObject(":/resource/lev_03/kolobok.png", mysl);
    produkt_mysl[7]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/12);

    for(int i=0; i<=7; i++)
    {
        produkt_mysl[i]->hide();
        produkt_mysl[i]->move(mysl->width()/2-produkt_mysl[i]->width()/2,
                              mysl->height()/3-produkt_mysl[i]->height()/2);
    }
    //produkt_mysl[0]->show();

    // ингридиенты

    produkt[0] = new PicObject(":/resource/lev_03/tazik-01.png", this);
    produkt[0]->resize_object(WIDTH_SCREEN/16, HEIGHT_SCREEN/12);
    produkt[0]->move(WIDTH_SCREEN/30, HEIGHT_SCREEN-HEIGHT_SCREEN/3+HEIGHT_SCREEN/10);
    produkt[0]->setObjectName("tazik");
    produkt[1] = new PicObject(":/resource/lev_03/milk.png", this);
    produkt[1]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
    produkt[0]->setObjectName("milk");
    produkt[2] = new PicObject(":/resource/lev_03/oil.png", this);
    produkt[2]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
    produkt[2]->setObjectName("oil");
    produkt[3] = new PicObject(":/resource/lev_03/egs.png", this);
    produkt[3]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/15);
    produkt[3]->setObjectName("egs");
    produkt[4] = new PicObject(":/resource/lev_03/muka.png", this);
    produkt[4]->resize_object(WIDTH_SCREEN/30, HEIGHT_SCREEN/15);
    produkt[4]->setObjectName("muka");
    produkt[5] = new PicObject(":/resource/lev_03/sol.png", this);
    produkt[5]->resize_object(WIDTH_SCREEN/50, HEIGHT_SCREEN/20);
    produkt[5]->setObjectName("sol");
    produkt[6] = new PicObject(":/resource/lev_03/venchik.png", this);
    produkt[6]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
    produkt[6]->setObjectName("venchik");
    produkt[7] = new PicObject(":/resource/lev_03/kolobok.png", this);
    produkt[7]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/12);
    produkt[7]->setObjectName("kolobok");
    produkt[7]->hide();

    // Составляем список координат где будут расположены предметы

    coordinates.append(QList<int>() << 0 << 0);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/8 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/60);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/5 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/60);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/3-WIDTH_SCREEN/13 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/5-HEIGHT_SCREEN/65);
    coordinates.append(QList<int>() << WIDTH_SCREEN/6 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/4);
    coordinates.append(QList<int>() << WIDTH_SCREEN-WIDTH_SCREEN/15 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/4);
    coordinates.append(QList<int>() << 0 << 0);

    mix_ingridients();

    // Расставляем ингридиенты

    for(int i=1; i<=6; i++)
    {
        x[i] = coordinates.at(produkt_value[i]).at(0);
        y[i] = coordinates.at(produkt_value[i]).at(1);
        produkt[i]->move(x[i], y[i]);
        produkt[i]->show();
    }

    set_mysl();

    connect(produkt[0], &PicObject::clicked, this, &Level_03::mousePressEvent);
    connect(produkt[1], &PicObject::clicked, this, &Level_03::mousePressEvent);
    connect(produkt[2], &PicObject::clicked, this, &Level_03::mousePressEvent);
    connect(produkt[3], &PicObject::clicked, this, &Level_03::mousePressEvent);
    connect(produkt[4], &PicObject::clicked, this, &Level_03::mousePressEvent);
    connect(produkt[5], &PicObject::clicked, this, &Level_03::mousePressEvent);
    connect(produkt[6], &PicObject::clicked, this, &Level_03::mousePressEvent);
    connect(produkt[7], &PicObject::clicked, this, &Level_03::mousePressEvent);
}

// ----------------------- Перемешиваем ингридиенты ------------------------------

void Level_03::mix_ingridients()
{
    int k;
    int temp;
    for(int i=1; i<=6; i++)
    {
        k = rnd(1,6);
        temp = produkt_value[k];
        produkt_value[k] = produkt_value[i];
        produkt_value[i] = temp;
    }
}

// ----------------------- Показываем о чем думает бабка -----------------------------

void Level_03::set_mysl()
{
    if(NUMBER>=0 && NUMBER<=7)
    {
        produkt_mysl[NUMBER]->show();
    }
}

// ---------------------- Нажатие кнопки мышки --------------------------------

void Level_03::mousePressEvent(QMouseEvent *pe)
{

}

// ----------------------- Отпускание кнопки мышки -----------------------------

void Level_03::mouseReleaseEvent(QMouseEvent *pe)
{

}

// ----------------------- Перемещение предметов -------------------------------

void Level_03::mouseMoveEvent(QMouseEvent *pe)
{

}

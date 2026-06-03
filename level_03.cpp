#include "level_03.h"
#include "qmediaplayer.h"
#include "qpushbutton.h"
#include <ctime>

Level_03::Level_03(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
}

Level_03::~Level_03()
{
    // delete background;
    // background = nullptr;
    // delete output;
    // output = nullptr;
    // delete sound;
    // sound = nullptr;
    // delete button_back;
    // button_back = nullptr;
    // for(int i=0; i<=6; i++)
    // {
    //     delete produkt_mysl[i];
    //     produkt_mysl[i] = nullptr;

    // }
    // for(int i=0; i<=7; i++)
    // {
    //     delete tazik[i];
    //     tazik[i] = nullptr;
    //     delete produkt[i];
    //     produkt[i] = nullptr;
    // }
    // delete table;
    // table = nullptr;
    // delete mysl;
    // mysl = nullptr;
    // delete babka;
    // babka = nullptr;
    // delete timer_show_kolobok;
    // timer_show_kolobok = nullptr;
    // delete kolobok;
    // kolobok = nullptr;
    // delete animate_persone;
    // animate_persone = nullptr;
    // delete prosrach;
    // prosrach = nullptr;
    // delete timer_victory;
    // timer_victory = nullptr;
    // delete hand;
    // hand = nullptr;

    // WIDTH_SCREEN = 0;
    // HEIGHT_SCREEN = 0;
    // NUMBER = 0;
    // CURRENT_PRODUKT = 100;

    // for(int i=0; i<=7; i++)
    // {
    //     x[i] = 0;
    //     y[i] = 0;
    // }

    // old_x = 0;
    // old_y = 0;

    // HELP_FLAG = false;
    // FLAG_LEVEL = 0;
    // produkt_value.clear();
    // produkt_mysl_value.clear();
    // coordinates.clear();
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
    STATUS_LEVEL = 0;
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

    animate_persone = new PicObject(this);
    prosrach = new PicObject(":/resource/lev_03/prosrach.png", this);
    animate_persone->setParent(prosrach);

    animate();
    connect(animate_persone, &PicObject::move_end, this, &Level_03::animate);

    set_object();
}


// ------------------------- Создаем объекты -------------------------------------

void Level_03::set_object()
{
    tazik[0] = new PicObject(":/resource/lev_03/tazik-01.png", this);       // Пустой тазик
    tazik[1] = new PicObject(":/resource/lev_03/tazik-02.png", this);       // Тазик с молоком
    tazik[2] = new PicObject(":/resource/lev_03/tazik-03.png", this);       // Тазик добавили масло
    tazik[3] = new PicObject(":/resource/lev_03/tazik-04.png", this);       // Тазик добавили яйца
    tazik[4] = new PicObject(":/resource/lev_03/tazik-05.png", this);       // Тазик добавили муку
    tazik[5] = new PicObject(":/resource/lev_03/tazik-05.png", this);       // Тазик добавили соль
    tazik[6] = new PicObject(":/resource/lev_03/tazik-06.png", this);       // тазик со взбитым тестом

    for(int i=0; i<=6; i++)
    {
        tazik[i]->resize_object(WIDTH_SCREEN/16, HEIGHT_SCREEN/12);
        tazik[i]->move(table->x()+table->width()/3,
                       table->y()-tazik[i]->height()/2-tazik[i]->height()/6);
        tazik[i]->hide();
    }

    tazik[0]->setObjectName("6");           // Имя пустого тазика
    tazik[6]->setObjectName("7");           // Имя полного тазика

    // Объекты в мыслях у бабки

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
    produkt_mysl[7] = new PicObject(":/resource/lev_03/pechka.png", mysl);
    produkt_mysl[7]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/12);

    for(int i=0; i<=7; i++)
    {
        produkt_mysl[i]->hide();
        produkt_mysl[i]->move(mysl->width()/2-produkt_mysl[i]->width()/2,
                              mysl->height()/3-produkt_mysl[i]->height()/2);
    }

    // Создаем всевозможные ингридиетты

        produkt[0] = new PicObject(":/resource/lev_03/milk.png", this);
        produkt[0]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
        produkt[0]->setObjectName("0");
        produkt[1] = new PicObject(":/resource/lev_03/oil.png", this);
        produkt[1]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
        produkt[1]->setObjectName("1");
        produkt[2] = new PicObject(":/resource/lev_03/egs.png", this);
        produkt[2]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/15);
        produkt[2]->setObjectName("2");
        produkt[3] = new PicObject(":/resource/lev_03/muka.png", this);
        produkt[3]->resize_object(WIDTH_SCREEN/30, HEIGHT_SCREEN/15);
        produkt[3]->setObjectName("3");
        produkt[4] = new PicObject(":/resource/lev_03/sol.png", this);
        produkt[4]->resize_object(WIDTH_SCREEN/50, HEIGHT_SCREEN/20);
        produkt[4]->setObjectName("4");
        produkt[5] = new PicObject(":/resource/lev_03/venchik.png", this);
        produkt[5]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
        produkt[5]->setObjectName("5");

        // создаем список координат для размещения продуктов

        coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/8 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/60);
        coordinates.append(QList<int>() << WIDTH_SCREEN/2 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
        coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/5 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/60);
        coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/3-WIDTH_SCREEN/13 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/5-HEIGHT_SCREEN/65);
        coordinates.append(QList<int>() << WIDTH_SCREEN/6 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/4);
        coordinates.append(QList<int>() << WIDTH_SCREEN-WIDTH_SCREEN/15 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/4);

        mix_coordinates();

        // Добавляем в конец списка координаты пустого и полного тазиков

        coordinates.append(QList<int>() << WIDTH_SCREEN/30 << HEIGHT_SCREEN-HEIGHT_SCREEN/3+HEIGHT_SCREEN/10);
        coordinates.append(QList<int>() << table->x()+table->width()/3 << table->y()-tazik[6]->height()/2-tazik[6]->height()/6);

        for(int i=0; i<=5; i++)         // Расставляем продукты
        {
            int x = coordinates.at(i).at(0);
            int y = coordinates.at(i).at(1);
            produkt[i]->move(x, y);
            produkt[i]->show();
        }

        // Ставим пустой тазик в левый нижний угол

        tazik[0]->move(coordinates.at(6).at(0), coordinates.at(6).at(1));
        tazik[0]->show();

        connect(tazik[0], &PicObject::clicked, this, &Level_03::mousePressEvent);
        connect(tazik[6], &PicObject::clicked, this, &Level_03::mousePressEvent);
        for(int i=0; i<=5; i++)
        {
            connect(produkt[i], &PicObject::clicked, this, &Level_03::mousePressEvent);
        }
}

// ----------------------------- Перемешиваем список координат -----------------------------

void Level_03::mix_coordinates()
{
    int k = 0;
    for(int i=0; i<=5; i++)
    {
        k = rnd(0,5);
        coordinates[i].swap(coordinates[k]);  // Меняем местами элементы списка
    }
}


// ------------------------ Анимация на уровне -----------------------------------

void Level_03::animate()
{
    int k = 0;
    k = rnd(0,3);
    switch(k)
    {
    case 0:
        prosrach->resize_object(WIDTH_SCREEN/8-WIDTH_SCREEN/120,HEIGHT_SCREEN/10);
        prosrach->move(WIDTH_SCREEN/2-WIDTH_SCREEN/50,HEIGHT_SCREEN/2+HEIGHT_SCREEN/20);
        animate_persone->load(":/resource/lev_03/utka.gif");
        animate_persone->move(0-prosrach->width()*2,0);
        animate_persone->move_to_x(0-prosrach->width(),prosrach->width()+prosrach->width()/2, 0, 80);
        animate_persone->animation_start(WIDTH_SCREEN/8, HEIGHT_SCREEN/10);
        animate_persone->show();
        break;
    case 1:
        prosrach->resize_object(WIDTH_SCREEN/8-WIDTH_SCREEN/120,HEIGHT_SCREEN/10);
        prosrach->move(WIDTH_SCREEN/2-WIDTH_SCREEN/50,HEIGHT_SCREEN/2-HEIGHT_SCREEN/10);
        animate_persone->load(":/resource/lev_03/duck.gif");
        animate_persone->move(0-prosrach->width()*2,0);
        animate_persone->move_to_x(0-prosrach->width(),prosrach->width()+prosrach->width()/2, 0, 80);
        animate_persone->animation_start(WIDTH_SCREEN/14, HEIGHT_SCREEN/8);
        animate_persone->show();
        break;
    case 2:
        prosrach->resize_object(WIDTH_SCREEN/8-WIDTH_SCREEN/90,HEIGHT_SCREEN/10);
        prosrach->move(WIDTH_SCREEN/2-WIDTH_SCREEN/50,HEIGHT_SCREEN/2-HEIGHT_SCREEN/8);
        animate_persone->load(":/resource/lev_03/kar.gif");
        animate_persone->move(0-prosrach->width()*2,0);
        animate_persone->move_to_x(0-prosrach->width(),prosrach->width()+prosrach->width()/2, 0, 80);
        animate_persone->animation_start(WIDTH_SCREEN/14, HEIGHT_SCREEN/8);
        animate_persone->show();
        break;
    case 3:
        prosrach->resize_object(WIDTH_SCREEN/8-WIDTH_SCREEN/120,HEIGHT_SCREEN/10);
        prosrach->move(WIDTH_SCREEN/2-WIDTH_SCREEN/50,HEIGHT_SCREEN/2+HEIGHT_SCREEN/20);
        animate_persone->load(":/resource/lev_03/cat.gif");
        animate_persone->move(prosrach->width()+prosrach->width(),0);
        animate_persone->move_to_x(prosrach->width()+prosrach->width()/2, 0-prosrach->width(), 0, 80);
        animate_persone->animation_start(WIDTH_SCREEN/8, HEIGHT_SCREEN/10);
        animate_persone->show();
        break;
    }
}

// ----------------- Нажатие кнопки мышки -----------------------------

void Level_03::mousePressEvent(QMouseEvent *pe)
{
    if(QObject::sender() && pe->button() == Qt::LeftButton)
    {
        name_active_object = QObject::sender()->objectName();
        CURRENT_OBJECT = name_active_object.toInt();
    }
}

// ----------------------- Перемещение предметов -------------------------------

void Level_03::mouseMoveEvent(QMouseEvent *pe)
{
    if((CURRENT_OBJECT==6)&&(STATUS_LEVEL==0))      // Перемещаем корзину
    {
        PicObject *active_object = this->findChild<PicObject*>(name_active_object); //указатель на объект по его имени
        active_object->raise();
        active_object->move(pe->position().x()-active_object->width()/2,
                            pe->position().y()-active_object->height()/2);
    } else
        if((STATUS_LEVEL>=1)&&(STATUS_LEVEL<=6)&&(CURRENT_OBJECT!=6)&&(CURRENT_OBJECT!=100))  // Наполняем корзину продуктами
    {
        produkt[CURRENT_OBJECT]->move(pe->position().x()-produkt[CURRENT_OBJECT]->width()/2,
                                      pe->position().y()-produkt[CURRENT_OBJECT]->height()/2);
        produkt[CURRENT_OBJECT]->raise();
    }
}

// ------------------------- Отпускаем кнопку мышки -------------------------------

void Level_03::mouseReleaseEvent(QMouseEvent *pe)
{
    if(CURRENT_OBJECT!=100)
    {
        if((STATUS_LEVEL==0)&&(CURRENT_OBJECT==6))  // Ставим корзину на стол
        {
            if((tazik[0]->x()>=table->x())&&(tazik[0]->x()<=table->x()+table->width())&&
                (tazik[0]->y()>=table->y()-table->height()/2)&&(tazik[0]->y()<=table->y()+table->height()/8))
            {
                tazik[0]->move(table->x()+table->width()/3,
                               table->y()-tazik[0]->height()/2-tazik[0]->height()/6);
                STATUS_LEVEL++;
                CURRENT_OBJECT = 100;
            } else return_object(pe);
        } else
            if((STATUS_LEVEL>=1)&&(STATUS_LEVEL<=6)&&(CURRENT_OBJECT!=6))  // Наполняем корзину продуктами
        {
            return_object(pe);
            CURRENT_OBJECT = 100;
        }
    } else return;
}

// ------------------------- Возвращаем объект на место --------------------------------

void Level_03::return_object(QMouseEvent *pe)
{
    PicObject *active_object = this->findChild<PicObject*>(name_active_object);
    int x = pe->position().x();
    int old_x = coordinates.at(CURRENT_OBJECT).at(0);
    int y = pe->position().y();
    int old_y = coordinates.at(CURRENT_OBJECT).at(1);
    active_object->move_to_xy(x, old_x, y, old_y, 1, 4);
}

// void Level_03::initial()
// {
//     produkt_value = {0,1,2,3,4,5,6,7};
//     produkt_mysl_value = {0,1,2,3,4,5,6,7};

//     background = new QLabel(this);
//     background->setStyleSheet("border-image: url(:/resource/lev_03/level_3.jpg);");
//     this->setCentralWidget(background);
//     background->show();

//     QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
//     this->setCursor(cursorTarget);

//     sound = new QMediaPlayer(this);
//     output = new QAudioOutput();
//     sound->setAudioOutput(output);
//     output->setVolume(1);

//     button_back = new QPushButton(this);
//     button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
//     button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
//     button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
//     button_back->show();

//     table = new PicObject(":/resource/lev_03/stol.png", this);
//     table->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/5);
//     table->move(WIDTH_SCREEN/2-WIDTH_SCREEN/20, HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
//     table->show();

//     babka = new PicObject(":/resource/lev_03/babka.png", this);
//     babka->resize_object(WIDTH_SCREEN/8, HEIGHT_SCREEN/3);
//     babka->move(WIDTH_SCREEN/2+WIDTH_SCREEN/4, HEIGHT_SCREEN/2+HEIGHT_SCREEN/10);
//     babka->show();

//     mysl = new PicObject(":/resource/lev_02/mysl.png", this);
//     mysl->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/5);
//     mysl->move(babka->x()+babka->width()/2, babka->y()-mysl->height());
//     mysl->show();

//     kolobok = new PicObject(":/resource/lev_03/kolobok.png", this);
//     kolobok->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/12);
//     kolobok->hide();

//     tazik[0] = new PicObject(":/resource/lev_03/tazik-01.png", this);       // Пустой тазик
//     tazik[0]->setObjectName("tazik-0");
//     tazik[1] = new PicObject(":/resource/lev_03/tazik-02.png", this);       // Тазик с молоком
//     tazik[1]->setObjectName("tazik-1");
//     tazik[2] = new PicObject(":/resource/lev_03/tazik-03.png", this);       // Тазик добавили масло
//     tazik[2]->setObjectName("tazik-2");
//     tazik[3] = new PicObject(":/resource/lev_03/tazik-04.png", this);       // Тазик добавили яйца
//     tazik[3]->setObjectName("tazik-3");
//     tazik[4] = new PicObject(":/resource/lev_03/tazik-05.png", this);       // Тазик добавили муку
//     tazik[4]->setObjectName("tazik-4");
//     tazik[5] = new PicObject(":/resource/lev_03/tazik-05.png", this);       // Тазик добавили соль
//     tazik[5]->setObjectName("tazik-5");
//     tazik[6] = new PicObject(":/resource/lev_03/tazik-06.png", this);       // тазик со взбитым тестом
//     tazik[6]->setObjectName("tazik-6");
//     tazik[7] = new PicObject(":/resource/lev_03/kolobok.png", this);       // колобок вместо тазика
//     tazik[7]->setObjectName("tazik-7");

//     for(int i=0; i<=7; i++)
//     {
//         tazik[i]->resize_object(WIDTH_SCREEN/16, HEIGHT_SCREEN/12);
//         tazik[i]->move(table->x()+table->width()/3,
//                        table->y()-tazik[i]->height()/2-tazik[i]->height()/6);
//         tazik[i]->hide();
//     }

//     // ингридиенты о чем думает бабка

//     produkt_mysl[0] = new PicObject(":/resource/lev_03/tazik-01.png", mysl);
//     produkt_mysl[0]->resize_object(WIDTH_SCREEN/16, HEIGHT_SCREEN/12);
//     produkt_mysl[0]->setObjectName("tazik_m");
//     produkt_mysl[1] = new PicObject(":/resource/lev_03/milk.png", mysl);
//     produkt_mysl[1]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
//     produkt_mysl[1]->setObjectName("milk_m");
//     produkt_mysl[2] = new PicObject(":/resource/lev_03/oil.png", mysl);
//     produkt_mysl[2]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
//     produkt_mysl[2]->setObjectName("oil_m");
//     produkt_mysl[3] = new PicObject(":/resource/lev_03/egs.png", mysl);
//     produkt_mysl[3]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/15);
//     produkt_mysl[3]->setObjectName("egs_m");
//     produkt_mysl[4] = new PicObject(":/resource/lev_03/muka.png", mysl);
//     produkt_mysl[4]->resize_object(WIDTH_SCREEN/30, HEIGHT_SCREEN/15);
//     produkt_mysl[4]->setObjectName("muka_m");
//     produkt_mysl[5] = new PicObject(":/resource/lev_03/sol.png", mysl);
//     produkt_mysl[5]->resize_object(WIDTH_SCREEN/50, HEIGHT_SCREEN/20);
//     produkt_mysl[5]->setObjectName("sol_m");
//     produkt_mysl[6] = new PicObject(":/resource/lev_03/venchik.png", mysl);
//     produkt_mysl[6]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
//     produkt_mysl[6]->setObjectName("venchik_m");
//     produkt_mysl[7] = new PicObject(":/resource/lev_03/pechka.png", mysl);
//     produkt_mysl[7]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/12);
//     produkt_mysl[7]->setObjectName("kolobok_m");

//     for(int i=0; i<=7; i++)
//     {
//         produkt_mysl[i]->hide();
//         produkt_mysl[i]->move(mysl->width()/2-produkt_mysl[i]->width()/2,
//                               mysl->height()/3-produkt_mysl[i]->height()/2);
//     }

//     // ингридиенты

//     produkt[0] = new PicObject(":/resource/lev_03/tazik-01.png", this);
//     produkt[0]->resize_object(WIDTH_SCREEN/16, HEIGHT_SCREEN/12);
//     produkt[0]->move(WIDTH_SCREEN/30, HEIGHT_SCREEN-HEIGHT_SCREEN/3+HEIGHT_SCREEN/10);
//     produkt[0]->setObjectName("tazik");
//     produkt[1] = new PicObject(":/resource/lev_03/milk.png", this);
//     produkt[1]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
//     produkt[1]->setObjectName("milk");
//     produkt[2] = new PicObject(":/resource/lev_03/oil.png", this);
//     produkt[2]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
//     produkt[2]->setObjectName("oil");
//     produkt[3] = new PicObject(":/resource/lev_03/egs.png", this);
//     produkt[3]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/15);
//     produkt[3]->setObjectName("egs");
//     produkt[4] = new PicObject(":/resource/lev_03/muka.png", this);
//     produkt[4]->resize_object(WIDTH_SCREEN/30, HEIGHT_SCREEN/15);
//     produkt[4]->setObjectName("muka");
//     produkt[5] = new PicObject(":/resource/lev_03/sol.png", this);
//     produkt[5]->resize_object(WIDTH_SCREEN/50, HEIGHT_SCREEN/20);
//     produkt[5]->setObjectName("sol");
//     produkt[6] = new PicObject(":/resource/lev_03/venchik.png", this);
//     produkt[6]->resize_object(WIDTH_SCREEN/60, HEIGHT_SCREEN/15);
//     produkt[6]->setObjectName("venchik");
//     produkt[7] = new PicObject(":/resource/lev_03/tazik_06.png", this);
//     produkt[7]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/12);
//     produkt[7]->setObjectName("kolobok");
//     produkt[7]->hide();

//     // Составляем список координат где будут расположены предметы

//     coordinates.append(QList<int>() << 0 << 0);
//     coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/8 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/60);
//     coordinates.append(QList<int>() << WIDTH_SCREEN/2 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
//     coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/5 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/60);
//     coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/3-WIDTH_SCREEN/13 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/5-HEIGHT_SCREEN/65);
//     coordinates.append(QList<int>() << WIDTH_SCREEN/6 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/4);
//     coordinates.append(QList<int>() << WIDTH_SCREEN-WIDTH_SCREEN/15 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/4);
//     coordinates.append(QList<int>() << 0 << 0);

//     mix_ingridients();

//     // Расставляем ингридиенты

//     for(int i=1; i<=6; i++)
//     {
//         x[i] = coordinates.at(produkt_value[i]).at(0);
//         y[i] = coordinates.at(produkt_value[i]).at(1);
//         produkt[i]->move(x[i], y[i]);
//         produkt[i]->show();
//     }

//     // объекты для анимации на уровне

//     animate_persone = new PicObject(this);
//     prosrach = new PicObject(":/resource/lev_03/prosrach.png", this);
//     animate_persone->setParent(prosrach);

//     animate();
//     set_mysl();

//     connect(produkt[0], &PicObject::clicked, this, &Level_03::mousePressEvent);
//     connect(produkt[1], &PicObject::clicked, this, &Level_03::mousePressEvent);
//     connect(produkt[2], &PicObject::clicked, this, &Level_03::mousePressEvent);
//     connect(produkt[3], &PicObject::clicked, this, &Level_03::mousePressEvent);
//     connect(produkt[4], &PicObject::clicked, this, &Level_03::mousePressEvent);
//     connect(produkt[5], &PicObject::clicked, this, &Level_03::mousePressEvent);
//     connect(produkt[6], &PicObject::clicked, this, &Level_03::mousePressEvent);
//     connect(produkt[7], &PicObject::clicked, this, &Level_03::mousePressEvent);
//     connect(tazik[6],   &PicObject::clicked, this, &Level_03::mousePressEvent);
//     connect(animate_persone, &PicObject::move_end, this, &Level_03::animate);

//     hand = new PicObject(":/resource/lev_01/ruka.png", this);
//     hand->resize_object(WIDTH_SCREEN/25, HEIGHT_SCREEN/12);
//     hand->move(500, 500);
//     hand->show();
//     hand->raise();
//     help();

//     connect(hand, &PicObject::move_end, this, &Level_03::help);
// }

// // ------------------------ Анимация на уровне -----------------------------------

// void Level_03::animate()
// {
//     int k = 0;
//     k = rnd(0,3);
//     switch(k)
//     {
//     case 0:
//         prosrach->resize_object(WIDTH_SCREEN/8-WIDTH_SCREEN/120,HEIGHT_SCREEN/10);
//         prosrach->move(WIDTH_SCREEN/2-WIDTH_SCREEN/50,HEIGHT_SCREEN/2+HEIGHT_SCREEN/20);
//         animate_persone->load(":/resource/lev_03/utka.gif");
//         animate_persone->move(0-prosrach->width()*2,0);
//         animate_persone->move_to_x(0-prosrach->width(),prosrach->width()+prosrach->width()/2, 0, 80);
//         animate_persone->animation_start(WIDTH_SCREEN/8, HEIGHT_SCREEN/10);
//         animate_persone->show();
//         break;
//     case 1:
//         prosrach->resize_object(WIDTH_SCREEN/8-WIDTH_SCREEN/120,HEIGHT_SCREEN/10);
//         prosrach->move(WIDTH_SCREEN/2-WIDTH_SCREEN/50,HEIGHT_SCREEN/2-HEIGHT_SCREEN/10);
//         animate_persone->load(":/resource/lev_03/duck.gif");
//         animate_persone->move(0-prosrach->width()*2,0);
//         animate_persone->move_to_x(0-prosrach->width(),prosrach->width()+prosrach->width()/2, 0, 80);
//         animate_persone->animation_start(WIDTH_SCREEN/14, HEIGHT_SCREEN/8);
//         animate_persone->show();
//         break;
//     case 2:
//         prosrach->resize_object(WIDTH_SCREEN/8-WIDTH_SCREEN/90,HEIGHT_SCREEN/10);
//         prosrach->move(WIDTH_SCREEN/2-WIDTH_SCREEN/50,HEIGHT_SCREEN/2-HEIGHT_SCREEN/8);
//         animate_persone->load(":/resource/lev_03/kar.gif");
//         animate_persone->move(0-prosrach->width()*2,0);
//         animate_persone->move_to_x(0-prosrach->width(),prosrach->width()+prosrach->width()/2, 0, 80);
//         animate_persone->animation_start(WIDTH_SCREEN/14, HEIGHT_SCREEN/8);
//         animate_persone->show();
//         break;
//     case 3:
//         prosrach->resize_object(WIDTH_SCREEN/8-WIDTH_SCREEN/120,HEIGHT_SCREEN/10);
//         prosrach->move(WIDTH_SCREEN/2-WIDTH_SCREEN/50,HEIGHT_SCREEN/2+HEIGHT_SCREEN/20);
//         animate_persone->load(":/resource/lev_03/cat.gif");
//         animate_persone->move(prosrach->width()+prosrach->width(),0);
//         animate_persone->move_to_x(prosrach->width()+prosrach->width()/2, 0-prosrach->width(), 0, 80);
//         animate_persone->animation_start(WIDTH_SCREEN/8, HEIGHT_SCREEN/10);
//         animate_persone->show();
//         break;
//     }
// }

// // ----------------------- Перемешиваем ингридиенты ------------------------------

// void Level_03::mix_ingridients()
// {
//     int k;
//     int temp;
//     for(int i=1; i<=6; i++)
//     {
//         k = rnd(1,6);
//         temp = produkt_value[k];
//         produkt_value[k] = produkt_value[i];
//         produkt_value[i] = temp;
//     }
// }

// // ----------------------- Показываем о чем думает бабка -----------------------------

// void Level_03::set_mysl()
// {
//     if(NUMBER>=0 && NUMBER<=7)
//     {
//         produkt_mysl[NUMBER]->show();
//     }
// }

// // ---------------------- Нажатие кнопки мышки --------------------------------

// void Level_03::mousePressEvent(QMouseEvent *pe)
// {
//     if(QObject::sender() && pe->button() == Qt::LeftButton)
//     {
//         name_active_object = QObject::sender()->objectName();       // Узнаем имя объекта который испустил сигнал
//         if(name_active_object=="tazik" || name_active_object=="tazik-6")
//         {
//             hand->hide();
//             disconnect(hand, &PicObject::move_end, this, &Level_03::help);          // убираем подсказку
//         }

//         if(NUMBER !=6)
//         {
//             PicObject *active_object = this->findChild<PicObject*>(name_active_object);
//             old_x = active_object->x();
//             old_y = active_object->y();
//         } else
//         {
//             old_x = tazik[6]->x();
//             old_y = tazik[6]->y();
//         }
//     }
// }

// // ----------------------- Отпускание кнопки мышки -----------------------------

// void Level_03::mouseReleaseEvent(QMouseEvent *pe)
// {
//     PicObject *active_object = this->findChild<PicObject*>(name_active_object);
//     if(NUMBER<7 && name_active_object!=nullptr)         // до колобка
//     {
//         if((pe->position().x()>=table->x())&&(pe->position().x()<=table->x()+table->width())&&
//             (pe->position().y()>=table->y()-table->height()/6)&&
//             (pe->position().y()<=table->y()+table->height()/4))
//         {
//             QString name_mysl_object = produkt_mysl[NUMBER]->objectName();
//             QString temp_name = name_active_object+"_m";

//             if(name_mysl_object==temp_name)   // если имя объекта совпадает с именем объекта в мысли
//             {
//                 produkt[NUMBER]->hide();
//                 tazik[NUMBER]->raise();
//                 if(NUMBER!=0)
//                 {
//                     delete tazik[NUMBER-1];
//                     tazik[NUMBER-1] = nullptr;
//                 }
//                 delete produkt_mysl[NUMBER];
//                 produkt_mysl[NUMBER] = nullptr;
//                 tazik[NUMBER]->show();
//                 NUMBER++;
//                 set_mysl();
//                 sound->setSource(QUrl("qrc:/resource/sound/yes.mp3"));
//                 sound->play();
//             } else
//             {
//                 active_object->move_to_xy(pe->position().x(), old_x, pe->position().y(), old_y, 1, 4);
//                 sound->setSource(QUrl("qrc:/resource/sound/nea.wav"));
//                 sound->play();
//             }
//             if(NUMBER==7) // Делаем подсказку тазик в печь
//             {
//                 HELP_FLAG = true;
//                 hand->show();
//                 help();
//                 connect(hand, &PicObject::move_end, this, &Level_03::help);
//             }
//         } else
//         {
//             active_object->move_to_xy(pe->position().x(), old_x, pe->position().y(), old_y, 1, 4);
//             sound->setSource(QUrl("qrc:/resource/sound/nea.wav"));
//             sound->play();
//         }
//     } else  // Если все ингридиенты собраны, ставим тазик в печь
//     {
//         if(NUMBER==8) return;
//         if((name_active_object!=nullptr)&&
//             (pe->position().x()<=WIDTH_SCREEN/5)&&(pe->position().x()>=WIDTH_SCREEN/7)&&
//             (pe->position().y()<=HEIGHT_SCREEN/2+HEIGHT_SCREEN/20)&&
//             (pe->position().y()>=HEIGHT_SCREEN/2-HEIGHT_SCREEN/20))
//         {
//             NUMBER=8;
//             kolobok->move(table->x()+table->width()/3,
//                           table->y()-kolobok->height()/2-kolobok->height()/6);

//             delete tazik[6];
//             tazik[6] = nullptr;
//             delete tazik[7];
//             tazik[7] = nullptr;
//             delete mysl;
//             mysl = nullptr;
//             delete produkt[7];
//             produkt[7] = nullptr;
//             timer_show_kolobok = new QTimer(this);
//             timer_show_kolobok->start(1);
//             connect(timer_show_kolobok, &QTimer::timeout, this, &Level_03::show_kolobok);
//             sound->setSource(QUrl("qrc:/resource/sound/show.mp3"));
//             sound->play();
//         } else
//         {
//             tazik[6]->move(old_x, old_y);
//         }
//     }
//     name_active_object = nullptr;
// }

// // ----------------------- Перемещение предметов -------------------------------

// void Level_03::mouseMoveEvent(QMouseEvent *pe)
// {
//     if(name_active_object!=nullptr)
//     {
//         PicObject *active_object = this->findChild<PicObject*>(name_active_object); //указатель на объект по его имени
//         active_object->raise();
//         active_object->move(pe->position().x()-active_object->width()/2,
//                             pe->position().y()-active_object->height()/2);
//     }
// }

// // -------------- Колобок появляется на столе -----------------------------

// void Level_03::show_kolobok()
// {
//     static int opacity;
//     if(FLAG_LEVEL==0)
//     {
//         opacity = 0;
//         FLAG_LEVEL = 1;
//     }
//     opacity++;
//     kolobok->opacity(opacity);
//     kolobok->show();
//     if(opacity>=255)
//     {
//         FLAG_LEVEL = 0;
//         timer_show_kolobok->stop();
//         disconnect(timer_show_kolobok, &QTimer::timeout, this, &Level_03::show_kolobok);
//         delete timer_show_kolobok;
//         timer_show_kolobok = nullptr;
//         timer_victory = new QTimer(this);
//         timer_victory->start(4);
//         connect(timer_victory, &QTimer::timeout, this, &Level_03::victory);
//         sound->setSource(QUrl("qrc:/resource/sound/tuk.mp3"));
//     }
// }

// // ------------------------ Победа ---------------------------------------

// void Level_03::victory()
// {
//     static int x;
//     static int y;
//     static bool FLAG_X;
//     static bool FLAG_Y;
//     static int index;

//     if(FLAG_LEVEL==0)
//     {
//         x = kolobok->x();
//         y = kolobok->y();
//         FLAG_X = true;
//         FLAG_Y = true;
//         index = 0;
//         FLAG_LEVEL = 1;
//     }

// hand->raise();
//     index++;

//     if(index >= 2000)
//     {
//         timer_victory->stop();
//         disconnect(timer_victory, &QTimer::timeout, this, &Level_03::victory);

//         delete timer_victory;
//         timer_victory = nullptr;
//         delete kolobok;
//         kolobok = nullptr;
//         delete sound;
//         sound = nullptr;
//         delete timer_show_kolobok;
//         timer_show_kolobok = nullptr;
//         delete animate_persone;
//         animate_persone = nullptr;
//         delete prosrach;
//         prosrach = nullptr;
//         emit next_level(4);
//         return;
//     }
//     if(FLAG_X&&FLAG_Y)
//     {
//         x+=5;
//         y+=5;
//         if(x>=WIDTH_SCREEN-kolobok->width())
//         {
//             FLAG_X = false;
//             sound->stop();
//             sound->play();
//         }
//         if(y>=HEIGHT_SCREEN-kolobok->height())
//         {
//             FLAG_Y = false;
//             sound->stop();
//             sound->play();
//         }
//     }
//     if(!FLAG_X&&FLAG_Y)
//     {
//         x-=5;
//         y+=5;
//         if(x<=0)
//         {
//             FLAG_X = true;
//             sound->stop();
//             sound->play();
//         }
//         if(y>=HEIGHT_SCREEN-kolobok->height())
//         {
//             FLAG_Y = false;
//             sound->stop();
//             sound->play();
//         }
//     }
//     if(FLAG_X&&!FLAG_Y)
//     {
//         x+=5;
//         y-=5;
//         if(x>=WIDTH_SCREEN-kolobok->width())
//         {
//             FLAG_X =  false;
//             sound->stop();
//             sound->play();
//         }
//         if(y<=0)
//         {
//             FLAG_Y = true;
//             sound->stop();
//             sound->play();
//         }
//     }
//     if(!FLAG_X&&!FLAG_Y)
//     {
//         x-=5;
//         y-=5;
//         if(x<=0)
//         {
//             FLAG_X = true;
//             sound->stop();
//             sound->play();
//         }
//         if(y<=0)
//         {
//             FLAG_Y = true;
//             sound->stop();
//             sound->play();
//         }
//     }
//     kolobok->move(x,y);
// }

// // --------------------------- Подсказка -------------------------------------------

// void Level_03::help()
// {
//     hand->raise();
//     if(!HELP_FLAG)
//     {
//         hand->move_to_xy(produkt[0]->x()+produkt[0]->width()/2,table->x()+table->width()/2,
//                          produkt[0]->y()+produkt[0]->height()/2,table->y(),2);
//     } else
//     {
//         hand->move_to_xy(produkt[6]->x()+produkt[6]->width()/2, WIDTH_SCREEN/6,
//                          produkt[6]->y()+produkt[6]->height()/2, HEIGHT_SCREEN/2, 2);
//     }
// }

// // -------------------------- Закрываем текущее окно --------------------------------

// void Level_03::back_level()
// {
//     this->close();
// }

#include "level_02.h"
#include <ctime>

Level_02::Level_02(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
}

Level_02::~Level_02()
{
    delete button_next;
    button_next = nullptr;
    delete button_back;
    button_back = nullptr;
    delete background_lev02;
    background_lev02 = nullptr;
    for(int i=0; i==7; i++)
    {
        delete instruments[i];
    }
    delete mysl;
    delete dedka;
    delete cell;
}

// ------------------- Инициализация ------------------------------------

void Level_02::initial()
{
    background_lev02 = new QLabel(this);
    background_lev02->setStyleSheet("border-image: url(:/resource/lev_02/saray.jpg);");
    this->setCentralWidget(background_lev02);
    background_lev02->show();

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    button_next = new QPushButton(this);
    button_next->setStyleSheet("border-image: url(:/resource/lev_01/next.png);");
    button_next->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_next->move(WIDTH_SCREEN-WIDTH_SCREEN/12, HEIGHT_SCREEN/20);
    button_next->hide();

    dedka = new PicObject(":/resource/lev_02/dedka.png", this);
    dedka->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/3);
    dedka->move(0,HEIGHT_SCREEN-dedka->height());
    dedka->show();

    mysl = new PicObject(":/resource/lev_02/mysl.png", this);
    mysl->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/3);
    mysl->move(dedka->width()/2, dedka->height());
    mysl->show();

    cell = new PicObject(":/resource/lev_02/fon.png", this);
    cell->resize_object(WIDTH_SCREEN/2, HEIGHT_SCREEN/10);
    cell->move(WIDTH_SCREEN/2-WIDTH_SCREEN/4,HEIGHT_SCREEN/30);
    cell->show();

    instruments[0] = new PicObject(":/resource/lev_02/fomka.png", this);
    instruments[0]->resize_object(WIDTH_SCREEN/14, HEIGHT_SCREEN/10);
    instruments[1] = new PicObject(":/resource/lev_02/leyka.png", this);
    instruments[1]->resize_object(WIDTH_SCREEN/13, HEIGHT_SCREEN/10);
    instruments[2] = new PicObject(":/resource/lev_02/lopata.png", this);
    instruments[2]->resize_object(WIDTH_SCREEN/10, HEIGHT_SCREEN/6);
    instruments[3] = new PicObject(":/resource/lev_02/molotok.png", this);
    instruments[3]->resize_object(WIDTH_SCREEN/21, HEIGHT_SCREEN/12);
    instruments[4] = new PicObject(":/resource/lev_02/serp.png", this);
    instruments[4]->resize_object(WIDTH_SCREEN/21, HEIGHT_SCREEN/12);
    instruments[5] = new PicObject(":/resource/lev_02/topor.png", this);
    instruments[5]->resize_object(WIDTH_SCREEN/26, HEIGHT_SCREEN/12);
    instruments[6] = new PicObject(":/resource/lev_02/vedro.png", this);
    instruments[6]->resize_object(WIDTH_SCREEN/26, HEIGHT_SCREEN/12);
    instruments[7] = new PicObject(":/resource/lev_02/vily.png", this);
    instruments[7]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/8);

    coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/8 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/5);
    coordinates.append(QList<int>() << WIDTH_SCREEN/3 << HEIGHT_SCREEN-HEIGHT_SCREEN/6);
    coordinates.append(QList<int>() << WIDTH_SCREEN-WIDTH_SCREEN/5 << HEIGHT_SCREEN-HEIGHT_SCREEN/6);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/17);
    coordinates.append(QList<int>() << WIDTH_SCREEN-WIDTH_SCREEN/4 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/17);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/5 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/12);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/12 << HEIGHT_SCREEN-HEIGHT_SCREEN/5);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/5 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/5);

    instruments[0]->move(coordinates.at(0).at(0), coordinates.at(0).at(1));
    instruments[0]->show();
    instruments[1]->move(coordinates.at(1).at(0), coordinates.at(1).at(1));
    instruments[1]->show();
    instruments[2]->move(coordinates.at(2).at(0), coordinates.at(2).at(1));
    instruments[2]->show();
    instruments[3]->move(coordinates.at(3).at(0), coordinates.at(3).at(1));
    instruments[3]->show();
    instruments[4]->move(coordinates.at(4).at(0), coordinates.at(4).at(1));
    instruments[4]->show();
    instruments[5]->move(coordinates.at(5).at(0), coordinates.at(5).at(1));
    instruments[5]->show();
    instruments[6]->move(coordinates.at(6).at(0), coordinates.at(6).at(1));
    instruments[6]->show();
    instruments[7]->move(coordinates.at(7).at(0), coordinates.at(7).at(1));
    instruments[7]->show();
}

// ------------------ Получаем ширину и высоту экрана ----------------------

void Level_02::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_02::get_height(int h)
{
    HEIGHT_SCREEN = h;
}

// -------------------- Возврат на 1 уровень -------------------------------

void Level_02::back_level()
{
    this->close();
}




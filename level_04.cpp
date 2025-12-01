#include "level_04.h"
#include <ctime>

Level_04::Level_04(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
}

Level_04::~Level_04()
{
    delete background;
    background = nullptr;
    delete button_back;
    button_back = nullptr;
    delete mysl;
    mysl = nullptr;
    delete vnuchka;
    vnuchka = nullptr;
    delete holst;
    holst = nullptr;
    delete vnuchka_holst;
    vnuchka_holst = nullptr;
    for(int i=0; i<7; i++)
    {
        delete pens[i];
        pens[i] = nullptr;
    }
}

// ------------------- Получаем ширину и высоту экрана --------------------

void Level_04::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_04::get_height(int h)
{
    HEIGHT_SCREEN = h;
}

// ------------------------- Инициализация --------------------------------

void Level_04::initial()
{
    // ------ курсор -------

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    // ---------------------

    background = new QLabel(this);
    background->setStyleSheet("border-image: url(:/resource/lev_04/fon.jpg);");
    this->setCentralWidget(background);
    background->show();
    button_back = new QPushButton(this);

    vnuchka = new PicObject(":/resource/lev_04/vnuchka-111.png", this);
    vnuchka->resize_object(WIDTH_SCREEN/8, HEIGHT_SCREEN/3);
    vnuchka->move(WIDTH_SCREEN/10, HEIGHT_SCREEN/2+HEIGHT_SCREEN/8);
    vnuchka->show();

    mysl = new PicObject(":/resource/lev_02/mysl.png", this);
    mysl->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/3);
    mysl->move(vnuchka->x()+vnuchka->width()/2, vnuchka->y()-vnuchka->height());
    mysl->show();

    holst = new PicObject(":/resource/lev_04/holst.png", this);
    holst->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    holst->move(WIDTH_SCREEN/2, HEIGHT_SCREEN/2-HEIGHT_SCREEN/4);
    holst->show();

    vnuchka_holst = new PicObject(":/resource/lev_04/vnuchka.png", holst);
    vnuchka_holst->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/3);
    vnuchka_holst->move(holst->width()/6, holst->height()/7);
    vnuchka_holst->show();

    container = new PicObject(":/resource/lev_02/fon.png", this);
    container->resize_object(WIDTH_SCREEN/3, HEIGHT_SCREEN/13);
    container->move(WIDTH_SCREEN/5, HEIGHT_SCREEN/20);
    container->show();

    pens[0] = new PicObject(":/resource/lev_04/karandash-1.png", this);
    pens[0]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[0]->move(container->x()+container->width()/15,
                  container->y()+container->height()/8);
    pens[0]->show();

    pens[1] = new PicObject(":/resource/lev_04/karandash-2.png", this);
    pens[1]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[1]->move(pens[0]->x()+container->width()/7, pens[0]->y());
    pens[1]->show();

    pens[2] = new PicObject(":/resource/lev_04/karandash-3.png", this);
    pens[2]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[2]->move(pens[1]->x()+container->width()/7, pens[1]->y());
    pens[2]->show();

    pens[3] = new PicObject(":/resource/lev_04/karandash-4.png", this);
    pens[3]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[3]->move(pens[2]->x()+container->width()/7, pens[2]->y());
    pens[3]->show();

    pens[4] = new PicObject(":/resource/lev_04/karandash-5.png", this);
    pens[4]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[4]->move(pens[3]->x()+container->width()/7, pens[3]->y());
    pens[4]->show();

    pens[5] = new PicObject(":/resource/lev_04/karandash-6.png", this);
    pens[5]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[5]->move(pens[4]->x()+container->width()/7, pens[4]->y());
    pens[5]->show();

    pens[6] = new PicObject(":/resource/lev_04/karandash-7.png", this);
    pens[6]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[6]->move(pens[5]->x()+container->width()/7, pens[5]->y());
    pens[6]->show();
    }

// -------------------------- Закрываем текущее окно --------------------------------

void Level_04::back_level()
{
    this->close();
}



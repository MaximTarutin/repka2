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
    holst->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/2+HEIGHT_SCREEN/6);
    holst->move(WIDTH_SCREEN/2, HEIGHT_SCREEN/2-HEIGHT_SCREEN/4);
    holst->show();
}

// -------------------------- Закрываем текущее окно --------------------------------

void Level_04::back_level()
{
    this->close();
}



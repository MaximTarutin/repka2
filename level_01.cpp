#include "level_01.h"


Level_01::Level_01(QWidget *parent)
    : QMainWindow(parent)
{

}

Level_01::~Level_01()
{
    delete chesnok_gray;
    delete baklagan_gray;
    delete repka_gray;
    delete button_next;
    delete button_back;
    delete background_lev01;
}

// ------------------- Инициализация --------------------------

void Level_01::initial()
{
    background_lev01 = new QLabel(this);
    background_lev01->setStyleSheet("border-image: url(:/resource/lev_01/fon.jpg);");
    this->setCentralWidget(background_lev01);
    background_lev01->show();

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

    repka_gray = new PicObject(":/resource/lev_01/repka-gray.png", this);
    repka_gray->resize_object(WIDTH_SCREEN/3, HEIGHT_SCREEN/3);
    repka_gray->move(WIDTH_SCREEN/15, HEIGHT_SCREEN-HEIGHT_SCREEN/3);
    repka_gray->show();

    baklagan_gray = new PicObject(":/resource/lev_01/baklagan-gray.png", this);
    baklagan_gray->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/5);
    baklagan_gray->move(WIDTH_SCREEN/60, HEIGHT_SCREEN/2+HEIGHT_SCREEN/20);
    baklagan_gray->show();

    chesnok_gray = new PicObject(":/resource/lev_01/chesnok-gray.png", this);
    chesnok_gray->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/7);
    chesnok_gray->move(WIDTH_SCREEN-WIDTH_SCREEN/3, HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    chesnok_gray->show();

    grusha_gray = new PicObject(":/resource/lev_01/grusha-gray.png", this);
    grusha_gray->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    grusha_gray->move(WIDTH_SCREEN/2+WIDTH_SCREEN/3, HEIGHT_SCREEN/2+HEIGHT_SCREEN/4);
    grusha_gray->show();

    morkovka_gray = new PicObject(":/resource/lev_01/morkovka-gray.png", this);
    morkovka_gray->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/4);
    morkovka_gray->move(WIDTH_SCREEN/2-WIDTH_SCREEN/4, HEIGHT_SCREEN/2+HEIGHT_SCREEN/4);
    morkovka_gray->show();

    ogurec_gray = new PicObject(":/resource/lev_01/ogurec-gray.png", this);
    ogurec_gray->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/5);
    ogurec_gray->move(WIDTH_SCREEN/2-WIDTH_SCREEN/20, HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
    ogurec_gray->show();
}

// ---------------- Получаем SCREEN_WIDTH ----------------------

void Level_01::get_width(int w)
{
    WIDTH_SCREEN = w;
}

// ---------------- Получаем SCREEN_HEIGHT ----------------------

void Level_01::get_height(int h)
{
    HEIGHT_SCREEN = h;
}

// ---------------- Возврат на главный экран --------------------

void Level_01::back_level()
{
    this->close();
}

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




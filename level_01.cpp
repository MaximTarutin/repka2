#include "level_01.h"
#include <ctime>


Level_01::Level_01(QWidget *parent)
    : QMainWindow(parent)
{
    srand(time(NULL));
}

Level_01::~Level_01()
{
    delete ptica;
    for(int i=0; i==8; i++)
    {
        delete ovoshi_gray[i];
    }
    for(int i=0; i==8; i++)
    {
        delete ovoshi_gray[i];
    }
    delete button_next;
    delete button_back;
    delete background_lev01;
}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Level_01::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
}


// ------------------- Инициализация --------------------------

void Level_01::initial()
{
    if(LEVEL_FLAG) return;

    LEVEL_FLAG = true;

    background_lev01 = new QLabel(this);
    background_lev01->setStyleSheet("border-image: url(:/resource/lev_01/fon.jpg);");
    this->setCentralWidget(background_lev01);
    background_lev01->show();

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    sklad = new PicObject(":/resource/lev_01/icon.png", this);
    sklad->resize_object(WIDTH_SCREEN/3, HEIGHT_SCREEN/3);
    sklad->move(WIDTH_SCREEN-WIDTH_SCREEN/4, HEIGHT_SCREEN/20);
    sklad->show();

    ptica = new PicObject(":/resource/lev_01/ptica.gif", this);
    ptica->animation_start(WIDTH_SCREEN/10, HEIGHT_SCREEN/8);
    ptica->move_to_x(0-ptica->width(),WIDTH_SCREEN+ptica->width(),0,40);
    ptica->show();

    ovoshi[0] = new PicObject(":/resource/lev_01/repka.png", this);
    ovoshi[0]->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/4);
    ovoshi[0]->move(sklad->x()+sklad->width()/2-ovoshi[0]->width()/2,
                    sklad->y()+sklad->height()/2-ovoshi[0]->height()/2);

    ovoshi[1] = new PicObject(":/resource/lev_01/baklagan.png", this);
    ovoshi[1]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    ovoshi[1]->move(sklad->x()+sklad->width()/2-ovoshi[0]->width()/2,
                    sklad->y()+sklad->height()/2-ovoshi[0]->height()/2);

    ovoshi[2] = new PicObject(":/resource/lev_01/chesnok.png", this);
    ovoshi[2]->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/7);
    ovoshi[2]->move(sklad->x()+sklad->width()/2-ovoshi[0]->width()/2,
                    sklad->y()+sklad->height()/2-ovoshi[0]->height()/2);

    ovoshi[3] = new PicObject(":/resource/lev_01/grusha.png", this);
    ovoshi[3]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    ovoshi[3]->move(sklad->x()+sklad->width()/2-ovoshi[0]->width()/2,
                    sklad->y()+sklad->height()/2-ovoshi[0]->height()/2);

    ovoshi[4] = new PicObject(":/resource/lev_01/morkovka.png", this);
    ovoshi[4]->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/4);
    ovoshi[4]->move(sklad->x()+sklad->width()/2-ovoshi[0]->width()/2,
                    sklad->y()+sklad->height()/2-ovoshi[0]->height()/2);

    ovoshi[5] = new PicObject(":/resource/lev_01/ogurec.png", this);
    ovoshi[5]->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/5);
    ovoshi[5]->move(sklad->x()+sklad->width()/2-ovoshi[0]->width()/2,
                    sklad->y()+sklad->height()/2-ovoshi[0]->height()/2);

    ovoshi[6] = new PicObject(":/resource/lev_01/tomat.png", this);
    ovoshi[6]->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/7);
    ovoshi[6]->move(sklad->x()+sklad->width()/2-ovoshi[0]->width()/2,
                    sklad->y()+sklad->height()/2-ovoshi[0]->height()/2);

    ovoshi[7] = new PicObject(":/resource/lev_01/tykva.png", this);
    ovoshi[7]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    ovoshi[7]->move(sklad->x()+sklad->width()/2-ovoshi[0]->width()/2,
                    sklad->y()+sklad->height()/2-ovoshi[0]->height()/2);

    ovoshi[8] = new PicObject(":/resource/lev_01/rediska.png", this);
    ovoshi[8]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    ovoshi[8]->move(sklad->x()+sklad->width()/2-ovoshi[0]->width()/2,
                    sklad->y()+sklad->height()/2-ovoshi[0]->height()/2);

    // Координаты серых объектов хранятся в списке

    QList<QList<int>>  coordinates;
    coordinates.append(QList<int>() << WIDTH_SCREEN/25 << HEIGHT_SCREEN-HEIGHT_SCREEN/4);
    coordinates.append(QList<int>() << WIDTH_SCREEN/60 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/20);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/10 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/3 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/4 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/4);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/20 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/5 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
    coordinates.append(QList<int>() << WIDTH_SCREEN/6 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/15);
    coordinates.append(QList<int>() << WIDTH_SCREEN-WIDTH_SCREEN/9 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/8);

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

    ovoshi_gray[0] = new PicObject(":/resource/lev_01/repka-gray.png", this);
    ovoshi_gray[0]->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/4);
    ovoshi_gray[0]->show();

    ovoshi_gray[1] = new PicObject(":/resource/lev_01/baklagan-gray.png", this);
    ovoshi_gray[1]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    ovoshi_gray[1]->show();

    ovoshi_gray[2] = new PicObject(":/resource/lev_01/chesnok-gray.png", this);
    ovoshi_gray[2]->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/7);
    ovoshi_gray[2]->show();

    ovoshi_gray[3]= new PicObject(":/resource/lev_01/grusha-gray.png", this);
    ovoshi_gray[3]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    ovoshi_gray[3]->show();

    ovoshi_gray[4] = new PicObject(":/resource/lev_01/morkovka-gray.png", this);
    ovoshi_gray[4]->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/4);
    ovoshi_gray[4]->show();

    ovoshi_gray[5] = new PicObject(":/resource/lev_01/ogurec-gray.png", this);
    ovoshi_gray[5]->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/5);
    ovoshi_gray[5]->show();

    ovoshi_gray[6] = new PicObject(":/resource/lev_01/tomat-gray.png", this);
    ovoshi_gray[6]->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/7);
    ovoshi_gray[6]->show();

    ovoshi_gray[7] = new PicObject(":/resource/lev_01/tykva-gray.png", this);
    ovoshi_gray[7]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    ovoshi_gray[7]->show();

    ovoshi_gray[8] = new PicObject(":/resource/lev_01/rediska-gray.png", this);
    ovoshi_gray[8]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    ovoshi_gray[8]->show();

    int temp = 0;
    int k = 0;
    value_i = {0,1,2,3,4,5,6,7,8};

    for(int i=0; i<9; i++)
    {
        k = rnd(0,8);
        temp = value_i[k];
        value_i[k] = value_i[i];        // Перемешиваем список овощей
        value_i[i] = temp;
    }

    for(int i=0; i<9; i++)
    {
        x1[i] = coordinates.at(value_i[i]).at(0);   // Расставляем серые овощи на поле
        y1[i] = coordinates.at(value_i[i]).at(1);
        ovoshi_gray[i]->move(x1[i],y1[i]);
    }

    QList<int>::const_reverse_iterator it = value_i.rbegin(); // читаем value_i с конца
    while (it != value_i.rend())
    {
        ovoshi[*it]->raise();     // складываем овощи по списку value_i
        ovoshi[*it]->show();      // на переднем плане первый элемент
        ++it;
    }

    help = new PicObject(":/resource/lev_01/ruka.png", this);
    help->resize_object(WIDTH_SCREEN/11, HEIGHT_SCREEN/11);
    help_move_end();
    help->show();
    connect(help, &PicObject::move_end, this, &Level_01::help_move_end);
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

// ----------------- Окончание движения руки ----------------------

void Level_01::help_move_end()
{
    help->hide();
    help->move_to_xy(ovoshi[value_i[0]]->x(),
                     ovoshi_gray[value_i[0]]->x(),
                     ovoshi[value_i[0]]->y(),
                     ovoshi_gray[value_i[0]]->y(), 5);
    help->show();
}

// ----------------- Нажатие кнопки мышки -----------------------------

void Level_01::mousePressEvent(QMouseEvent *pe)
{
    if(((pe->position().x() > ovoshi[CURRENT_OBJECT]->x())and
       (pe->position().x() < ovoshi[CURRENT_OBJECT]->x()+ovoshi[CURRENT_OBJECT]->width()/2)and
       (pe->position().y() > ovoshi[CURRENT_OBJECT]->y())and
       (pe->position().y() < ovoshi[CURRENT_OBJECT]->y()+ovoshi[CURRENT_OBJECT]->height()/2)))
    {
        disconnect(help, &PicObject::move_end, this, &Level_01::help_move_end);
        help->hide();
    }
    qDebug() << ovoshi[CURRENT_OBJECT]->width() << ovoshi[CURRENT_OBJECT]->x();
}

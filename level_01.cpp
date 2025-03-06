#include "level_01.h"
#include <ctime>


Level_01::Level_01(QWidget *parent)
    : QMainWindow(parent)
{
    srand(time(NULL));
}

Level_01::~Level_01()
{
    delete bird;
    for(int i=0; i==8; i++)
    {
        delete vegetable[i];
    }
    for(int i=0; i==8; i++)
    {
        delete vegetable_gray[i];
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

    timer_bird = new QTimer(this);

    background_lev01 = new QLabel(this);
    background_lev01->setStyleSheet("border-image: url(:/resource/lev_01/fon.jpg);");
    this->setCentralWidget(background_lev01);
    background_lev01->show();

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    warehouse = new PicObject(":/resource/lev_01/icon.png", this);
    warehouse->resize_object(WIDTH_SCREEN/3, HEIGHT_SCREEN/3);
    warehouse->move(WIDTH_SCREEN-WIDTH_SCREEN/4, HEIGHT_SCREEN/20);
    warehouse->show();

    bird = new PicObject(":/resource/lev_01/ptica.gif", this);
    bird->animation_start(WIDTH_SCREEN/10, HEIGHT_SCREEN/8);
    bird->move_to_x(0-bird->width(),WIDTH_SCREEN+bird->width(),0,40);
    bird->show();

    connect(bird, &PicObject::move_end, this, [this](){timer_bird->start(100);});  // если птица долетела до конца экрана
    connect(timer_bird, &QTimer::timeout, this, &Level_01::flight_bird);

    vegetable[0] = new PicObject(":/resource/lev_01/repka.png", this);
    vegetable[0]->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/4);
    vegetable[0]->move(warehouse->x()+warehouse->width()/2-vegetable[0]->width()/2,
                    warehouse->y()+warehouse->height()/2-vegetable[0]->height()/2);

    vegetable[1] = new PicObject(":/resource/lev_01/baklagan.png", this);
    vegetable[1]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    vegetable[1]->move(warehouse->x()+warehouse->width()/2-vegetable[0]->width()/2,
                    warehouse->y()+warehouse->height()/2-vegetable[0]->height()/2);

    vegetable[2] = new PicObject(":/resource/lev_01/chesnok.png", this);
    vegetable[2]->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/7);
    vegetable[2]->move(warehouse->x()+warehouse->width()/2-vegetable[0]->width()/2,
                    warehouse->y()+warehouse->height()/2-vegetable[0]->height()/2);

    vegetable[3] = new PicObject(":/resource/lev_01/grusha.png", this);
    vegetable[3]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    vegetable[3]->move(warehouse->x()+warehouse->width()/2-vegetable[0]->width()/2,
                    warehouse->y()+warehouse->height()/2-vegetable[0]->height()/2);

    vegetable[4] = new PicObject(":/resource/lev_01/morkovka.png", this);
    vegetable[4]->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/4);
    vegetable[4]->move(warehouse->x()+warehouse->width()/2-vegetable[0]->width()/2,
                    warehouse->y()+warehouse->height()/2-vegetable[0]->height()/2);

    vegetable[5] = new PicObject(":/resource/lev_01/ogurec.png", this);
    vegetable[5]->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/5);
    vegetable[5]->move(warehouse->x()+warehouse->width()/2-vegetable[0]->width()/2,
                    warehouse->y()+warehouse->height()/2-vegetable[0]->height()/2);

    vegetable[6] = new PicObject(":/resource/lev_01/tomat.png", this);
    vegetable[6]->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/7);
    vegetable[6]->move(warehouse->x()+warehouse->width()/2-vegetable[0]->width()/2,
                    warehouse->y()+warehouse->height()/2-vegetable[0]->height()/2);

    vegetable[7] = new PicObject(":/resource/lev_01/tykva.png", this);
    vegetable[7]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    vegetable[7]->move(warehouse->x()+warehouse->width()/2-vegetable[0]->width()/2,
                    warehouse->y()+warehouse->height()/2-vegetable[0]->height()/2);

    vegetable[8] = new PicObject(":/resource/lev_01/rediska.png", this);
    vegetable[8]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    vegetable[8]->move(warehouse->x()+warehouse->width()/2-vegetable[0]->width()/2,
                    warehouse->y()+warehouse->height()/2-vegetable[0]->height()/2);

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

    vegetable_gray[0] = new PicObject(":/resource/lev_01/repka-gray.png", this);
    vegetable_gray[0]->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/4);
    vegetable_gray[0]->show();

    vegetable_gray[1] = new PicObject(":/resource/lev_01/baklagan-gray.png", this);
    vegetable_gray[1]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    vegetable_gray[1]->show();

    vegetable_gray[2] = new PicObject(":/resource/lev_01/chesnok-gray.png", this);
    vegetable_gray[2]->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/7);
    vegetable_gray[2]->show();

    vegetable_gray[3]= new PicObject(":/resource/lev_01/grusha-gray.png", this);
    vegetable_gray[3]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    vegetable_gray[3]->show();

    vegetable_gray[4] = new PicObject(":/resource/lev_01/morkovka-gray.png", this);
    vegetable_gray[4]->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/4);
    vegetable_gray[4]->show();

    vegetable_gray[5] = new PicObject(":/resource/lev_01/ogurec-gray.png", this);
    vegetable_gray[5]->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/5);
    vegetable_gray[5]->show();

    vegetable_gray[6] = new PicObject(":/resource/lev_01/tomat-gray.png", this);
    vegetable_gray[6]->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/7);
    vegetable_gray[6]->show();

    vegetable_gray[7] = new PicObject(":/resource/lev_01/tykva-gray.png", this);
    vegetable_gray[7]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    vegetable_gray[7]->show();

    vegetable_gray[8] = new PicObject(":/resource/lev_01/rediska-gray.png", this);
    vegetable_gray[8]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    vegetable_gray[8]->show();

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
        vegetable_gray[i]->move(x1[i],y1[i]);
    }

    QList<int>::const_reverse_iterator it = value_i.rbegin(); // читаем value_i с конца
    while (it != value_i.rend())
    {
        vegetable[*it]->raise();     // складываем овощи по списку value_i
        vegetable[*it]->show();      // на переднем плане первый элемент
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
    help->move_to_xy(vegetable[value_i[0]]->x(),
                     vegetable_gray[value_i[0]]->x(),
                     vegetable[value_i[0]]->y(),
                     vegetable_gray[value_i[0]]->y(), 5);
    help->show();
}

// ----------------- Нажатие кнопки мышки -----------------------------

void Level_01::mousePressEvent(QMouseEvent *pe)
{
    if(((pe->position().x() > vegetable[CURRENT_OBJECT]->x())and
       (pe->position().x() < vegetable[CURRENT_OBJECT]->x()+vegetable[CURRENT_OBJECT]->width()/2)and
       (pe->position().y() > vegetable[CURRENT_OBJECT]->y())and
       (pe->position().y() < vegetable[CURRENT_OBJECT]->y()+vegetable[CURRENT_OBJECT]->height()/2)))
    {
        disconnect(help, &PicObject::move_end, this, &Level_01::help_move_end);
        help->hide();
    }
    qDebug() << vegetable[CURRENT_OBJECT]->width() << vegetable[CURRENT_OBJECT]->x();
}

// --------------------- Полет птицы через случайный промежуток времени ------------------

void Level_01::flight_bird()
{
    int i = rnd(0,100);
    int j = rnd(0,100);
    if(i==j)
    {
        int bird_y = rnd(0, HEIGHT_SCREEN/10);
        bird->move_to_x(0-bird->width(),WIDTH_SCREEN+bird->width(),bird_y,40);
        bird->raise();
        timer_bird->stop();
    }
}


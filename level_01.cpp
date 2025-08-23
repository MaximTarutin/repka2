#include "level_01.h"
#include <ctime>

Level_01::Level_01(QWidget *parent)
    : QMainWindow(parent)
{
    srand(time(NULL));
    sound = new QMediaPlayer(this);
    output = new QAudioOutput();
    sound->setAudioOutput(output);
    output->setVolume(1);
}

Level_01::~Level_01()
{
    delete sound;
    sound = nullptr;
    delete output;
    output = nullptr;
    delete timer_bird;
    timer_bird = nullptr;
    delete bird;
    bird = nullptr;
    for(int i=0; i==8; i++)
    {
        delete vegetable[i];
        vegetable[i] = nullptr;
        delete vegetable_gray[i];
        vegetable_gray[i] = nullptr;
    }
    delete button_next;
    button_next = nullptr;
    delete button_back;
    button_back = nullptr;
    delete background_lev01;
    background_lev01 = nullptr;
}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Level_01::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
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

// ------------------- Инициализация --------------------------

void Level_01::initial()
{
    if(LEVEL_FLAG) return;                  // Если уровень уже запускался, то пропускаем инициализацию

    LEVEL_FLAG = true;

    timer_bird = new QTimer(this);

    background_lev01 = new QLabel(this);
    background_lev01->setStyleSheet("border-image: url(:/resource/lev_01/fon.jpg);");
    this->setCentralWidget(background_lev01);
    background_lev01->show();

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    warehouse = new PicObject(":/resource/lev_01/icon.png", this);
    warehouse->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/3);
    warehouse->move(WIDTH_SCREEN-WIDTH_SCREEN/4, HEIGHT_SCREEN/20);
    warehouse->show();

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

    vegetable[0] = new PicObject(":/resource/lev_01/repka.png", this);
    vegetable[0]->resize_object(WIDTH_SCREEN/10, HEIGHT_SCREEN/4);
    vegetable[1] = new PicObject(":/resource/lev_01/baklagan.png", this);
    vegetable[1]->resize_object(WIDTH_SCREEN/19, HEIGHT_SCREEN/7);
    vegetable[2] = new PicObject(":/resource/lev_01/chesnok.png", this);
    vegetable[2]->resize_object(WIDTH_SCREEN/15, HEIGHT_SCREEN/6);
    vegetable[3] = new PicObject(":/resource/lev_01/grusha.png", this);
    vegetable[3]->resize_object(WIDTH_SCREEN/15, HEIGHT_SCREEN/6);
    vegetable[4] = new PicObject(":/resource/lev_01/morkovka.png", this);
    vegetable[4]->resize_object(WIDTH_SCREEN/15, HEIGHT_SCREEN/5);
    vegetable[5] = new PicObject(":/resource/lev_01/ogurec.png", this);
    vegetable[5]->resize_object(WIDTH_SCREEN/12, HEIGHT_SCREEN/5);
    vegetable[6] = new PicObject(":/resource/lev_01/tomat.png", this);
    vegetable[6]->resize_object(WIDTH_SCREEN/12, HEIGHT_SCREEN/8);
    vegetable[7] = new PicObject(":/resource/lev_01/tykva.png", this);
    vegetable[7]->resize_object(WIDTH_SCREEN/12, HEIGHT_SCREEN/6);
    vegetable[8] = new PicObject(":/resource/lev_01/rediska.png", this);
    vegetable[8]->resize_object(WIDTH_SCREEN/13, HEIGHT_SCREEN/6);

    for(int i=0; i<9; i++)
    {
        vegetable[i]->move(warehouse->x()+warehouse->width()/2-vegetable[i]->width()/2,
                           warehouse->y()+warehouse->height()/2-vegetable[i]->height()/2);
    }

    // Координаты серых объектов хранятся в списке

    coordinates_g.append(QList<int>() << WIDTH_SCREEN/25 << HEIGHT_SCREEN-HEIGHT_SCREEN/4);
    coordinates_g.append(QList<int>() << WIDTH_SCREEN/60 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/20);
    coordinates_g.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/10 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    coordinates_g.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/3 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    coordinates_g.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/4 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/4);
    coordinates_g.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/20 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
    coordinates_g.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/5 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
    coordinates_g.append(QList<int>() << WIDTH_SCREEN/6 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/15);
    coordinates_g.append(QList<int>() << WIDTH_SCREEN-WIDTH_SCREEN/9 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/8);

    vegetable_gray[0] = new PicObject(":/resource/lev_01/repka-gray.png", this);
    vegetable_gray[0]->resize_object(WIDTH_SCREEN/10, HEIGHT_SCREEN/4);
    vegetable_gray[1] = new PicObject(":/resource/lev_01/baklagan-gray.png", this);
    vegetable_gray[1]->resize_object(WIDTH_SCREEN/19, HEIGHT_SCREEN/7);
    vegetable_gray[2] = new PicObject(":/resource/lev_01/chesnok-gray.png", this);
    vegetable_gray[2]->resize_object(WIDTH_SCREEN/15, HEIGHT_SCREEN/6);
    vegetable_gray[3]= new PicObject(":/resource/lev_01/grusha-gray.png", this);
    vegetable_gray[3]->resize_object(WIDTH_SCREEN/15, HEIGHT_SCREEN/6);
    vegetable_gray[4] = new PicObject(":/resource/lev_01/morkovka-gray.png", this);
    vegetable_gray[4]->resize_object(WIDTH_SCREEN/15, HEIGHT_SCREEN/5);
    vegetable_gray[5] = new PicObject(":/resource/lev_01/ogurec-gray.png", this);
    vegetable_gray[5]->resize_object(WIDTH_SCREEN/12, HEIGHT_SCREEN/5);
    vegetable_gray[6] = new PicObject(":/resource/lev_01/tomat-gray.png", this);
    vegetable_gray[6]->resize_object(WIDTH_SCREEN/12, HEIGHT_SCREEN/8);
    vegetable_gray[7] = new PicObject(":/resource/lev_01/tykva-gray.png", this);
    vegetable_gray[7]->resize_object(WIDTH_SCREEN/12, HEIGHT_SCREEN/6);
    vegetable_gray[8] = new PicObject(":/resource/lev_01/rediska-gray.png", this);
    vegetable_gray[8]->resize_object(WIDTH_SCREEN/13, HEIGHT_SCREEN/6);

    for(int i=0; i<9; i++)
    {
        vegetable_gray[i]->show();
    }

    mix_vegetables(); // перемешаем овощи

    for(int i=0; i<9; i++)
    {
        x1[i] = coordinates_g.at(value_i[i]).at(0);   // Расставляем серые овощи на поле
        y1[i] = coordinates_g.at(value_i[i]).at(1);
        vegetable_gray[i]->move(x1[i],y1[i]);
    }

    QList<int>::const_reverse_iterator it = value_i.rbegin(); // читаем value_i с конца
    while (it != value_i.rend())
    {
        vegetable[*it]->raise();     // складываем овощи по списку value_i
        vegetable[*it]->show();      // на переднем плане первый элемент
        ++it;
    }    
    animation_level();      // запускаем анимацию на уровне
}

// ---------------- Перемешаем список нумерации овощей --------------------------

void Level_01::mix_vegetables()
{
    int temp = 0;
    int k = 0;
    value_i = {0,1,2,3,4,5,6,7,8};      // порядок овощей
    for(int i=0; i<9; i++)
    {
        k = rnd(0,8);
        temp = value_i[k];
        value_i[k] = value_i[i];        // Перемешиваем список овощей
        value_i[i] = temp;
    }
}

// ----------------- Анимация на уровне --------------------------

void Level_01::animation_level()
{
    help = new PicObject(":/resource/lev_01/ruka.png", this);
    help->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/11);
    help_move_end();
    help->show();
    connect(help, &PicObject::move_end, this, &Level_01::help_move_end);

    bird = new PicObject(":/resource/lev_01/ptica.gif", this);
    bird->animation_start(WIDTH_SCREEN/10, HEIGHT_SCREEN/8);
    bird->move_to_x(0-bird->width(),WIDTH_SCREEN+bird->width(),0,40);
    bird->show();
    bird->raise();

    connect(bird, &PicObject::move_end, this, [this](){timer_bird->start(100);});  // если птица долетела до конца экрана
    connect(timer_bird, &QTimer::timeout, this, &Level_01::flight_bird);
}

// ----------------- Окончание движения руки ----------------------

void Level_01::help_move_end()
{
    help->hide();
    help->move_to_xy(vegetable[value_i[0]]->x(),
                     vegetable_gray[value_i[0]]->x(),
                     vegetable[value_i[0]]->y(),
                     vegetable_gray[value_i[0]]->y(), 3);
    help->show();
}

// --------------------- Полет птицы через случайный промежуток времени ------------------

void Level_01::flight_bird()
{
    int i = rnd(0,150);
    int j = rnd(0,150);
    if(i==j)
    {
        int bird_y = rnd(0, HEIGHT_SCREEN/10);
        bird->move_to_x(0-bird->width(),WIDTH_SCREEN+bird->width(),bird_y,40);
        bird->raise();
        timer_bird->stop();
    }
}

// ---------------- Возврат на главный экран --------------------

void Level_01::back_level()
{
    if(LEVEL_END)
    {
        for(int i=0; i<9; i++)
        {
            if (vegetable[i] != (void*)0) // если объект существует, то удаляем его
            {
                delete vegetable[i];
                vegetable[i] = nullptr;
            }
        }
    }
    this->close();
}

// ----------------- Нажатие кнопки мышки -----------------------------

void Level_01::mousePressEvent(QMouseEvent *pe)
{
    if(((pe->position().x() > vegetable[value_i[CURRENT_OBJECT]]->x())and
       (pe->position().x() < vegetable[value_i[CURRENT_OBJECT]]->x()+vegetable[value_i[CURRENT_OBJECT]]->width())and
       (pe->position().y() > vegetable[value_i[CURRENT_OBJECT]]->y())and
       (pe->position().y() < vegetable[value_i[CURRENT_OBJECT]]->y()+vegetable[value_i[CURRENT_OBJECT]]->height())))
    {
        if (help != (void*)0)
        {
            disconnect(help, &PicObject::move_end, this, &Level_01::help_move_end);
            delete help;
            help=nullptr;
        }
        CURRENT_OBJECT_ACTIVE = true;
    }
}

// --------------------------------- Перемещение овощей ----------------------------------

void Level_01::mouseMoveEvent(QMouseEvent *pe)
{
    if(CURRENT_OBJECT_ACTIVE)
    {
        vegetable[value_i[CURRENT_OBJECT]]->raise();
        vegetable[value_i[CURRENT_OBJECT]]->move(pe->position().x()-
                                                 vegetable[value_i[CURRENT_OBJECT]]->width()/2,
                                                 pe->position().y()-
                                                 vegetable[value_i[CURRENT_OBJECT]]->height()/2);
    }
}

// --------------------------------- Отпускаем кнопку мышки ----------------------------------

void Level_01::mouseReleaseEvent(QMouseEvent *pe)
{
    if(LEVEL_END) return;
    pe->pos();
    int x1_g = vegetable_gray[value_i[CURRENT_OBJECT]]->x();
    int x2_g = vegetable_gray[value_i[CURRENT_OBJECT]]->x()+vegetable_gray[value_i[CURRENT_OBJECT]]->width();
    int x1 = vegetable[value_i[CURRENT_OBJECT]]->x();
    int x1_1 = warehouse->x()+warehouse->width()/2-vegetable[0]->width()/2;
    int x2 = vegetable[value_i[CURRENT_OBJECT]]->x()+vegetable[value_i[CURRENT_OBJECT]]->width();
    int y1_g = vegetable_gray[value_i[CURRENT_OBJECT]]->y();
    int y2_g = vegetable_gray[value_i[CURRENT_OBJECT]]->y()+vegetable_gray[value_i[CURRENT_OBJECT]]->height();
    int y1 = vegetable[value_i[CURRENT_OBJECT]]->y();
    int y1_1 = warehouse->y()+warehouse->height()/2-vegetable[0]->height()/2;
    int y2 = vegetable[value_i[CURRENT_OBJECT]]->y()+vegetable[value_i[CURRENT_OBJECT]]->height();

    CURRENT_OBJECT_ACTIVE = false;
    if((x2>x1_g)&&(x1<x2_g)&&(y2>y1_g)&&(y1<y2_g))
    {
        vegetable[value_i[CURRENT_OBJECT]]->move(vegetable_gray[value_i[CURRENT_OBJECT]]->x(),
                                                 vegetable_gray[value_i[CURRENT_OBJECT]]->y());
        CURRENT_OBJECT++;
        sound->setSource(QUrl("qrc:/resource/sound/yes.mp3"));
        sound->play();
        if(CURRENT_OBJECT>8)
        {
            CURRENT_OBJECT=8;
            LEVEL_END = true;
            victory();
        }
    } else
    {
        sound->setSource(QUrl("qrc:/resource/sound/nea.wav"));
        sound->play();
        vegetable[value_i[CURRENT_OBJECT]]->move_to_xy(x1,x1_1,y1,y1_1, 1, 4);  // возвращаем овощ на место
    }

}

// ---------------------------------- Победа ----------------------------------------------

void Level_01::victory()
{
    int x1, y1;         // конечные координаты
    int x, y;           // начальные координаты
    int direction;      // направление движения овощей

    for(int i=0; i<9; i++)
    {
        direction = rnd(0,3);
        x = vegetable[i]->x();
        y = vegetable[i]->y();

        switch(direction)
        {
        case 0: x1 = rnd(WIDTH_SCREEN, WIDTH_SCREEN*2);
                y1 = rnd(HEIGHT_SCREEN, HEIGHT_SCREEN*2);
            break;
        case 1: x1 = rnd(WIDTH_SCREEN, WIDTH_SCREEN*2);
                y1 = rnd(-HEIGHT_SCREEN, -HEIGHT_SCREEN*2);
            break;
        case 2: x1 = rnd(-WIDTH_SCREEN*2, -WIDTH_SCREEN);
                y1 = rnd(-HEIGHT_SCREEN*2, -HEIGHT_SCREEN);
            break;
        case 3: x1 = rnd(-WIDTH_SCREEN, -WIDTH_SCREEN*2);
                y1 = rnd(HEIGHT_SCREEN, HEIGHT_SCREEN*2);
            break;
        }
        vegetable[i]->move_to_xy(x,x1,y,y1,0,4);
        delete vegetable_gray[i];
        vegetable_gray[i] = nullptr;
    }

    delete warehouse;
    warehouse = nullptr;

    repka = new PicObject(":/resource/lev_01/repka.png", this);
    repka->show();
    repka->move(WIDTH_SCREEN/25, HEIGHT_SCREEN/2+HEIGHT_SCREEN/8);
    repka->resize_object(WIDTH_SCREEN/10*2, HEIGHT_SCREEN/4*2);
    LEVEL_END = true;
    emit next_level();
    button_next->show();
}


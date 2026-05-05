#include "level_05.h"
#include "qmediaplayer.h"
#include "qpushbutton.h"
#include <ctime>

Level_05::Level_05(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
}
Level_05::~Level_05()
{
    delete output;
    output = nullptr;
    delete sound;
    sound = nullptr;
    delete background;
    background = nullptr;
    delete button_back;
    button_back = nullptr;
    delete pic_mysl;
    pic_mysl = nullptr;
    delete mysl;
    mysl = nullptr;
    delete dog;
    dog = nullptr;
    for(int i=0; i<=8; i++)
    {
        delete panel[i];
        panel[i] = nullptr;
        delete pazl[i];
        pazl[i] = nullptr;
    }
    delete timer_victory;
    timer_victory = nullptr;
}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Level_05::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
}

// -------------------- Получаем разрешение экрана --------------------------------

void Level_05::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_05::get_height(int h)
{
    HEIGHT_SCREEN = h;
}

// --------------------------- Инициализация --------------------------------------

void Level_05::initial()
{
    sound = new QMediaPlayer(this);
    output = new QAudioOutput();
    sound->setAudioOutput(output);
    output->setVolume(1);

    // ------ курсор -------

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    // ---------------------

    background = new QLabel(this);
    background->setStyleSheet("border-image: url(:/resource/lev_05/dvor.jpeg);"); // Фон экрана
    this->setCentralWidget(background);
    background->show();

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    dog = new PicObject(":/resource/lev_05/zuchka.png", this);
    dog->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/2+HEIGHT_SCREEN/20);
    dog->move(WIDTH_SCREEN/2+WIDTH_SCREEN/8, HEIGHT_SCREEN/2-HEIGHT_SCREEN/8);    // Собака на фоне
    dog->show();

    mysl = new PicObject(":/resource/lev_02/mysl.png", this);
    mysl->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/3+HEIGHT_SCREEN/15);
    mysl->move(dog->x()+dog->width()/2, dog->y()-dog->height()/2-dog->height()/6);  // Мысль собаки
    mysl->show();

    panel[0] = new PicObject(":/resource/lev_05/cyan.png", this);
    panel[0]->resize_object(WIDTH_SCREEN/9, HEIGHT_SCREEN/5);

    coordinates_panel.append(QList<int>() << WIDTH_SCREEN/40 << HEIGHT_SCREEN/6);
    panel[0]->move(coordinates_panel.at(0).at(0), coordinates_panel.at(0).at(1));
    coordinates_panel.append(QList<int>() << panel[0]->x()+panel[0]->width() << panel[0]->y());
    coordinates_panel.append(QList<int>() << panel[0]->x()+panel[0]->width()*2 << panel[0]->y());
    coordinates_panel.append(QList<int>() << panel[0]->x() << panel[0]->y()+panel[0]->height());
    coordinates_panel.append(QList<int>() << panel[0]->x()+panel[0]->width() << panel[0]->y()+panel[0]->height());
    coordinates_panel.append(QList<int>() << panel[0]->x()+panel[0]->width()*2 << panel[0]->y()+panel[0]->height());
    coordinates_panel.append(QList<int>() << panel[0]->x() << panel[0]->y()+panel[0]->height()*2);
    coordinates_panel.append(QList<int>() << panel[0]->x()+panel[0]->width() << panel[0]->y()+panel[0]->height()*2);
    coordinates_panel.append(QList<int>() << panel[0]->x()+panel[0]->width()*2 << panel[0]->y()+panel[0]->height()*2);


    for(int i=1; i<=8; i++)
    {
        panel[i] = new PicObject(":/resource/lev_05/cyan.png", this);                       // Рисуем панель
        panel[i]->resize_object(WIDTH_SCREEN/9, HEIGHT_SCREEN/5);
        panel[i]->move(coordinates_panel.at(i).at(0), coordinates_panel.at(i).at(1));
        panel[i]->show();
        qDebug() << i << panel[i]->pos();
    }

    int nabor = rnd(0,5);      // случайный набор пазлов

    pic_mysl = new PicObject(":/resource/lev_05/00-"+QString::number(nabor)+".png", mysl);
    pic_mysl->resize_object(WIDTH_SCREEN/11, HEIGHT_SCREEN/6);
    pic_mysl->move(mysl->width()/3, mysl->height()/5);
    pic_mysl->show();

    for(int i=0; i<=8; i++)         // создаем элементы пазла
    {
        QString name = ":/resource/lev_05/0"+QString::number(i+1)+"-"+QString::number(nabor)+".png";
        pazl[i] = new PicObject(name, this);
        pazl[i]->resize_object(WIDTH_SCREEN/9, HEIGHT_SCREEN/5);
        pazl[i]->hide();
        pazl[i]->setObjectName(QString::number(i));
        connect(pazl[i], &PicObject::clicked, this, &Level_05::mousePressEvent);
    }

    pazl[0]->move(panel[0]->x(), panel[6]->y()+HEIGHT_SCREEN/5+HEIGHT_SCREEN/100);
    pazl[1]->move(pazl[0]->x()+pazl[0]->width()+WIDTH_SCREEN/90, pazl[0]->y());
    pazl[2]->move(pazl[1]->x()+pazl[1]->width()+WIDTH_SCREEN/90, pazl[1]->y());
    pazl[3]->move(pazl[2]->x()+pazl[2]->width()+WIDTH_SCREEN/90, pazl[2]->y());
    pazl[4]->move(pazl[2]->x()+pazl[2]->width()+WIDTH_SCREEN/90,
                  pazl[3]->y()-pazl[3]->height()-HEIGHT_SCREEN/100);                // Расставляем пазлы сначала по порядку
    pazl[5]->move(pazl[2]->x()+pazl[2]->width()+WIDTH_SCREEN/90,
                  pazl[4]->y()-pazl[4]->height()-HEIGHT_SCREEN/100);
    pazl[6]->move(pazl[2]->x()+pazl[2]->width()+WIDTH_SCREEN/90,
                  pazl[5]->y()-pazl[5]->height()-HEIGHT_SCREEN/100);
    pazl[7]->move(pazl[4]->x()+pazl[4]->width()+WIDTH_SCREEN/90,
                  pazl[0]->y()-pazl[0]->height()-HEIGHT_SCREEN/100);
    pazl[8]->move(pazl[4]->x()+pazl[4]->width()+WIDTH_SCREEN/90, pazl[0]->y());

    coordinates_pazl.append(QList<int>() << pazl[0]->x() << pazl[0]->y());
    coordinates_pazl.append(QList<int>() << pazl[1]->x() << pazl[1]->y());
    coordinates_pazl.append(QList<int>() << pazl[2]->x() << pazl[2]->y());
    coordinates_pazl.append(QList<int>() << pazl[3]->x() << pazl[3]->y());
    coordinates_pazl.append(QList<int>() << pazl[4]->x() << pazl[4]->y());          // Составляем список возможных координат
    coordinates_pazl.append(QList<int>() << pazl[5]->x() << pazl[5]->y());
    coordinates_pazl.append(QList<int>() << pazl[6]->x() << pazl[6]->y());
    coordinates_pazl.append(QList<int>() << pazl[7]->x() << pazl[7]->y());
    coordinates_pazl.append(QList<int>() << pazl[8]->x() << pazl[8]->y());

    //-------------- Перемешаем список координат пазлов -------------------

    QList<int> temp;
    int k = 0;

    for(int i=0; i<=8; i++)
    {
        k = rnd(0,8);
        coordinates_pazl[i].swap(coordinates_pazl[k]);  // Меняем местами элементы списка
    }

    // --------------------------------------------------------------------

    for(int i=0; i<=8; i++)
    {
        int x = coordinates_pazl.at(i).at(0);           // Расставляем пазлы
        int y = coordinates_pazl.at(i).at(1);
        pazl[i]->move(x,y);
        pazl[i]->show();
    }
}

// ------------------------- Нажимаем кнопку мышки --------------------------

void Level_05::mousePressEvent(QMouseEvent *pe)
{
    if(ACTIVE_PAZL==100)
    {
        if(QObject::sender() && pe->button() == Qt::LeftButton)
        {
            QString nameobj = QObject::sender()->objectName();   // Получаем имя объекта по которому кликнули
            ACTIVE_PAZL = nameobj.toInt();                       // Получаем номер пазла
        }
    } else return;
}

// ----------------------- Перемещаем мышку ---------------------------------

void Level_05::mouseMoveEvent(QMouseEvent *pe)
{
    if(ACTIVE_PAZL!=100)
    {
        pazl[ACTIVE_PAZL]->raise();
        pazl[ACTIVE_PAZL]->move(pe->position().x()-pazl[ACTIVE_PAZL]->width()/2,
                                pe->position().y()-pazl[ACTIVE_PAZL]->height()/2);
    } else return;
}

// ----------------------- Отпускаем кнопку мышки --------------------------

void Level_05::mouseReleaseEvent(QMouseEvent *pe)
{
    if(ACTIVE_PAZL!=100)
    {
        int x = pe->position().x()-pazl[ACTIVE_PAZL]->width()/2;
        int y = pe->position().y()-pazl[ACTIVE_PAZL]->height()/2;
        int x0 = coordinates_panel.at(ACTIVE_PAZL).at(0)-panel[ACTIVE_PAZL]->width()/2;
        int x1 = coordinates_panel.at(ACTIVE_PAZL).at(0)+panel[ACTIVE_PAZL]->width()/2;     // область куда ставим пазл
        int y0 = coordinates_panel.at(ACTIVE_PAZL).at(1)-panel[ACTIVE_PAZL]->height()/2;
        int y1 = coordinates_panel.at(ACTIVE_PAZL).at(1)+panel[ACTIVE_PAZL]->height()/2;
        int x2 = coordinates_panel.at(ACTIVE_PAZL).at(0);
        int y2 = coordinates_panel.at(ACTIVE_PAZL).at(1);

        if((x>=x0)and(x<=x1)and(y>=y0)and(y<=y1))
        {
            pazl[ACTIVE_PAZL]->move(x2, y2); qDebug() << ACTIVE_PAZL;
        } else
        {
            pazl[ACTIVE_PAZL]->move_to_xy(pazl[ACTIVE_PAZL]->x(), coordinates_pazl.at(ACTIVE_PAZL).at(0),
                                          pazl[ACTIVE_PAZL]->y(), coordinates_pazl.at(ACTIVE_PAZL).at(1), 1,10);
        }
    }

    ACTIVE_PAZL = 100;

    int check_victory = 0;  // счетчик правильно поставленных пазлов

    for(int i=0; i<=8; i++) // Проверяем все ли пазлы поставлены на место
    {
        if((pazl[i]->x()==coordinates_panel.at(i).at(0))&&
           (pazl[i]->y()==coordinates_panel.at(i).at(1))) check_victory++;
    }
    if(check_victory==9)
    {
        timer_victory = new QTimer();
        connect(timer_victory, &QTimer::timeout, this, &Level_05::victory);
        timer_victory->start(3000);
        dog_victory = new PicObject(this);
        dog_victory->load(":/resource/lev_05/dog1.gif");
        dog_victory->animation_start(WIDTH_SCREEN/8, HEIGHT_SCREEN/6);
        dog_victory->move_to_x(WIDTH_SCREEN+dog_victory->width(), 0-dog_victory->width(),
                               HEIGHT_SCREEN-dog_victory->height(), 1, 1);
        dog_victory->show();


    }
}

// ----------------------------- Победа ---------------------------------------

void Level_05::victory()
{
    static int count;
    dog_victory->move_to_x(WIDTH_SCREEN+dog_victory->width(), 0-dog_victory->width(),
                           HEIGHT_SCREEN-dog_victory->height(), 1, 1);
    count++;
    if(count>=3)
    {
        emit next_level(6);
    }
}


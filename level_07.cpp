#include "level_07.h"
#include "qmediaplayer.h"

Level_07::Level_07(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
}

Level_07::~Level_07()
{
    delete output;
    output = nullptr;
    delete sound;
    sound = nullptr;    
    delete mysl;
    mysl = nullptr;
    delete myschka;
    myschka = nullptr;
    delete mouse;
    mouse = nullptr;
    delete chees;
    chees = nullptr;
    delete mouse_victory;
    mouse_victory = nullptr;    
    delete button_back;
    button_back = nullptr;
    delete timer_animation;
    timer_animation = nullptr;
    delete background;
    background = nullptr;
    for(int i=1; i<=16; i++)
    {
        delete puzle[i];
        puzle[i] = nullptr;
    }

    WIDTH_SCREEN = 0;
    HEIGHT_SCREEN = 0;
    CLICKED_PUZLE = 100;

    for(int i=0; i<=16; i++)
    {
        position_pusle[i] = 0;
        angle_of_rotate[i] = 0;
    }
}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Level_07::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
}

// -------------------- Получаем разрешение экрана --------------------------------

void Level_07::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_07::get_height(int h)
{
    HEIGHT_SCREEN = h;
}


// ----------------------------- Инициализация -------------------------------------

void Level_07::initial()
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
    background->setStyleSheet("border-image: url(:/resource/lev_07/dvor.jpg);"); // Фон экрана
    this->setCentralWidget(background);
    background->show();

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    myschka = new PicObject(":/resource/lev_07/myshka.png", this);
    myschka->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/3);
    myschka->move(WIDTH_SCREEN-myschka->width()*2, HEIGHT_SCREEN-myschka->height());
    myschka->show();

    mouse = new PicObject(":/resource/lev_07/ura.gif", this);
    mouse->animation_start(WIDTH_SCREEN/5, HEIGHT_SCREEN/3);
    mouse->move(WIDTH_SCREEN/20, HEIGHT_SCREEN-mouse->height());
    mouse->show();

    chees = new PicObject(":/resource/lev_07/syr.png", this);
    chees->resize_object(WIDTH_SCREEN/10, HEIGHT_SCREEN/5);
    chees->move(WIDTH_SCREEN/8, HEIGHT_SCREEN/6);
    chees->show();

    mysl = new PicObject(":/resource/lev_02/mysl.png", this);
    mysl->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/3+HEIGHT_SCREEN/15);
    mysl->move(myschka->x()+myschka->width()/2, myschka->y()-myschka->height());
    mysl->show();

    create_puzle();             // Создаем набор пазлов
    rotate_puzle();             // Рандомно переворачиваем пазлы

}

// -------------------------------- Создаем набор пазлов -------------------------------------------

void Level_07::create_puzle()
{
    int k = rnd(0,3);           // Выбираем случайный набор
    static int g = 0;           // ряд

    QString puzle_name = ":/resource/lev_07/00-"+QString::number(k)+".png";
    puzle[0] = new PicObject(puzle_name, mysl);
    puzle[0]->resize_object(WIDTH_SCREEN/12, HEIGHT_SCREEN/8);
    puzle[0]->move(mysl->width()/4, mysl->height()/4);
    puzle[0]->show();

    for(int i=1; i<=16; i++)
    {
        if(i<10) puzle_name = ":/resource/lev_07/0"+QString::number(i)+"-"+QString::number(k)+".png";
        else puzle_name = ":/resource/lev_07/"+QString::number(i)+"-"+QString::number(k)+".png";
        puzle[i] = new PicObject(puzle_name, this);
        puzle[i]->setObjectName(QString::number(i));
        puzle[i]->resize_object(WIDTH_SCREEN/10, HEIGHT_SCREEN/6);
        puzle[i]->raise();
        puzle[i]->hide();
        connect(puzle[i], &PicObject::clicked, this, &Level_07::mousePressEvent);
    }
    puzle[1]->move(WIDTH_SCREEN/4, HEIGHT_SCREEN/6);
    for(int i=1; i<=4; i++)
    {
        for(int j=1; j<=4; j++)
        {
            int k=4*(i-1)+j;            // Вычисляем порядковый номер карты            
            if(k%5 == 0) g++;
            int x = puzle[1]->x()+puzle[1]->width()*(j-1);
            int y = puzle[g+1]->y()+puzle[g+1]->height()*(i-1);
            puzle[k]->move(x,y);
            puzle[k]->show();
        }
    }
    g = 0;  // Обнуляем статическую переменную
}

// -------------------------------- Рандомный поворот пазлов --------------------------------------

void Level_07::rotate_puzle()
{
    int k = 0;
    for(int i=1; i<=16; i++)
    {
        int a = rnd(0,3);
        position_pusle[i] = a;
        switch(a)
        {
        case 0: angle_of_rotate[i] = 0;     break;
        case 1: angle_of_rotate[i] = 90;    break;
        case 2: angle_of_rotate[i] = 180;   break;
        case 3: angle_of_rotate[i] = 270;   break;
        }
        puzle[i]->rotate_object(angle_of_rotate[i]);

    // проверим не находятся ли все пазлы в нулевом состоянии (исходная картинка)

        if(position_pusle[i] != 0) k++;
    }
    if(k==0) rotate_puzle();
}

// --------------------------------- Кликаем мышкой ---------------------------------------------

void Level_07::mousePressEvent(QMouseEvent *pe)
{
    if(QObject::sender() && pe->button() == Qt::LeftButton)     // вращаем по часовой стрелке
    {
        QString nameobj = QObject::sender()->objectName();   // Получаем имя объекта по которому кликнули
        CLICKED_PUZLE = nameobj.toInt();                      // Получаем номер пазла
        int angle = angle_of_rotate[CLICKED_PUZLE]+90;
        position_pusle[CLICKED_PUZLE]++;
        if(position_pusle[CLICKED_PUZLE] > 3) position_pusle[CLICKED_PUZLE] = 0;
        if(angle > 270) angle = 0;
        angle_of_rotate[CLICKED_PUZLE] = angle;
        puzle[CLICKED_PUZLE]->rotate_object(angle_of_rotate[CLICKED_PUZLE]);
        check_to_victory();
    }
    if(QObject::sender() && pe->button() == Qt::RightButton)    // вращаем против часовой стрелки
    {
        QString nameobj = QObject::sender()->objectName();   // Получаем имя объекта по которому кликнули
        CLICKED_PUZLE = nameobj.toInt();                      // Получаем номер пазла
        int angle = angle_of_rotate[CLICKED_PUZLE]-90;
        position_pusle[CLICKED_PUZLE]--;
        if(position_pusle[CLICKED_PUZLE] < 0) position_pusle[CLICKED_PUZLE] = 3;
        if(angle < 0) angle = 270;
        angle_of_rotate[CLICKED_PUZLE] = angle;
        puzle[CLICKED_PUZLE]->rotate_object(angle_of_rotate[CLICKED_PUZLE]);
        check_to_victory();
    }
}

// --------------------------------- Проверка на победу -----------------------------------------

void Level_07::check_to_victory()
{
    int k = 0;
    for(int i=1; i<=16; i++)
    {
        if(position_pusle[i]==0) k++;
    }
    if(k == 16)
    {
        delete puzle[0];
        puzle[0] = nullptr;
        timer_animation = new QTimer(this);
        connect(timer_animation, &QTimer::timeout, this, &Level_07::victory);
        timer_animation->start(3000);
        victory();
    } else return;
}

// ------------------------------- Победа ------------------------------------------------

void Level_07::victory()
{
    button_back->hide();
    mysl->hide();
    static int k = 0;
    if(k == 0)
    {
        delete mysl;
        mysl = nullptr;
        delete myschka;
        myschka = nullptr;
        delete button_back;
        button_back = nullptr;
        mouse_victory = new PicObject(":/resource/lev_07/ura1.gif", this);
        mouse_victory->animation_start(WIDTH_SCREEN/4, HEIGHT_SCREEN/2);
        mouse_victory->move(WIDTH_SCREEN-mouse_victory->width(), HEIGHT_SCREEN-mouse_victory->height());
        mouse_victory->show();
    }
    k++;
    if(k==4)
    {
        k = 0;
        emit next_level(8);
    }
}






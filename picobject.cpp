#include "picobject.h"

PicObject::PicObject(QWidget *parent):QLabel(parent)
{
    width_frame = width();
    height_frame = height();
    setScaledContents(true); //--------------------------------------------
    setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored ); //--------------------------------
}

PicObject::PicObject(QString path, QWidget *parent):QLabel(parent)
{
    width_frame = width()-height();
    height_frame = height();
    path_to_image = path;
    pixmap.load(path_to_image);
    setScaledContents(true); //--------------------------------------------
    setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored ); //--------------------------------
    //setFrameStyle(2);
}

PicObject::PicObject(QString path, int width, int height, QWidget *parent):QLabel(parent)
{
    resize(width, height);
    width_frame = width;
    height_frame = height;
    path_to_image = path;
    pixmap.load(path_to_image);
    pixmap1 = pixmap;
    pixmap1 = pixmap.scaled( width, height, Qt::KeepAspectRatio);
    setPixmap(pixmap1);
    setScaledContents(true); //------------------------------------------------------
    setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored ); //----------------------------------------
}

PicObject::~PicObject()
{
    if (movie == (void*)0)
    {
        delete movie;
        movie = nullptr;
    }
}

// Загрузка изображения

void PicObject::load(QString path)
{
    path_to_image = path;
    pixmap.load(path_to_image);
    pixmap1 = pixmap;
    pixmap1 = pixmap.scaled( width(), height(), Qt::KeepAspectRatio);
    setPixmap(pixmap1);
    setScaledContents(true); //------------------------------------------------------
    setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored ); //----------------------------------------
}

// Изменение размера объекта

void PicObject::resize_object(int w, int h)
{
    resize(w,h);
    pixmap1 = pixmap.scaled(w, h, Qt::KeepAspectRatio);
    setPixmap(pixmap1);
    setScaledContents(true); //------------------------------------------------------
    setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored ); //----------------------------------------
}

// Анимация объектов (gif) - старт

void PicObject::animation_start(int w, int h)
{
    QString a = path_to_image.right(3);
    if (a=="gif")
    {
        movie = new QMovie(path_to_image);
        setMovie(movie);
        movie->start();
        resize(w,h);
        movie->setScaledSize(QSize(w, h));
    }
}

// Анимация объектов (gif) - стоп

void PicObject::animation_stop()
{
    if (movie != (void*)0) movie->stop();
}

// Вращение объекта

void PicObject::rotate_object(int angle)
{
    pixmap1 = pixmap;
    QTransform trans;
    trans.rotate(angle);
    pixmap1 = pixmap1.transformed(trans);
    pixmap1 = pixmap1.scaled(width(), height(), Qt::KeepAspectRatio);
    setPixmap(pixmap1);
    setScaledContents(true); //------------------------------------------------------
    setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored ); //----------------------------------------
    emit changig_angle();
}

// Перемещение объекта по оси х со скоростью speed

void PicObject::move_to_x(int x, int x1, int y, int speed)
{
    timer_move = new QTimer();
    timer_move->start(speed);
    TEMP_X = x;
    TEMP_X1 = x1;
    TEMP_Y = y;
    TEMP_P = 10;
    connect(timer_move, &QTimer::timeout, this, &PicObject::move_to_x_temp);
}

// Перемещение объекта по оси х со скоростью speed на p пикселей за шаг

void PicObject::move_to_x(int x, int x1, int y, int speed, int p)
{
    timer_move = new QTimer();
    timer_move->start(speed);
    TEMP_X = x;
    TEMP_X1 = x1;
    TEMP_Y = y;
    TEMP_P = p;
    connect(timer_move, &QTimer::timeout, this, &PicObject::move_to_x_temp);
}

void PicObject::move_to_x_temp()
{
    if(TEMP_X<TEMP_X1)
    {
        TEMP_X=TEMP_X+TEMP_P;
        move(TEMP_X, TEMP_Y);
        if(TEMP_X<TEMP_X1) return;
    } else
    {
        TEMP_X=TEMP_X-TEMP_P;
        move(TEMP_X, TEMP_Y);
        emit changing_xy();
        if(TEMP_X>TEMP_X1) return;
    }
    emit move_end();
    timer_move->stop();
    disconnect(timer_move, &QTimer::timeout, this, &PicObject::move_to_x_temp);
    delete timer_move;
    timer_move = nullptr;
    TEMP_X=0;
    TEMP_Y=0;
    TEMP_X1=0;
    TEMP_Y1=0;
    TEMP_P=0;
}

// Перемещение объекта по оси y со скоростью speed

void PicObject::move_to_y(int x, int y, int y1, int speed)
{
    timer_move = new QTimer();
    timer_move->start(speed);
    TEMP_X = x;
    TEMP_Y = y;
    TEMP_Y1 = y1;
    TEMP_P = 10;
    connect(timer_move, &QTimer::timeout, this, &PicObject::move_to_y_temp);
}

// Перемещение объекта по оси х со скоростью speed на p пикселей за шаг

void PicObject::move_to_y(int x, int y, int y1, int speed, int p)
{
    timer_move = new QTimer();
    timer_move->start(speed);
    TEMP_X = x;
    TEMP_Y = y;
    TEMP_Y1 = y1;
    TEMP_P = p;
    connect(timer_move, &QTimer::timeout, this, &PicObject::move_to_y_temp);
}

void PicObject::move_to_y_temp()
{
    if(TEMP_Y<TEMP_Y1)
    {        
        TEMP_Y=TEMP_Y+TEMP_P;
        move(TEMP_X, TEMP_Y);
        emit changing_xy();
        if(TEMP_Y<TEMP_Y1) return;
    } else
    {
        TEMP_Y=TEMP_Y-TEMP_P;
        move(TEMP_X, TEMP_Y);
        emit changing_xy();
        if(TEMP_Y>TEMP_Y1) return;
    }
    emit move_end();
    timer_move->stop();
    disconnect(timer_move, &QTimer::timeout, this, &PicObject::move_to_y_temp);
    delete timer_move;
    timer_move = nullptr;
    TEMP_X=0;
    TEMP_Y=0;
    TEMP_X1=0;
    TEMP_Y1=0;
    TEMP_P=0;
}

// Перемещение по диагонали от x,y до x1,y1 со скоростью speed в милисекундах

void PicObject::move_to_xy(int x, int x1, int y, int y1, int speed)
{
    move(x,y);
    timer_move = new QTimer();
    timer_move->start(speed);
    if(x<x1)
    {
        TEMP_P = 1;
    } else
    {
        TEMP_P = -1;
    }
        TEMP_X = x;
        TEMP_X1 = x1;
        TEMP_Y = y;
        TEMP_Y1 = y1;
        TEMP_K = (float(y)-y1)/(x-x1);
        TEMP_B = y1-(((float(y)-y1)/(x-x1))*x1);
    connect(timer_move, &QTimer::timeout, this, &PicObject::move_to_xy_temp);
}

// Перемещение по диагонали от x,y до x1,y1 со скоростью speed в милисекундах, р - смещение в пикселях

void PicObject::move_to_xy(int x, int x1, int y, int y1, int speed, int p)
{
    move(x,y);
    timer_move = new QTimer();
    timer_move->start(speed);
    if(x<x1)
    {
        TEMP_P = p;
    } else
    {
        TEMP_P = -p;
    }
    TEMP_X = x;
    TEMP_X1 = x1;
    TEMP_Y = y;
    TEMP_Y1 = y1;
    TEMP_K = (float(y)-y1)/(x-x1);
    TEMP_B = y1-(((float(y)-y1)/(x-x1))*x1);
    connect(timer_move, &QTimer::timeout, this, &PicObject::move_to_xy_temp);
}

void PicObject::move_to_xy_temp()
{
    TEMP_Y = TEMP_K*TEMP_X+TEMP_B;
    if(TEMP_X < TEMP_X1)
    {
        move(TEMP_X, TEMP_Y);
        TEMP_X=TEMP_X+TEMP_P;
        emit changing_xy();
        if(TEMP_X>=TEMP_X1)
        {
            emit move_end();
            disconnect(timer_move, &QTimer::timeout, this, &PicObject::move_to_xy_temp);
            delete timer_move;
            timer_move = nullptr;
        }
        return;
    }
    if(TEMP_X > TEMP_X1)
    {
        move(TEMP_X, TEMP_Y);
        TEMP_X=TEMP_X+TEMP_P;
        emit changing_xy();
        if(TEMP_X<=TEMP_X1)
        {
            emit move_end();
            disconnect(timer_move, &QTimer::timeout, this, &PicObject::move_to_xy_temp);
            delete timer_move;
            timer_move = nullptr;
        }
        return;
    }
}

void PicObject::opacity(int opacity)
{
    emit changing_opacity_signal();
    if(opacity<0) opacity = 0;
    if(opacity>255) opacity = 255;
    QImage image(path_to_image);
    QPainter p;
    p.begin(&image);
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.fillRect(image.rect(), QColor(0, 0, 0, opacity));
    p.end();
    pixmap1 = pixmap1.fromImage(image);
    pixmap1 = pixmap1.scaled( width(), height(), Qt::KeepAspectRatio);
    setPixmap(pixmap1);
    pixmap = pixmap1;
    setScaledContents(true); //------------------------------------------------------
    setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored ); //----------------------------------------
}

void PicObject::mousePressEvent(QMouseEvent *event)
{
    emit clicked(event);
}

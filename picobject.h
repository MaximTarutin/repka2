/****************************************************************************************
 *                          Библиотека работы с изображениями на QLabel                 *
 *======================================================================================*
 *                                      Конструкторы                                    *
 *======================================================================================*
 *   PicObject(QWidget *parent = nullptr);                                              *
 *   - задатся родительский объект                                                      *
 * -------------------------------------------------------------------------------------*
 *   PicObject(QString path, QWidget *parent = nullptr);                                *
 *   - задается путь к файлу изображения и указывается родительский объект              *
 *--------------------------------------------------------------------------------------*
 *   PicObject(QString path, int width, int height, QWidget *parent = nullptr);         *
 *   - задается путь к файлу изображений, ширина и высота объекта в пикселях и          *
 *     родительский объект                                                              *
 *======================================================================================*
 *                                          Методы                                      *
 *======================================================================================*
 *   void load(QString path);                                                           *
 *   - загружает изображение по пути path                                               *
 * -------------------------------------------------------------------------------------*
 *   void resize_object(int w, int h);                                                  *
 *   - устанавливает размер объекта w - ширина, h - высота в пикселях                   *
 * -------------------------------------------------------------------------------------*
 *   void animation_start(int w, int h);                                                *
 *   - запускает анимацию объекта (при условии, что это gif)                            *
 *   - w - ширина объекта, h - высота объекта                                           *
 *--------------------------------------------------------------------------------------*
 *   void animation_stop();                                                             *
 *   - останавливает анимацию объекта (при условии, что это gif)                        *
 *--------------------------------------------------------------------------------------*
 *   void rotate_object(int angle);                                                     *
 *   - поворачивает объект на угол angle                                                *
 *--------------------------------------------------------------------------------------*
 *   void move_to_x(int x, int x1, int y, int speed);                                   *
 *   - перемещение объекта по оси х, где х и х1 - координаты х, у - координата у,       *
 *     speed - время в мс через которое объект сместится на 10 пикселов                 *
 *--------------------------------------------------------------------------------------*
 *   void move_to_x(int x, int x1, int y, int speed, int p);                            *
 *  - перемещение объекта по оси х со смещением на p пикселей за время speed милисекунд *
 *--------------------------------------------------------------------------------------*
 *   void move_to_y(int x, int y, int y1, int speed);                                   *
 *   - перемещение объекта по оси у, где х - координата х, у и у1 - координаты у        *
 *     speed - время в мс через которое объект сместится на 10 пикселов                 *
 *--------------------------------------------------------------------------------------*
 *   void move_to_y(int x, int y, int y1, int speed, int p);                            *
 *  - перемещение объекта по оси у со смещением на p пикселей за время speed милисекунд *
 *--------------------------------------------------------------------------------------*
 *   void move_to_xy(int x, int x1, int y, int y1, int speed);                          *
 *   - перемещение по диагонали, где х и х1 - координаты х, у и у1 - координаты у,      *
 *   speed - время в мс через которое объект сместится на 1 пиксель                     *
 *--------------------------------------------------------------------------------------*
 *   void move_to_xy(int x, int x1, int y, int y1, int speed, int p);                   *
 *   - перемещение по диагонали, где х и х1 - координаты х, у и у1 - координаты у,      *
 *   speed время в милмисекундах, через которое объект сместится на p пикселей          *
 *--------------------------------------------------------------------------------------*
 *   void opacity(int opacity);                                                         *
 *  - устанавливаем прозрачность объека в пределах 0 - 255, где 0 - полная прозрачность *
 *======================================================================================*
 *                                      Сигналы                                         *
 *======================================================================================*
 *   void move_end();                                                                   *
 *   - Сигнал окончания движения в методах move_to_..                                   *
 *--------------------------------------------------------------------------------------*
 *   void changing_xy();                                                                *
 *   - Сигнал при изменении координат в методах move_to_...                             *
 *--------------------------------------------------------------------------------------*
 *   void changing_opacity_signal();                                                    *
 *   - Сигнал при изменении прозрачности                                                *
 *--------------------------------------------------------------------------------------*
 *   void changig_angle();                                                              *
 *   - Сигнал изменения угла поворота объекта                                           *
 ****************************************************************************************/


#ifndef PICOBJECT_H
#define PICOBJECT_H

#include <QLabel>
#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QMovie>
#include <QPainter>
#include <QSize>
#include <QTransform>
#include <QEvent>
#include <QPaintEvent>
#include <QImage>

class PicObject : public QLabel
{
    Q_OBJECT
public:
    PicObject(QWidget *parent = nullptr);
    PicObject(QString path, QWidget *parent = nullptr);
    PicObject(QString path, int width, int height, QWidget *parent = nullptr);
    ~PicObject();

    QPixmap     pixmap;
    QPixmap     pixmap1;                                                // Временный pixmap
    QTimer      *timer_move = nullptr;                                  // Таймер движения объекта
    QMovie      *movie = nullptr;                                       // Анимация
    QPainter    *painter = nullptr;
    int width_frame;
    int height_frame;

    void load(QString path);                                        // Загружает картинку из заданного пути
    void resize_object(int w, int h);                               // Изменяет размеры объекта w - ширина, h - высота
    void animation_start(int w, int h);                             // Cтарт анимации gif - w - ширина, h - высота
    void animation_stop();                                          // Остановка анимации
    void rotate_object(int angle);                                  // Поворот объекта на угол  angle
    void move_to_x(int x, int x1, int y, int speed);                // перемещение по оси x (x, x1 - начальная и конечная координата x,
                                                                    // y - координата y, speed - скорость перемещения
    void move_to_x(int x, int x1, int y, int speed, int p);         // перемещение по оси x (x, x1 - начальная и конечная координата x,
                                                                    // y1 - координата y1, speed - скорость перемещения, p - смещение в
                                                                    // пикселях
    void move_to_y(int x, int y, int y1, int speed);                // перемещение по оси x (y, y1 - начальная и конечная координата y,
                                                                    // x - координата x, speed - скорость перемещения
    void move_to_y(int x, int y, int y1, int speed, int p);         // перемещение по оси x (y, y1 - начальная и конечная координата y,
                                                                    // x - координата x, speed - скорость перемещения, p - смещение в
                                                                    // пикселях
    void move_to_xy(int x, int x1, int y, int y1, int speed);       // перемещение по диагонали
    void move_to_xy(int x, int x1, int y, int y1, int speed, int p);// перемещение по диагонали, p - смещение в пикселях

    void opacity(int opacity);                                      // устанавливаем прозрачность объека в пределах 0 - 255, где
                                                                    // 0 - полная прозрачность
    void change_opacity(int opacity, int opacity1, int step);       // изменение прозрачности от opacity до opacity1 с шагом step

signals:
    void move_end();                                        // Сигнал окончания движения в методах move_to_...
    void changing_xy();                                     // Сигнал при изменении координат в методах move_to_...
    void changing_opacity_signal();                         // Сигнал при изменении прозрачности
    void changig_angle();                                   // Сигнал изменения угла поворота объектаСигнал окончания перемещения


private:
    QString path_to_image;                                  // Путь к изображению
    int TEMP_X, TEMP_X1;                                    // Временные координаты для вычислений перемещения объекта
    int TEMP_Y, TEMP_Y1;
    int TEMP_P;                                             // Временная переменная смещения в пикселях
    float TEMP_K;                                           // Коэффициенты смещения объекта (y=kx+b)
    float TEMP_B;
    void move_to_x_temp();                                  // Временная функция перемещения по x
    void move_to_y_temp();                                  // Временная функция перемещения по y
    void move_to_xy_temp();                                 // Временная функция перемещения по xy
};

#endif // PICOBJECT_H

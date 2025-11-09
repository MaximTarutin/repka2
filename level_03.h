#ifndef LEVEL__3_H
#define LEVEL__3_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include "picobject.h"

class Level_03 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_03(QWidget *parent = nullptr);
    ~Level_03();

public slots:
    void initial();                             // Инициализация уровня
    void get_width(int w);                      // Получаем WIDTH_SCREEN
    void get_height(int h);                     // Получаем HEIGHT_SCREEN

private:
    int WIDTH_SCREEN = 0;                       // Ширина экрана
    int HEIGHT_SCREEN = 0;                      // Высота экрана
    int NUMBER = 0;                             // Номер ингридиента в мыслях бабки
    int CURRENT_PRODUKT = 100;                  // Номер выбранного продукта (100 - продукт не выбран)
    int x[8] = {};                              // Координаты продуктов
    int y[8] = {};
    int old_x = 0;                              // координаты объекта до перемещения
    int old_y = 0;

    int  rnd(int a, int b);                     // Случайные числа в диапазоне от a до b
    void mix_ingridients();                     // перемешиваем список ингридиентов
    void set_mysl();                            // показываем о чем думает бабка

    QLabel          *background = nullptr;      // Фон уровня
    QMediaPlayer    *sound = nullptr;           // Проигрыватель
    QAudioOutput    *output = nullptr;          // Аудиовыход
    QPushButton     *button_back = nullptr;     // Кнопка назад
    QTimer          *timer_show_kolobok;        // Таймер появления колобка
    QTimer          *timer_victory;             // Таймер анимации при победе
    PicObject       *table = nullptr;           // Стол
    PicObject       *babka = nullptr;           // Бабка
    PicObject       *mysl = nullptr;            // Мысль бабки
    PicObject       *tazik[8] = {};             // Состояния тазика по мере наполняемости продуктами
    PicObject       *kolobok = nullptr;         // Колобок
    PicObject       *produkt[8] = {};           // Продукты
    PicObject       *produkt_mysl[8] = {};      // Продукты в мысли:
                                                // 0 - тазик
                                                // 1 - молоко
                                                // 2 - масло
                                                // 3 - яйца
                                                // 4 - мука
                                                // 5 - соль
                                                // 6 - венчик
                                                // 7 - колобок

    QString         name_active_object;         // имя объекта по которому кликнули мышкой
    QList<QList<int>>  coordinates = {};        // Список координаты продуктов (список в списке - [[a,b],[a,b],...,[a,b]])
    QList<int>  produkt_value = {};             // Список нумерации продукты
    QList<int>  produkt_mysl_value = {};        // Список нумерации продукты в мысли

protected:
    virtual void mousePressEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);
    virtual void mouseReleaseEvent(QMouseEvent *pe);

private slots:
    void show_kolobok();                        // Колобок появляется на столе
    void victory();                             // Победа

signals:
};

#endif // LEVEL__3_H

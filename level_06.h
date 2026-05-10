#ifndef LEVEL__6_H
#define LEVEL__6_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>

class Level_06 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_06(QWidget *parent = nullptr);
    ~Level_06();

    void initial();                                 // Инициализация
    QPushButton *button_back = nullptr;             // Кнопка назад

public slots:
    void get_width(int w);                          // Получаем ширину экрана
    void get_height(int h);                         // Получаем высоту экрана

private:
    int WIDTH_SCREEN = 0;                           // Ширина экрана
    int HEIGHT_SCREEN = 0;                          // Высота экрана

    QLabel          *background = nullptr;          // Фон
    QMediaPlayer    *sound = nullptr;               // Звуки
    QAudioOutput    *output = nullptr;              // Аудтовыход

    int rnd(int a, int b);                          // Случайные числа в диапазоне от a до b

signals:
    void next_level(int lev);                       // Сигнал переход на следующий уровень
};

#endif // LEVEL__6_H

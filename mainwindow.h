#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGuiApplication>
#include <QScreen>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLabel              *background_logo = nullptr;                     // Фон
    QPushButton         *button_start = nullptr;                        // Кнопка старт
    QPushButton         *button_exit = nullptr;                         // Кнопка выход

    int WIDTH_SCREEN;                                               // Ширина экрана
    int HEIGHT_SCREEN;                                              // Высота экрана

    void screen_size();                                             // Получаем разрешение экрана и
                                                                    // определяем результаты в переменные
                                                                    // WIDTH_SCREEN и SCREEN_HEIGHT

private slots:
    void exit_of_game();                                            // Выход из игры

};
#endif // MAINWINDOW_H

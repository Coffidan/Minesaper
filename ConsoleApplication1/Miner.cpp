#include <iostream>
#include <SFML/Graphics.hpp>//подключаем библиотеку графикс
#include <time.h>// подключение библиотке рандом 
using namespace sf;

int main()
{
    srand(time(NULL));// для рандома 

    RenderWindow window(VideoMode(400, 400), "Dota 3 Beta test");//создаем окно 400 на 400

    int sd = 32;//размер плитки
    int array[12][12];// массив сетка 
    int arr[12][12];// массив сетки

    Texture t;
    t.loadFromFile("C:\\Users\\Взрослая академия\\Documents\\ConsoleApplication2\\Texture\\tiles.png");//ставим картинку
    Sprite tiles(t);

    for (int i = 1; i <= 10; i++)//рандомная позиция бомб
        for (int j = 1; j <= 10; j++)
        {
            arr[i][j] = 10;// придаем масиву значение плитки
            if (rand() % 5 == 0)   array[i][j] = 9;//придаем масиву значение бомбы
            else array[i][j] = 0;//иначе он равен 0
        }

    for (int i = 1; i <= 10; i++)//рандомная позиция цифр
        for (int j = 1; j <= 10; j++)
        {
            int b = 0;// новый коэфицинет
            if (array[i][j] == 9) continue;// переход к следующему действию, смотрим гед стоят бомбы и ставим цыфры в зависимости бомб
            if (array[i + 1][j] == 9) b++;
            if (array[i][j + 1] == 9) b++;
            if (array[i - 1][j] == 9) b++;
            if (array[i][j - 1] == 9) b++;
            if (array[i + 1][j + 1] == 9) b++;
            if (array[i - 1][j - 1] == 9) b++;
            if (array[i - 1][j + 1] == 9) b++;
            if (array[i + 1][j - 1] == 9) b++;
            array[i][j] = b;// при равниваем полученую цифру
        }

    while (window.isOpen())// открываем окно
    {
        Vector2i pos = Mouse::getPosition(window);// подключаем мышь
        int x = pos.x / sd; // по оси x
        int y = pos.y / sd;// по оси y

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)//условие закрытие окна
                window.close();// окно закрыто

            if (e.type == Event::MouseButtonPressed)// условие нажатия мышки
                if (e.key.code == Mouse::Left) arr[x][y] = array[x][y];//расскрытие ячейки
                else if (e.key.code == Mouse::Right) arr[x][y] = 11; // флажок
        }

        window.clear(Color::Red);//  красим в красный

        for (int i = 1; i <= 10; i++)// создаем двухмерный массив
            for (int j = 1; j <= 10; j++)
            {
                if (arr[x][y] == 9) arr[i][j] = array[i][j];// попадения на бомбу игра заканчивается и расскрываются плитки
                tiles.setTextureRect(IntRect(arr[i][j] * sd, 0, sd, sd));// расположение плиток
                tiles.setPosition(i * sd, j * sd);// расположение игрового поля 10 на 10
                window.draw(tiles);// выводим поле на окно
            }

        window.display();//вывод картники
    }

    return 0;
}

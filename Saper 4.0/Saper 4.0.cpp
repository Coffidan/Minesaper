#include <SFML/Graphics.hpp>
#include <time.h>// подключение библиотке рандом 
using namespace sf;

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(400, 400), "Minesweeper!");//создаем окно 400 на 400

    int sd = 32;//размер плитки
    int array[12][12];// массив сетка
    int arr[12][12]; 

    Texture t;
    t.loadFromFile("C:\\Save\\Saper 4.0\\Texture\\tiles.jpg");//ставим картинку
    Sprite tiles(t);

    for (int i = 1;i <= 10;i++)//позиция бомб
        for (int j = 1;j <= 10;j++)
        {
            arr[i][j] = 10;
            if (rand() % 5 == 0)   array[i][j] = 9;
            else array[i][j] = 0;
        }

    for (int i = 1;i <= 10;i++)//позиция цифр
        for (int j = 1;j <= 10;j++)
        {
            int b = 0;
            if (array[i][j] == 9) continue;
            if (array[i + 1][j] == 9) b++;
            if (array[i][j + 1] == 9) b++;
            if (array[i - 1][j] == 9) b++;
            if (array[i][j - 1] == 9) b++;
            if (array[i + 1][j + 1] == 9) b++;
            if (array[i - 1][j - 1] == 9) b++;
            if (array[i - 1][j + 1] == 9) b++;
            if (array[i + 1][j - 1] == 9) b++;
            array[i][j] = b;
        }

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / sd;
        int y = pos.y /sd;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();//закрытие окна

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left) arr[x][y] = array[x][y];//расскрытие ячейки
                else if (e.key.code == Mouse::Right) arr[x][y] = 11; // флажок
        }

        window.clear(Color::White);

        for (int i = 1;i <= 10;i++)
            for (int j = 1;j <= 10;j++)//прекращения игры
            {
                if (arr[x][y] == 9) arr[i][j] = array[i][j];
                tiles.setTextureRect(IntRect(arr[i][j] * sd, 0, sd, sd));// расположение плиток
               tiles.setPosition(i * sd, j * sd);
                window.draw(tiles);
            }

        window.display();//вывод картники
    }

    return 0;
}

// Homework14.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include "Timer.h"

//using namespace std;

std::mutex m;

int getXcoord()
{
    CONSOLE_SCREEN_BUFFER_INFO info_x;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_x);
    return info_x.dwCursorPosition.X;
}

int getYcoord()
{
    CONSOLE_SCREEN_BUFFER_INFO info_y;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
    return info_y.dwCursorPosition.Y;
}


void drawProgressBar(size_t i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(i * 100));
    m.lock();
    std::cout << "\n" << i;
    std::thread::id idd = std::this_thread::get_id();
    std::cout << "\t" << idd << "\t";
    m.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 15; j < 48; j++) {
        srand((unsigned)time(NULL));
        int random = (rand() % 10);
        std::this_thread::sleep_for(std::chrono::milliseconds(random * 10 * (i + 1)));
        m.lock();
        consol_parameter::SetPosition(j, (i + 2));
        std::cout << (char)254u;
        m.unlock();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    m.lock();
    consol_parameter::SetPosition(49, (i + 2));
    std::cout << "\t" << (time.count() / 1000) << " s";
    m.unlock();
}

void func() {
    std::cout << "#\tid ";
    /*std::cout << getXcoord() << ";" << getYcoord();*/
    std::cout << "\t\tProgress Bar\t\t\t";
    /*std::cout << getXcoord() << ";" << getYcoord();*/
    std::cout << " Time\n";
    int n = 5;
    std::thread* t = new std::thread[n];
    for (size_t i = 0; i < n; i++) {
        t[i] = std::thread(drawProgressBar, i);
    }
    for (size_t i = 0; i < n; i++) {
        t[i].join();
    }
    consol_parameter::SetPosition(0, 7);
}

int main()
{
    func();

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

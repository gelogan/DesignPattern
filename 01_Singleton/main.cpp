#include <iostream>
#include "Singleton.h"

int main(int argc, char const *argv[])
{
    std::cout << "Hello, from 01_Singleton";
    std::cout << "--- [1] Singleton1 ---" << std::endl;
    Singleton1::test();

    std::cout << "\n--- [2] SingletonStatic ---" << std::endl;
    SingletonStatic::test();

    std::cout << "\n--- [3] Singleton2 ---" << std::endl;
    Singleton2::PS3FileSystem ps3FS;
    ps3FS.writeFile((char*)"/sys/test.txt", (char*)"Hello PS3");

    std::cout << "\n--- [4] Singleton3 ---" << std::endl;
    Singleton3::FileSystem::instance().readFile((char*)"/sys/test.bin");

    std::cout << "\n--- [5] Singleton4 ---" << std::endl;
    std::cout << "Singleton4 is initialized at: " << &Singleton4::FileSystem::instance() << std::endl;

    std::cout << "\n--- [6] Singleton5 ---" << std::endl;
    {
    Singleton5::FileSystem fs1;
    std::cout << "FileSystem instantiated safely." << std::endl;
    // Singleton5::FileSystem fs2; // 取消注释此行将触发 assert 报错
    }

    std::cout << "\n--- [7] Singleton7 ---" << std::endl;
    Singleton7::BulletManager bm;
    Singleton7::Bullet* bullet1 = bm.create(98, 10);
    bm.move(*bullet1);
    std::cout << "Bullet is on screen: " << (bm.isOnScreen(*bullet1) ? "True" : "False") << std::endl;
    delete bullet1;

    std::cout << "\n--- [8] Singleton8 ---" << std::endl;
    Singleton8::Bullet bullet2(98, 10);
    bullet2.move();
    std::cout << "Bullet is on screen: " << (bullet2.isOnScreen() ? "True" : "False") << std::endl;

    std::cout << "\n--- [9] Singleton9 ---" << std::endl;
    Singleton9::Enemy enemy;
    enemy.doSomething();

    std::cout << "\n--- [10] Singleton10 ---" << std::endl;
    Singleton10::Log logProvider;
    Singleton10::FileSystem fsProvider;
    Singleton10::ConcreteAudioPlayer audioProvider;

    // 服务定位器 (Service Locator) 注入依赖
    Singleton10::Game::instance().provide(&logProvider);
    Singleton10::Game::instance().provide(&fsProvider);
    Singleton10::Game::instance().provide(&audioProvider);

    // 触发播放逻辑
    Singleton10::foo();
    return 0;
}

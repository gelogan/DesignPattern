#include "flyweight.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;
using namespace Flyweight::TerrainClass;

int main() {
    // 初始化随机数种子
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    cout << "=== Flyweight Pattern Demonstration ===\n\n";

    // 实例化世界，内部构造函数会调用 generateTerrain()
    World world;

    cout << "Terrain Map (10x10 Grid):\n";
    cout << "--------------------------------------------------\n";
    
    // 遍历地图，打印视觉表示
    for (int y = 0; y < Flyweight::HEIGHT; y++) {
        for (int x = 0; x < Flyweight::WIDTH; x++) {
            const Terrain& tile = world.getTile(x, y);
            
            // 根据移动消耗或水域属性打印不同字符
            if (tile.isWater()) {
                cout << "[ ~~ ] "; // 河流
            } else if (tile.getMovementCost() == 3) {
                cout << "[ ^^ ] "; // 丘陵
            } else {
                cout << "[ .. ] "; // 草地
            }
        }
        cout << "\n";
    }
    cout << "--------------------------------------------------\n\n";

    cout << "Memory Address Verification (The core of Flyweight):\n";
    
    // 提取几个特定坐标的地形地址进行对比
    const Terrain* t1 = &world.getTile(0, 0);
    const Terrain* t2 = &world.getTile(1, 0);
    const Terrain* t3 = &world.getTile(2, 0);
    
    cout << "Tile (0,0) Texture: " << setw(6) << t1->getTexture().name 
         << " | Memory Address: " << t1 << "\n";
    cout << "Tile (1,0) Texture: " << setw(6) << t2->getTexture().name 
         << " | Memory Address: " << t2 << "\n";
    cout << "Tile (2,0) Texture: " << setw(6) << t3->getTexture().name 
         << " | Memory Address: " << t3 << "\n\n";
         
    cout << "Conclusion: Even with 100 tiles, there are only 3 distinct memory addresses allocated for Terrain objects.\n";

    return 0;
}
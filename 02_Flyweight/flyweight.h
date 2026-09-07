#ifndef cpp_flyweight_h
#define cpp_flyweight_h

#include <iostream>
#include <string>
#include <cstdlib>

namespace Flyweight
{
  class Mesh {};
  class Skeleton {};
  class Pose {};
  class Vector {};
  class Color {};
  
  // 赋予 Texture 实际的属性，以便在终端中打印验证
  class Texture {
  public:
      std::string name;
      Texture(std::string n = "default") : name(n) {}
  };

  // 缩小尺寸，方便在控制台输出完整的矩阵
  static const int WIDTH = 10;
  static const int HEIGHT = 10;

  static Texture GRASS_TEXTURE("Grass");
  static Texture HILL_TEXTURE("Hill");
  static Texture RIVER_TEXTURE("River");

  // 实现简单的随机数生成
  inline int random(int max) { 
      if (max <= 0) return 0;
      return std::rand() % max; 
  }

  // 补全 foo() 中使用的占位函数
  inline void use(int cost) { 
      // 仅作占位，避免未使用变量警告
      (void)cost; 
  }

  namespace HeavyTree
  {
    class Tree
    {
    private:
      Mesh mesh_;
      Texture bark_;
      Texture leaves_;
      Vector position_;
      double height_ = 0;
      double thickness_ = 0;
      Color barkTint_;
      Color leafTint_;
    };
  }

  namespace SplitTree
  {
    class TreeModel
    {
    private:
      Mesh mesh_;
      Texture bark_;
      Texture leaves_;
    };

    class Tree
    {
    private:
      TreeModel* model_ = nullptr;
      Vector position_;
      double height_ = 0;
      double thickness_ = 0;
      Color barkTint_;
      Color leafTint_;
    };
  }

  namespace TerrainEnum
  {
    enum Terrain
    {
      TERRAIN_GRASS,
      TERRAIN_HILL,
      TERRAIN_RIVER
    };

    class World
    {
    private:
      Terrain tiles_[WIDTH][HEIGHT];
    public:
      int getMovementCost(int x, int y);
      bool isWater(int x, int y);
    };

    inline int World::getMovementCost(int x, int y)
    {
      switch (tiles_[x][y])
      {
        case TERRAIN_GRASS: return 1;
        case TERRAIN_HILL:  return 3;
        case TERRAIN_RIVER: return 2;
        default: return 0; // 补充默认返回，防止编译警告
      }
    }

    inline bool World::isWater(int x, int y)
    {
      switch (tiles_[x][y])
      {
        case TERRAIN_GRASS: return false;
        case TERRAIN_HILL:  return false;
        case TERRAIN_RIVER: return true;
        default: return false;
      }
    }
  }

  namespace TerrainClass
  {
    class Terrain
    {
    public:
      Terrain(int movementCost,
              bool isWater,
              Texture texture)
      : movementCost_(movementCost),
        isWater_(isWater),
        texture_(texture)
      {}

      int getMovementCost() const { return movementCost_; }
      bool isWater() const { return isWater_; }
      const Texture& getTexture() const { return texture_; }

    private:
      int movementCost_;
      bool isWater_;
      Texture texture_;
    };

    class World
    {
    public:
      World()
      : grassTerrain_(1, false, GRASS_TEXTURE),
        hillTerrain_(3, false, HILL_TEXTURE),
        riverTerrain_(2, true, RIVER_TEXTURE)
      {
          // 在构造时直接生成地形
          generateTerrain();
      }
      const Terrain& getTile(int x, int y) const;
      
    private:
      Terrain* tiles_[WIDTH][HEIGHT];

      Terrain grassTerrain_;
      Terrain hillTerrain_;
      Terrain riverTerrain_;
      
      void generateTerrain();
    };

    inline void World::generateTerrain()
    {
      for (int x = 0; x < WIDTH; x++)
      {
        for (int y = 0; y < HEIGHT; y++)
        {
          if (random(10) == 0)
          {
            tiles_[x][y] = &hillTerrain_;
          }
          else
          {
            tiles_[x][y] = &grassTerrain_;
          }
        }
      }

      int x = random(WIDTH);
      for (int y = 0; y < HEIGHT; y++) {
        tiles_[x][y] = &riverTerrain_;
      }
    }

    inline const Terrain& World::getTile(int x, int y) const
    {
      return *tiles_[x][y];
    }

    inline void foo()
    {
      World world;
      int cost = world.getTile(2, 3).getMovementCost();
      use(cost);
    }
  }
}
#endif
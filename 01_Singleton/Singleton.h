#include <iostream>
#include <cassert>

namespace Singleton1
{
  class FileSystem
  {
  public:
    static FileSystem& instance()
    {
      // 惰性初始化
      if (instance_ == NULL) instance_ = new FileSystem();
      return *instance_;
    }
  private:
    FileSystem() {}
    static FileSystem* instance_;
  };

  FileSystem* FileSystem::instance_ = NULL; // 补全静态变量初始化

  void test()
  {
    if (&FileSystem::instance() == NULL)
    {
      std::cout << "singleton is null!" << std::endl;
    }
    else
    {
      std::cout << "singleton is ok" << std::endl;
    }
  }
}

namespace SingletonStatic
{
  class FileSystem
  {
  public:
    static FileSystem& instance()
    {
      static FileSystem *instance = new FileSystem();
      return *instance;
    }
  private:
    FileSystem() {}
  };

  void test()
  {
    if (&FileSystem::instance() == NULL)
    {
      std::cout << "singleton is null!" << std::endl;
    }
    else
    {
      std::cout << "singleton is ok" << std::endl;
    }
  }
}

namespace Singleton2
{
  class FileSystem
  {
  public:
    virtual ~FileSystem() {}
    virtual char* readFile(char* path) = 0;
    virtual void  writeFile(char* path, char* contents) = 0;
  };

  class PS3FileSystem : public FileSystem
  {
  public:
    virtual char* readFile(char* path)
    {
      std::cout << "[PS3] Reading from: " << path << std::endl;
      return path; // 占位返回
    }
    virtual void writeFile(char* path, char* contents)
    {
      std::cout << "[PS3] Writing [" << contents << "] to: " << path << std::endl;
    }
  };

  class WiiFileSystem : public FileSystem
  {
  public:
    virtual char* readFile(char* path)
    {
      std::cout << "[WII] Reading from: " << path << std::endl;
      return path; // 占位返回
    }
    virtual void writeFile(char* path, char* contents)
    {
      std::cout << "[WII] Writing [" << contents << "] to: " << path << std::endl;
    }
  };
}

namespace Singleton3
{
#define PLAYSTATION3 1
#define WII 2
#define PLATFORM PLAYSTATION3

  class PS3FileSystem;
  class WiiFileSystem;

  class FileSystem
  {
  public:
    static FileSystem& instance();
    virtual ~FileSystem() {}
    virtual char* readFile(char* path) = 0;
    virtual void  writeFile(char* path, char* contents) = 0;
  protected:
    FileSystem() {}
  };

  class PS3FileSystem : public FileSystem
  {
    virtual char* readFile(char* path)
    {
      std::cout << "[PS3 Macro] Reading from: " << path << std::endl;
      return path;
    }
    virtual void writeFile(char* path, char* contents) {
        std::cout << "[PS3 Macro] Writing to: " << path << std::endl;
    }
  };

  class WiiFileSystem : public FileSystem
  {
    virtual char* readFile(char* path)
    {
      std::cout << "[WII Macro] Reading from: " << path << std::endl;
      return path;
    }
    virtual void writeFile(char* path, char* contents) {
        std::cout << "[WII Macro] Writing to: " << path << std::endl;
    }
  };

  FileSystem& FileSystem::instance()
  {
    #if PLATFORM == PLAYSTATION3
      static FileSystem *instance = new PS3FileSystem();
    #elif PLATFORM == WII
      static FileSystem *instance = new WiiFileSystem();
    #endif
    return *instance;
  }
}

namespace Singleton4
{
  class FileSystem
  {
  public:
    static FileSystem& instance() { return instance_; }
  private:
    FileSystem() {}
    static FileSystem instance_;
  };

  FileSystem FileSystem::instance_ = FileSystem();
}

namespace Singleton5
{
  class FileSystem
  {
  public:
    FileSystem()
    {
      assert(!instantiated_);
      instantiated_ = true;
    }
    ~FileSystem() { instantiated_ = false; }
  private:
    static bool instantiated_;
  };

  bool FileSystem::instantiated_ = false;
}

namespace Singleton7
{
  #define SCREEN_WIDTH 100
  #define SCREEN_HEIGHT 100

  class Bullet
  {
  public:
    int getX() const { return x_; }
    int getY() const { return y_; }
    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }
  private:
    int x_, y_;
  };

  class BulletManager
  {
  public:
    Bullet* create(int x, int y)
    {
      Bullet* bullet = new Bullet();
      bullet->setX(x);
      bullet->setY(y);
      return bullet;
    }
    bool isOnScreen(Bullet& bullet)
    {
      return bullet.getX() >= 0 &&
             bullet.getX() < SCREEN_WIDTH &&
             bullet.getY() >= 0 &&
             bullet.getY() < SCREEN_HEIGHT;
    }
    void move(Bullet& bullet)
    {
      bullet.setX(bullet.getX() + 5);
    }
  };
}

namespace Singleton8
{
  class Bullet
  {
  public:
    Bullet(int x, int y) : x_(x), y_(y) {}
    bool isOnScreen()
    {
      return x_ >= 0 && x_ < SCREEN_WIDTH &&
             y_ >= 0 && y_ < SCREEN_HEIGHT;
    }
    void move() { x_ += 5; }
  private:
    int x_, y_;
  };
}

namespace Singleton9
{
  class Log
  {
  public:
    virtual ~Log() {}
    virtual void write(const char* text) = 0;
  };

  // --- 补充一个实体 Log 类用于测试 ---
  class ConsoleLog : public Log 
  {
  public:
    void write(const char* text) override {
      std::cout << "[Singleton9 Log]: " << text << std::endl;
    }
  };

  class GameObject
  {
  protected:
    Log& getLog() { return log_; }
  private:
    static Log& log_;
  };

  // --- 补充静态成员变量初始化 ---
  ConsoleLog g_consoleLog;
  Log& GameObject::log_ = g_consoleLog;

  class Enemy : public GameObject
  {
  public: // 改为 public 方便外部测试
    void doSomething()
    {
      getLog().write("I can log!");
    }
  };
}

namespace Singleton10
{
  class Log {
  public:
      virtual void print(const char* msg) { std::cout << "[Game Log] " << msg << std::endl; }
  };
  class FileSystem {};
  
  class AudioPlayer
  {
  public:
    virtual void play(int id) = 0;
  };

  // --- 补充实体 AudioPlayer ---
  class ConcreteAudioPlayer : public AudioPlayer {
  public:
    void play(int id) override {
      std::cout << "[Singleton10 Audio] Playing Sound ID: " << id << " (VERY LOUD BANG!)" << std::endl;
    }
  };

  class Game
  {
  public:
    static Game& instance() { return instance_; }

    // --- 设置log_, et. al. …… ---
    void provide(Log* log) { log_ = log; }
    void provide(FileSystem* fs) { fileSystem_ = fs; }
    void provide(AudioPlayer* ap) { audioPlayer_ = ap; }

    Log&         getLog()         { return *log_; }
    FileSystem&  getFileSystem()  { return *fileSystem_; }
    AudioPlayer& getAudioPlayer() { return *audioPlayer_; }

  private:
    // 增加构造函数用于赋空值
    Game() : log_(nullptr), fileSystem_(nullptr), audioPlayer_(nullptr) {}
    static Game instance_;

    Log         *log_;
    FileSystem  *fileSystem_;
    AudioPlayer *audioPlayer_;
  };

  Game Game::instance_ = Game();

  void foo()
  {
    int VERY_LOUD_BANG = 1001;
    Game::instance().getAudioPlayer().play(VERY_LOUD_BANG);
  }
}
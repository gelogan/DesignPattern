#ifndef observer_h
#define observer_h

#include <iostream>
#include <cassert>

#define ASSERT assert

namespace ObserverPattern
{
  using namespace std;

  static const int SURFACE_BRIDGE = 0;

  class Entity {
  public:
    bool isHero() const { return false; }
    bool isStandingOn(int surface) const { return false; }
    bool isOnSurface() { return true; }
    void accelerate(int force) {}
    void update() {}
  };

  enum Event
  {
    EVENT_ENTITY_FELL
  };

  enum Achievement
  {
    ACHIEVEMENT_FELL_OFF_BRIDGE
  };

  static const int GRAVITY = 1;
  static const int EVENT_START_FALL = 1;

  namespace Motivation
  {
    class Physics
    {
    public:
      void updateEntity(Entity& entity);
      void notify(Entity& entity, int event) {}
    };

    void Physics::updateEntity(Entity& entity)
    {
      bool wasOnSurface = entity.isOnSurface();
      entity.accelerate(GRAVITY);
      entity.update();
      if (wasOnSurface && !entity.isOnSurface())
      {
        notify(entity, EVENT_START_FALL);
      }
    }
  }

  namespace Pattern
  {
    class Observer
    {
    public:
      virtual ~Observer() {}
      virtual void onNotify(const Entity& entity, Event event) = 0;
    };

    class Achievements : public Observer
    {
    public:
      virtual void onNotify(const Entity& entity, Event event)
      {
        switch (event)
        {
        case EVENT_ENTITY_FELL:
          if (entity.isHero() && heroIsOnBridge_)
          {
            unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
          }
          break;
        }
      }

    private:
      void unlock(Achievement achievement)
      {
        // 补全：输出解锁信息
        cout << "Unlocked achievement: " << achievement << endl;
      }

      bool heroIsOnBridge_ = true; // 给个默认值防止未定义行为
    };

    static const int MAX_OBSERVERS = 10;

    class Subject
    {
    public:
      void addObserver(Observer* observer)
      {
        if (numObservers_ < MAX_OBSERVERS) {
          observers_[numObservers_++] = observer;
        }
      }

      void removeObserver(Observer* observer)
      {
        int index;
        for (index = 0; index < numObservers_; index++)
        {
          if (observers_[index] == observer) break;
        }

        if (index < numObservers_)
        {
          for (; index < numObservers_ - 1; index++)
          {
            observers_[index] = observers_[index + 1];
          }
          numObservers_--;
        }
      }

    protected:
      void notify(const Entity& entity, Event event)
      {
        for (int i = 0; i < numObservers_; i++)
        {
          observers_[i]->onNotify(entity, event);
        }
      }

    private:
      Observer* observers_[MAX_OBSERVERS];
      int numObservers_ = 0; // 初始化
    };

    class Physics : public Subject
    {
    public:
      void updateEntity(Entity& entity);
    };

    class PhysicsEvent : public Observer
    {
      Subject entityFell_;
      Subject& entityFell() { return entityFell_; }

      virtual void onNotify(const Entity& entity, Event event) {}

      void physicsEvent()
      {
        PhysicsEvent physics;
        physics.entityFell().addObserver(this);
      }
    };
  }

  namespace LinkedObservers
  {
    class Observer
    {
      friend class Subject;

    public:
      Observer() : next_(NULL) {}
      virtual void onNotify(const Entity& entity, Event event) {}
    private:
      Observer* next_;
    };

    class Subject
    {
    public:
      Subject() : head_(NULL) {}

      void addObserver(Observer* observer);
      void removeObserver(Observer* observer);
      void notify(const Entity& entity, Event event);
    private:
      Observer* head_;
    };

    void Subject::addObserver(Observer* observer)
    {
      observer->next_ = head_;
      head_ = observer;
    }

    void Subject::removeObserver(Observer* observer)
    {
      if (head_ == observer)
      {
        head_ = observer->next_;
        observer->next_ = NULL;
        return;
      }

      Observer* current = head_;
      while (current != NULL)
      {
        if (current->next_ == observer)
        {
          current->next_ = observer->next_;
          observer->next_ = NULL;
          return;
        }
        current = current->next_;
      }
    }

    void Subject::notify(const Entity& entity, Event event)
    {
      Observer* observer = head_;
      while (observer != NULL)
      {
        observer->onNotify(entity, event);
        observer = observer->next_;
      }
    }
  }

  namespace One
  {
    class Observable;

    class Observer
    {
      friend class Observable;

    public:
      bool isObserving() const { return observable_ != NULL; }
      void observe(Observable& observable);
      void detach();

    protected:
      Observer() : prev_(this), next_(this) {}
      virtual ~Observer() { detach(); }
      virtual void onNotify(Observable& observable) = 0;

    private:
      Observable* observable_ = NULL;
      Observer* prev_;
      Observer* next_;
    };

    class Observable
    {
      friend class Observer;

    public:
      bool hasObserver() const { return observer_ != NULL; }

    protected:
      Observable() : observer_(NULL) {}
      virtual ~Observable()
      {
        while (observer_ != NULL) observer_->detach();
      }

      void notify()
      {
        if (observer_ == NULL) return;

        Observer* observer = observer_;
        do
        {
          observer->onNotify(*this);
          observer = observer->next_;
        } while (observer != observer_);
      }

      Observer* observer_;
    };

    void Observer::observe(Observable& observable)
    {
      detach();

      if (observable.observer_ == NULL)
      {
        observable.observer_ = this;
      }
      else
      {
        prev_ = observable.observer_->prev_;
        next_ = observable.observer_;
        observable.observer_->prev_->next_ = this;
        observable.observer_->prev_ = this;
      }
      observable_ = &observable;
    }

    void Observer::detach()
    {
      if (observable_ == NULL) return;

      if (observable_->observer_ == this)
      {
        if (next_ == this)
        {
          observable_->observer_ = NULL;
        }
        else
        {
          observable_->observer_ = next_;
        }
      }

      prev_->next_ = next_;
      next_->prev_ = prev_;

      prev_ = this;
      next_ = this;
      observable_ = NULL;
    }

    class Noise : public Observable
    {
    public:
      Noise(const char* name) : name_(name) {}
      void sound()
      {
        cout << name_ << "!" << endl;
        notify();
      }
    private:
      const char* name_;
    };

    class Ear : public Observer
    {
    public:
      Ear(const char* name) : name_(name) {}
      int numObserved = 0;

    protected:
      virtual void onNotify(Observable & observable)
      {
        numObserved++;
        cout << name_ << " heard it!" << endl;
      }
    private:
      const char* name_;
    };

    void destructSoloObserverTest()
    {
      Ear* ear = new Ear("ear");
      Noise noise("beep");
      ear->observe(noise);

      delete ear;
      ASSERT(!noise.hasObserver());

      noise.sound();
    }

    void destructMultipleObserverTest()
    {
      Ear* ear1 = new Ear("ear1");
      Ear* ear2 = new Ear("ear2");
      Noise noise("beep");
      ear1->observe(noise);
      ear2->observe(noise);

      delete ear2;
      ASSERT(noise.hasObserver());

      delete ear1;
      ASSERT(!noise.hasObserver());

      noise.sound();
    }

    void destructObservableTest()
    {
      Ear ear1("ear1");
      Ear ear2("ear2");
      Noise* noise = new Noise("beep");
      ear1.observe(*noise);
      ear2.observe(*noise);

      delete noise;
      ASSERT(!ear1.isObserving());
      ASSERT(!ear2.isObserving());
    }

    void notifyTest()
    {
      Noise noise1("beep");
      Ear ear1("one");
      Ear ear2("two");
      Ear ear3("three");

      noise1.sound();
      ASSERT(ear1.numObserved == 0);
      ASSERT(ear2.numObserved == 0);
      ASSERT(ear3.numObserved == 0);

      ear1.observe(noise1);
      noise1.sound();
      ASSERT(ear1.numObserved == 1);
      ASSERT(ear2.numObserved == 0);
      ASSERT(ear3.numObserved == 0);

      ear2.observe(noise1);
      noise1.sound();
      ASSERT(ear1.numObserved == 2);
      ASSERT(ear2.numObserved == 1);
      ASSERT(ear3.numObserved == 0);

      ear3.observe(noise1);
      noise1.sound();
      ASSERT(ear1.numObserved == 3);
      ASSERT(ear2.numObserved == 2);
      ASSERT(ear3.numObserved == 1);

      ear2.detach();
      noise1.sound();
      ASSERT(ear1.numObserved == 4);
      ASSERT(ear2.numObserved == 2);
      ASSERT(ear3.numObserved == 2);

      ear1.detach();
      noise1.sound();
      ASSERT(ear1.numObserved == 4);
      ASSERT(ear2.numObserved == 2);
      ASSERT(ear3.numObserved == 3);

      ear3.detach();
      noise1.sound();
      ASSERT(ear1.numObserved == 4);
      ASSERT(ear2.numObserved == 2);
      ASSERT(ear3.numObserved == 3);
    }

    void observeTest()
    {
      Ear ear("ear");
      Noise beep("beep");
      Noise boop("boop");

      ear.observe(beep);
      beep.sound();
      ASSERT(ear.numObserved == 1);
      boop.sound();
      ASSERT(ear.numObserved == 1);

      ear.observe(boop);
      beep.sound();
      ASSERT(ear.numObserved == 1);
      boop.sound();
      ASSERT(ear.numObserved == 2);
    }

    void test()
    {
      destructSoloObserverTest();
      destructMultipleObserverTest();
      destructObservableTest();
      notifyTest();
      observeTest();
    }
  }

  namespace Pool
  {
    class Binding;
    class BindingPool;
    class Listener;

    class Event
    {
    public:
      Event(BindingPool& pool)
      : pool_(pool), binding_(NULL) {}

      // 补全析构函数
      ~Event();

      void addListener(Listener& listener);
      void removeListener(Listener& listener);
      void send(const char* data);

    private:
      BindingPool& pool_;
      Binding* binding_;
    };

    class Listener
    {
    public:
      Listener(const char* name)
      : name_(name), numEvents_(0) {} // 增加统计追踪

      int numEvents() const { return numEvents_; }
      void incrementEvents() { numEvents_++; }
      void decrementEvents() { numEvents_--; }

      void receive(const char* data)
      {
        cout << name_ << " received " << data << endl;
      }

    private:
      const char* name_;
      int numEvents_; 
    };

    class Binding
    {
      friend class BindingPool;
      friend class Event;

    public:
      Binding() : listener_(NULL), next_(NULL) {}

    private:
      Listener* listener_;
      Binding* next_;
    };

    class BindingPool
    {
    public:
      BindingPool()
      {
        free_ = &bindings_[0];
        for (int i = 0; i < POOL_SIZE - 1; i++)
        {
          bindings_[i].next_ = &bindings_[i + 1];
        }
      }

      Binding* newBinding()
      {
        if (free_ == NULL) return NULL; 
        Binding* binding = free_;
        free_ = free_->next_;
        return binding;
      }

      // 补全：释放Binding的机制
      void freeBinding(Binding* binding)
      {
        binding->listener_ = NULL;
        binding->next_ = free_;
        free_ = binding;
      }

    private:
      static const int POOL_SIZE = 100;
      Binding bindings_[POOL_SIZE];
      Binding* free_;
    };

    Event::~Event()
    {
      Binding* current = binding_;
      while (current != NULL)
      {
        Binding* next = current->next_;
        if (current->listener_) {
          current->listener_->decrementEvents();
        }
        pool_.freeBinding(current);
        current = next;
      }
      binding_ = NULL;
    }

    void Event::addListener(Listener& listener)
    {
      Binding* binding = pool_.newBinding();
      if (!binding) return;
      binding->listener_ = &listener;
      binding->next_ = binding_;
      binding_ = binding;
      listener.incrementEvents(); // 同步增加监听计数
    }

    void Event::removeListener(Listener& listener)
    {
      Binding* prev = NULL;
      Binding* current = binding_;

      while (current != NULL)
      {
        if (current->listener_ == &listener)
        {
          if (prev == NULL)
          {
            binding_ = current->next_;
          }
          else
          {
            prev->next_ = current->next_;
          }
          
          listener.decrementEvents(); // 同步减少监听计数
          pool_.freeBinding(current);
          return;
        }
        prev = current;
        current = current->next_;
      }
    }

    void Event::send(const char* data)
    {
      Binding* binding = binding_;
      while (binding != NULL)
      {
        binding->listener_->receive(data);
        binding = binding->next_;
      }
    }

    void destructEventTest()
    {
      BindingPool pool;

      Event* event1 = new Event(pool);
      Event* event2 = new Event(pool);

      Listener listener1("listener 1");
      Listener listener2("listener 2");

      event1->addListener(listener1);
      event1->addListener(listener2);
      event2->addListener(listener1);
      event2->addListener(listener2);

      ASSERT(listener1.numEvents() == 2);
      ASSERT(listener2.numEvents() == 2);

      delete event1;

      ASSERT(listener1.numEvents() == 1);
      ASSERT(listener2.numEvents() == 1);

      delete event2;

      ASSERT(listener1.numEvents() == 0);
      ASSERT(listener2.numEvents() == 0);
    }

    void test()
    {
      destructEventTest();

      BindingPool pool;

      Event event1(pool);
      Event event2(pool);

      Listener listener1("listener 1");
      Listener listener2("listener 2");
      Listener listener3("listener 3");

      event1.addListener(listener1);
      event1.addListener(listener2);
      event2.addListener(listener2);
      event2.addListener(listener3);

      event1.send("first");
      event2.send("second");
    }
  }

  void test()
  {
    cout << "--- Running One::test() ---" << endl;
    One::test();
    cout << "--- Running Pool::test() ---" << endl;
    Pool::test();
    cout << "All tests passed successfully!" << endl;
  }
}

#endif
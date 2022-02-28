//
// Created by jeremy on 2022-02-27.
//

#ifndef PROJECT_EVENTBUS_H
#define PROJECT_EVENTBUS_H


#include <list>
#include <map>
#include <typeindex>

#include "events/Event.h"


class HandlerFunctionBase {

    virtual void Call(Event *event) = 0;

public:

    void Exec(Event *event)
    {
        Call(event);
    }

};


template<class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase {
public:

    typedef void (T::*MemberFunction)(EventType *);

    MemberFunctionHandler(T *instance, MemberFunction memberFunction) :
            instance(instance), memberFunction(memberFunction) { };

    void Call(Event *event) override
    {
        (instance->*memberFunction)(static_cast<EventType*>(event));
    }

private:

    T *instance;
    MemberFunction memberFunction;

};


class EventBus {

    typedef std::list<HandlerFunctionBase *> HandlerList;
    std::map<std::type_index, HandlerList *> subscribers;

protected:

    static EventBus *bus;
    EventBus() = default;

public:

    EventBus(EventBus&) = delete;  // no copying
    void operator=(const EventBus&) = delete;  // no assignment

    static EventBus *GetInstance()
    {
        if (bus == nullptr)
            bus = new EventBus();
        return bus;
    }

    template<typename EventType>
    void Publish(EventType *event)
    {
        HandlerList *handlers = subscribers[typeid(EventType)];
        if (handlers == nullptr)
            return;

        for (auto& handler : *handlers) {
            if (handler != nullptr)
                handler->Exec(event);
        }
    }


    template<class T, class EventType>
    void Subscribe(T *instance, void (T::*memberFunction)(EventType *))
    {
        HandlerList *handlers = subscribers[typeid(EventType)];
        if (handlers == nullptr) {
            handlers = new HandlerList();
            subscribers[typeid(EventType)] = handlers;
        }

        handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
    }

};

#endif //PROJECT_EVENTBUS_H

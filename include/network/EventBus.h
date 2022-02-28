//
// Created by jeremy on 2022-02-27.
//

#ifndef PROJECT_EVENTBUS_H
#define PROJECT_EVENTBUS_H


#include <list>
#include <map>
#include <typeindex>


class Event {
protected:
    virtual ~Event() { };
};


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

    void Call(Event *event)
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

public:

    template<typename EventType>
    void Publish(EventType *event);

    template<class T, class EventType>
    void Subscribe(T *instance, void (T::*memberFunction)(EventType *));

};


#endif //PROJECT_EVENTBUS_H

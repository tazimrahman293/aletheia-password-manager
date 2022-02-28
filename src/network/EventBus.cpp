//
// Created by jeremy on 2022-02-27.
//

#include <network/EventBus.h>


EventBus *EventBus::GetInstance()
{
    if (bus == nullptr)
        bus = new EventBus();
    return bus;
}


template<typename EventType>
void EventBus::Publish(EventType *event)
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
void EventBus::Subscribe(T *instance, void (T::*memberFunction)(EventType *))
{
    HandlerList *handlers = subscribers[typeid(EventType)];
    if (handlers == nullptr) {
        handlers = new HandlerList();
        subscribers[typeid(EventType)] = handlers;
    }

    handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
}

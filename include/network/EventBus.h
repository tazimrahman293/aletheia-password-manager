//
// Created by jeremy on 2022-02-27.
//

#ifndef PROJECT_EVENTBUS_H
#define PROJECT_EVENTBUS_H


#include <list>
#include <map>
#include <typeindex>

#include "events/Event.h"


/**
 * Virtual base class for a callable member function.
 */
class HandlerFunctionBase {

    // Pure virtual, to be overridden
    virtual void Call(Event *event) = 0;

public:

    /**
     * A public interface for the overridden Call method.
     * @param event the event parameter to be passed to subscribers' event handlers
     */
    void Exec(Event *event)
    {
        Call(event);
    }

};


/**
 * Wrapper class for subscribing class instances' member functions to events.
 * @tparam T type of the subscribing class
 * @tparam EventType type of the event being subscribed to
 */
template<class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase {
public:

    typedef void (T::*MemberFunction)(EventType *);

    MemberFunctionHandler(T *instance, MemberFunction memberFunction) :
            instance(instance), memberFunction(memberFunction) { };

    /**
     * Calls the subscribed handler method with the event parameter as its argument.
     * @param event
     */
    void Call(Event *event) override
    {
        (instance->*memberFunction)(static_cast<EventType*>(event));
    }

private:

    // The class instance that has subscribed using this handler
    T *instance;

    // The member function of class T to use as a handler function
    MemberFunction memberFunction;

};


/**
 * Singleton class for managing all subscriptions and calling relevant handler functions for
 * subscribers.
 */
class EventBus {

    typedef std::list<HandlerFunctionBase *> HandlerList;

    // Maps event types to arrays of handler functions that subscribe to them
    std::map<std::type_index, HandlerList *> subscribers;

protected:

    // Single instance of the class
    static EventBus *bus;

    // Default constructor
    EventBus() = default;

public:

    EventBus(EventBus&) = delete;  // no copying
    void operator=(const EventBus&) = delete;  // no assignment

    /**
     * Returns a pointer to the single instance of EventBus, creating it if it doesn't exist already.
     * @return a handle for the EventBus
     */
    static EventBus *GetInstance()
    {
        if (bus == nullptr)
            bus = new EventBus();
        return bus;
    }

    /**
     * Executes all the handler functions subscribed to a particular event type.
     * @tparam EventType the type of event to publish
     * @param event the event instance to pass to the handler functions
     */
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

    /**
     * Adds an instance and one of its member functions to the subscriber list for a type of event.
     * @tparam T the subscribing class type
     * @tparam EventType the type of event being subscribed to
     * @param instance the class instance to subscribe
     * @param memberFunction member function pointer which will handle the event when it occurs
     */
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

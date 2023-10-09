# Party_Llama

C++ event system library

---
### ! This is a personal project and not meant to be used in any actual capacity !
- I don't mind anyone using it, I would just advise against it
---

# Event Systems

## Events

`Events` are user defined structs that are then passed into an `Event System` to be handled.

We'll use a stripped down networking program for examples

**Example:**
```c++
// Event for a network connection being closed
struct Disconn {
	int sock_fd;
};

// Event for a message over a socket
struct Message {
	const char* data;
	size_t size;
};

// Event system types are described later
pllama::EventSystem_Immediate<Message, Disconn> netSys;
```

## Event Handlers

`Event Handlers` are functions/lambdas/functors that can be called with
```c++
void operator()(const Event_t&);
```

**Example:**
```c++
auto lambda_handler = [](const Message&){ std::cout << "lambda_handler\n";};

void function_handler(const Message&) { std::cout << "function_handler\n"; }

struct functor_handler {
	void operator()(const Message&) { std::cout << "functor_handler\n"; }
};
```

## Registering Handlers

`Event Handlers` need to be registered with an `Event System`
```c++
netSys.on<Message>(lambda_handler);
netSys.on<Message>(function_hanlder);
netSys.on<Message>(functor_handler{});
```
Now when a `Message` `Event` is emitted on `netSys` all three handlers will run.

## Emitting Events

`Events` are emitted using the template function `emit<T>`

**Example:**
```c++
// ... read message from socket ...
Message mess{data, size};

// All handlers registered for Message events will fire
netSys.emit<Message>(mess);
```

## EventSystem_Immediate

`EventSystem_Immediate` handles events on the thread that emits the event in the order those handlers were added.

```c++
pllama::EventSystem_Immediate<Message, Disconn> evSys;
```

## EventSystem_Async

`EventSystem_Async` handles events asynchronously, dispatching each handler to a separate thread.

```c++
// EventSystem_Async is constructed with a size_t, for the number of threads
pllama::EventSystem_Async<Message, Disconn> evSys_async{4};
```
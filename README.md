# Dart Data Structures Reimplemented in C

A **C-based reimplementation** of Dart's core data structures (`List`, `Set`, `Map`) for educational and systems programming use cases. This project provides a hands-on exploration of memory management, function pointers, and modular C design to simulate object-oriented behavior in a low-level language.

## 🧰 Features
- ✅ **Dynamic Arrays** (`List`): Auto-resizing arrays with OOP-style methods (`list.add(...)`, `list.get(...)`).
- ✅ **Hash Tables** (`Map`): Key-value storage with djb2 hashing and collision handling via chaining.
- ✅ **Hash Sets** (`Set`): Unique element storage built atop hash tables.
- ✅ **Function Pointers**: Simulated method calls like `list.add(list, item)`.
- ✅ **Modular Design**: Clean separation of headers, implementations, and factory patterns.

## 🚀 Why This Project?
This project bridges the gap between high-level language abstractions (like Dart) and low-level systems programming in C. It’s ideal for:
- Learning **manual memory management** in C.
- Understanding **data structure internals**.
- Exploring **OOP patterns in C** using function pointers.
- Building reusable, performant C libraries.

## 🛠️ Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/da578/dart-reimplementation
   ```
2. Compile with GCC:
   ```bash
   gcc main.c list.c map.c set.c -o demo
   ```

## 📦 Usage Examples

### List
```c
#include "list.h"

int main() {
    List* list = ListFactory.empty(4, true); // Growable list
    int a = 10, b = 20;
    list->add(list, &a);
    list->add(list, &b);

    for (size_t i = 0; i < list->size; i++) {
        printf("Index %zu: %d\n", i, *(int*)list->get(list, i));
    }

    list->destroy(list);
    return 0;
}
```

### Map (Hash Table)
```c
#include "map.h"

int main() {
    Map* map = MapFactory.empty(8, true);
    int value1 = 100, value2 = 200;
    map->put(map, "key1", &value1);
    map->put(map, "key2", &value2);

    int* result = (int*)map->get(map, "key1");
    printf("Value for 'key1': %d\n", *result);

    map->destroy(map);
    return 0;
}
```

### Set (Unique Elements)
```c
#include "set.h"

int main() {
    Set* set = SetFactory.empty(8, true);
    set->add(set, "apple");
    set->add(set, "banana");
    set->add(set, "apple"); // Duplicate - ignored

    printf("Contains 'apple'? %d\n", set->contains(set, "apple")); // Output: 1 (true)

    set->destroy(set);
    return 0;
}
```

## 🤝 Contributing
Contributions are welcome! To contribute:
1. Fork the project.
2. Create a feature branch (`git checkout -b feature/new-structure`).
3. Commit changes (`git commit -m "Add new data structure"`).
4. Push to the branch (`git push origin feature/new-structure`).
5. Open a Pull Request.

## 📄 License
MIT License (2025)  
Copyright (c) 2025 Dzulkifli Anwar  

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
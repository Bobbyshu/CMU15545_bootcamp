# Move Constructor vs Move Assignment Operator

**`move constructor`** 和 **`move assignment operator`** 的核心区别并不在于是否“废弃”传入的对象，而在于它们的使用场景和调用时对象的状态。

---

## 主要区别

### 1. Move Constructor（移动构造函数）
- **作用**：创建一个新对象，并从传入的对象中**转移资源**。
- **行为**：
  - 转移资源后，传入的对象（右值）被置于“有效但未定义”的状态（例如内部数据指针可能被置为 `nullptr`，`size` 可能被设置为 0）。
  - 传入的对象仍然有效，但内容变为空。

- **调用场景**：
  - 在创建新对象时触发。
  - 示例：
    ```cpp
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = std::move(a); // 调用移动构造函数
    ```

---

### 2. Move Assignment Operator（移动赋值操作符）
- **作用**：将一个已有对象的资源替换为另一个对象的资源。
- **行为**：
  - 当前对象的资源会被释放（如果有），以接收传入对象的资源。
  - 转移资源后，传入的对象（右值）同样被置于“有效但未定义”的状态。

- **调用场景**：
  - 在赋值操作时触发（针对已有对象）。
  - 示例：
    ```cpp
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b;
    b = std::move(a); // 调用移动赋值操作符
    ```

---

## 传入对象的状态

无论是 `move constructor` 还是 `move assignment operator`，**传入对象的资源都会被转移**，转移后传入对象的状态如下：
1. **仍然是有效对象**（可以调用其成员函数）。
2. **内部资源变成未定义状态**：
   - 对于容器，可能是空状态（如 `size == 0`，指针为 `nullptr`）。
   - 尝试访问其内容通常是未定义行为。

所以，传入对象在**两种情况下都会被“废弃资源”**，只是对象本身没有销毁。

---

## 对比总结

| 特性                        | Move Constructor（移动构造函数）    | Move Assignment Operator（移动赋值操作符） |
|-----------------------------|-------------------------------------|------------------------------------------|
| **作用**                    | 创建新对象并转移资源               | 用现有对象接收传入对象的资源              |
| **传入对象的状态**          | 资源被转移，状态未定义             | 资源被转移，状态未定义                    |
| **释放当前对象的资源**      | 不会（当前对象是新建的）            | 会（先释放已有资源，再接收新资源）         |
| **使用场景**                | 新对象的初始化                     | 已有对象的赋值                            |

---

## 示例对比

### 移动构造函数
```cpp
std::vector<int> a = {1, 2, 3};
std::vector<int> b = std::move(a); // 调用移动构造函数
```

1. b 是新对象，从 a 中接管资源
2. a 的资源被转移，其内容变为空

### 移动赋值操作符
```cpp
std::vector<int> a = {1, 2, 3};
std::vector<int> b;
b = std::move(a); // 调用移动赋值操作符
```

1. b 是已有对象。
2. b 先释放自己的资源（如果有），然后从 a 接管资源
3. a 的资源被转移，其内容变为空

核心区别：移动构造函数创建新对象，移动赋值操作符替换已有对象的资源
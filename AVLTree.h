#pragma once
// 树的高度越小，查找速度越快。
// 平衡二叉树（Balanced Binary Tree 或 Height-Balanced Tree），因由前苏联数学家 Adelson-Velskii 和 Landis 提出，所以又称 AVL 树。
// 平衡二叉树或空树的定义：
// - 左子树和右子树的深度之差的绝对值不超过1。
// - 左子树和右子树也必须是平衡二叉树。
// - 树高为 O(log n)，保证了高效的查找、插入和删除操作。

// 平衡因子：右子树高度 - 左子树高度

/**
 * @brief An AVLTree-based map implementation
 * @details The map is sorted according to the natural ordering of its
 *  keys or by a {@code Compare} function provided; This implementation
 *  provides guaranteed log(n) time cost for the contains, get, insert
 *  and remove operations.
 */

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

 // 定义模板类 AvlTreeMap，它接受三个模板参数：
 // - Key：键的类型
 // - Value：值的类型
 // - Compare：比较函数的类型，默认为 std::less<Key>，即对 Key 类型的元素进行小于比较
template <typename Key, typename Value, typename Compare = std::less<Key>>
class AvlTreeMap {
private:
    // 类型别名定义，以简化代码
    using USize = size_t; // USize：无符号整数类型，用于表示大小和索引
    using Factor = int64_t; // Factor：有符号整数类型，用于表示平衡因子

    // 默认构造函数初始化比较函数对象 compare
    Compare compare = Compare(); // 比较函数对象，用于树中的所有比较操作，以保持键的顺序

public:
    // Entry 结构体：表示键值对
    struct Entry {
        Key key;    // 键
        Value value; // 值

        // 重载 "==" 运算符，用于比较两个 Entry 是否相等
        bool operator==(const Entry& rhs) const noexcept {
            return this->key == rhs.key && this->value == rhs.value;
        }

        // 重载 "!=" 运算符，用于比较两个 Entry 是否不相等
        bool operator!=(const Entry& rhs) const noexcept {
            return this->key != rhs.key || this->value != rhs.value;
        }
    };

private:
    // Node 结构体：表示树中的每个节点
    struct Node {
        using Ptr = std::shared_ptr<Node>; // 使用智能指针管理 Node 对象
        using Provider = const std::function<Ptr(void)>&; // 提供节点的函数类型
        using Consumer = const std::function<void(const Ptr&)>&; // 消费节点的函数类型

        Key key;    // 节点的键
        Value value; // 节点的值

        Ptr left = nullptr; // 左子树
        Ptr right = nullptr; // 右子树

        USize height = 1; // 节点的高度，叶子节点的高度为1

        // 构造函数：创建仅包含键的节点
        explicit Node(Key k) : key(std::move(k)) {}

        // 构造函数：创建包含键值对的节点
        explicit Node(Key k, Value v) : key(k), value(std::move(v)) {}

        ~Node() = default; // 默认析构函数

        // 判断当前节点是否为叶子节点
        inline bool isLeaf() const noexcept {
            return this->left == nullptr && this->right == nullptr;
        }

        // 更新当前节点的高度，左右子树的高度影响当前节点的高度
        inline void updateHeight() noexcept {
            if (this->isLeaf()) {
                this->height = 1; // 叶子节点高度为1
            }
            else if (this->right == nullptr) {
                this->height = this->left->height + 1; // 只有左子树时，节点高度为左子树的高度 + 1
            }
            else if (this->left == nullptr) {
                this->height = this->right->height + 1; // 只有右子树时，节点高度为右子树的高度 + 1
            }
            else {
                // 左右子树都有时，节点高度为左右子树中较高的一方 + 1
                this->height = std::max(this->left->height, this->right->height) + 1;
            }
        }

        // 计算当前节点的平衡因子：右子树高度 - 左子树高度
        inline Factor factor() const noexcept {
            if (this->isLeaf()) {
                return 0; // 叶子节点的平衡因子为0
            }
            else if (this->left == nullptr) {
                return (Factor)this->right->height; // 只有右子树时，平衡因子为右子树高度
            }
            else if (this->right == nullptr) {
                return (Factor)-this->left->height; // 只有左子树时，平衡因子为负的左子树高度
            }
            else {
                // 如果左右子树都有，平衡因子为右子树高度 - 左子树高度
                return (Factor)(this->right->height - this->left->height);
            }
        }

        // 返回当前节点的键值对
        inline Entry entry() const { return Entry{ key, value }; }

        // 创建一个包含指定键的节点
        static Ptr from(const Key& k) { return std::make_shared<Node>(Node(k)); }

        // 创建一个包含指定键值对的节点
        static Ptr from(const Key& k, const Value& v) { return std::make_shared<Node>(Node(k, v)); }
    };

    // 还可以添加 AVL 树的根节点、插入、删除、查找等操作的成员函数

};

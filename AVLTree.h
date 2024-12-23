#pragma once
// ���ĸ߶�ԽС�������ٶ�Խ�졣
// ƽ���������Balanced Binary Tree �� Height-Balanced Tree��������ǰ������ѧ�� Adelson-Velskii �� Landis ����������ֳ� AVL ����
// ƽ�������������Ķ��壺
// - �������������������֮��ľ���ֵ������1��
// - ��������������Ҳ������ƽ���������
// - ����Ϊ O(log n)����֤�˸�Ч�Ĳ��ҡ������ɾ��������

// ƽ�����ӣ��������߶� - �������߶�

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

 // ����ģ���� AvlTreeMap������������ģ�������
 // - Key����������
 // - Value��ֵ������
 // - Compare���ȽϺ��������ͣ�Ĭ��Ϊ std::less<Key>������ Key ���͵�Ԫ�ؽ���С�ڱȽ�
template <typename Key, typename Value, typename Compare = std::less<Key>>
class AvlTreeMap {
private:
    // ���ͱ������壬�Լ򻯴���
    using USize = size_t; // USize���޷����������ͣ����ڱ�ʾ��С������
    using Factor = int64_t; // Factor���з����������ͣ����ڱ�ʾƽ������

    // Ĭ�Ϲ��캯����ʼ���ȽϺ������� compare
    Compare compare = Compare(); // �ȽϺ��������������е����бȽϲ������Ա��ּ���˳��

public:
    // Entry �ṹ�壺��ʾ��ֵ��
    struct Entry {
        Key key;    // ��
        Value value; // ֵ

        // ���� "==" ����������ڱȽ����� Entry �Ƿ����
        bool operator==(const Entry& rhs) const noexcept {
            return this->key == rhs.key && this->value == rhs.value;
        }

        // ���� "!=" ����������ڱȽ����� Entry �Ƿ����
        bool operator!=(const Entry& rhs) const noexcept {
            return this->key != rhs.key || this->value != rhs.value;
        }
    };

private:
    // Node �ṹ�壺��ʾ���е�ÿ���ڵ�
    struct Node {
        using Ptr = std::shared_ptr<Node>; // ʹ������ָ����� Node ����
        using Provider = const std::function<Ptr(void)>&; // �ṩ�ڵ�ĺ�������
        using Consumer = const std::function<void(const Ptr&)>&; // ���ѽڵ�ĺ�������

        Key key;    // �ڵ�ļ�
        Value value; // �ڵ��ֵ

        Ptr left = nullptr; // ������
        Ptr right = nullptr; // ������

        USize height = 1; // �ڵ�ĸ߶ȣ�Ҷ�ӽڵ�ĸ߶�Ϊ1

        // ���캯�����������������Ľڵ�
        explicit Node(Key k) : key(std::move(k)) {}

        // ���캯��������������ֵ�ԵĽڵ�
        explicit Node(Key k, Value v) : key(k), value(std::move(v)) {}

        ~Node() = default; // Ĭ����������

        // �жϵ�ǰ�ڵ��Ƿ�ΪҶ�ӽڵ�
        inline bool isLeaf() const noexcept {
            return this->left == nullptr && this->right == nullptr;
        }

        // ���µ�ǰ�ڵ�ĸ߶ȣ����������ĸ߶�Ӱ�쵱ǰ�ڵ�ĸ߶�
        inline void updateHeight() noexcept {
            if (this->isLeaf()) {
                this->height = 1; // Ҷ�ӽڵ�߶�Ϊ1
            }
            else if (this->right == nullptr) {
                this->height = this->left->height + 1; // ֻ��������ʱ���ڵ�߶�Ϊ�������ĸ߶� + 1
            }
            else if (this->left == nullptr) {
                this->height = this->right->height + 1; // ֻ��������ʱ���ڵ�߶�Ϊ�������ĸ߶� + 1
            }
            else {
                // ������������ʱ���ڵ�߶�Ϊ���������нϸߵ�һ�� + 1
                this->height = std::max(this->left->height, this->right->height) + 1;
            }
        }

        // ���㵱ǰ�ڵ��ƽ�����ӣ��������߶� - �������߶�
        inline Factor factor() const noexcept {
            if (this->isLeaf()) {
                return 0; // Ҷ�ӽڵ��ƽ������Ϊ0
            }
            else if (this->left == nullptr) {
                return (Factor)this->right->height; // ֻ��������ʱ��ƽ������Ϊ�������߶�
            }
            else if (this->right == nullptr) {
                return (Factor)-this->left->height; // ֻ��������ʱ��ƽ������Ϊ�����������߶�
            }
            else {
                // ��������������У�ƽ������Ϊ�������߶� - �������߶�
                return (Factor)(this->right->height - this->left->height);
            }
        }

        // ���ص�ǰ�ڵ�ļ�ֵ��
        inline Entry entry() const { return Entry{ key, value }; }

        // ����һ������ָ�����Ľڵ�
        static Ptr from(const Key& k) { return std::make_shared<Node>(Node(k)); }

        // ����һ������ָ����ֵ�ԵĽڵ�
        static Ptr from(const Key& k, const Value& v) { return std::make_shared<Node>(Node(k, v)); }
    };

    // ��������� AVL ���ĸ��ڵ㡢���롢ɾ�������ҵȲ����ĳ�Ա����

};

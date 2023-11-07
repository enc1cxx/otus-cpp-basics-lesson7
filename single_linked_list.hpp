#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <string>
#include <utility>

namespace single_linked_list {

template <typename Type>
class SingleLinkedList {
  // Узел списка
  struct Node {
    Node() = default;
    Node(const Type &val, Node *next) : value(val), next_node(next) {}
    Type value;
    Node *next_node = nullptr;
  };

  // Шаблон класса «Базовый Итератор».
  // Определяет поведение итератора на элементы односвязного списка
  // ValueType — совпадает с Type (для Iterator) либо с const Type (для
  // ConstIterator)
  template <typename ValueType>
  class BasicIterator {
    // Класс списка объявляется дружественным, чтобы из методов списка
    // был доступ к приватной области итератора
    friend class SingleLinkedList;

    // Конвертирующий конструктор итератора из указателя на узел списка
    explicit BasicIterator(Node *node) { node_ = node; }

   public:
    // Объявленные ниже типы сообщают стандартной библиотеке о свойствах этого
    // итератора

    // Категория итератора — forward iterator
    // (итератор, который поддерживает операции инкремента и многократное
    // разыменование)
    using iterator_category = std::forward_iterator_tag;
    // Тип элементов, по которым перемещается итератор
    using value_type = Type;
    // Тип, используемый для хранения смещения между итераторами
    using difference_type = std::ptrdiff_t;
    // Тип указателя на итерируемое значение
    using pointer = ValueType *;
    // Тип ссылки на итерируемое значение
    using reference = ValueType &;

    BasicIterator() = default;

    // Конвертирующий конструктор/конструктор копирования
    // При ValueType, совпадающем с Type, играет роль копирующего конструктора
    // При ValueType, совпадающем с const Type, играет роль конвертирующего
    // конструктора
    BasicIterator(const BasicIterator<Type> &other) noexcept {
      node_ = other.node_;
    }

    // Чтобы компилятор не выдавал предупреждение об отсутствии оператора = при
    // наличии пользовательского конструктора копирования, явно объявим оператор
    // = и попросим компилятор сгенерировать его за нас
    BasicIterator &operator=(const BasicIterator &rhs) = default;

    // Оператор сравнения итераторов (в роли второго аргумента выступает
    // константный итератор) Два итератора равны, если они ссылаются на один и
    // тот же элемент списка либо на end()
    [[nodiscard]] bool operator==(
        const BasicIterator<const Type> &rhs) const noexcept {
      return node_ == rhs.node_;
    }

    // Оператор проверки итераторов на неравенство
    // Противоположен !=
    [[nodiscard]] bool operator!=(
        const BasicIterator<const Type> &rhs) const noexcept {
      return node_ != rhs.node_;
    }

    // Оператор сравнения итераторов (в роли второго аргумента итератор)
    // Два итератора равны, если они ссылаются на один и тот же элемент списка
    // либо на end()
    [[nodiscard]] bool operator==(
        const BasicIterator<Type> &rhs) const noexcept {
      return node_ == rhs.node_;
    }

    // Оператор проверки итераторов на неравенство
    // Противоположен !=
    [[nodiscard]] bool operator!=(
        const BasicIterator<Type> &rhs) const noexcept {
      return node_ != rhs.node_;
    }

    // Оператор прединкремента. После его вызова итератор указывает на следующий
    // элемент списка Возвращает ссылку на самого себя Инкремент итератора, не
    // указывающего на существующий элемент списка, приводит к неопределённому
    // поведению
    BasicIterator &operator++() noexcept {
      node_ = node_->next_node;
      return *this;
    }

    // Оператор постинкремента. После его вызова итератор указывает на следующий
    // элемент списка Возвращает прежнее значение итератора Инкремент итератора,
    // не указывающего на существующий элемент списка, приводит к
    // неопределённому поведению
    BasicIterator operator++(int) noexcept {
      auto old_value(*this);
      ++(*this);
      return old_value;
    }

    // Операция разыменования. Возвращает ссылку на текущий элемент
    // Вызов этого оператора у итератора, не указывающего на существующий
    // элемент списка, приводит к неопределённому поведению
    [[nodiscard]] reference operator*() const noexcept { return node_->value; }

    // Операция доступа к члену класса. Возвращает указатель на текущий элемент
    // списка Вызов этого оператора у итератора, не указывающего на существующий
    // элемент списка, приводит к неопределённому поведению
    [[nodiscard]] pointer operator->() const noexcept {
      if (node_) {
        return &node_->value;
      } else {
        return nullptr;
      }
    }

   private:
    Node *node_ = nullptr;
  };

 public:
  using value_type = Type;
  using reference = value_type &;
  using const_reference = const value_type &;

  // Итератор, допускающий изменение элементов списка
  using Iterator = BasicIterator<Type>;
  // Константный итератор, предоставляющий доступ для чтения к элементам списка
  using ConstIterator = BasicIterator<const Type>;

  // Возвращает итератор, ссылающийся на первый элемент
  // Если список пустой, возвращённый итератор будет равен end()
  [[nodiscard]] Iterator begin() noexcept { return Iterator(head_->next_node); }

  // Возвращает итератор, указывающий на позицию, следующую за последним
  // элементом односвязного списка Разыменовывать этот итератор нельзя — попытка
  // разыменования приведёт к неопределённому поведению
  [[nodiscard]] Iterator end() noexcept { return Iterator(nullptr); }

  // Возвращает константный итератор, ссылающийся на первый элемент
  // Если список пустой, возвращённый итератор будет равен end()
  // Результат вызова эквивалентен вызову метода cbegin()
  [[nodiscard]] ConstIterator begin() const noexcept {
    return ConstIterator(head_->next_node);
  }

  // Возвращает константный итератор, указывающий на позицию, следующую за
  // последним элементом односвязного списка Разыменовывать этот итератор нельзя
  // — попытка разыменования приведёт к неопределённому поведению Результат
  // вызова эквивалентен вызову метода cend()
  [[nodiscard]] ConstIterator end() const noexcept {
    return ConstIterator(nullptr);
  }

  // Возвращает константный итератор, ссылающийся на первый элемент
  // Если список пустой, возвращённый итератор будет равен cend()
  [[nodiscard]] ConstIterator cbegin() const noexcept {
    return ConstIterator(head_->next_node);
  }

  // Возвращает константный итератор, указывающий на позицию, следующую за
  // последним элементом односвязного списка Разыменовывать этот итератор нельзя
  // — попытка разыменования приведёт к неопределённому поведению
  [[nodiscard]] ConstIterator cend() const noexcept {
    return ConstIterator(nullptr);
  }

 public:
  SingleLinkedList() {
    head_ = new Node();
    end_ = new Node();
  };
  // Возвращает количество элементов в списке за время O(1)
  [[nodiscard]] size_t size() const noexcept { return size_; }

  SingleLinkedList(std::initializer_list<Type> values) {
    SingleLinkedList temp;
    temp.init(values.begin(), values.end());
    swap(temp);
  }

  // Move ctor
  SingleLinkedList(SingleLinkedList &&other) noexcept {
    size_ = other.size_;
    other.size_ = 0;
    head_ = other.head_;
    other.head_ = nullptr;
    end_ = other.end_;
    other.end_ = nullptr;
  }

  // Move assignment operator
  SingleLinkedList &operator=(SingleLinkedList &&rhs) noexcept {
    this->size_ = rhs.size_;
    rhs.size_ = 0;
    this->head_ = rhs.head_;
    rhs.head_ = nullptr;
    this->end_ = rhs.end_;
    rhs.end_ = nullptr;

    return *this;
  }

  template <typename TypeIt>
  void init(TypeIt begin, TypeIt end) {
    Node *node = head_;
    for (TypeIt i = begin; i != end; ++i) {
      ++size_;
      node->next_node = new Node(*i, nullptr);
      node = node->next_node;
    }
  }

  SingleLinkedList(const SingleLinkedList &other) {
    SingleLinkedList temp;
    temp.init(other.begin(), other.end());
    swap(temp);
  }

  SingleLinkedList &operator=(const SingleLinkedList &rhs) {
    if (this != &rhs) {
      SingleLinkedList temp(rhs);
      swap(temp);
    }
    return *this;
  }

  Type &operator[](const size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Index");
    } else {
      Node *p = head_->next_node;
      for (size_t i = 0; i != index; ++i) {
        p = p->next_node;
      }
      return p->value;
    }
  }

  // Обменивает содержимое списков за время O(1)
  void swap(SingleLinkedList &other) noexcept {
    std::swap(head_, other.head_);
    other.head_ = nullptr;
    std::swap(end_, other.end_);
    other.end_ = nullptr;
    std::swap(size_, other.size_);
  }

  // Сообщает, пустой ли список за время O(1)
  [[nodiscard]] bool is_empty() const noexcept {
    if (!size_) {
      return true;
    }
    return false;
  }

  // Вставляет элемент value в начало списка за время O(1)
  void push_front(const Type &value) {
    head_->next_node = new Node(value, head_->next_node);
    if (size_ == 0) {
      end_ = head_->next_node;
    }
    ++size_;
  }

  void push_back(const Type &value) {
    if (size_ == 0) {
      push_front(value);
    } else {
      Node *new_node =
          new Node(value, nullptr);  // обновляем указатель на последний
      end_->next_node = new_node;
      end_ = new_node;
      ++size_;  // обновляем размер
    }
  }

  void print() {
    if (is_empty()){
      std::cout << "Single linked list is empty" << std::endl;
      return;
    } 
    for (auto it = this->begin(); it != this->end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }

  // Очищает список за время O(N)
  void clear() noexcept {
    if (head_){
      while (head_->next_node) {
        delete std::exchange(head_->next_node, head_->next_node->next_node);
      }
    size_ = 0;
  }
}

// Возвращает итератор, указывающий на позицию перед первым элементом
// односвязного списка. Разыменовывать этот итератор нельзя - попытка
// разыменования приведёт к неопределённому поведению
[[nodiscard]] Iterator
before_begin() noexcept {
  return Iterator(head_);
}

  // Возвращает константный итератор, указывающий на позицию перед первым
  // элементом односвязного списка. Разыменовывать этот итератор нельзя -
  // попытка разыменования приведёт к неопределённому поведению
  [[nodiscard]] ConstIterator cbefore_begin() const noexcept {
    return ConstIterator{const_cast<Node *>(&head_)};
  }

  // Возвращает константный итератор, указывающий на позицию перед первым
  // элементом односвязного списка. Разыменовывать этот итератор нельзя -
  // попытка разыменования приведёт к неопределённому поведению
  [[nodiscard]] ConstIterator before_begin() const noexcept {
    return cbefore_begin();
  }

  /*
   * Вставляет элемент value после элемента, на который указывает pos.
   * Возвращает итератор на вставленный элемент
   * Если при создании элемента будет выброшено исключение, список останется в
   * прежнем состоянии
   */
  Iterator insert(ConstIterator pos, const Type &value) {
    if (pos.node_) {
      auto &new_node = pos.node_;
      new_node->next_node = new Node(value, new_node->next_node);
      ++size_;
      return Iterator{new_node->next_node};
    } else {
      return Iterator(nullptr);
    }
  }

  void pop_front() noexcept {
    if (size_ != 0) {
      delete std::exchange(head_->next_node, head_->next_node->next_node);
      --size_;
    }
  }

  /*
   * Удаляет элемент, следующий за pos.
   * Возвращает итератор на элемент, следующий за удалённым
   */
  Iterator erase(ConstIterator pos) noexcept {
    if (pos.node_ && pos.node_->next_node) {
      --size_;
      delete std::exchange(pos.node_->next_node,
                           pos.node_->next_node->next_node);
      return Iterator{pos.node_->next_node};
    } else {
      return Iterator(nullptr);
    }
  }

  ~SingleLinkedList() { clear(); }

 private:
  // Фиктивный узел, используется для вставки "перед первым элементом"
  Node *head_;

  Node *end_;

  size_t size_ = 0;
};

template <typename Type>
void swap(SingleLinkedList<Type> &lhs, SingleLinkedList<Type> &rhs) noexcept {
  lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type> &lhs,
                const SingleLinkedList<Type> &rhs) {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type> &lhs,
                const SingleLinkedList<Type> &rhs) {
  return !(lhs == rhs);
}

template <typename Type>
bool operator<(const SingleLinkedList<Type> &lhs,
               const SingleLinkedList<Type> &rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end());
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type> &lhs,
                const SingleLinkedList<Type> &rhs) {
  return lhs < rhs || lhs == rhs;
}

template <typename Type>
bool operator>(const SingleLinkedList<Type> &lhs,
               const SingleLinkedList<Type> &rhs) {
  return rhs < lhs;
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type> &lhs,
                const SingleLinkedList<Type> &rhs) {
  return rhs < lhs || lhs == rhs;
}

}  // namespace single_linked_list
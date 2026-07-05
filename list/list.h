#include <memory>
#include <iterator>
#include <type_traits>

namespace custom_std {
  // std::list underlying implementation uses a doubly linked list for efficient front and back insertion
  template< class T >
  struct node {
    T data_;
    node<T> * next_;
    node<T> * prev_;
  };

  template< class T, class Allocator = std::allocator<T> >
  class list {
    public:
      using value_type      = T;
      using allocator_type  = Allocator;
      using size_type       = std::size_t;
      using difference_type = std::ptrdiff_t;
      using reference       = value_type &;
      using const_reference = value_type const &;
      using pointer         = typename std::allocator_traits<Allocator>::pointer;
      using const_pointer   = pointer const;
      // TODO: implement custom iterator type for this class here
      // using iterator        = some implementation;
      // using const_iterator  = some implementation;

      list() : list(Allocator()) {}
      explicit list( Allocator const & alloc = Allocator() ) : alloc_{alloc} {} 
      explicit list( std::size_t count, const_reference value, 
          Allocator const & alloc = Allocator() ) 
        : alloc_{alloc}, count_{count} {
        for ( auto i{0u}; i < count_; ++i ) {
          // TODO: clean this up alongside the iterator ctor as well...
          // this just seems kinda messy;
          pointer val = alloc_.allocate(sizeof(value_type));
          *val = value;

          if ( i == 0 ) {
            head_.data_ = *val;
            tail_ = head_;
          } else {
            node cur;
            cur.data_ = *val;
            cur.prev_ = &tail_;
            tail_.next_ = &cur;
            tail_ = cur;
          }
        }
      }
      template<class InputIt, 
        typename = std::enable_if_t<!std::is_integral<InputIt>::value> >
      explicit list ( InputIt first, InputIt last, 
          Allocator const & alloc = Allocator() ) : alloc_{alloc} {
        for ( auto i{first}; i != last; ++i ) {
          pointer val = alloc_.allocate(sizeof(value_type));
          *val = *i;

          if ( i == first ) {
            head_.data_ = *val;
            tail_ = head_;
          } else {
            node cur;
            cur.data_ = *val;
            cur.prev_ = &tail_;
            tail_.next_ = &cur;
            tail_ = cur;
          }

          ++count_;
        }
      }
      ~list() { // implement this with the linkedlist 
        node * current = &head_;
        while ( current ) {
          node * next = current->next_;
          delete current;
          current = next;
        }
      }

      list& operator=( const_reference other ) {
        head_  = other.head_;
        tail_  = other.tail_;
        count_ = other.count_;
        return *this;
      }

      list& operator=( list && other ) noexcept {
        if ( this != other ) {
          // TODO: gotta finish this here
        }

        return *this;
      }

      std::size_t size()      { return count_; }
      const_reference front() { return head_.data_; }
      const_reference back()  { return tail_.data_; }

    private:
      allocator_type alloc_;
      std::size_t count_{0};
      node head_;
      node tail_;
  };
}

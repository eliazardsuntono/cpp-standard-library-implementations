#include <memory>
#include <iterator>
#include <type_traits>

namespace custom_std {
  template< class T >
  struct node {
    T * data_;
    T * next_;
    T * prev_;
  };

  template< class T, class Allocator = std::allocator<T> >
  class list {
    public:
      using value_type      = T;
      using node_ptr_type   = std::unique_ptr<node<T>>;
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
          pointer current = head_;
          for ( auto i{0u}; i < count_; ++i ) {
            pointer val = alloc_.allocate(sizeof(value_type));
            *val = value;
            if ( !i ) { // allocate the head
              head_{val, nullptr, nullptr};
            } else {

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
            head_ = std::make_unique<node<T>>(*val, nullptr, nullptr);
            tail_ = std::make_unique<node<T>>(head_);
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
      ~list() {
        // TODO: fix this lol
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

      /*
       * different scenarios:
       * 1. this_->size() < other.size()  => we need to allocate more memory
       * 2. this_->size() > other.size()  => we can continously swap until we get to the end of the other list and then we free the other one
       * 3. this_->size() == other.size() => we can just swap continously
       */ 
      // I can do something clever and go backwards and essentially go backward until we get the thing here 
      list& operator=( list && other ) noexcept {
        if ( this != other ) {
          if (this->size() < other.size()) {
            std::size_t data_left = other.size() - this->size();
            node_ptr_type current = other.tail_;
            while ( current && data_left > 0 ) { // fill the back up and swap the 
                
            }
          }
        }

        return *this;
      }

      list& operator=( std::initializer_list<value_type> ilist );

      std::size_t size()      const { return count_; }
      const_reference front() const { return head_.data_; }
      const_reference back()  const { return tail_.data_; }

    private:
      allocator_type alloc_;
      std::size_t count_{0};
      node head_;
      node tail_;
  };
}

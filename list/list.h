#include <memory>
#include <iterator>
#include <type_traits>

namespace custom_std {
  // std::list underlying implementation uses a doubly linked list for efficient front and back insertion
  template< class T >
  struct doubly_linked_list {
    T data_;
    doubly_linked_list<T> * next_;
    doubly_linked_list<T> * prev_;
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
      using double_ll_type  = doubly_linked_list<value_type>; 
      // TODO: implement custom iterator type for this class here
      // using iterator        = some implementation;
      // using const_iterator  = some implementation;

      list() : list(Allocator()) {}
      explicit list( Allocator const & alloc = Allocator() ) : alloc_{alloc} {} 
      explicit list( std::size_t count, const_reference value, 
          Allocator const & alloc = Allocator() ) 
        : alloc_{alloc}, count_{count} {
        for ( auto i{0u}; i < count_; ++i ) {
          pointer val = alloc_.allocate(sizeof(value_type));
          *val = value;

          if ( i == 0 ) {
            head_.data_ = *val;
            tail_ = head_;
          } else {
            double_ll_type cur;
            cur.data_ = *val;
            cur.prev_ = &tail_;
            tail_.next_ = &cur;
            tail_ = cur;
          }
        }
      }
      template<class InputIt, 
        typename = std::enable_if_t<!std::is_integral<InputIt>::value> >
      explicit list ( InputIt first, InputIt last, Allocator const & alloc = Allocator() );
      ~list() {
      }

      std::size_t size()      { return count_; }
      const_reference front() { return head_.data_; }
      const_reference back()  { return tail_.data_; }

    private:
      allocator_type alloc_;
      std::size_t count_;
      double_ll_type head_;
      double_ll_type tail_;
  };
}

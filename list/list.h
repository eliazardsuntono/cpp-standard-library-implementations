#include <memory>
#include <iterator>

namespace custom_std {
  // std::list underlying implementation uses a doubly linked list for efficient front and back insertion
  template< class T >
  struct doubly_linked_list {
    T data_;
    T * next_;
    T * prev_;
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
      using pointer         = std::allocator_type<Allocator>::pointer;
      using const_pointer   = pointer const;
      // TODO: implement custom iterator type for this class here
      // using iterator        = some implementation;
      // using const_iterator  = some implementation;

      list() : list(Allocator()) {}
      explicit list( Allocator const & alloc = Allocator() ) {

      }
      explicit list( Allocator const & alloc );
      explicit list( std::size_t count, const_reference value, 
          Allocator const & alloc = Allocator() );
      template<class InputIt>
      explicit list ( InputIt first, InputIt last, Allocator const & alloc = Allocator() );
      ~list()=default;
    private:
      doubly_linked_list<value_type> head_;
      doubly_linked_list<value_type> tail_;
      std::size_t size_;
  };
}

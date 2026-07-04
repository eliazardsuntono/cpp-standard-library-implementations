#include <memory>
#include <iterator>

namespace custom_std {
  // std::list underlying implementation uses a doubly linked list for efficient front and back insertion
  template< class T >
  struct doubly_linked_list {
    T * data_ = nullptr;
    T * next_ = nullptr;
    T * prev_ = nullptr;
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
      using pointer         = std::allocator_traits<Allocator>::pointer;
      using const_pointer   = pointer const;
      // TODO: implement custom iterator type for this class here
      // using iterator        = some implementation;
      // using const_iterator  = some implementation;

      list() : list(Allocator()) {}
      explicit list( Allocator const & alloc = Allocator() ) : alloc_{alloc} {} 
      explicit list( Allocator const & alloc ) : alloc_{alloc} {}
      explicit list( std::size_t count, const_reference value, 
          Allocator const & alloc = Allocator() ) : count_(count), alloc_(alloc) {
        for ( auto i{0u}; i < count_; ++i ) {
          pointer val = alloc_.allocate(sizeof(value_type));
          if ( !head ) {
            head->data_ = val;
            tail->data_ = val;
          } else {
            tail_->next = val;
            tail_ = val;
          }
        }
      }
      template<class InputIt>
      explicit list ( InputIt first, InputIt last, Allocator const & alloc = Allocator() ) {
        // TODO: could be worth looking into on how to reduce code duplication for this loop here
        for ( auto i{InputIt}; i != lasts; ++i ) {
          pointer val = alloc_.allocate(sizeof(value_type));
          if ( !head ) {
            head_->data_ = val;
            tail_->data_ = val;
          } else {
            tail_->next_ = val;
            tail_->data_ = val;
          }
        }
      }
      ~list()=default; // do I have to define dtor here? 

    private:
      std::allocator alloc_;
      doubly_linked_list<value_type> * head_{nullptr};
      doubly_linked_list<value_type> * tail_{nullptr};
      std::size_t count_;
  };
}

#include <memory>

namespace custom_std {
  template< typename T, typename Allocator = std::allocator<T> >
  class vector {
    public:
      vector() noexcept(noexcept(Allocator)) : vector(Allocator()) {}
      explicit vector( Allocator const & alloc ) noexcept;
      explicit vector( size_t count, T const & val, Allocator const & alloc = Allocator() );
      vector( vector const & other );
      vector( vector && other );
      vector( std::initializer_list<T> init_list, Allocator const & alloc );

      T * const data()    const { return data_; }
      size_t const size() const { return size_; }

    private:
      T * data_;
      size_t size_;
  };
}

#include <iostream>
#include <stdexcept>
#include <memory>
#include <cstddef>
#include <iterator>

namespace custom_std {
  template< typename T, typename Allocator = std::allocator<T> >
  class vector {
    public:
      using value_type             = T;
      using allocator_type         = Allocator;
      using size_type              = std::size_t;
      using difference_type        = std::ptrdiff_t;
      using reference              = value_type &;
      using const_reference        = value_type const &;
      using pointer                = typename std::allocator_traits<Allocator>::pointer;
      using const_pointer          = typename std::allocator_traits<Allocator>::const_pointer;
      // using iterator               =;
      // using const_iterator         =;
      // using reverse_iterator       = std::reverse_iterator<iterator>;
      // using const_reverse_iterator = std::reverse_iterator<const_iterator>

      vector() noexcept(noexcept(Allocator())) : vector(Allocator()) {}
      explicit vector( Allocator const & alloc ) noexcept 
        : alloc_{alloc}, size_{0} {}
      explicit vector( size_t count, T const & val, Allocator const & alloc = Allocator() )
        : alloc_{alloc}, size_{count} {
          data_ = std::allocator_traits<Allocator>::allocate(alloc_, count);
          for ( auto i{0u}; i < count; ++i ) {
            std::allocator_traits<Allocator>::construct(alloc_, data_ + i, val);
          }
        }
      vector( vector const & other ) {
        if ( size_ ) clear();

        data_ = std::allocator_traits<Allocator>::allocate(alloc_, other.size_);
        for ( auto i{0u}; i < other.size_; ++i ) {
          auto const & val = other.data_[i];
          std::allocator_traits<Allocator>::construct(alloc_, data_ + i, val);
        }
      }
      vector( vector && other ) {
        data_       = other.data_;
        size_       = other.size_;
        alloc_      = std::move(other.alloc_);
        other.data_ = nullptr;
        other.size_ = 0;
      }
      vector( std::initializer_list<T> init_list, Allocator const & alloc = Allocator() ) 
        : alloc_{alloc}, size_{init_list.size()} {
          data_ = std::allocator_traits<Allocator>::allocate(alloc_, size_);
          auto idx{0u}; 
          for ( auto const & val : init_list ) {
            std::allocator_traits<Allocator>::construct(alloc_, data_ + idx, val);  
            ++idx; 
          }
        }
      ~vector() { clear(); }

      reference at( size_type pos ) {
        const_reference val = const_cast<vector const *>(this)->at(pos);
        return const_cast<T &>(val);
      }
      const_reference at( size_type pos ) const {
        if ( pos >= size_ )
          throw std::runtime_error("Position specified > current size");

        return data_[pos];
      }
      reference operator[]( size_type pos ) { return at(pos); }
      const_reference operator[]( size_type pos ) const { return at(pos); }
      reference front() { return at(0); }
      const_reference() front const { at(0); }
      reference back() { return at(size_ - 1); }
      const_reference back() const { return at(size_ - 1); }
      T * const data()    const { return data_; }
      size_t const size() const { return size_; }

      void clear() {
        std::allocator_traits<Allocator>::destroy(alloc_, data_);
      }
      void swap() {

      }

    private:
      allocator_type alloc_;
      size_t size_;
      T * data_;
  };
}

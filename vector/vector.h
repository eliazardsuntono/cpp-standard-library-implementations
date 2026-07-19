#include <iostream>
#include <stdexcept>
#include <memory>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <limits>

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
        : alloc_{alloc}, size_{0}, capacity_{0} {}
      explicit vector( size_t count, T const & val, Allocator const & alloc = Allocator() )
        : alloc_{alloc}, size_{count}, capacity_{count} {
          try {
            data_ = std::allocator_traits<Allocator>::allocate(alloc_, count);
            for ( auto i{0u}; i < count; ++i ) {
              std::allocator_traits<Allocator>::construct(alloc_, data_ + i, val);
            }
          } catch ( std::bad_alloc const & e ) {
            std::cout << "Error in construction: " << e.what() << std::endl;
            throw;
          }
        }
      vector( vector const & other ) {
        try {
          data_ = std::allocator_traits<Allocator>::allocate(alloc_, other.size_);
          for ( auto i{0u}; i < other.size_; ++i ) {
            auto const & val = other.data_[i];
            std::allocator_traits<Allocator>::construct(alloc_, data_ + i, val);
          }
          size_     = other.size_;
          capacity_ = other.capacity_;
        } catch ( std::bad_alloc const & e ) {
          std::cout << "Error in construction: " << e.what() << std::endl;
          throw;
        }
      }
      vector( vector && other ) noexcept {
        data_       = other.data_;
        size_       = other.size_;
        capacity_   = other.capacity_
        alloc_      = std::move(other.alloc_);
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
      }
      vector( std::initializer_list<T> init_list, Allocator const & alloc = Allocator() ) 
        : alloc_{alloc}, size_{init_list.size()}, capacity_{init_list.size()} {
          try { 
            data_ = std::allocator_traits<Allocator>::allocate(alloc_, size_);
            auto idx{0u}; 
            for ( auto const & val : init_list ) {
              std::allocator_traits<Allocator>::construct(alloc_, data_ + idx, val);  
              ++idx; 
            }
          } catch ( std::bad_alloc const & e  ) {
            std::cout << "Error in construction: " << e.what() << std::endl;
            throw;
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
      const_reference front() const { return at(0); }
      reference back() { return at(size_ - 1); }
      const_reference back() const { return at(size_ - 1); }
      T * data() {
        T * const data = const_cast<vector const *>(this)->data(); 
        return const_cast<T *>(data);
      }
      T * const data() const { return data_; }

      bool empty() { return size_ == 0; }
      size_type size() const { return size_; }
      size_type capacity() const { return capacity_; }
      size_type max_size() const noexcept {
        return std::allocator_traits<Allocator>::max_size() / sizeof(value_type);
      }
      void reserve( size_type new_cap ) {
        if ( new_cap <= capacity_ ) return;
        pointer dst = std::allocator_traits<Allocator>::allocate(alloc_, new_cap);
        std::memcpy(data_, dst, size_);
        capacity_ = new_cap;
      }
      size_type capacity() const { return capacity_; }
      void shrink_to_fit() {
        try{
          if ( size_ == capacity_) return;
          pointer dst = std::allocator_traits<Allocator>::allocate(alloc_, size_);
          std::memcpy(dst, data_, size_);
        } catch ( std::bad_alloc const & e ) { // NOTE: if allocation fails, then we just do nothing
          return;
        }
      }

      void clear() {
        std::allocator_traits<Allocator>::destroy(alloc_, data_);
      }
      void swap() {

      }

    private:
      allocator_type alloc_;
      size_type size_;
      size_type capacity_;
      T * data_;
  };
}

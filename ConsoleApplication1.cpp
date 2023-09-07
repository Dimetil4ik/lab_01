

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <string>
#include <math.h>

template<class C>
struct gfp {

};

template< template<class, class...> class C, class T, class... Types>
struct gfp<C<T, Types...>> {
    typedef T type;
};

void write_to_file(const char* fn, void * const  data, const size_t& size) {
    std::ofstream stream;
    stream.open(fn, std::ios::binary | std::ios::out);
    if (stream.is_open()) {
        stream.write((char*)data, size);
    }
    else throw std::runtime_error("Failed to open the file!\n");
    stream.close(); return;
}

void * read_from_file(const char * fn, size_t * size) {
    std::ifstream stream;
    stream.open(fn, std::ios::binary | std::ios::in | std::ios::ate);
    char * ptr;
    if (stream.is_open()) {
        *size = stream.tellg();
        stream.seekg(0, std::ios::beg);
        ptr = (char*)malloc(*size);
        if (!ptr) throw std::bad_alloc();
        try {
            stream.read(ptr, *size);
        }
        catch (...) {
            free(ptr);
            throw;
        }
    }
    else throw std::runtime_error("Error occured, while reading the file!\n");
    stream.close();
    return ptr;
}

/*void  read_from_file(const char fn) {
    std::ifstream stream;
      stream.open(fn, std::ios::binary | std::ios::in | std::ios::ate);
         char * ptr;
       if(stream.is_open()) {
           size_t size = stream.tellg();
             stream.seekg(0,std::ios::beg);
                ptr = (char*) malloc(size);
                 if(!ptr) throw std::bad_alloc();
              stream.read(ptr,*size);
       } else throw std::runtime_error("Error reading file!\n");
         stream.close();
          return ptr;
}*/

template< class C, typename std::enable_if<std::is_copy_constructible<C>::value&&
    std::is_default_constructible<C>::value, bool>::type = true,
    class T = typename gfp<C>::type >
     /*requires requires(C c, T t) { {c.push_back(std::declval<T>())};
{c.reserve(size_t())}; }*/
  C read_from_file_into_container(const char* fn)
      
{
    size_t size;
    T* ptr;
    C container{};
    ptr = (T*)read_from_file(fn, &size);
    try {
        container.reserve(size);
        for (size_t i = 0; i < size / sizeof(T); ++i) {
            container.push_back(*(ptr + i));
        }
    }
    catch (...) {
        free((char*)ptr);
        throw;
    }
    free((char*)ptr);
    return container;
}

template<class C>
void find_min_and_max(C& container,
      typename C::value_type& min,
         typename C::value_type& max) {
     min = container[0];
       max = container[0];
    for (auto& val : container) {
               if (val > max) max = val;
        else if (val < min) min = val;
    }
}

     template<typename T>
T generateRandomDigitInRangeOf(const T& lower_border,
    const T& upper_border) noexcept {
    return static_cast<T>(((((double)rand()) / RAND_MAX) * 
        (upper_border - lower_border))
        + lower_border);
}

double generateRandomDigitInRangeOf(const double& lower_border,
    const double& upper_border) noexcept {
    return ((((double)rand()) / RAND_MAX) * (upper_border - lower_border))
        + lower_border;
}














#define SCREEN_WIDTH  70
#define stream_input 0


int main()
{





#ifndef stream_input
    srand((unsigned int)time(NULL));
    const size_t array_size = 10000;
    double arr[array_size];
    for (size_t i = 0; i < array_size; ++i)
           arr[i] =
        generateRandomDigitInRangeOf(-15, 15); arr[3] = 36;
    
    write_to_file("data.bin", arr, sizeof(arr));
    auto numbers = read_from_file_into_container<std::vector<double>>("data.bin");
    size_t number_count = array_size;
    size_t bin_count = 35;
#else





        size_t number_count = { 0 };
    std::vector<double> numbers;
    std::cerr << "Enter number count:\n";
    std::cin >> number_count;
    numbers.resize(number_count);
    std::cerr << "Enter values:\n";
    for (size_t i = 0; i < number_count; ++i)
        std::cin >> numbers[i];
    size_t bin_count = { 0 };
    std::cerr << "Enter number of bins:\n";
    std::cin >> bin_count;
#endif

    
     std::vector<size_t> bins(bin_count,0);
    decltype(numbers)::value_type min = 0, max = 0;
    find_min_and_max(numbers, min, max);
    double bin_size = 
        (double)(max - min) /
        (double)bin_count;
    bool found;   
    for (size_t i = 0; i < number_count; ++i) {
        found = false;
           for (size_t j = 0; (j < bin_count - 1) && !found; ++j) {
             auto lower_border = min + (j) * bin_size;
            auto higher_border = lower_border + bin_size; 
            
            if (((numbers[i]) >= lower_border) && ((numbers[i]) < higher_border)) {
               ++bins[j];
                found = true;
            }
        }
           if (!found) { ++bins[bin_count - 1]; }
    }
   
    size_t max_length = bins[0];
    for (size_t i = 1; i < bins.size(); ++i) {
        if (bins[i] > max_length) max_length = bins[i];
    }
    
     size_t length;

     std::cout << "\n"; 
        size_t j;  size_t y = std::to_string(max_length).size();
           std::string t(y, '0');
         std::string* g = &t; // (std::string*) ::operator new(sizeof(std::string(y, '0')));
          
         std::string str1(SCREEN_WIDTH + 2 + 3, '-');
            str1[0] = '+'; 
            while (str1.size() != y + SCREEN_WIDTH + 2 + 3
                ) {
                str1.push_back('-');
            } str1[str1.size() - 1] = '+';
        std::cout << str1<<std::endl;
        for (size_t i = 0; i < bins.size(); ++i) {
        length =  (size_t)(
            (static_cast<double>(SCREEN_WIDTH) * bins[i]) / max_length); 
        new(static_cast<void*>(g)) std::string{ std::move(std::to_string(bins[i])) };
      
         for (; g->size() != y;) {
             g->insert((*g).begin(),' ');
          }       
         std::cout << "| " << *g <<"|";
        for (j = 0; j < length; ++j) {
            std::cout << "*";
        }   for (size_t z = j; z < SCREEN_WIDTH + 1; ++z) {
            std::cout << " ";
        }    std::cout << "|";
        std::cout << std::endl;
         //g->~basic_string();
    } std::cout << str1;
      
    return 0;
}

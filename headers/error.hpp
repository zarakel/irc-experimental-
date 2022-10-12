
# include "headers.hpp"


class errorExcute : public std::exception {

    private:
        const char * _strerror;

    public:
        errorExcute(const char * str) : _strerror(str) {};
        const char * what() const throw() {return _strerror; };
};
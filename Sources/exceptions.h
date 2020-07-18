#ifndef _EXPCEPTION
#define _EXPCEPTION

class exception {
private:
    std::string err_code = "";
public:
    exception(std::string msg) { this->err_code = msg; }

public:
    inline void show_error() { std::cout << err_code; }
};


class IMAGE_NULL_EXCEPTION : public exception {
public:
    IMAGE_NULL_EXCEPTION(std::string msg = "File Is Null Use Another File") : exception(msg) {}
};

class Text_SO_BIG : public exception {
public:
    Text_SO_BIG(std::string msg = "Text Limit Exceeded Exception ") : exception(msg) {}
};


class IMAGE_EXTENSION_ERROR : public exception {
public:
    IMAGE_EXTENSION_ERROR(std::string msg = "Use Image's Extension Like  *.png  ! \n") : exception(msg) {}
};


#endif

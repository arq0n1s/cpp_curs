#include <iostream>
#include <cstring>

// using namespace std;

class MyString {
private:
    char *language;
    bool m_is_person_name;
    char *m_str_content;
public:
    MyString()
    :MyString("","",0)
    {
        std::cout << "> default constructor has called" << std::endl;
    }
    
    MyString(const char *content, const char *lang, bool personal = false):
            m_is_person_name(personal)
        {
            // verificare de null-pointer

            m_str_content = new char[strlen(content)+1];
            strcpy(m_str_content, content);

            language = new char[strlen(lang)+1];
            strcpy(language, lang);

            std::cout << "> parametrized constructor has called" << std::endl;
    }
    
    MyString(const MyString& other)
    : MyString(other.m_str_content, other.language, other.m_is_person_name)
    {
        std::cout << "> copy constructor has called" << std::endl;
    }

    bool is_empty(){
        bool check;

        if(this->m_str_content == nullptr){
            check = true;
            std::cout << "this string is empty" << std::endl;
        }
        else{
            check = length() > 0;
            std::cout << "this string doesn't empty" << std::endl;
        }
        return check;
    }

    size_t length(){
        return strlen(this->m_str_content);
    }

    const char* c_str(){
        return m_str_content;
    }

    void concat(const char *str){
        char *concat_str = new char[strlen(m_str_content)+strlen(str)];
        strcat(concat_str,m_str_content);
        strcat(concat_str,str);
        delete[] m_str_content;
        m_str_content = concat_str;
        std::cout << "concatenated strings: " << concat_str << std::endl;
    }



    ~MyString(){
        delete[] m_str_content;
        delete[] language;

        std::cout << "destructor has called" << std::endl;
    }

};


int main (){
    

    MyString SecondString;
    std::cout << "second string ieyt" << std::endl;
    SecondString.is_empty();

    MyString ThreeString("Vitalii", "moldavian", true);
    std::cout << "three string ieyt" << std::endl;
    ThreeString.is_empty();
    std::cout << "length of three string: " << ThreeString.length() << std::endl;

    MyString newString = ThreeString;
    std::cout << "the string from newString is: " << newString.c_str() << std::endl;

    char newstr;
    std::cout << "get ur new string: ";
    std::cin >> newstr;





}
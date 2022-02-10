#include "hawk.hpp"

namespace HAWK{
TYPE::TYPE(){
    m_type=TYPE_NONE;
}
TYPE::TYPE(num number){
    m_type=TYPE_NUM;
    m_number=number;
}
TYPE::TYPE(std::string str){
    m_type=TYPE_STR;
    m_str=str;
}
TYPE::TYPE(std::vector<TYPE> label){
    m_type=TYPE_LABEL;
    m_label=label;
}
curr_type TYPE::get_type(){
    return m_type;
}
num TYPE::get_num(){
    return m_number;
}
std::string TYPE::get_str(){
    return m_str;
}
std::vector<TYPE> TYPE::get_label(){
    return m_label;
}
TYPE TYPE::operator+(TYPE other){
    if(m_type==TYPE_NUM){
        return m_number+other.m_number;
    }
    else if(m_type==TYPE_STR){
        return m_str+other.get_str();
    }
    return TYPE();
}
TYPE TYPE::operator-(TYPE other){
    return m_number-other.m_number;
}
TYPE TYPE::operator*(TYPE other){
    return m_number*other.m_number;
}
TYPE TYPE::operator/(TYPE other){
    return m_number/other.m_number;
}
TYPE TYPE::operator%(TYPE other){
    return (int64_t)m_number%(int64_t)other.m_number;
}
TYPE TYPE::operator^(TYPE other){
    return (int64_t)m_number^(int64_t)other.m_number;
}
TYPE TYPE::operator==(TYPE other){
    auto x=other.get_type();
    if (m_type==x){
        if(x==TYPE_STR){
            return m_str==other.get_str();
        }
        else if(x==TYPE_NUM){
            return m_number==other.get_num();
        }
        else if(x==TYPE_LABEL){
            auto x=other.get_label();
            if(m_label.size()==x.size()){
                for (size_t i=0;i<m_label.size();++i){
                    if(!(x[i]==m_label[i]).get_num()){
                        return 0;
                    }
                }
                return 1;
            }
            return 0;
        }
        return 1;//it is none 
    }
    return 0;
}
TYPE TYPE::operator!=(TYPE other){
    return !(*this==other);
}
TYPE TYPE::operator<(TYPE other){
    return m_number<other.m_number;
}
TYPE TYPE::operator>(TYPE other){
    return m_number>other.m_number;
}
TYPE TYPE::operator<=(TYPE other){
    return m_number<=other.m_number;
}
TYPE TYPE::operator>=(TYPE other){
    return m_number>=other.m_number;
}
TYPE TYPE::operator&&(TYPE other){
    return (bool)m_number&&(bool)other.m_number;
}
TYPE TYPE::operator||(TYPE other){
    return (bool)m_number||(bool)other.m_number;
}
TYPE TYPE::operator!(){
    return !(bool)m_number;
}
TYPE TYPE::operator&(TYPE other){
    return (int64_t)m_number&(int64_t)other.m_number;
}
TYPE TYPE::operator|(TYPE other){
    return (int64_t)m_number|(int64_t)other.m_number;
}
TYPE TYPE::operator~(){
    return ~(int64_t)m_number;
}
TYPE TYPE::operator<<(TYPE other){
    return (int64_t)m_number<<(int64_t)other.m_number;
}
TYPE TYPE::operator>>(TYPE other){
    return (int64_t)m_number>>(int64_t)other.m_number;
}
TYPE TYPE::operator-(){
    return -m_number;
}
}
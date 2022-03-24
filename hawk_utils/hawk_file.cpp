#include "../include/hawk_file.hpp"
#include <fstream>
#include <iostream>
#include <cstdint>
namespace HAWK_VM{
HAWK_FILE::HAWK_FILE(HawkType* code ,size_t size,std::string filename){
    m_filename=filename;
    m_code=code;
    m_size=size;
}
HAWK_FILE::HAWK_FILE(std::string filename){
    m_filename=filename;
}
void HAWK_FILE::write(){
    write(m_code,m_size,m_filename);
}
HawkType* HAWK_FILE::read(){
    return read(m_filename);
}
void HAWK_FILE::write(HawkType* code,size_t size,std::string filename){
    m_output_file=std::ofstream(filename, std::ios::binary);
    m_output_file.write(reinterpret_cast<char*>(&size), sizeof(size));
    write(code,size);
    m_output_file.close();
}
void HAWK_FILE::write(HawkType* code,size_t size){
    for(size_t i=0;i<size;i++){
        m_output_file.write(reinterpret_cast<char*>(&code[i].type), sizeof(code[i].type));
        if(code[i].type==TYPE_NUM||code[i].type==TYPE_OP){
            m_output_file.write(reinterpret_cast<char*>(&code[i].number), sizeof(code[i].number));
        }
        else if(code[i].type==TYPE_ARRAY||code[i].type==TYPE_STR||code[i].type==TYPE_LABEL){
            m_output_file.write(reinterpret_cast<char*>(&code[i].size), sizeof(code[i].size));
            write(code[i].array,code[i].size);
        }
    }
}
HawkType* HAWK_FILE::read(std::string filename){ 
    m_read_file=std::ifstream(filename, std::ios::binary);
    m_read_file.read(reinterpret_cast<char*>(&m_size), sizeof(m_size));
    m_code=NULL;
    m_code=(HawkType*)malloc(m_size*sizeof(HawkType));
    read(m_code,m_size);
    m_read_file.close(); 
    return m_code;
}
void HAWK_FILE::read(HawkType* code,size_t size){
    for(size_t i=0;i<size;i++){
        m_read_file.read(reinterpret_cast<char*>(&code[i].type), sizeof(code[i].type));
        if(code[i].type==TYPE_NUM||code[i].type==TYPE_OP){
            m_read_file.read(reinterpret_cast<char*>(&code[i].number), sizeof(code[i].number));
        }
        else if(code[i].type==TYPE_ARRAY||code[i].type==TYPE_STR||code[i].type==TYPE_LABEL){
            m_read_file.read(reinterpret_cast<char*>(&code[i].size), sizeof(code[i].size));
            code[i].array=(HawkType*)malloc(code[i].size*sizeof(HawkType));
            read(code[i].array,code[i].size);
            to_clear.push_back(&code[i].array);
        }
    }
}
void HAWK_FILE::clean_up(){
    if(m_code!=NULL){
        for(auto&i:to_clear){
            if((*i)!=NULL) {
                free(*i);
                *i=NULL;
            }
        }
        free(m_code);
        m_code=NULL;
    }
}
}

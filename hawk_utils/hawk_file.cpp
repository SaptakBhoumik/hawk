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
    m_output_file.write(reinterpret_cast<char*>(&size), sizeof(size_t));
    write(code,size);
    m_output_file.close();
}
void HAWK_FILE::write(HawkType* code,size_t size){
    for(size_t i=0;i<size;i++){
        m_output_file.write(reinterpret_cast<char*>(&code[i].type), sizeof(num));
        if(code[i].type==TYPE_NUM){
            m_output_file.write(reinterpret_cast<char*>(&code[i].number), sizeof(num));
        }
        else if(code[i].type==TYPE_OP){
            m_output_file.write(reinterpret_cast<char*>(&code[i].number), sizeof(num));
        }
        else if(code[i].type==TYPE_LABEL){
            m_output_file.write(reinterpret_cast<char*>(&code[i].size), sizeof(num));
            write(code[i].array,code[i].size);
        }
        else if(code[i].type==TYPE_ARRAY){
            m_output_file.write(reinterpret_cast<char*>(&code[i].size), sizeof(num));
            write(code[i].array,code[i].size);
        }
    }
}
HawkType* HAWK_FILE::read(std::string filename){ 
    m_read_file=std::ifstream(filename, std::ios::binary);
    m_read_file.read(reinterpret_cast<char*>(&m_size), sizeof(size_t));
    m_code=NULL;
    m_code=(HawkType*)malloc(m_size*sizeof(HawkType));
    read(m_code,m_size);
    m_read_file.close(); 
    return m_code;
}
void HAWK_FILE::read(HawkType* code,size_t size){
    for(size_t i=0;i<size;i++){
        m_read_file.read(reinterpret_cast<char*>(&code[i].type), sizeof(num));
        if(code[i].type==TYPE_NUM){
            m_read_file.read(reinterpret_cast<char*>(&code[i].number), sizeof(num));
        }
        else if(code[i].type==TYPE_OP){
            m_read_file.read(reinterpret_cast<char*>(&code[i].number), sizeof(num));       
        }
        else if(code[i].type==TYPE_LABEL){
            m_read_file.read(reinterpret_cast<char*>(&code[i].size), sizeof(num));
            to_clear.push_back(i);
            code[i].array=(HawkType*)malloc(code[i].size*sizeof(HawkType));
            read(code[i].array,code[i].size);
        }
        else if(code[i].type==TYPE_ARRAY){
            m_read_file.read(reinterpret_cast<char*>(&code[i].size), sizeof(num));
            to_clear.push_back(i);
            code[i].array=(HawkType*)malloc(code[i].size*sizeof(HawkType));
            read(code[i].array,code[i].size);
        }
    }
}
void HAWK_FILE::clean_up(){
    if(m_code!=NULL){
        for(auto&i:to_clear){
            if(m_code[i].array!=NULL) {
                free(m_code[i].array);
                m_code[i].array=NULL;
            }
        }
        free(m_code);
        m_code=NULL;
    }
}
}

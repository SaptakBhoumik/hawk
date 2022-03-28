#include "../include/hawk_file.hpp"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <bits/stdc++.h>
//TODO: endianness
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
    if(!m_output_file){
        std::cout<<"Error opening file: "<<filename<<"\n";
        exit(1);
    }
    m_output_file.write(reinterpret_cast<char*>(&size), sizeof(size));
    write(code,size);
    m_output_file.close();
}
void HAWK_FILE::write(HawkType* code,size_t size){
    // std::reverse_copy(code,code+size,m_output_file);
    for(size_t i=0;i<size;i++){
        char type=code[i].type;
        m_output_file.write(reinterpret_cast<char*>(&type), sizeof(type));
        if(code[i].type==TYPE_NUM){
            m_output_file.write(reinterpret_cast<char*>(&code[i].number), sizeof(code[i].number));
        }
        else if(code[i].type==TYPE_OP){
            char op= (char)code[i].number;
            m_output_file.write(reinterpret_cast<char*>(&op), sizeof(op));
        }
        else if(code[i].type==TYPE_STR){
            m_output_file.write(reinterpret_cast<char*>(&code[i].size), sizeof(code[i].size));
            for(size_t j=0;j<code[i].size;++j){
                char res=code[i].ptr[j].number;
                m_output_file.write(reinterpret_cast<char*>(&res), sizeof(res));
            }
        }
        else if(code[i].type==TYPE_ARRAY||code[i].type==TYPE_LABEL){
            m_output_file.write(reinterpret_cast<char*>(&code[i].size), sizeof(code[i].size));
            write(code[i].ptr,code[i].size);
        }
    }
}
HawkType* HAWK_FILE::read(std::string filename){ 
    m_read_file=std::ifstream(filename, std::ios::binary);
    if(!m_read_file){
        std::cout<<"Error opening file: "<<filename<<"\n";
        exit(1);
    }
    m_read_file.read(reinterpret_cast<char*>(&m_size), sizeof(m_size));
    m_code=NULL;
    m_code=(HawkType*)malloc(m_size*sizeof(HawkType));
    read(m_code,m_size);
    m_read_file.close(); 
    return m_code;
}
void HAWK_FILE::read(HawkType* code,size_t size){
    for(size_t i=0;i<size;i++){
        char type=0;
        m_read_file.read(reinterpret_cast<char*>(&type), sizeof(type));
        code[i].type=(curr_type)type;
        if(code[i].type==TYPE_NUM){
            m_read_file.read(reinterpret_cast<char*>(&code[i].number), sizeof(code[i].number));
        }
        else if(code[i].type==TYPE_OP){
            char op=0;
            m_read_file.read(reinterpret_cast<char*>(&op), sizeof(op));
            code[i].number=op;
        }
        else if(code[i].type==TYPE_STR){
            m_read_file.read(reinterpret_cast<char*>(&code[i].size), sizeof(code[i].size));
            code[i].ptr=(HawkType*)malloc(code[i].size*sizeof(HawkType));
            for(size_t j=0;j<code[i].size;++j){
                char res=0;
                m_read_file.read(reinterpret_cast<char*>(&res), sizeof(res));
                code[i].ptr[j]=(HawkType){.type=TYPE_NUM ,.number=(num)res};
            }
        }
        else if(code[i].type==TYPE_ARRAY||code[i].type==TYPE_LABEL){
            m_read_file.read(reinterpret_cast<char*>(&code[i].size), sizeof(code[i].size));
            code[i].ptr=(HawkType*)malloc(code[i].size*sizeof(HawkType));
            read(code[i].ptr,code[i].size);
            to_clear.push_back(&code[i].ptr);
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

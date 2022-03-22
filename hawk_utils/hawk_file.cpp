#include "../include/hawk_file.hpp"
#include <fstream>
#include <iostream>
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
    write(code,size);
    m_output_file.close();
}
void HAWK_FILE::write(HawkType* code,size_t size){
    m_output_file.write(reinterpret_cast<char*>(&size), sizeof(size_t));
    for(size_t i=0;i<size;i++){
        m_output_file.write(reinterpret_cast<char*>(&code[i].type), sizeof(curr_type));
        if(code[i].type==TYPE_NUM){
            m_output_file.write(reinterpret_cast<char*>(&code[i].number), sizeof(num));
        }
        else if(code[i].type==TYPE_OP){
            m_output_file.write(reinterpret_cast<char*>(&code[i].number), sizeof(short));
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
    HawkType* code;
    m_read_file=std::ifstream(filename, std::ios::binary);
    m_read_file.read(reinterpret_cast<char*>(&m_size), sizeof(size_t));
    code=new HawkType[m_size];
    read(code,m_size);
    m_read_file.close(); 
    return code;
}
void HAWK_FILE::read(HawkType* code,size_t size){
    for(size_t i=0;i<size;i++){
        m_read_file.read(reinterpret_cast<char*>(&code[i].type), sizeof(curr_type));
        if(code[i].type==TYPE_NUM){
            m_read_file.read(reinterpret_cast<char*>(&code[i].number), sizeof(num));
        }
        else if(code[i].type==TYPE_OP){
            m_read_file.read(reinterpret_cast<char*>(&code[i].number), sizeof(short));
        }
        else if(code[i].type==TYPE_LABEL){
            m_read_file.read(reinterpret_cast<char*>(&code[i].size), sizeof(num));
            code[i].array=new HawkType[code[i].size];
            read(code[i].array,code[i].size);
        }
        else if(code[i].type==TYPE_ARRAY){
            m_read_file.read(reinterpret_cast<char*>(&code[i].size), sizeof(num));
            code[i].array=new HawkType[code[i].size];
            read(code[i].array,code[i].size);
        }
    }
}
}
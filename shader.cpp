#include "shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

ShaderProgramSource shader::ParseShader(const std::string& filepath){


	std::ifstream shaderFile(filepath);
	std::string line;
	std::stringstream ss[2];
	 
	int type= 0; //initialize

	//get content from shader file
	while(getline(shaderFile,line)){
		if (line.find("#Shader")!=std::string::npos){
			if(line.find("vertex")!=std::string::npos){
				type = 0;
			}//set mode to vertex
			else if (line.find("fragment")!=std::string::npos){
				type= 1;
			}//set mode to fragment
		}
		else
		{
			ss[type]<<line<<'\n';
		}
	}
	return {ss[0].str(),ss[1].str()};
}

unsigned int shader::CompileShader(unsigned int type,const std::string& source){

	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id,1,&src,nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id,GL_COMPILE_STATUS,&result);

	if(result == GL_FALSE){
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length*sizeof(char));

		glGetShaderInfoLog(id, length, &length, message);
        std::cout<<"Failed to compile "<<(type==GL_VERTEX_SHADER?"vertex":"fragment") << " shader!\n";
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;
	}

	return id;
}

unsigned int shader::CreateShader(const std::string& vertexShader,const std::string& fragmentShader){

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

	glAttachShader(program,vs);
	glAttachShader(program,fs);
	glLinkProgram(program);
	glValidateProgram(program);

	return program;

}

shader::shader(const std::string& filepath)
	:FilePath(filepath),RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	RendererID = CreateShader(source.VertexSource,source.FragmentSource);	

}
shader::~shader(){
	glDeleteProgram(RendererID);
}
void shader::Bind() const{
	glUseProgram(RendererID);
}
void shader::Unbind() const{
	glUseProgram(0);
}


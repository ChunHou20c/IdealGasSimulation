#pragma once
#include <string>


//source code of the shader
struct ShaderProgramSource{
	std::string VertexSource;
	std::string FragmentSource;
};

class shader{

private:
	std::string FilePath;//file path of the source
	unsigned int RendererID;//program ID

//functions
private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader,const std::string& fragmentShader);

public:
	ShaderProgramSource ParseShader(const std::string&filepath);
	shader(const std::string& filepath);
	~shader();
	void Bind() const;//use shader
	void Unbind() const;

};

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include<fstream>
#include <vector>

using namespace std;

std::string readFile(const std::string& file_name)
{
    ifstream f;
    f.open(file_name);

    if (!f.is_open()) {
        cout << "unable to open file: " << file_name << std::endl << "Press any key to exit ...";
        getchar();
        exit(1);
    }

    string s;
    s.assign((std::istreambuf_iterator<char>(f)),
        (std::istreambuf_iterator<char>()));
    f.close();
    return s;
}

GLuint loadshaders(const char* v_file, const char* f_file)
{
    GLuint v_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint f_id = glCreateShader(GL_FRAGMENT_SHADER);

    string v_code = readFile(v_file);
    const char* v = v_code.c_str();
    glShaderSource(v_id,1,&v,NULL);
    glCompileShader(v_id);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    glGetShaderiv(v_id, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(v_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength>0)
    {
        std::vector<char> v_error_message(InfoLogLength + 1);
        glGetShaderInfoLog(v_id, InfoLogLength, NULL, &v_error_message[0]);
        printf("%s\n", &v_error_message[0]);
    }

    string f_code = readFile(f_file);
    const char* f = f_code.c_str();
    glShaderSource(f_id, 1, &f, NULL);
    glCompileShader(f_id);

    glGetShaderiv(f_id, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(f_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength>0)
    {
        std::vector<char> f_error_message(InfoLogLength + 1);
        glGetShaderInfoLog(f_id, InfoLogLength, NULL, &f_error_message[0]);
        printf("%s\n", &f_error_message[0]);
    }

    GLuint prg_ID = glCreateProgram();
    glAttachShader(prg_ID, v_id);
    glAttachShader(prg_ID, f_id);
    glLinkProgram(prg_ID);

    glGetProgramiv(prg_ID, GL_LINK_STATUS, &Result);
    glGetProgramiv(prg_ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength>0)
    {
        vector<char> p_error_message(InfoLogLength + 1);
        glGetProgramInfoLog(prg_ID, InfoLogLength, NULL, &p_error_message[0]);
        printf("%s\n", &p_error_message[0]);
    }

    glDetachShader(prg_ID, v_id);
    glDetachShader(prg_ID, f_id);

    glDeleteShader(v_id);
    glDeleteShader(f_id);

    return prg_ID;
}

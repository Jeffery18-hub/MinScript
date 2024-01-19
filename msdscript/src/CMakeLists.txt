# 添加源文件
set(SOURCES
        main.cpp
        cmdline.cpp
        cmdline.hpp
        exec.cpp
        exec.h
        expr.cpp
        expr.hpp
        parse.cpp
        parse.hpp
        val.cpp val.h pointer.h Env.cpp Env.h)

# 生成可执行文件
add_executable(msdscript ${SOURCES})

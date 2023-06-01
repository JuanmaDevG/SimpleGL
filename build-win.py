######################################################################################################################
#This build file automatically manages:
#
#-> The dependencies in this order: (ninja wrapper for python) (build.ninja file cosntruction) (compilation with ninja)
# (test compilation and run) (automated .obj file cleanup)
#
#-> Make a useful info log about ninja and it's compile and clean options
#
######################################################################################################################
from ninja import Writer
from enum import Enum

COMPILE = "clang++"
OPTIONS = " -Wall -Wextra -Werror -O3"
HEADER_DIR = ".\\include\\"
SOURCE_DIR = ".\\src\\"
BUILD_DIR = ".\\build\\"
OBJ_DIR = BUILD_DIR + "obj\\"
OBJECTS = ["VBO", "EBO", "VAO", "Shader"]
LIB_NAME = "simpleGL.lib"

#External includes
DEPENDENCIES = ["glew32s"] #.lib or .dll files needed
EXTERNAL_BIN_DIR = SOURCE_DIR + "external\\"

#############################
#         BUILT INS         #
#############################
DEP_STR = "".join(map(lambda x: " " + x + ".lib", DEPENDENCIES))
SRC_LIST = list(map(lambda x: SOURCE_DIR + x + ".cpp", OBJECTS))
OBJ_LIST = list(map(lambda x: OBJ_DIR + x + ".obj", OBJECTS))
OBJ_STR = " ".join(OBJ_LIST)

class Rule(Enum):
    compile_obj = "compile_obj"
    vertex_array = OBJECTS[2]
    link = "link"

DEPENDENCIES = {
    OBJECTS[2]:" ".join(OBJ_LIST[0], OBJ_LIST[1])
}

RULES = {
    Rule.compile_obj:COMPILE + OPTIONS + " -I" + HEADER_DIR + " -o $out -c $in",
    Rule.vertex_array:COMPILE + OPTIONS + " -I" + HEADER_DIR + " -L" + OBJ_DIR + " -o $out -c $in",
    Rule.link:"llvm-lib /OUT:$out " + OBJ_STR + " /LIBPATH:" + EXTERNAL_BIN_DIR + DEP_STR
}



if __name__ == "__main__":
    buildMaker = Writer(open("build.ninja", 'w',encoding='utf8'))

    #Rule writing
    for rule_id in RULES:
        buildMaker.rule\
        (
            rule_id.value, RULES[rule_id]
        )
        buildMaker.newline()

    #Build targets
    for obj in OBJ_LIST:
        buildMaker.build(obj, Rule.compile_obj.value, SRC_LIST[OBJ_LIST.index(obj)])
        buildMaker.newline()

    #Link phase
    buildMaker.build(BUILD_DIR + LIB_NAME, Rule.link.value)   

    buildMaker.close()
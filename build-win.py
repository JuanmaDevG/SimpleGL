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
OPTIONS = " -Wall -Wextra -O3"
HEADER_DIR = "include\\"
SOURCE_DIR = "src\\"
BUILD_DIR = "build\\"
OBJ_DIR = BUILD_DIR + "obj\\"
OBJECTS = ["VBO", "EBO", "VAO", "Shader"]
LIB_NAME = "simpleGL.lib"

#External includes
DEPENDENCIES = ["opengl32", "glew32s"] #.lib or .dll files
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
    link = "link"

RULES = {
    Rule.compile_obj:COMPILE + OPTIONS + " -I" + HEADER_DIR + " -c -o $out $in",
    Rule.link:"llvm-lib /OUT:$out " + OBJ_STR + " /LIBPATH:" + EXTERNAL_BIN_DIR + DEP_STR
}

OBJ_WITH_DEPS = {
    OBJ_LIST[2]:SRC_LIST[:2]
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
        if obj in OBJ_WITH_DEPS:
            local_deps = OBJ_WITH_DEPS[obj]
        else:
            local_deps = None
        buildMaker.build(obj, Rule.compile_obj.value, SRC_LIST[OBJ_LIST.index(obj)],implicit=local_deps)
        buildMaker.newline()

    #Link phase
    buildMaker.build(BUILD_DIR + LIB_NAME, Rule.link.value, implicit=OBJ_LIST)
    buildMaker.close()
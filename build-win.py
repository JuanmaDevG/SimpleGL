######################################################################################################################
#This build file automatically manages:
#
#-> The dependencies in this order: (ninja wrapper for python) (build.ninja file cosntruction) (compilation with ninja)
# (test compilation and run) (automated .obj file cleanup)
#
#-> Make a useful info log about ninja and it's compile and clean options
#
######################################################################################################################
import sys
import os

from ninja import Writer
from enum import Enum

COMPILE = "clang++"
OPTIONS = " -Wall -Werror -Wno-undef -Wno-undefined-inline -Wextra -O3" #No needed linker to just compile obj files
HEADER_DIR = "include\\"
SOURCE_DIR = "src\\"
BUILD_DIR = "build\\"
OBJ_DIR = BUILD_DIR + "obj\\"
OBJECTS = ["VBO", "EBO", "VAO", "Shader"]
LIB_NAME = "SimpleGL"

DEPENDENCIES = ["glew32s"] #.lib or .dll files
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


def makeRules(buildMaker: Writer):
    for rule_id in RULES:
        buildMaker.rule\
        (
            rule_id.value, RULES[rule_id]
        )
        buildMaker.newline()

def makeObjBuilds(buildMaker: Writer):
    for obj in OBJ_LIST:
        if obj in OBJ_WITH_DEPS:
            local_deps = OBJ_WITH_DEPS[obj]
        else:
            local_deps = None
        buildMaker.build(obj, Rule.compile_obj.value, SRC_LIST[OBJ_LIST.index(obj)],implicit=local_deps)
        buildMaker.newline()

def makeLinkBuild(buildMaker: Writer):
    buildMaker.build(BUILD_DIR + LIB_NAME + ".lib", Rule.link.value, implicit=OBJ_LIST)

def make_ninja():
    print("Making build.ninja file")

    #BuildMaker needs a TextIOWrapper to work
    buildMaker = Writer(open("build.ninja", 'w',encoding='utf8'))

    makeRules(buildMaker)
    makeObjBuilds(buildMaker)
    makeLinkBuild(buildMaker)

    buildMaker.close()

TESTS = ["VBO_01", "EBO_01", "VAO_01"]
def execute_tests():
    print("Compiling library...")
    os.system("ninja")

    for test in TESTS:
        print("Test: " + test)
        os.system(
            COMPILE + " -I" + HEADER_DIR + " -L" + BUILD_DIR 
            + " -l" + LIB_NAME + " -lopengl32" 
            + " -o test.exe test\\test_" + test + ".cpp"
        )
        os.system("test")
        os.system("del test")



#Option handling is very simple because nothing more needed
if __name__ == "__main__":
    print("-----------------------")
    print("Build file for SimpleGL")
    print("-----------------------", end="\n\n")

    make_ninja()

    if sys.argv.count("-t") > 0:
        execute_tests()
    
    if sys.argv.count("-c") > 0 or sys.argv.count("--clean") > 0:
        os.system("ninja -t clean")
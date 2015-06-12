#!/bin/bash
#$1 = destination
#$2 = problem name
#$3 -> 0 = stdin 1 = file

problemLocation=$1
problemName=$2

problemFileOutput=$3
problemInputFile=""
problemOutputFile=""

if [ "${problemFileOutput}" == "1" ]; then
    problemInputFile=$4
    if [ "${problemInputFile}" == "" ]; then
        problemInputFile="${problemName}.in"
    fi

    problemOutputFile=$5
    if [ "${problemOutputFile}" == "" ]; then
        problemOutputFile="${problemName}.out"
    fi   
fi

function write {
    echo -e $1 >> $problemLocation
}

if [ -a $problemLocation ]; then
    echo "Fisierul ${problemLocation} exista deja"
else
    touch $problemLocation
    echo "Fisierul ${problemLocation} creat cu succes"

    creationTime=$(date +"%d-%m-%Y")
    write "//Problem ${problemName} @ ${creationTime}"
    write "#include <algorithm>"

    if [ $problemFileOutput == 1 ]; then
        write "#include <fstream>"
    fi

    write "#include <iostream>"
    write "#include <vector>"
    write "#include <queue>"
    write "using namespace std;"
    write ""
    write "const int inf = 0x3f3f3f3f, kMaxN = 0;"
    write "const double eps = 1e-7;"
    write ""
    write "#define int64 long long"
    write ""

    if [ $problemFileOutput == 1 ]; then
        write "ifstream fin(\"${problemInputFile}\");"
        write "ofstream fout(\"${problemOutputFile}\");"
        write ""
    fi
    
    write "int main() {"

    if [ $problemFileOutput == 0 ]; then
        write "\tios::sync_with_stdio(false);"
    fi
    
    write ""
    write "\treturn 0;"
    write "}"

fi

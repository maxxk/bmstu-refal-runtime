#!/bin/bash
#Run from build directory

TestsDir="../Tests"
TmpRefSourceFile="source.ref"
TmpCSourceFile="source.c"
RealOutputFile="output.txt"

red='\e[0;31m'
green='\e[0;32m'
NC='\e[0m' # No Color

function AssertSuccess
{
	if [ "$?" != 0 ] ; then
		echo -e "${red}[FAIL] $1${NC}"		
	fi
}

#Собираем библиотеку рантайма.
cd ../Runtime/build 
make 1>/dev/null 
AssertSuccess "Runtime-build error" 
cd - 1>/dev/null

#Компилируем компилятор! В итоге получаем исполняемый файл refalc, который кладется в папку, прописанную в переменной PATH.
go install -compiler gccgo ${GOPATH}/src/BMSTU-Refal-Compiler/refalc/refalc.go 
AssertSuccess "Can't build compiler"

if [ ! -z "$1" ]; then 
	TestsDir="$1"
fi

for sourceFile in `ls ${TestsDir}/*.ref`
do	
	cp ${sourceFile} ${TmpRefSourceFile}
	#Компилируем рефал программу
	refalc ${TmpRefSourceFile} 1>/dev/null 
	AssertSuccess "Can't compile refal source ${sourceFile}"		
	
	#Собираем весь проект - линкуем сгенерированный файл с библиотекой исполнения.
	cp ${TmpCSourceFile} ../Project/main.c
	cd ../Project/build/ 
	make 1>/dev/null
	AssertSuccess "Can't build project!"
	
	#Запускаем испольняемый файл.
	./Project > ${RealOutputFile}
	AssertSuccess "Bad execuatable file!"
	
	#Проверям ожидаемое с полученным
	cmp -s ${RealOutputFile} ../${sourceFile%.*}.out
	if [ "$?" != 0 ]
	then
		echo -e "${red}[FAIL]: ${sourceFile} ${NC}"		
	else
		echo -e "${green}[OK]: ${sourceFile} ${NC}"		
	fi		

	cd - 1>/dev/null
done

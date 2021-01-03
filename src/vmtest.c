#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "vm.h"

int hello[] = {
	ICONST, 97,
	PRINTC,
	HALT
};

int loop[] = {
// .GLOBALS 2; N, I
// N = 10                      ADDRESS
	ICONST, 10,            // 0
	GSTORE, 0,             // 2
// I = 0
	ICONST, 0,             // 4
	GSTORE, 1,             // 6
// WHILE I<N:
// START (8):
	GLOAD, 1,              // 8
	GLOAD, 0,              // 10
	ILT,                   // 12
	BRF, 24,               // 13
//     I = I + 1
	GLOAD, 1,              // 15
	ICONST, 1,             // 17
	IADD,                  // 19
	GSTORE, 1,             // 20
	BR, 8,                 // 22
// DONE (24):
// PRINT "LOOPED "+N+" TIMES."
	HALT                   // 24
};

const int FACTORIAL_ADDRESS = 0;
int factorial[] = {
//.def factorial: ARGS=1, LOCALS=0	ADDRESS
//	IF N < 2 RETURN 1
	LOAD, 0,                // 0
	ICONST, 2,              // 2
	ILT,                    // 4
	BRF, 10,                // 5
	ICONST, 1,              // 7,
	RET,                    // 9
//CONT:
//	RETURN N * FACT(N-1)
	LOAD, 0,                // 10
	LOAD, 0,                // 12
	ICONST, 1,              // 14
	ISUB,                   // 16
	CALL, 0, 1, 0,    // 17
	IMUL,                   // 21
	RET,                    // 22
//.DEF MAIN: ARGS=0, LOCALS=0
// PRINT FACT(1)
	ICONST, 5,              // 23    <-- MAIN METHOD!
	CALL, 0, 1, 0,    // 25
	PRINT,                  // 29
	HALT                    // 30
};

static int function[] = {
	//								ADDRESS
	//.def main() { print f(10); }
	ICONST, 10,             // 0
	CALL, 8, 1, 1,          // 2
	PRINT,                 // 6
	HALT,                   // 7
	//.def f(x): ARGS=1, LOCALS=1
	//  a = x;
	LOAD, 0,                // 8	<-- start of f
	STORE, 1,
	// return 2*a
	LOAD, 1,
	ICONST, 2,
	IMUL,
	RET
};

static int myfunction[] = {
	//								ADDRESS
	//.def main() { print f(10); }
	ICONST, 10,             // 0
	CALL, 8, 1, 1,          // 2
	PRINT,                 // 6
	HALT,                   // 7
	//.def f(x): ARGS=1, LOCALS=1
	//  a = x;
	LOAD, 0,                // 8	<-- start of f
	STORE, 1,
	// return 2*a
	LOAD, 1,
	ICONST, 2,
	IMUL,
	RET
};

/*
	ICONST, 72,  //H
	ICONST, 101, //e
	ICONST, 108, //l
	ICONST, 108, //l
	ICONST, 111, //o
	ICONST, 97,
	*/
static int displayMensaje[] = {
	//								ADDRESS
	//.def main() { print f("hello"); }
	ICONST, 72,              // 0
	ICONST, 101,             // 2
	ICONST, 108,
	ICONST, 108,
	ICONST, 111,   
	CALL, 16, 5, 0,          // 6
	PRINTC,                  // 8
	HALT,                    // 9
	//.def f(x): ARGS=1, LOCALS=1
	LOAD, 0,                 // 10	<-- start of f
	STORE, 0,
	LOAD, 1,
	LOAD, 0,                 // 10	<-- start of f
	STORE, 1,
	LOAD, 1,
	RET
};

static int readcharandEcho[] = {
	READ, 
	PRINTC, 
	HALT
};

int mensaje[] = {
	//ICONST, 4,
	//ICONST, 'h',
	//Icadenas, 'hola' 0 "hola", 
	ICONST, 'H',
	//PRINTC,
	ICONST,  'o',
	//PRINTC,
	ICONST, 'l',
	//PRINTC,
    ICONST, 'a',
	ICONST, 4,
	PRINTC,
	//ICONST, 11,
	//PRINTC,
	HALT
};

int main(int argc, char *argv[]) {
	VM *vm;

	// printf("\nfunction Test\n");	
	// vm = vm_create(function, sizeof(function), 0);
	// vm_exec(vm, 0, true);
	// vm_free(vm);

	// printf("\nDisplayMensaje Test\n");	
	// vm = vm_create(displayMensaje, sizeof(displayMensaje), 0);
	// vm_exec(vm, 0, true);
	// vm_free(vm);



	printf("Mensaje Test:\n");
	vm = vm_create(mensaje, sizeof(mensaje), 0);
	vm_exec(vm, 0, true);
	vm_free(vm);
	
	// printf("\t \n Read and Echo char Test:\n");
	// vm = vm_create(readcharandEcho, sizeof(readcharandEcho), 0);
	// vm_exec(vm, 0, false);
	// //vm_print_data(vm->globals, vm->nglobals);
	// vm_free(vm);

	// descomentar par probar las otras pruebas


	// printf("Loop Test\n");	
	// vm = vm_create(loop, sizeof(loop), 2);
	// vm_exec(vm, 0, true);
	// //vm_print_data(vm->globals, vm->nglobals);
	// vm_free(vm);

	// int t1 = (clock() / (CLOCKS_PER_SEC / 1000));
	// vm = vm_create(loop, sizeof(loop), 2);
	// vm_exec(vm, 0, true);
	// vm_print_data(vm->globals, vm->nglobals);
	// vm_free(vm);
    // int t2 = (clock() / (CLOCKS_PER_SEC / 1000));
	// printf("----------------\n");	
    // printf("duration loop = %d ms\n", (t2 - t1));

	// printf("Factorial Test\n");	
	// vm = vm_create(factorial, sizeof(factorial), 0);
	// vm_exec(vm, 23, false);
	// vm_free(vm);

	return(0);	
}


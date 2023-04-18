#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int a, b, x, error;
	error = 1;
	x = 0;
	cout << "Enter a b" << endl;
	cin >> a >> b;
	_asm
	{
		xor eax, eax
		xor ebx, ebx

		mov eax, a; <eax> = a
		mov ebx, b; <ebx> = b

		cmp eax, ebx; сравнение eax и ebx
		jg great; eax > ebx
		jl m4; eax < ebx
		mov x, 6; <eax> = <ebx>
		jmp end_if

		great :
			imul eax; <eax> = a ^ 2
			jo of_error; флаг переполнения
			sub eax, ebx; <eax> = a ^ 2 - b
			push eax; eax в стек
			mov eax, a; <eax> = a
			sub eax, 3; <eax> = a - 3
			mov ebx, eax; <ebx> = a - 3
			jz zero_error; флаг, на случай деления на 0
			pop eax; <eax> = a ^ 2 - b
			cdq;
			idiv ebx; <eax> = a ^ 2 - b / a - 3
			mov x, eax; 

			jmp end_if

		m4 :
			or ebx, ebx
			jz zero_error
			imul eax; <eax> = a ^ 2
			jo of_error;
			sub eax, 3; <eax> = a ^ 2 - 3
			cdq; расширяем регистр eax для последующего деления
			idiv ebx; <eax> = a ^ 2 - 3 / b
			mov x, eax; помещаем в x результат

			jmp end_if

		of_error:
			mov error, -1;
			jmp end_if;
		
		zero_error:
			mov error, 0;
			jmp end_if

		end_if :

	}
	if (error == 0) cout << "division by zero" << endl;
	if (error == -1) cout << "overflow" << endl;
	if (error == 1) cout << "asm: " << x << endl;

	if (error != -1)
	{
		if (a > b)
		{
			if (a == 3) cout << "divison by zero";
			if (a != 3) cout << "C++: " << (int)(pow(a, 2) - b) / (a - 3);

		}
		if (a == b)
		{
			cout << "C++: " << 6;
		}
		if (a < b)
		{
			if (b == 0) cout << "divison by zero";
			if (b != 0) cout << "C++: " << (int)(pow(a, 2) - 3) / b;
		}
	}
	return 0;
}

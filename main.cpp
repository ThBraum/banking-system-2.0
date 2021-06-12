#include <iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include "contabancaria.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	char ch;
	int num;
	int opc;
	do
	{
		system("cls");
		cout<<"\n\n\n\tMENU";
		cout<<"\n\n\t[ 1 ] NOVA CONTA" << endl;
		cout<<"\t[ 2 ] DEPOSITO" << endl;
		cout<<"\t[ 3 ] SAQUE" << endl;
		cout<<"\t[ 4 ] CONSULTA DE SALDO" << endl;
		cout<<"\t[ 5 ] EXTRATO" << endl;
		cout<<"\t[ 6 ] FECHAR UMA CONTA" << endl;
		cout<<"\t[ 7 ] ATUALIZAR CONTA" << endl;
		cout<<"\t[ 8 ] SAIR" << endl;
		cout<<"\n\tOpcao: ";
		cin>>ch;
		system("cls");
		
		
		switch(ch)
		{
		case '1':
			
			cout << "[ 1 ] CORRENTE";
			cout << "\n[ 2 ] POUPANCA";
			cout << "\n[ 3 ] LIMITE";
			cout << "\nOpcao de conta a ser criada: ";
			cin >> opc;
			
			
			if(opc == 1){
				registro_conta_corrente();
			}else if(opc == 2){
				registro_conta_poupanca();
			}else if(opc ==3){
				registro_conta_limite();
			}else{
				cout << "Opcao invalida" << endl;
			}
			
			break;
		case '2':
			cout<<"\n\n\tNumero da conta: "; cin>>num;
			depositar_retirar(num, 1);
			break;
		case '3':
			cout<<"\n\n\tNumero da conta: "; cin>>num;
			depositar_retirar(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tNumero da conta: "; cin>>num;
			exibir_detalhes(num);
			break;
		case '5':
			exibir_tudo();
			break;
		case '6':
			cout<<"\n\n\tNumero da conta: : "; cin>>num;
			excluir_conta(num);
			break;
		 case '7':
			cout<<"\n\n\tNumero da conta: "; cin>>num;
			alterar_dados_conta(num);
			break;
		 case '8':
			cout<<"\n\n\tObrigado por utilizar esse sistema de gerenciamento bancario";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	
	return 0;
}

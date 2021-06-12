#include <iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include "contabancaria.h"


void conta::criar_conta_corrente()
{
	cout<<"\nNumero da conta: ";
	cin>>num_conta;
	cout<<"\n\nNome do proprietario da conta: ";
	cin.ignore();
	cin.getline(nome,50);
	cout<<"\nEntre com o valor inicial: ";
	cin>>depositar;
	cout<<"\n\n\nConta criada com sucesso!";
	tipo = 'C';
}

void conta:: criar_conta_poupanca()
{
	cout<<"\nNumero da conta: ";
	cin>>num_conta;
	cout<<"\n\nNome do proprietario da conta: ";
	cin.ignore();
	cin.getline(nome,50);
	cout<<"\nEntre com o valor inicial: ";
	cin>>depositar;
	
	system("cls");
	
	cout << "\n\tData -  Informacoes para aniversario da conta" << endl;
	cout << "Dia: ";
	cin >> dia;
	cout << "\nMes: ";
	cin >> mes;
	cout << "\nAno: ";
	cin >> ano;
	
	cout<<"\n\n\nConta criada com sucesso!";
	tipo = 'P';
}

void conta::criar_conta_limite()
{
	cout<<"\nNumero da conta: ";
	cin>>num_conta;
	cout<<"\n\nNome do proprietario da conta: ";
	cin.ignore();
	cin.getline(nome,50);
	cout << "\nEntre com o limite da conta: ";
	cin >> limite;
	cout<<"\nEntre com o valor inicial: ";
	cin>>depositar;
	cout<<"\n\n\nConta criada com sucesso!";
	tipo = 'L';
}

void conta::mostrar_conta() const
{
	cout<<"\nNumero da conta: "<<num_conta;
	cout<<"\nNome do proprietario da conta: ";
	cout<<nome;
	cout<<"\nTipo da conta: "<<tipo;
	cout<<"\nSaldo : "<<depositar;
}


void conta::alterar_dados()
{
	cout<<"\nNumero da conta: "<<num_conta;
	cout<<"\nNovo proprietario da conta: ";
	cin.ignore();
	cin.getline(nome,50);
	cout<<"\nNovo tipo de conta: ";
	cin>>tipo;
	tipo=toupper(tipo);
	cout<<"\nNovo saldo: ";
	cin>>depositar;
}

	
void conta::deposito(int x)
{
	depositar+=x;
}
	
void conta::retirar(int x)
{
	depositar-=x;
	if(tipo != 'L' && depositar < 0){
		cout << "Saldo indisponivel em conta" << endl;
		depositar +=x;
	}
	
	int limite_conta = 0 - limite;
	
	if(tipo == 'L' && depositar < limite_conta){
		cout << "Erro: saldo inferior ao limite negativo permitido";
	}
}
	
void conta::imprime_contas() const
{
	if(tipo == 'C'){
		cout << "\tN/c:" << num_conta <<setw(10) << "\tNome: " << nome << " \tTipo: Corrente" << "\t   Saldo: "<<depositar<<endl;
	}else if(tipo == 'P'){
		cout << "\tN/c:" << num_conta <<setw(10) << "\tNome: " << nome << " \tTipo: Poupanca" << "\t   Saldo: "<<depositar<< "\tData: " << dia << "/" << mes << "/" << ano << endl;
	}else{
		cout << "\tN/c:" << num_conta <<setw(10) << "\tNome: " << nome << " \tTipo: Limite" << "\t   Saldo: "<<depositar<<endl;
	}
	 
}

	
int conta::retnum_conta() const
{
	return num_conta;
}

int conta::retdeposit() const
{
	return depositar;
}

char conta::rettipo() const
{
	return tipo;
}





void registro_conta_corrente() //funcao que registra em arquivo
{
	conta ac;
	ofstream outFile;
	outFile.open("conta.dat",ios::binary|ios::app);
	ac.criar_conta_corrente();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(conta));
	outFile.close();
}

void registro_conta_poupanca() //funcao que registra em arquivo
{
	conta ac;
	ofstream outFile;
	outFile.open("conta.dat",ios::binary|ios::app);
	ac.criar_conta_poupanca();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(conta));
	outFile.close();
}

void registro_conta_limite()
{
	conta ac;
	ofstream outFile;
	outFile.open("conta.dat",ios::binary|ios::app);
	ac.criar_conta_limite();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(conta));
	outFile.close();
}


void exibir_detalhes(int n) //função para ler registro específico do arquivo
{
	conta ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("conta.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Arquivo nao pode ser aberto! Pressione qualquer tecla";
		return;
	}
	cout<<"\nDETALHES DO SALDO\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(conta)))
	{
		if(ac.retnum_conta()==n)
		{
			ac.mostrar_conta();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nEsse numero de conta nao existe";
}


void alterar_dados_conta(int n) //funcao para alterar dados gravados no arquivo
{
	bool found=false;
	conta ac;
	fstream File;
	File.open("conta.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Arquivo nao pode ser aberto! Pressione qualquer tecla";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(conta));
		if(ac.retnum_conta()==n)
		{
			ac.mostrar_conta();
			cout<<"\n\nEntre com os novos detalhes da conta"<<endl;
			ac.alterar_dados();
			int pos=(-1)*static_cast<int>(sizeof(conta));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(conta));
			cout<<"\n\n\t Informacoes atualizadas";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Registro não encontrado ";
}


void excluir_conta(int n) //funcao para deletar conta do arquivo
{
	conta ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("conta.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Arquivo nao pode ser aberto! Pressione qualquer tecla";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(conta)))
	{
		if(ac.retnum_conta()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(conta));
		}
	}
	inFile.close();
	outFile.close();
	remove("conta.dat");
	rename("Temp.dat","conta.dat");
	cout<<"\n\n\tRecord Deleted ..";
}



void exibir_tudo() //funcao que exibe todas contas
{
	conta ac;
	ifstream inFile;
	inFile.open("conta.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Arquivo nao pode ser aberto! Pressione qualquer tecla";
		return;
	}
	cout<<"\n\n\t\tCONTAS CADASTRADAS\n\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(conta)))
	{
		ac.imprime_contas();
	}
	inFile.close();
}

void depositar_retirar(int n, int option) // funcao para realizar depositos e saque
{
	int amt;
	bool found=false;
	conta ac;
	fstream File;
	File.open("conta.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Arquivo nao pode ser aberto! Pressione qualquer tecla";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(conta));
		if(ac.retnum_conta()==n)
		{
			ac.mostrar_conta();
			if(option==1)
			{
				cout<<"\n\n\tPARA DEPOSITAR QUANTIDADE ";
				cout<<"\n\nValor a ser depositado: ";
				cin>>amt;
				ac.deposito(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tPARA RETIRAR MONTANTE";
				cout<<"\n\nInsira o valor a ser retirado: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				//if((bal<500 && ac.rettipo()=='S') || (bal<1000 && ac.rettipo()=='C'))
				//	cout<<"Saldo insuficiente";
				//else
				ac.retirar(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(conta));
			cout<<"\n\n\t Informacoes atualizadas";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Registro não encontrado ";
}


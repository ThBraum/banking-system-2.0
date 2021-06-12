#ifndef CONTABANCARIA_H
#define CONTABANCARIA_H


class conta
{
	int num_conta;
	char nome[50];
	int depositar;
	char tipo;
	int dia, mes, ano; 
	int limite;
	
	public:
		void criar_conta_corrente();	//funcao que recebe dados do usuario
		void criar_conta_poupanca();
		void criar_conta_limite();
		void mostrar_conta() const;	//funcao que mostra dados na tela
		void alterar_dados();	//funcao para adicionar novos dados
		void deposito(int);	//funcao para aceitar o valor e adicionar ao valor do saldo
		void retirar(int);	//funcao para aceitar o valor e subtrair do valor do saldo
		void imprime_contas() const;	//funcao para mostrar dados em formato tabular
		int retnum_conta() const;	//funcao para retornar o número da conta
		int retdeposit() const;	//funcao para retornar o valor do saldo
		char rettipo() const;	//funcao para retornar o tipo de conta
};

void registro_conta_corrente();	//funcao para escrever o registro em arquivo binario
void registro_conta_poupanca();
void registro_conta_limite();
void exibir_detalhes(int);	//funcao para exibir detalhes da conta fornecidos pelo usuário
void alterar_dados_conta(int);	//funcao para modificar o registro do arquivo
void excluir_conta(int);	//funcao para apagar o registro do arquivo
void exibir_tudo();		//funcao para exibir todos os detalhes da conta
void depositar_retirar(int, int); //funcao para depositar/retirar quantia para determinada conta 

#endif

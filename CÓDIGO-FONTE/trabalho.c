//Alunas: Morgana Zagury e Thays Marciel
#include <stdio.h>//standard
#include <stdlib.h>//manipulacao memoria
#include <string.h>//manipulacao strings
#include <windows.h>//comando cls e sleep
#include <conio.h> //getch
//defini��es
#define TAM_MAX 50
#define MAX_DISCIPLINAS 50
#define MAX_PREREQUISITOS 10
#define MAX_AGENDA 50
#define MAX_ATIVIDADES 20
#define LINES_PER_PAGE 7
//FUNCIONALIDADES:
//1) apresenta��o da matriz curricular (leitura a partir de um arquivo) 
//2) apresenta��o das disciplinas cursadas (hist�rico) 
//3) agenda do aluno (atividades e compromissos/ ex eventos tarefas etc)
//4) apresenta��o de atividades pendentes (tarefas da semana/ ex calendario moodle)
//5) pagina��o em listagens grandes

//DEFINI��O STRUCTS:
typedef enum {
    Obrigatoria,
    Optativa
} TipoDisciplina;//cria o tipo disciplina

typedef struct {
    int semestre;
    char codigo[10];
    char nome[100];
    int cargaHoraria;
    char preRequisito[6];
    TipoDisciplina tipo;
} Disciplina;//usa o tipo disciplina

typedef struct {
    char codigoDisciplina[10];       
    char horario[100];                
    char diasSemana[20];             
} Agenda;

typedef struct {
    char titulo[100];                
    char codigoDisciplina[10];       
    char prazo[20];                  
    int concluida;                   
} Atividade;

Disciplina disciplinas[MAX_DISCIPLINAS];
Agenda agenda[MAX_AGENDA];            
Atividade atividades[MAX_ATIVIDADES]; 
int qtdRegistros = 0;                
int qtdAgenda = 0;                    
int qtdAtividades = 0;                

//Elementos da agenda: disciplina, horario  e dia da semana
void cadastrarAgendatxt() {
    int size1; // n�mero de linhas registradas
    FILE *arq3 = fopen("agenda.txt", "r");//abre arquivo no modo read

    if (arq3 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fscanf(arq3, "%d", &size1); // l� o n�mero de compromissos j� registrados
    char compromissoAgenda[size1][100];
    char horario[size1][100];
    char diaSemana[size1][100];

    for (int i = 0; i < size1; i++) {
        fscanf(arq3, "%s %s %s", compromissoAgenda[i], horario[i], diaSemana[i]);
    }

    fclose(arq3); // fecha o arquivo de leitura

    // Reabre o arquivo para escrita
    arq3 = fopen("agenda.txt", "w");
    if (arq3 == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Solicita novo compromisso do usu�rio
    char novoCompromisso[100];
    char novoHorario[100];
    char novoDiaSemana[100];

    printf("Digite o nome do compromisso que deseja registrar: ");
    scanf("%s", novoCompromisso);

    printf("Digite o horario do compromisso: (ex: 14h) ");
    scanf("%s", novoHorario);

    printf("Digite o dia da semana do compromisso: ");
    scanf("%s", novoDiaSemana);

    // Atualiza o arquivo com os compromissos antigos e o novo
    fprintf(arq3, "%d\n", size1 + 1); // Atualiza o n�mero de compromissos
    for (int i = 0; i < size1; i++) {
        fprintf(arq3, "%s %s %s", compromissoAgenda[i], horario[i], diaSemana[i]);
    }
    fprintf(arq3, "%s %s %s", novoCompromisso, novoHorario, novoDiaSemana); // Adiciona o novo compromisso

    fclose(arq3); // Fecha o arquivo
    printf("Compromisso registrado com sucesso!\n");
     Sleep(2000);
     system("cls");
     
}


//Elementos da atividade: nome da atividade, codigo da disciplina e prazo atividade 

void cadastrarAtividadetxt() {
    int size2; // n�mero de linhas registradas
    FILE *arq4 = fopen("atividadesPendentes.txt", "r");

    if (arq4 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // L� o n�mero de atividades existentes
    fscanf(arq4, "%d", &size2); 

    // Declara arrays para armazenar os dados j� existentes
    char nomeAtividade[size2][100];
    char codigoDisc[size2][100];
    char prazoAtividade[size2][300];

    // L� os dados j� registrados
    for (int i = 0; i < size2; i++) {
        fscanf(arq4, "%s %s %s", nomeAtividade[i], codigoDisc[i], prazoAtividade[i]);
    }

    fclose(arq4); // fecha o arquivo de leitura

    // Reabre o arquivo para escrita
    arq4 = fopen("atividadesPendentes.txt", "w");
    if (arq4 == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
	//Registra novos dados
    char novaAtividade[100];
    char novoCodigoDisc[100];
    char novoPrazoAtividade[100];

    printf("Digite o nome da atividade que deseja registrar: ");
    scanf("%s", novaAtividade);

    printf("Digite o codigo da disciplina: ");
    scanf("%s", novoCodigoDisc);

    printf("Qual o prazo da atividade: (ex: 25/10/2024) ");
    scanf("%s", novoPrazoAtividade);

    // Atualiza o arquivo com os compromissos antigos e o novo
    fprintf(arq4, "%d\n", size2 + 1); // Atualiza o n�mero de compromissos

    // Grava os compromissos antigos
    for (int i = 0; i < size2; i++) {
        fprintf(arq4, "%s %s %s\n", nomeAtividade[i], codigoDisc[i], prazoAtividade[i]);
    }

    // Adiciona o novo compromisso
    fprintf(arq4, "%s %s %s\n", novaAtividade, novoCodigoDisc, novoPrazoAtividade);

    fclose(arq4); // Fecha o arquivo
    printf("Atividade registrada com sucesso!\n");
    
    Sleep(5000);
    system("cls");
}

// Elementos do Historico: codigo, nome da disciplina, media final e status do aluno
void cadastrarHistoricotxt() {
    
    int tamanho;
    FILE *arq1 = fopen("historico.txt", "r");
    if (arq1 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    // L� o tamanho (quantidade de disciplinas) do arquivo
    fscanf(arq1, "%d", &tamanho);
    
    // Declara arrays para armazenar os dados lidos
    char codigo[tamanho][100];
    char nomeDisciplina[tamanho][300];
    char mediaFinal[tamanho][100];
    char statusDoAluno[tamanho][100];
    
    // L� os dados do arquivo
    for (int i = 0; i < tamanho; i++) {
        fscanf(arq1, "%s %s %s %s", codigo[i], nomeDisciplina[i], mediaFinal[i], statusDoAluno[i]);
    }
    
    fclose(arq1);
    
    // Reabre o arquivo para escrita (modo "w" apaga os dados antigos)
    arq1 = fopen("historico.txt", "w");
    if (arq1 == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    
    // Cria vari�veis para o novo registro
    char novoCodigo[100];
    char novoNomeDisciplina[100];
    char novoMediaFinal[100];
    char novoStatusDoAluno[100];
    
    // Recebe os novos dados
    printf("Digite o codigo da disciplina que deseja registrar: ");
    scanf("%s", novoCodigo);
    printf("Digite o nome da disciplina que deseja registrar: ");
    scanf("%s", novoNomeDisciplina);
    printf("Digite a media final da disciplina que deseja registrar: ");
    scanf("%s", novoMediaFinal);
    
    // Converte novoMediaFinal de string para float para poder comparar
    float media = atof(novoMediaFinal);
    
    // Calcula o status do aluno com base na m�dia convertida
    if (media >= 6.0) {
        strcpy(novoStatusDoAluno, "Aprovado");
    } else {
        strcpy(novoStatusDoAluno, "Reprovado");
    }
    
    // Escreve o novo tamanho (incrementado)
    fprintf(arq1, "%d\n", tamanho + 1);
    
    // Escreve os registros antigos de volta no arquivo
    for (int i = 0; i < tamanho; i++) {
        fprintf(arq1, "%s %s %s %s\n", codigo[i], nomeDisciplina[i], mediaFinal[i], statusDoAluno[i]);
    }
    
    // Escreve o novo registro no arquivo
    fprintf(arq1, "%s %s %s %s\n", novoCodigo, novoNomeDisciplina, novoMediaFinal, novoStatusDoAluno);
    
    fclose(arq1);
    
    printf("Historico registrado com sucesso!\n");
    
    // Pausa e limpa a tela
    Sleep(2000);
    system("cls");
}

//Elementos de cadastro de disciplina: codigo, nome, carga horaria, qual semestre, pre requisitos, obrigatoriedade
void cadastrarMateriastxt() {
    int tamanhoMaterias;
    FILE *arq2 = fopen("materias.txt", "r");
    if (arq2 == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    // L� o tamanho do n�mero de mat�rias no arquivo
    fscanf(arq2, "%d", &tamanhoMaterias);

    // Arrays para armazenar os dados das mat�rias
    char codigoMaterias[tamanhoMaterias][100];
    char nomeMaterias[tamanhoMaterias][100];
    char cargaHoraria[tamanhoMaterias][100];
    char qualPeriodo[tamanhoMaterias][100];
    char preRequisitos[tamanhoMaterias][100];
    char statusDisciplina[tamanhoMaterias][100];

    // L� os dados do arquivo
    for (int i = 0; i < tamanhoMaterias; i++) {
        fscanf(arq2, "%s %s %s %s %s %s", 
		    codigoMaterias[i], 
            nomeMaterias[i], 
            cargaHoraria[i], 
            qualPeriodo[i], 
            preRequisitos[i], 
            statusDisciplina[i]);
    }

    fclose(arq2);

    // Reabre o arquivo para escrita
    arq2 = fopen("materias.txt", "w");
    if (arq2 == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Coleta os novos dados do usu�rio
    char novoCodigo[100];
    printf("Digite o codigo da disciplina que deseja registrar: ");
    scanf("%s", novoCodigo);

    char novoNomeDisciplina[100];
    printf("Digite o nome da disciplina que deseja registrar: ");
    scanf("%s", novoNomeDisciplina);

    char novaCargaHoraria[100];
    printf("Digite a carga horaria da disciplina que deseja registrar: ");
    scanf("%s", novaCargaHoraria);

    char novoQualPeriodo[100];
    printf("Digite o periodo da disciplina que deseja registrar: ");
    scanf("%s", novoQualPeriodo);

    char novoPreRequisitos[100];
    printf("Digite os pre-requisitos da disciplina (se nao tiver, digite '0'): ");
    scanf("%s", novoPreRequisitos);

    char novoStatusDisciplina[100];
    printf("Digite se a disciplina eh obrigatoria ou optativa: ");
    scanf("%s", novoStatusDisciplina);

    // Escreve o novo tamanho do n�mero de mat�rias
    fprintf(arq2, "%d\n", tamanhoMaterias + 1);

    // Grava as mat�rias existentes de volta no arquivo
    for (int i = 0; i < tamanhoMaterias; i++) {
        fprintf(arq2, "%s %s %s %s %s %s\n", 
            codigoMaterias[i], 
            nomeMaterias[i], 
            cargaHoraria[i], 
            qualPeriodo[i], 
            preRequisitos[i], 
            statusDisciplina[i]);
    }

    // Grava a nova disciplina no arquivo
    fprintf(arq2, "%s %s %s %s %s %s\n", 
        novoCodigo, 
        novoNomeDisciplina, 
        novaCargaHoraria, 
        novoQualPeriodo, 
        novoPreRequisitos, 
        novoStatusDisciplina);

    fclose(arq2);
    printf("Disciplina registrada com sucesso!\n");
    
     
    Sleep(2000);
    system("cls");
}

void mostraAgenda() {
    FILE *arqNotes;
    char compromisso[100], horario[100], diaSemana[100];
    int listagensPorPagina; // Vari�vel para armazenar o n�mero de listagens por p�gina
    int currentLine = 0; // Linha atual exibida

    // Abrir o arquivo agenda.txt para leitura
    arqNotes = fopen("agenda.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (arqNotes == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // L� o n�mero de compromissos registrados (primeira linha do arquivo)
    int totalCompromissos;
    fscanf(arqNotes, "%d", &totalCompromissos);

    // Solicita ao usu�rio o n�mero de listagens por p�gina
    printf("Digite quantas listagens deseja por pagina: ");
    scanf("%d", &listagensPorPagina);
    getchar(); // Captura o Enter ap�s a leitura do n�mero

    // Exibe as linhas em p�ginas
    while (1) {
        system("cls"); // Limpa a tela

        // Cabe�alho da se��o
        printf("Agenda:\n");

        // Exibe as linhas em p�ginas
        for (int i = 0; i < listagensPorPagina && currentLine < totalCompromissos; i++, currentLine++) {
            if (fscanf(arqNotes, "%s %s %s", compromisso, horario, diaSemana) == 3) {
                // Exibe o conte�do sem o formato de tabela
                printf("Compromisso: %s\nHor�rio: %s\nDia da Semana: %s\n\n", compromisso, horario, diaSemana);
            } else {
                // Se n�o houver mais linhas, finalize
                printf("\nTodas as atividades exibidas. Pressione Enter para sair...\n");
                getchar(); // Aguarda o usu�rio pressionar Enter antes de sair
                fclose(arqNotes);
                return; // Sai da fun��o
            }
        }

        // Se o n�mero total de linhas ainda n�o foi exibido, exibe a op��o de continuar
        if (currentLine < totalCompromissos) {
            printf("\nPressione Enter para continuar...");
            getchar(); // Aguarda o usu�rio pressionar Enter para continuar
        } else {
            // Se todos os compromissos j� foram exibidos
            printf("\nTodas as atividades exibidas. Pressione Enter para sair...\n");
            getchar(); // Aguarda o usu�rio pressionar Enter antes de sair
            fclose(arqNotes);
            return; // Sai da fun��o
        }
    }

    // Fechar o arquivo
    fclose(arqNotes);
    Sleep(2000);
    system("cls");
}

void imprimeCabecalhoMinimalistaAtiv() {
    printf("Atividade          | Codigo | Data|\n");
    printf("-----------------------------------\n");
}

void mostraAtividades() {
    FILE *arqAtivs;
    char line4[100];
    int listagensPorPagina; // Vari�vel para armazenar o n�mero de listagens por p�gina
    int currentLine = 0; // Linha atual exibida

    arqAtivs = fopen("atividadesPendentes.txt", "r");

    if (arqAtivs == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Solicita ao usu�rio o n�mero de listagens por p�gina
    printf("Digite quantas listagens deseja por pagina: ");
    scanf("%d", &listagensPorPagina);
    getchar(); // Captura o Enter ap�s a leitura do n�mero

    // Exibe as linhas em p�ginas
    while (1) {
        system("cls"); // Limpa a tela

        // Exibe o cabe�alho antes de cada p�gina
        imprimeCabecalhoMinimalistaAtiv();

        // Exibe as linhas em p�ginas
        for (int i = 0; i < listagensPorPagina; i++, currentLine++) {
            if (fgets(line4, sizeof(line4), arqAtivs) != NULL) {
                printf("%s", line4);
            } else {
                // Se n�o houver mais linhas, finaliza
                printf("\nTodas as atividades exibidas. Pressione Enter para sair...\n");
                getchar(); // Aguarda o usu�rio pressionar Enter antes de sair
                fclose(arqAtivs);
                return; // Sai da fun��o
            }
        }

        // Exibe a op��o de continuar
        printf("\nPressione Enter para continuar...");
        getchar(); // Aguarda o usu�rio pressionar Enter para continuar
    }

    fclose(arqAtivs);
    Sleep(2000);
    system("cls");
}


void imprimeCabecalhoMinimalistaHist() {
//	printf("Historico Escolar:\n");
    printf("Codigo | Disciplina        | Nota Final | Status|\n");
    printf("-------------------------------------------------\n");
}

void mostraHistorico() {
    FILE *arqHist;
    char line6[100];
    int listagensPorPagina; // Vari�vel para armazenar o n�mero de listagens por p�gina
    int currentLine = 0; // Linha atual exibida

    arqHist = fopen("historico.txt", "r");

    if (arqHist == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Solicita ao usu�rio o n�mero de listagens por p�gina
    printf("Digite quantas listagens deseja por pagina: ");
    scanf("%d", &listagensPorPagina);
    getchar(); // Aguarda o usu�rio digitar enter

    // Exibe as linhas em p�ginas
    while (1) {
        system("cls"); // Limpa a tela

        // Exibe o cabe�alho antes de mostrar cada p�gina de listagens
        imprimeCabecalhoMinimalistaHist();

        // Exibe as linhas em p�ginas
        for (int i = 0; i < listagensPorPagina; i++, currentLine++) {
            if (fgets(line6, sizeof(line6), arqHist) != NULL) {
                printf("%s", line6);
            } else {
                // Se n�o houver mais linhas, finaliza
                printf("\nTodas as linhas exibidas. Pressione Enter para sair...\n");
                getchar(); // Aguarda o usu�rio pressionar Enter antes de sair
                fclose(arqHist);
                return; // Sai da fun��o
            }
        }

        // Se o n�mero total de linhas ainda n�o foi exibido, exibe a op��o de continuar
        printf("\nPressione Enter para continuar...");
        getchar(); // Aguarda o usu�rio pressionar Enter para continuar
    }

    fclose(arqHist);
    Sleep(2000);
    system("cls");
}

//MATRIZ COME�A AQUI EMBAIXO

//AQUI COME�A MOSTRA MATRIZ
void imprimeCabecalhoMinimalista() {
    printf("Semestre | Nome Disciplina | Carga Horaria | Pre-requisitos | Tipo |\n");
    printf("--------------------------------------------------------------------\n"); // Linha de separa��o
}

void mostraMatriz() {
    FILE *arq;
    char linhasComp[256]; // Aumentado para acomodar linhas maiores
    int listagensPorPagina; // Vari�vel para armazenar o n�mero de listagens por p�gina
    int currentLine = 0; // Linha atual exibida

    // Solicita ao usu�rio o n�mero de listagens por p�gina
    printf("Digite quantas listagens deseja por pagina: ");
    scanf("%d", &listagensPorPagina);
    getchar(); // Captura o Enter ap�s a leitura do n�mero

    arq = fopen("matrizNova.txt", "r");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Exibe as linhas em p�ginas
    while (1) {
        system("cls"); // Limpa a tela
        imprimeCabecalhoMinimalista(); // Exibe o cabe�alho da tabela

        // Exibe as linhas em p�ginas
        for (int i = 0; i < listagensPorPagina; i++, currentLine++) {
            if (fgets(linhasComp, sizeof(linhasComp), arq) != NULL) {
          
                int semestre;
                char codigo[10], nome[50], tipo[15];
                int cargaHoraria, preRequisitos;

                // L� e formata a linha
                if (sscanf(linhasComp, "%d %s %[^\n] %d %d %s", &semestre, codigo, nome, &cargaHoraria, &preRequisitos, tipo) == 6) {
                    // Exibe a linha formatada com o novo formato
                    printf(" %-8d | %-17s | %-12d | %-16d | %-10s |\n", semestre, nome, cargaHoraria, preRequisitos, tipo);
                } else {
                    printf("%s\n", linhasComp);
                }
            } else {
                // Se n�o houver mais linhas, finalize
                //imprimeLinhaOrganizacao(); // Imprime a linha de organiza��o antes de sair
                printf("\nTodas as linhas exibidas. Pressione Enter para sair...\n");
                getchar(); // Aguarda o usu�rio pressionar Enter antes de sair
                fclose(arq);
                system("cls"); // Limpa a tela ap�s ler a �ltima linha
                return; // Sai da fun��o
            }
        }

        // Se o n�mero total de linhas ainda n�o foi exibido, exibe a op��o de continuar
        printf("\nPressione Enter para continuar...");
        getchar(); // Aguarda o usu�rio pressionar Enter para continuar
    }

    fclose(arq);
    system("cls");
}
//AQUI ACABA A MATRIZ
void mostraASCII() {   
 printf("     _     _                                             _                _           \n");
    printf("    (_)   | |                                           | |              (_)          \n");
    printf(" ___ _ ___| |_ ___ _ __ ___   __ _    __ _  ___ __ _  __| | ___ _ __ ___  _  ___ ___  \n");
    printf("/ __| / __| __/ _ \\ '_ ` _ \\ / _` |  / _` |/ __/ _` |/ _` |/ _ \\ '_ ` _ \\| |/ __/ _ \\ \n");
    printf("\\__ \\ \\__ \\ ||  __/ | | | | | (_| | | (_| | (_| (_| | (_| |  __/ | | | | | | (_| (_) |\n");
    printf("|___/_|___/\\__\\___|_| |_| |_|\\__,_|  \\__,_|\\___\\__,_|\\__,_|\\___|_| |_| |_|_|\\___\\___/ \n");
    printf("\n");
}

int main() {
    char op = ' ';
    
    do {
        mostraASCII();  
printf("\n\n\n");
         printf("+---------------------------------------+\n");
    printf("| Escolha uma das opcoes:              |\n");
    printf("|                                       |\n");
    printf("| 1 - Matriz Curricular                 |\n");
    printf("| 2 - Historico Escolar                 |\n");
    printf("| 3 - Agenda                            |\n");
    printf("| 4 - Atividades Pendentes              |\n");
    printf("| x - Sair                             |\n");
    printf("+---------------------------------------+\n");
        scanf("%c", &op);

        if (op == 'x') {
            break; 
        } else {
            switch (op) {
                case '1':
                    mostraMatriz(); 
                    break;
                case '2': {
                    char escolha;
                    printf("Escolha uma opcao:\n 1 - Mostrar Historico\n 2 - Cadastrar Historico\n");
                    scanf(" %c", &escolha);
                    if (escolha == '1') {
                        mostraHistorico(); // Certifique-se de que esta fun��o est� definida
                    } else if (escolha == '2') {
                        cadastrarHistoricotxt(); // Certifique-se de que esta fun��o est� definida
                    }
                    break;
                }
                case '3': {
                    char escolha;
                    printf("Escolha uma opcao:\n 1 - Mostrar Agenda\n 2 - Cadastrar Agenda\n");
                    scanf(" %c", &escolha);
                    if (escolha == '1') {
                        mostraAgenda(); // Certifique-se de que esta fun��o est� definida
                    } else if (escolha == '2') {
                        cadastrarAgendatxt(); // Certifique-se de que esta fun��o est� definida
                    }
                    break;
                }
                case '4': {
                    char escolha;
                    printf("Escolha uma opcao:\n 1 - Mostrar Atividades\n 2 - Cadastrar Atividades\n");
                    scanf(" %c", &escolha);
                    if (escolha == '1') {
                        mostraAtividades(); // Certifique-se de que esta fun��o est� definida
                    } else if (escolha == '2') {
                        cadastrarAtividadetxt(); // Certifique-se de que esta fun��o est� definida
                    }
                    break;
                }
            }
        }
    } while (1);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALUNOS 100
#define MAX_NOME 50
#define MAX_CURSO 30

typedef struct {
    int matricula;
    char nome[MAX_NOME];
    char curso[MAX_CURSO];
    float nota1;
    float nota2;
    float media;
    char situacao[20];
} Aluno;

Aluno banco_dados[MAX_ALUNOS];
int total_alunos = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void calcularMediaSituacao(Aluno *aluno) {
    aluno->media = (aluno->nota1 + aluno->nota2) / 2.0;
    
    if (aluno->media >= 7.0) {
        strcpy(aluno->situacao, "Aprovado");
    } else if (aluno->media >= 5.0) {
        strcpy(aluno->situacao, "Recuperação");
    } else {
        strcpy(aluno->situacao, "Reprovado");
    }
}

void cadastrarAluno() {
    if (total_alunos >= MAX_ALUNOS) {
        printf("❌ Banco de dados cheio! Não é possível cadastrar mais alunos.\n");
        return;
    }

    Aluno novo_aluno;
    
    printf("\n=== CADASTRO DE NOVO ALUNO ===\n");
    
    printf("Matrícula: ");
    scanf("%d", &novo_aluno.matricula);
    limparBuffer();
    
    printf("Nome: ");
    fgets(novo_aluno.nome, MAX_NOME, stdin);
    novo_aluno.nome[strcspn(novo_aluno.nome, "\n")] = '\0';
    
    printf("Curso: ");
    fgets(novo_aluno.curso, MAX_CURSO, stdin);
    novo_aluno.curso[strcspn(novo_aluno.curso, "\n")] = '\0';
    
    printf("Nota 1: ");
    scanf("%f", &novo_aluno.nota1);
    
    printf("Nota 2: ");
    scanf("%f", &novo_aluno.nota2);
    
    calcularMediaSituacao(&novo_aluno);
    
    banco_dados[total_alunos] = novo_aluno;
    total_alunos++;
    
    printf("✅ Aluno cadastrado com sucesso!\n");
}

void listarAlunos() {
    if (total_alunos == 0) {
        printf("❌ Nenhum aluno cadastrado.\n");
        return;
    }
    
    printf("\n=== LISTA DE ALUNOS ===\n");
    printf("%-10s %-20s %-20s %-6s %-6s %-6s %-12s\n", 
           "Matrícula", "Nome", "Curso", "Nota1", "Nota2", "Média", "Situação");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < total_alunos; i++) {
        printf("%-10d %-20s %-20s %-6.1f %-6.1f %-6.1f %-12s\n",
               banco_dados[i].matricula,
               banco_dados[i].nome,
               banco_dados[i].curso,
               banco_dados[i].nota1,
               banco_dados[i].nota2,
               banco_dados[i].media,
               banco_dados[i].situacao);
    }
}

void buscarAluno() {
    if (total_alunos == 0) {
        printf("❌ Nenhum aluno cadastrado.\n");
        return;
    }
    
    int opcao;
    printf("\n=== BUSCAR ALUNO ===\n");
    printf("1. Por matrícula\n");
    printf("2. Por nome\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    limparBuffer();
    
    if (opcao == 1) {
        int matricula;
        printf("Digite a matrícula: ");
        scanf("%d", &matricula);
        
        for (int i = 0; i < total_alunos; i++) {
            if (banco_dados[i].matricula == matricula) {
                printf("\n🎯 Aluno encontrado:\n");
                printf("Matrícula: %d\n", banco_dados[i].matricula);
                printf("Nome: %s\n", banco_dados[i].nome);
                printf("Curso: %s\n", banco_dados[i].curso);
                printf("Nota 1: %.1f\n", banco_dados[i].nota1);
                printf("Nota 2: %.1f\n", banco_dados[i].nota2);
                printf("Média: %.1f\n", banco_dados[i].media);
                printf("Situação: %s\n", banco_dados[i].situacao);
                return;
            }
        }
        printf("❌ Aluno não encontrado.\n");
        
    } else if (opcao == 2) {
        char nome_busca[MAX_NOME];
        printf("Digite o nome: ");
        fgets(nome_busca, MAX_NOME, stdin);
        nome_busca[strcspn(nome_busca, "\n")] = '\0';
        
        printf("\n🔍 Resultados da busca:\n");
        int encontrados = 0;
        
        for (int i = 0; i < total_alunos; i++) {
            if (strstr(banco_dados[i].nome, nome_busca) != NULL) {
                printf("%d - %s (%s)\n", 
                       banco_dados[i].matricula, 
                       banco_dados[i].nome, 
                       banco_dados[i].curso);
                encontrados++;
            }
        }
        
        if (encontrados == 0) {
            printf("❌ Nenhum aluno encontrado.\n");
        }
    } else {
        printf("❌ Opção inválida.\n");
    }
}

void estatisticas() {
    if (total_alunos == 0) {
        printf("❌ Nenhum aluno cadastrado.\n");
        return;
    }
    
    float soma_medias = 0;
    int aprovados = 0, recuperacao = 0, reprovados = 0;
    float maior_media = -1, menor_media = 11;
    
    for (int i = 0; i < total_alunos; i++) {
        soma_medias += banco_dados[i].media;
        
        if (banco_dados[i].media > maior_media) maior_media = banco_dados[i].media;
        if (banco_dados[i].media < menor_media) menor_media = banco_dados[i].media;
        
        if (banco_dados[i].media >= 7.0) aprovados++;
        else if (banco_dados[i].media >= 5.0) recuperacao++;
        else reprovados++;
    }
    
    printf("\n=== ESTATÍSTICAS ===\n");
    printf("Total de alunos: %d\n", total_alunos);
    printf("Média geral: %.2f\n", soma_medias / total_alunos);
    printf("Maior média: %.2f\n", maior_media);
    printf("Menor média: %.2f\n", menor_media);
    printf("Aprovados: %d (%.1f%%)\n", aprovados, (aprovados * 100.0) / total_alunos);
    printf("Recuperação: %d (%.1f%%)\n", recuperacao, (recuperacao * 100.0) / total_alunos);
    printf("Reprovados: %d (%.1f%%)\n", reprovados, (reprovados * 100.0) / total_alunos);
}

void salvarDados() {
    FILE *arquivo = fopen("alunos.dat", "wb");
    if (arquivo == NULL) {
        printf("❌ Erro ao criar arquivo.\n");
        return;
    }
    
    fwrite(&total_alunos, sizeof(int), 1, arquivo);
    fwrite(banco_dados, sizeof(Aluno), total_alunos, arquivo);
    
    fclose(arquivo);
    printf("✅ Dados salvos com sucesso!\n");
}

void carregarDados() {
    FILE *arquivo = fopen("alunos.dat", "rb");
    if (arquivo == NULL) {
        printf("ℹ️  Nenhum dado anterior encontrado.\n");
        return;
    }
    
    fread(&total_alunos, sizeof(int), 1, arquivo);
    fread(banco_dados, sizeof(Aluno), total_alunos, arquivo);
    
    fclose(arquivo);
    printf("✅ Dados carregados com sucesso!\n");
}

int main() {
    int opcao;
    
    printf("🎓 SISTEMA DE GESTÃO DE ALUNOS\n");
    printf("===============================\n");
    
    carregarDados();
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Listar alunos\n");
        printf("3. Buscar aluno\n");
        printf("4. Estatísticas\n");
        printf("5. Salvar dados\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                cadastrarAluno();
                break;
            case 2:
                listarAlunos();
                break;
            case 3:
                buscarAluno();
                break;
            case 4:
                estatisticas();
                break;
            case 5:
                salvarDados();
                break;
            case 0:
                printf("💾 Salvando dados...\n");
                salvarDados();
                printf("👋 Até logo!\n");
                break;
            default:
                printf("❌ Opção inválida.\n");
        }
    } while (opcao != 0);
    
    return 0;
}
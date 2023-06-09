#include "listas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Data* ler_data() {
    Data* d= (Data*)malloc(sizeof(Data));
    printf("Insira a data da consulta (dd mm aaaa): \n");
    scanf("%d %d %d", &d->dia, &d->mes, &d->ano);
    return d;
}

Data* ler_mes() {
    Data* d= (Data*)malloc(sizeof(Data));
    printf("Insira o mes e ano(mm aaaa): \n");
    scanf("%d %d", &d->mes, &d->ano);
    d->dia = 1;
    return d;
}

Hora* ler_hora() {
    Hora* h= (Hora*)malloc(sizeof(Hora));
    while(true){
        printf("Insira o horario da consulta (hh mm): \n");
        scanf("%d %d", &h->hora, &h->minuto);
        if((h->hora >= 8 && h->hora < 12) || (h->hora >= 14 && h->hora < 18)){
            break;
        }
        printf("Horario inválido\n");
    }
    return h;
}

Medico* med_cria(){
    return NULL;
}

Medico* med_insere(Medico* m, int crm, char nome[80], char area[100], char telefone[20]){
    Medico* novo = (Medico*)malloc(sizeof(Medico));
    novo->crm=crm;
    strcpy(novo->nome, nome);
    strcpy(novo->area, area);
    strcpy(novo->telefone, telefone);
    novo->prox=m;
    return novo;
}

Medico* med_busca(Medico* m, int crm){
    Medico* l = (Medico*)malloc(sizeof(Medico));
    for(l=m;l!=NULL;l=l->prox){
        if(l->crm == crm){
            return l;
        }
    }
    return NULL;
}

void med_imprime(Medico* m){
    Medico* l;
    for(l=m;l!=NULL;l=l->prox){
        printf("CRM: %d\n", l->crm);
        printf("Nome: %s\n", l->nome);
        printf("Area de atuação: %s\n", l->area);
        printf("Telefone: %s\n\n", l->telefone);
    }
}

int med_vazio(Medico* m){
    return (m == NULL);
}

Medico* ler_medico(Medico* m){
    int crm;
    char nome[80], telefone[20], area[100];

    printf("Insira o CRM do medico:\n");
    scanf("%d", &crm);
    printf("Insira o nome do medico:\n");
    getchar();
    fgets(nome, 80, stdin);
    printf("Insira a area de atuacao do medico:\n");
    getchar();
    fgets(area, 100, stdin);
    printf("Insira o telefone do medico:\n");
    getchar();
    fgets(telefone, 20, stdin);
    return med_insere(m, crm, nome, area, telefone);
}

Paciente* pac_cria(){
    return NULL;
}

Paciente* pac_insere(Paciente* p, int cpf, char nome[80], char telefone[20]){
    Paciente* novo = (Paciente*)malloc(sizeof(Paciente));
    novo->cpf=cpf;
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    novo->prox=p;
    return novo;
}

Paciente* pac_busca(Paciente* p, int cpf){
    Paciente* l = (Paciente*)malloc(sizeof(Paciente));
    for(l=p;l!=NULL;l=l->prox){
        if(l->cpf==cpf){
            return l;
        }
    }
    return NULL;
}

void pac_imprime(Paciente* p){
    Paciente* l;
    for(l=p;l!=NULL;l=l->prox){
        printf("CPF: %d\n", l->cpf);
        printf("Nome: %s\n", l->nome);
        printf("Telefone: %s\n\n", l->telefone);
    }
}

int pac_vazio(Paciente* p){
    return(p == NULL);
}

Paciente* ler_paciente(Paciente* p){
    int cpf;
    char nome[80], telefone[20];

    printf("Insira o CPF do paciente:\n");
    scanf("%d", &cpf);
    printf("Insira o nome do paciente:\n");
    getchar();
    fgets(nome, 80, stdin);
    printf("Insira o telefone do paciente:\n");
    getchar();
    fgets(telefone, 20, stdin);
    return pac_insere(p, cpf, nome, telefone);
}

Consulta* consulta_cria(){
    return NULL;
}

Consulta* consulta_insere(Consulta* c, Medico* m, Paciente* p, Data* d, Hora* h, char convenio[80], int flag){
    Consulta* novo = (Consulta*)malloc(sizeof(Consulta));
    novo->m = m;
    novo->p = p;
    novo->d = d;
    novo->h = h;
    strcpy(novo->convenio, convenio);
    novo->flag = flag;
    novo->prox = c;
    return novo;
}

void consulta_imprime(Consulta* c){
    Consulta* l;
    for(l=c;l!=NULL;l=l->prox){
        printf("Paciente: %s\n", l->p->nome);
        printf("Medico: %s\n", l->m->nome);
        printf("Data: %d/%d/%d\n", l->d->dia, l->d->mes, l->d->ano);
        printf("Horario: %d:%d\n", l->h->hora, l->h->minuto);
        printf("Convenio: %s\n", l->convenio);
        if(l->flag == 0){
            printf("Status: agendada\n\n");
        }
        if(l->flag == 1){
            printf("Status: cancelada\n\n");
        }
        if(l->flag == 2){
            printf("Status: realizada\n\n");
        }
    }
}

int consulta_vazio(Consulta* c){
    return(c==NULL);
}


Consulta* ler_consulta(Consulta* c, Medico* m, Paciente* p){
    char convenio[80];
    int crm, cpf, cancelar;
    system("clear");
    printf("Insira o convenio da consulta: \n");
    getchar();
    fgets(convenio, 80, stdin);
    while(true){
        printf("Insira o CRM do médico: ");
        scanf("%d", &crm);
        if(med_busca(m, crm)!=NULL){
            break;
        }

        printf("CRM não encontrado, insira novamente\n");
    }
    while(true){
        printf("Insira o CPF do paciente: ");
        scanf("%d", &cpf);
        if(pac_busca(p, cpf)!=NULL){
            break;
        }
        printf("CPF não encontrado, insira novamente\n");
    }

    while(true){
        Data* d= ler_data();
        Hora* h= ler_hora();
        if(consulta_busca(c,med_busca(m, crm),pac_busca(p, cpf), d, h)){
            c=consulta_insere(c, med_busca(m, crm), pac_busca(p, cpf), d, h, convenio, 0);
            system("clear");
            printf("Agendado!\n");
            return c;
        }
        else{
            system("clear");
            printf("Data indisponivel\nDeseja cancelar o agendamento? (0 - sim / 1 - não)\n");
            scanf("%d", &cancelar);
            if(cancelar==0){
                return c;
            }
        }

    }
}

bool consulta_busca(Consulta* c, Medico* m, Paciente* p, Data* d, Hora* h){
    Consulta* l =(Consulta*)malloc(sizeof(Consulta));
    for(l=c;l!=NULL;l=l->prox){
        if((l->d->dia == d->dia && l->d->mes == d->mes && l->d->ano == d->ano) && (c->p->cpf == p->cpf || c->m->crm == m->crm)){
            if((l->h->hora == h->hora && l->h->minuto == h->minuto) && (c->p->cpf == p->cpf || c->m->crm == m->crm)){
                return false;
            }
        }
    }
    return true;
}

Consulta* consulta_remove(Consulta* c){
    int cpf;
    printf("Digite o CPF do paciente:\n");
    scanf("%d", &cpf);

    Data* d = ler_data();
    Hora* h = ler_hora();

    Consulta* ant = NULL;
    Consulta* l = c;

    while (l != NULL){
        ant = l;
        l = l->prox;
        if(l->p->cpf == cpf && l->d->dia == d->dia && l->d->mes == d->mes && l->d->ano == d->ano && l->h->hora == h->hora && l->h->minuto == h->minuto){
            break;
        }
    }

    if (l == NULL){
        printf("Consulta não encontrada\n");
        return c;
    }

    if(l->flag == 1){
        printf("Consulta ja realizada, nao e possivel desmarcar\n");
    }

    if (ant == NULL){
        c = l->prox;
    }
    else {
        ant->prox = l->prox;
    }

    free(l);
    printf("Consulta desmarcada!\n");
    return c;
}



Consulta* consultar(Consulta* c) {
    Consulta* l= (Consulta*)malloc(sizeof(Consulta));
    int cpf;
    printf("Digite o CPF do paciente:\n");
    scanf("%d", &cpf);
    Data* d= ler_data();
    Hora* h= ler_hora();
    for(l=c; l!=NULL;l=l->prox) {
        if(l->p->cpf == cpf && l->d->dia == d->dia && l->d->mes == d->mes && l->d->ano == d->ano && l->h->hora == h->hora && l->h->minuto == h->minuto) {
            l->flag= 1;
            printf("Digite a descricao da consulta:\n");
            getchar();
            fgets(l->descricao, 300, stdin);
            printf("Consulta realizada!\n");
            return c;
        }
    }
    printf("Consulta nao encontrada!\n");
    return c;
}



void lista_consulta_dia(Consulta* c, Data* d) {
    Consulta* l = (Consulta*)malloc(sizeof(Consulta));
    for(l=c;l!=NULL;l=l->prox){
        if(l->d->dia == d->dia && l->d->mes == d->mes && l->d->ano == d->ano){
            if(l->flag == 0){
                printf("Paciente: %s\n", l->p->nome);
                printf("Medico: %s\n", l->m->nome);
                printf("Data: %d/%d/%d\n", l->d->dia, l->d->mes, l->d->ano);
                printf("Horario: %d:%d\n", l->h->hora, l->h->minuto);
                printf("Convenio: %s\n\n", l->convenio);
            }
        }
    }

}

void lista_consulta_paciente(Consulta* c, int cpf) {
    Consulta* l = (Consulta*)malloc(sizeof(Consulta));
    for(l=c;l!=NULL;l=l->prox){
        if(l->p->cpf == cpf && l->flag == 1){
            printf("Paciente: %s\n", l->p->nome);
            printf("Medico: %s\n", l->m->nome);
            printf("Data: %d/%d/%d\n", l->d->dia, l->d->mes, l->d->ano);
            printf("Horario: %d:%d\n", l->h->hora, l->h->minuto);
            printf("Convenio: %s\n\n", l->convenio);
        }
    }
}

void lista_consulta_descricao(Consulta* c, Data* d, Hora* h, int cpf) {
    Consulta* l= (Consulta*)malloc(sizeof(Consulta));

    for(l=c; l!=NULL;l=l->prox) {
        if(l->p->cpf == cpf && l->d->dia == d->dia && l->d->mes == d->mes && l->d->ano == d->ano && l->h->hora == h->hora && l->h->minuto == h->minuto) {
            printf("Descricao da consulta: \n%s\n", l->descricao);
        }
    }
    if(l == NULL){
        printf("Consulta nao encontrada!\n");
    }
}

void lista_consulta_medico_area(Consulta* c, char area[100], Data* d) {
    Consulta* l= (Consulta*)malloc(sizeof(Consulta));
    Consulta* j= (Consulta*)malloc(sizeof(Consulta));
    int cont;


    for (l = c; l != NULL; l = l->prox) {
        cont = 0;
        if (l->d->mes == d->mes && strcmp(l->m->area, area) == 0 && l->flag==1) {
            for (j=c;j!=NULL;j = j->prox) {
                if(j==l){
                    break;
                }
                if (j->p->cpf == l->p->cpf) {
                    cont++;
                    break;
                }
            }
            if (cont == 0) {
                printf("Paciente: %s\n", l->p->nome);
            }
        }
    }
}


void lista_consulta_pacientes_medico(Medico* m, Consulta* c) {
    Medico* l = (Medico*)malloc(sizeof(Medico));
    Consulta* j = (Consulta*)malloc(sizeof(Consulta));
    for(l=m;l!=NULL;l=l->prox){
        printf("Medico: %s\n", l->nome);
        bool paciente_impresso = false;
        for(j=c;j!=NULL;j=j->prox){
            if(j->m->crm == l->crm){
                if(j->flag==1){
                    if (!paciente_impresso) {
                        printf("Paciente: %s\n", j->p->nome);
                        paciente_impresso = true;
                    }
                }
            }
        }
        printf("\n\n");
    }
}


void relatorio(Consulta* c, Medico* m, Paciente* p) {
    Data* d;
    Hora* h;
    system("clear");
    int escolha, cpf;
    char area[100];
    printf("Escolha o tipo de relatorio:\n1- Lista de consultas no dia\n2- Lista de consultas realizadas por um paciente\n3- Descricao de consulta\n4- Pacientes que consultaram por especialidade no mes\n5- Pacientes de determinado medico\n ");
    scanf("%d", &escolha);
    system("clear");
    switch(escolha) {
    case 1: d = ler_data();
            system("clear");
            lista_consulta_dia(c, d);
        break;
    case 2: printf("Digite o CPF do paciente:\n");
            scanf("%d", &cpf);
            system("clear");
            lista_consulta_paciente(c, cpf);
        break;
    case 3: printf("Digite o CPF do paciente:\n");
            scanf("%d", &cpf);
            d= ler_data();
            h= ler_hora();

            system("clear");
            lista_consulta_descricao(c, d, h, cpf);
        break;
    case 4:
            printf("Digite a area desejada:\n");
            getchar();
            fgets(area, 100, stdin);

            area[strcspn(area, "\n")] = '\0';

            printf("\n");

            d= ler_mes();
            system("clear");
            lista_consulta_medico_area(c, area, d);
        break;
    case 5:
        lista_consulta_pacientes_medico(m, c);
        break;
    }
}

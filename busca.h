#ifndef BUSCA_H
#define BUSCA_H

#include "produto.h"

/* * Eu criei esse cabeçalho para declarar as assinaturas das minhas funções 
 * de busca, Assim, o main.c sabe que elas existem sem precisar ver 
 * a implementação inteira do busca.c
 */

/* Função para buscar produto pelo nome */
void buscarPorNome(Estoque *e);

/* Função para buscar produto pelo ID */
void buscarPorID(Estoque *e, int id);

#endif
#ifndef EDITAR_H
#define EDITAR_H

#include "produto.h"

/* * Cabeçalho que eu fiz para modularizar a funcionalidade de edição
 * Exporta a função para que o menu no main.c consiga chamá-la
 */

void editarProduto(Estoque *e, int id);

#endif
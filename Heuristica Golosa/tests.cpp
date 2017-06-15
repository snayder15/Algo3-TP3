#include "heuristicaGolosa.h"
#include "mini_test.h"


void test_clique() {
	heuristicaGolosa hg;
	hg.init(12,19);
	hg.cargar_ejes(1,2);
	hg.cargar_ejes(2,4);
	hg.cargar_ejes(1,3);
	hg.cargar_ejes(3,4);
	hg.cargar_ejes(4,5);
	hg.cargar_ejes(4,6);
	hg.cargar_ejes(5,7);
	hg.cargar_ejes(6,7);
	hg.cargar_ejes(4,7);
	hg.cargar_ejes(5,6);
	hg.cargar_ejes(6,8);
	hg.cargar_ejes(7,9);
	hg.cargar_ejes(8,10);
	hg.cargar_ejes(9,11);
	hg.cargar_ejes(10,11);
	hg.cargar_ejes(10,12);
	hg.cargar_ejes(11,12);
	hg.cargar_ejes(2,8);
	hg.cargar_ejes(1,8);
	ASSERT_EQ(hg.mayor_grado(),3);
	ASSERT_EQ(hg.son_adyacentes(0,7),true);
	ASSERT_EQ(hg.son_adyacentes(0,11),false);
	hg.clique_maxima();
	hg.mostrar_solucion();
}

void test_clique2() {
	heuristicaGolosa hg1;
	hg1.init(15,20);
	hg1.cargar_ejes(1,2);
	hg1.cargar_ejes(1,3);
	hg1.cargar_ejes(2,4);
	hg1.cargar_ejes(3,4);
	hg1.cargar_ejes(4,5);
	hg1.cargar_ejes(4,6);
	hg1.cargar_ejes(5,7);
	hg1.cargar_ejes(6,7);
	hg1.cargar_ejes(5,6);
	hg1.cargar_ejes(3,6);
	hg1.cargar_ejes(1,11);
	hg1.cargar_ejes(11,12);
	hg1.cargar_ejes(8,10);
	hg1.cargar_ejes(8,9);
	hg1.cargar_ejes(10,12);
	hg1.cargar_ejes(9,12);
	hg1.cargar_ejes(12,13);
	hg1.cargar_ejes(12,14);
	hg1.cargar_ejes(13,15);
	hg1.cargar_ejes(14,15);
	hg1.clique_maxima();
	hg1.mostrar_solucion();
}

int main() {
  RUN_TEST(test_clique);
  RUN_TEST(test_clique2);
  return 0;
}

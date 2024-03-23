#include "coord.h"

/// Funcoes de E/S de coordenadas
std::istream& operator>>(std::istream& I, Coord& C)
{
  I >> C.lin >> C.col;
  return I;
}

std::ostream& operator<<(std::ostream& O, const Coord& C)
{
  O << C.lin << ';' << C.col;
  return O;
}


double Coord::calcular_heuristica(Coord& C) const {

	  double dcol = col - C.col;
	  double dlin = lin - C.lin;

	  double modulo_dlin = fabs(dlin);
	  double modulo_dcol = fabs(dcol);

	  double dmin = std::min(modulo_dlin, modulo_dcol);

	  double ddif = modulo_dlin - modulo_dcol;


	  double hrot;
	  if (dlin == 0 || dcol == 0 || dcol == dlin) {
		  hrot = 0;
	  }else {
		  hrot= ((3.14159265359) / 4) / 2;
	  }
	  return sqrt(2.0) * dmin + fabs(ddif) + hrot;

  }

#include "Sommet.h"

CSommet::CSommet()
{

}
CSommet::CSommet(XMFLOAT3 coords)
{
   SetCoords(coords);
}

void CSommet::SetCoords(XMFLOAT3 coords_in)
{
   coords = coords_in;
}
void CSommet::SetNormale(XMFLOAT3 normale_in)
{
   normale = normale_in;
}
XMFLOAT3 CSommet::GetCoords()
{
   return coords;
}
XMFLOAT3 CSommet::GetNormale()
{
   return normale;
}
#include "Terrain.h"

void CTerrain::InitIndex()
{
   pIndices = new unsigned int[GetIndexSize()]; 
   int k = 0;
   for (int y = 0; y < M - 1; ++y)
   {
      for (int x = 0; x < M - 1; ++x)
      {
         // L'important ici est d'utiliser la même formule pour identifier
         // les sommets qu'au moment de leur création
         pIndices[k++] = y*M + x;
         pIndices[k++] = (y + 1) * M + (x + 1);
         pIndices[k++] = y*M + (x + 1);
         pIndices[k++] = y*M + x;
         pIndices[k++] = (y + 1)* M + x;
         pIndices[k++] = (y + 1)* M + (x + 1);
      }
   }
}
unsigned int CTerrain::GetIndexSize()
{
    return nbPolygones * 3; 
}
unsigned int* CTerrain::GetIndex()
{
   return pIndices;
}
XMVECTOR CTerrain::ObtenirPosition(int x, int y)
{
   XMVECTOR resultat = XMLoadFloat3(&sommets[y * M + x].GetCoords());

   return resultat;
}
XMFLOAT3 CTerrain::CalculerNormales(int x, int y)
{
   XMVECTOR n1;
   XMVECTOR n2;
   XMVECTOR n3;
   XMVECTOR n4;

   XMVECTOR v1;
   XMVECTOR v2;
   XMVECTOR v3;
   XMVECTOR v4;

   n1 = n2 = n3 = n4 = XMVectorSet(0, 0, 1, 0); // Le Z est le haut
   // v1 = p1 – p0, etc...

   if (y < M-1) v1 = ObtenirPosition(x, y + 1) - ObtenirPosition(x, y);
   if (x < M - 1)v2 = ObtenirPosition(x + 1, y) - ObtenirPosition(x, y);
   if (y > 0) v3 = ObtenirPosition(x, y - 1) - ObtenirPosition(x, y);
   if (x > 0) v4 = ObtenirPosition(x - 1, y) - ObtenirPosition(x, y);

   // les produits vectoriels
   if (y < M - 1 && x < M - 1) n1 = XMVector3Cross(v1, v2);
   if (y > 0 && x < M - 1) n2 = XMVector3Cross(v2, v3);
   if (y > 0 && x > 0) n3 = XMVector3Cross(v3, v4);
   if (y < M - 1 && x > 0) n4 = XMVector3Cross(v4, v1);

   n1 = n1 + n2 + n3 + n4;
   n1 = XMVector3Normalize(n1);

   XMFLOAT3 resultat;
   XMStoreFloat3(&resultat, n1);

   return resultat;
}
void CTerrain::ConstruireTerrain(float scaleXY, float scaleZ, unsigned char* table)
{
   XMFLOAT3 sommet;
   XMFLOAT3 normale;
   CSommet csommet;

   //calcul des sommets
   for (int y = 0; y < M; ++y)
   {
      for (int x = 0; x < M; ++x)
      {
         sommet = XMFLOAT3((x * scaleXY), (y * scaleXY), (table[y * M + x] * scaleZ));
         csommet.SetCoords(sommet);

         sommets.push_back(csommet);
      }
   }
   //calcul des normales
   for (int x = 0; x < M; ++x)
   {
      for (int y = 0; y < M; ++y)
      {
         normale = CalculerNormales(x, y);
         sommets[y*M+x].SetNormale(normale);
      }
   }
}
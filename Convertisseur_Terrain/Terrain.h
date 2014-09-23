#pragma once
#include "Sommet.h"
#include <vector>

const int M = 257;
class CTerrain
{
   unsigned int* pIndices;   
 
   int nbSommets;
   int nbPolygones = (M - 1) * (M - 1) * 2;
   XMVECTOR ObtenirPosition(int x, int y);

public:
   std::vector<CSommet> sommets;

   unsigned int GetIndexSize();
   void InitIndex();
   XMFLOAT3 CalculerNormales(int x, int y);
   unsigned int* GetIndex();
   void ConstruireTerrain(float scaleXY, float scaleZ, unsigned char* table);
};

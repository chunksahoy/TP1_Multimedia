#include <DirectXMath.h>
#include <fstream>
#include <iostream>
#include "Terrain.h"

using namespace DirectX;
using namespace std;

void LireFichierHeightmap(unsigned char* table);
void EnregistrerTout(CTerrain& terrain);
const string NOM_FICHIER = "Terrain_genere";


int main()
{
   unsigned char table[M][M];
   CTerrain terrain;

   LireFichierHeightmap(&table[0][0]);
   terrain.ConstruireTerrain(1, 0.05, &table[0][0]);

   terrain.InitIndex();

   EnregistrerTout(terrain);

   return 0;
}
void LireFichierHeightmap(unsigned char* table)
{
   ifstream fichier;
   fichier.open("Terrain_Test.raw", ios::in | ios_base::binary);
   fichier.read((char*)table, M * M);
   fichier.close();
}

void EnregistrerTout(CTerrain& terrain)
{
   ofstream fichier;
   fichier.open(NOM_FICHIER, ios::out | ios_base::binary);

   fichier.write((char*)terrain.sommets.data(), M * M * sizeof(CSommet));
   fichier.write((char*)terrain.GetIndex(), terrain.GetIndexSize() * sizeof(unsigned int));

   fichier.close();
}

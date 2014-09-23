#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class CSommet
{
   XMFLOAT3 coords;
   XMFLOAT3 normale;

public:
   void SetCoords(XMFLOAT3);
   void SetNormale(XMFLOAT3);
   XMFLOAT3 GetCoords();
   XMFLOAT3 GetNormale();
   CSommet();
   CSommet(XMFLOAT3);
};
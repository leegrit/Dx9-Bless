#pragma once

class Helper
{
public :
	static D3DXMATRIX CalcBillboardY(D3DXMATRIX viewMatrix);
	static D3DXMATRIX GetWorldToBillboard(D3DXVECTOR3 position, D3DXVECTOR3 rotationEuler, D3DXVECTOR3 scale,
		D3DXMATRIX viewMatrix);


};


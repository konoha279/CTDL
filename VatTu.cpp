#include "VatTu.h"
void InsertVatTu(PTRVatTu &p, VatTu vt)
{
	if (p == NULL)
	{
		p = new NodeVatTu;
		p->vatTu = vt;
		p->left = NULL;
		p->right = NULL;
	}
	else
	{
		if (SoSanhVatTu(p->vatTu, vt) == 1)
		{
			InsertVatTu(p->left, vt);
		}
		else if (SoSanhVatTu(p->vatTu, vt) == -1)
		{
			InsertVatTu(p->right, vt);
		}
		else p->vatTu->soLuongTon += vt->soLuongTon;
	}
}

int SoSanhVatTu(VatTu vt1, VatTu vt2)
{
	if (!strcmp(vt1->maVT, vt2->maVT))
	{
		if (!strcmp(vt1->tenVT, vt2->tenVT))
		{
			if (vt1->soLuongTon == vt2->soLuongTon)
				return 0;
			else if (vt1->soLuongTon > vt2->soLuongTon)
				return 1;
			else if (vt1->soLuongTon < vt2->soLuongTon)
				return -1;
		}
		else return strcmp(vt1->tenVT, vt2->tenVT);
	}
	else return strcmp(vt1->maVT, vt2->maVT);
}

void CreateTree(PTRVatTu &root)
{
	
}



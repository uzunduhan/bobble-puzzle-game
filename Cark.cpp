#include "Cark.hpp"
#include <fstream>
#include "Oyun.hpp"
#include "Animasyon.hpp"
#include <iostream>

Cark::Cark(const std::string& fileName, Oyun* oyun)
{

	m_konum = sf::Vector2f(310.0f, 702.5);

	std::ifstream dosya("../Projeler/BobblePuzzleGame/" + fileName + ".txt");

	if (dosya.is_open())
	{
		std::string kaplamaIsmi;
		dosya >> kaplamaIsmi;
		m_kaplama = oyun->kaplamaEkle(kaplamaIsmi, false);

		std::string gecici;
		dosya >> gecici >> m_aktifAnimasyon;
		dosya >> gecici >> m_aktifYon;
		dosya >> gecici;

		while (!dosya.eof())
		{
			AnimasyonPtr anim = std::make_shared<Animasyon>();
			std::string isim;
			std::string yon;
			sf::Vector2i konum;
			sf::Vector2i boyut;
			int cerceveSayisi;
			dosya >> isim >> isim;
			dosya >> yon >> yon;
			dosya >> gecici >> konum.x >> konum.y;
			dosya >> gecici >> boyut.x >> boyut.y;
			dosya >> gecici >> cerceveSayisi;
			dosya >> gecici;

			anim->carkOlustur(m_kaplama, konum, boyut, cerceveSayisi);

			//anim->olustur(m_kaplama, konum, boyut, cerceveSayisi);
			m_animasyonlar[yon][isim] = anim;

		}
	}
}

void Cark::ciz(Pencere& pencere)
{
	m_animasyonlar[m_aktifYon][m_aktifAnimasyon]->m_konum = m_konum;
	m_animasyonlar[m_aktifYon][m_aktifAnimasyon]->ciz(pencere);
}
#include "Top.hpp"
#include "Pencere.hpp"
#include "Oyun.hpp"
#include <iostream>
#include <fstream>

Top::Top(float boyut, sf::Color topRengi, const std::string& fileName, Oyun* oyun)
{
	this->m_boyut = boyut;
	m_sekil.setRadius(boyut);
	m_konum = sf::Vector2f(310.0f, 702.5);

	m_sekil.setFillColor(topRengi);
	m_sekil.setOrigin(sf::Vector2f(m_boyut, m_boyut));

	m_hizX = 8;
	m_hizY = 8;

	std::string tempTopRengi;
	if (topRengi == sf::Color::Green)
	{
		tempTopRengi = "Yesil";
	}
	else if (topRengi == sf::Color::Red)
	{
		tempTopRengi = "Kirmizi";
	}
	else if (topRengi == sf::Color::Blue)
	{
		tempTopRengi = "Mavi";
	}
	else if (topRengi == sf::Color::Yellow)
	{
		tempTopRengi = "Sari";
	}

	std::ifstream dosya("../Projeler/BobblePuzzleGame/" + fileName + ".txt");

	if (dosya.is_open())
	{
		std::string kaplamaIsmi;
		dosya >> kaplamaIsmi;
		m_kaplama = oyun->kaplamaEkle(kaplamaIsmi, false);

		std::string gecici;
		dosya >> gecici >> m_aktifAnimasyon;
		dosya >> gecici;
		m_aktifRenk = tempTopRengi;

		while (!dosya.eof())
		{
			TopAnimasyonlariPtr anim = std::make_shared<TopAnimasyonlari>();
			std::string isim;
			std::string renk;
			sf::Vector2i konum;
			sf::Vector2i boyut;
			int cerceveSayisi;
			dosya >> isim >> isim;
			dosya >> renk >> renk;
			dosya >> gecici >> konum.x >> konum.y;
			dosya >> gecici >> boyut.x >> boyut.y;
			dosya >> gecici >> cerceveSayisi;
			dosya >> gecici;


			anim->olustur(m_kaplama, konum, boyut, cerceveSayisi);

			//anim->olustur(m_kaplama, konum, boyut, cerceveSayisi);
			m_animasyonlar[renk][isim] = anim;

		}
	}
}



TopPtr Top::topUret(float cap, sf::Color renk, const std::string& fileName, Oyun* oyun)
{
	return std::make_shared<Top>(cap, renk, fileName, oyun);
}

void Top::ciz(Pencere& pencere)
{
	m_animasyonlar[m_aktifRenk][m_aktifAnimasyon]->m_konum = m_konum;
	m_animasyonlar[m_aktifRenk][m_aktifAnimasyon]->ciz(pencere);
}

void Top::firlatma(float aci)
{
	aci = 270 - aci;
	m_dereceCos = cos(aci * PI / 180);
	m_dereceSin = sin(aci * PI / 180);

	m_konum.x += m_hizX * m_dereceCos;
	m_konum.y -= m_hizY * m_dereceSin;
}


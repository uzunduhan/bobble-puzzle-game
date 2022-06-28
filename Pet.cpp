#include "Pet.hpp"
#include <fstream>
#include "Oyun.hpp"
#include "AnimasyonPet.hpp"
#include <iostream>

Pet::Pet(const std::string& fileName, Oyun* oyun)
{

	m_konum = sf::Vector2f(400.f, 739.0f);

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
			AnimasyonPetPtr anim = std::make_shared<AnimasyonPet>();
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

			if (yon == "Sol")
			{
				anim->petiTerstenOlustur(m_kaplama, konum, boyut, cerceveSayisi);
			}
			else
			{
				anim->petOlustur(m_kaplama, konum, boyut, cerceveSayisi);
			}

			m_animasyonlar[yon][isim] = anim;

		}
	}
}

void Pet::guncelle(float gecenSure)
{
	m_animasyonlar[m_aktifYon][m_aktifAnimasyon]->petGuncelle();
}

void Pet::tusBasildi(sf::Keyboard::Key tus)
{
	if (tus == sf::Keyboard::Left)
	{
		animasyonDegistir("Dondurme");
		yonDegistir("Sol");
	}
	if (tus == sf::Keyboard::Right)
	{
		animasyonDegistir("Dondurme");
		yonDegistir("Sag");
	}
}

void Pet::tusBirakma(sf::Keyboard::Key tus)
{
	if (tus == sf::Keyboard::Left)
	{
		if (m_aktifYon == "Sol" && m_aktifAnimasyon == "Dondurme")
		{
			m_aktifAnimasyon = "Sabit";
		}
	}
	if (tus == sf::Keyboard::Right)
	{
		if (m_aktifYon == "Sag" && m_aktifAnimasyon == "Dondurme")
		{
			m_aktifAnimasyon = "Sabit";
		}
	}
}

void Pet::animasyonDegistir(const std::string& yeniAnimasyon)
{
	m_aktifAnimasyon = yeniAnimasyon;
}

void Pet::yonDegistir(const std::string& yeniYon)
{
	m_aktifYon = yeniYon;
}

void Pet::ciz(Pencere& pencere)
{
	m_animasyonlar[m_aktifYon][m_aktifAnimasyon]->m_konum = m_konum;
	m_animasyonlar[m_aktifYon][m_aktifAnimasyon]->ciz(pencere);
}
#include "AnimasyonPet.hpp"
#include "Pencere.hpp"
#include <iostream>

AnimasyonPet::AnimasyonPet()
{
	m_aktifYon = "Sag";
	m_aktifSprite = 0;
	m_sayac = 0;
	m_degisimSuresi = 5;
	m_konum = sf::Vector2f(0.0f, 0.0f);
}

void AnimasyonPet::petOlustur(TexturePtr kaplama, const sf::Vector2i& konum, const sf::Vector2i& boyut, int cerceveSayisi)
{
	sf::Vector2i sonKonum = konum;
	for (int i = 0; i < cerceveSayisi; i++)
	{
		sf::Sprite sprite;

		sprite.setTexture(*kaplama);
		sprite.setTextureRect(sf::IntRect(sonKonum, boyut));
		sprite.setOrigin(sf::Vector2f(boyut.x / 2, boyut.y / 2));
		sprite.setScale(sf::Vector2f(3.0f, 3.0f));
		m_spriteListesi.push_back(sprite);
		sonKonum.x += boyut.x + 2;
	}
}

void AnimasyonPet::petiTerstenOlustur(TexturePtr kaplama, const sf::Vector2i& konum, const sf::Vector2i& boyut, int cerceveSayisi)
{
	sf::Vector2i sonKonum = konum;
	for (int i = 0; i < cerceveSayisi; i++)
	{
		sf::Sprite sprite;

		sprite.setTexture(*kaplama);
		sprite.setTextureRect(sf::IntRect(sonKonum, boyut));
		sprite.setOrigin(sf::Vector2f(boyut.x / 2, boyut.y / 2));
		sprite.setScale(sf::Vector2f(3.0f, 3.0f));
		m_spriteListesi.push_back(sprite);
		sonKonum.x -= boyut.x + 2;
	}
}

void AnimasyonPet::petGuncelle()
{
	if (m_sayac == m_degisimSuresi)
	{
		m_aktifSprite = (m_aktifSprite + 1) % m_spriteListesi.size();
		m_sayac = 0;
	}
	m_sayac++;
}

void AnimasyonPet::ciz(Pencere& pencere)
{
	m_spriteListesi[m_aktifSprite].setPosition(m_konum);
	pencere.ciz(m_spriteListesi[m_aktifSprite]);
}
